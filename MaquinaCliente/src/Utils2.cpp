#include "Utils2.h"

int singularidadPlayer = 0;
LOGINSTATE logState;

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
            std::cout << " >>  " << tmp << std::endl;
            if(logState == LOGINSTATE::VERIFYING){
                if(tmp == "CONNECTED")
                    logState = LOGINSTATE::SUCCESS;
                else if(tmp == "ALREADYCON"){
                    std::cout << "Already connected\n";
                    logState = LOGINSTATE::LOGIN;
                }
                else if(tmp == "ROULETTE"){
                    logState = LOGINSTATE::ROULETTE;
                }
                else if( tmp == "INEXISTENT"){
                    std::cout << "Username doesn't exist\n";
                    logState = LOGINSTATE::LOGIN;
                }
            }
            else{
            analyzeMessage(tmp);
            }
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

void analyzeMessage(std::string message){
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
        std::cout << "Usuarios conectados: " << std::endl;
        std::cout << "ID: " << idUSer << "User: " << nameUser << std::endl;
    }
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
}

void showUsers(sf::TcpSocket* _socket){
    std::cout << "Usuarios conectados:" << std::endl;
    SendMsg(_socket, "USERS");
}

void keyPressed(char key, sf::TcpSocket* _socket){
    switch(key){
        case 'i':
            inventory(_socket);
            break;
        case 'u':
            showUsers(_socket);
            break;
        default:
            break;
    }
}
