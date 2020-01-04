#include "Utils2.h"



int singularidadPlayer = 0;
LOGINSTATE logState;
int playerAttack = 0;
int playerDefense = 0;

void ReceiveMsg(sf::TcpSocket* client){
    sf::Packet pack;
    sf::Socket::Status receiveStatus;
    while(true)
    {
        pack.clear();
        receiveStatus = client->receive(pack);
        if(receiveStatus == sf::Socket::Disconnected)
        {
            std::cout << "Is Disconnected\n";
            return;
        }
        if (receiveStatus != sf::Socket::Done)
        {
            std::cout << "Recepción de datos fallida" << std::endl;
        }
        else if(receiveStatus == sf::Socket::Done)
        {
            std::string tmp;
            pack >> tmp;
            if(logState == LOGINSTATE::VERIFYING){
                if(tmp == "CONNECTED")
                    logState = LOGINSTATE::SUCCESS;
                else if(tmp == "ALREADYCON"){
                    std::cout << "Already connected\n";
                    sleep(1);

                    logState = LOGINSTATE::LOGIN;
                }
                else if(tmp == "ROULETTE"){
                    sleep(1);
                    std::cout << "Singularidad total: " << singularidadPlayer << std::endl;
                    logState = LOGINSTATE::ROULETTE;
                }
                else if( tmp == "INEXISTENT"){
                    std::cout << "Username doesn't exist\n";
                    logState = LOGINSTATE::LOGIN;
                }
            }
            analyzeMessage(client, tmp);

        }
    }
}

bool SendMsg(sf::TcpSocket* _socket, std::string msg)
{
    sf::Packet infoToSend;
    infoToSend << msg;
    sf::Socket::Status sendStatus = _socket->send(infoToSend);
    infoToSend.clear();
    std::cout << "Message sent: " << msg << std::endl;
    if(sendStatus == sf::Socket::Disconnected)
        return false;
    if(sendStatus != sf::Socket::Done)
    {
        std::cout << "Envio de datos fallido" << std::endl;
        return false;
    }
    return true;

}

void WaitTime(){
    sleep(5);
    if(logState == LOGINSTATE::VERIFYING){
        logState = LOGINSTATE::LOGIN;
        std::cout << "Login out of time" << std::endl;
    }
}

void analyzeMessage(sf::TcpSocket* _socket, std::string message){
    int index = 0;
    std::string tmpString = getNextString(&index, message);
    for(int i = 0; i < tmpString.length(); i++)
    {
        tmpString[i] = std::toupper(tmpString[i]);
    }
    if(tmpString == "GEM"){
        std::string tipo = getNextString(&index, message);
        int cantidad = getNextInt(&index, message);
        int poder = getNextInt(&index, message);

        singularidadPlayer += poder*cantidad;
        std::cout << tipo << " - Cantidad: " << cantidad << " unidad/es. " << "Singularidad total: " << poder*cantidad << std::endl;

    }
    else if(tmpString == "USER"){

        int idUSer = getNextInt(&index, message);
        std::string nameUser = getNextString(&index, message);
        std::cout << "ID: " << idUSer << " User: " << nameUser << std::endl;
    }
    else if(tmpString == "BATTLE"){
        int atEnemigo = getNextInt(&index, message);
        int defEnemigo = getNextInt(&index, message);
        int hpEnemigo = getNextInt(&index, message);
        int turnos = getNextInt(&index, message);

        std::cout << "Player - AT: " << playerAttack << " DEF: " << playerDefense << std::endl;
        std::cout << "Enemy - AT: " << atEnemigo << " DEF: " << defEnemigo << " HP: " << hpEnemigo << std::endl;
        std::cout << "El enemigo ha muerto despues de " << turnos << " turnos. El jugador ha recibido " << atEnemigo*(turnos-1) << " puntos de daño" << std::endl;
        std::cout << "\n¡El enemigo ha soltado una gema!\n";
        SendMsg(_socket, "GENCOLLECT");
    }
    else if((message == "CONNECTED")|| (message == "ALREADYCON")|| (message == "ROULETTE")|| ( message == "INEXISTENT")){

    }
    else
        std::cout << " >>  " << message << std::endl;



}

int getNextInt(int *index, std::string message){
   std::string number = "";
   char tmpChar;
    do
        {
            tmpChar = message[*index];
            if(tmpChar >= '0' && tmpChar <= '9')
                number += tmpChar;
            else if(tmpChar != ' ' && tmpChar != '_')
            {
                std::cout << "Collect message incorrect" << std::endl;
                return -1;
            }
            (*index)++;
        }
        while((tmpChar != ' ' && tmpChar != '_') && *index < message.length());
        return std::stoi(number);
}

std::string getNextString(int *index, std::string message){
    std::string tmpString = "";
    char tmpChar;
    do
    {
        tmpChar = message[*index];
        if(tmpChar != ' ' && tmpChar != '_')
            tmpString += tmpChar;
        (*index)++;
    }
    while((tmpChar != ' ' && tmpChar != '_') && *index < message.length());
    return tmpString;
}

void inventory(sf::TcpSocket* _socket){
    std::cout << "Mostrando inventario:" << std::endl;
    SendMsg(_socket, "GETGEMS");
    sleep(2);
    std::cout << "Singularidad total: " << singularidadPlayer << std::endl;
}

void showUsers(sf::TcpSocket* _socket){
    std::cout << "Usuarios conectados:" << std::endl;
    SendMsg(_socket, "USERS");
}


void battle(sf::TcpSocket* _socket){
    std::cout << "Empieza el combate: " << std::endl;
    SendMsg(_socket, "BATTLE_"+std::to_string(playerAttack)+"_"+std::to_string(playerDefense));

}

bool keyPressed(char key, sf::TcpSocket* _socket){
    switch(key){
        case 'i':
        case 'I':
            inventory(_socket);
            return true;
            break;
        case 'u':
        case 'U':
            showUsers(_socket);
            return true;
            break;
        case 'f':
        case 'F':
            battle(_socket);
            return true;
            break;
        case 'e':
        case 'E':
            return false;
            break;
        default:
            break;
    }
    return true;
}
