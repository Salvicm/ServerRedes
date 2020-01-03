#include "Globals.h"

void analyzeMessage(sf::TcpSocket* client, std::string message);
void gameFunct(sf::TcpSocket* client);
void getNewConnections();
void sendMessage(sf::TcpSocket* client, std::string message);
void sendMessage(sf::TcpSocket* client, int message);
void receiveMessages(sf::TcpSocket* client);
std::string getUserName(sf::TcpSocket* client);
std::string getUserName(int client);

int getNextInt(int *index, std::string message);
std::string getNextString(int *index, std::string message);


void verifyUser(sf::TcpSocket* client, std::string userName, std::string password);
void spinRoulette(sf::TcpSocket* client);
void getGems(sf::TcpSocket* client);
void selectMap(sf::TcpSocket* client);
void moveCharacter(sf::TcpSocket* client);
void battleAction(sf::TcpSocket* client);
void getPlayers(sf::TcpSocket* client);
void updateEnemies(sf::TcpSocket* client);
void collect(sf::TcpSocket* client, int gemID);

void getNewConnections()
{
    while(gameRunning)
    {
        sf::TcpSocket* newClient = new sf::TcpSocket();
        if (dispatcher.accept(*newClient) != sf::Socket::Done)
        {
        }
        else
        {
            std::cout << "Conexión establecida con : " << newClient << std::endl;
            sockets[newClient] = -1;
            std::thread gameThread(&gameFunct, newClient);
            gameThread.detach();
            sendMessage(newClient, "Enter Help to get all available commands");

        }
    }
}

void gameFunct(sf::TcpSocket* client)  // Esto se ejecutará en cada thread de nuevo user, controla el juego
{
    std::thread listener(&receiveMessages, client);
    listener.detach();


}

void sendMessage(sf::TcpSocket* client, std::string message)
{
    sf::Packet infoToSend;
    infoToSend << message;
    sf::Socket::Status sendStatus = client->send(infoToSend);
    infoToSend.clear();
    if(sendStatus == sf::Socket::Disconnected)
        return;
    if(sendStatus != sf::Socket::Done)
    {
        std::cout << "Envio de datos fallido" << std::endl;
    }
}




void receiveMessages(sf::TcpSocket* client)
{
    sf::Packet pack;
    sf::Socket::Status receiveStatus;
    while(gameRunning)
    {
        receiveStatus = client->receive(pack);
        if(receiveStatus == sf::Socket::Disconnected)
        {
            std::cout << client << " With ID: " << getUserName(sockets[client]) << " has Disconnected\n";
            sockets.erase(client);
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
            if(sockets[client] != -1)
                std::cout << " >> ID: " << getUserName(sockets[client]) << " >> " << tmp << std::endl;
            analyzeMessage(client, tmp);
        }
    }
}
std::string getUserName(sf::TcpSocket* client)
{
    try
    {

        std::string tmpQuery = "SELECT nombreUser FROM Cuentas WHERE ID_User = '" + std::to_string(sockets[client]) + "'";
        res = stmt->executeQuery(tmpQuery.c_str());
        while(res->next())
        {
            return res->getString("nombreUser");
        }
    }
    catch(sql::SQLException &e)
    {
        switch(e.getErrorCode())
        {
        case 1064:// Fallo de mensaje en la query
            sendMessage(client, "MessageError please do NOT send strange characters.\n");
            break;
        default:
            std::cout << e.getErrorCode() << std::endl;
            break;
        }
    }
}
std::string getUserName(int client)
{
    try
    {
        std::string tmpQuery = "SELECT nombreUser FROM Cuentas WHERE ID_User = '" + std::to_string(client) + "'";
        res = stmt->executeQuery(tmpQuery.c_str());
        while(res->next())
        {
            return res->getString("nombreUser");
        }
    }
    catch(sql::SQLException &e)
    {
        switch(e.getErrorCode())
        {
        case 1064:// Fallo de mensaje en la query

            break;
        default:
            std::cout << e.getErrorCode() << std::endl;
            break;
        }
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
            else
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

void analyzeMessage(sf::TcpSocket* client, std::string message)
{
    int index = 0;
    std::string tmpString = getNextString(&index, message);
    for(int i = 0; i < tmpString.length();i++){
        tmpString[i] = std::toupper(tmpString[i]);
    }

    if(tmpString == "HELP" || tmpString ==  "help")
    {
        std::string helpMsg = ">> Help:\nType VERIFY to verify an account.\nType ROULETTE to spin the roulette.\nType GETGEMS to get all disponible gems.\nType SELECTMAP to get select a map.\nType MOVE to... well, move.\nType BATTLE to send a Battle Action.\nType USERS to get all disponible players.\nType UPDATEENEMIES to move the enemies.\n";
        sendMessage(client, helpMsg);
    }


    else if(tmpString == "VERIFY")
    {   std::string a = getNextString(&index, message);
        std::string b = getNextString(&index, message);
        verifyUser(client, a, b);
    }
    else if(tmpString ==  "ROULETTE")
        spinRoulette(client);
    else if(tmpString ==  "GETGEMS")
        getGems(client);
    else if(tmpString ==  "SELECTMAP")
        selectMap(client);
    else if(tmpString ==  "MOVE")
        moveCharacter(client);
    else if(tmpString ==  "BATTLE")
        battleAction(client);
    else if(tmpString ==  "COLLECT")
        collect(client, getNextInt(&index, message));
    else if(tmpString ==  "USERS")
        getPlayers(client);
    else if(tmpString ==  "UPDATEENEMIES")
        updateEnemies(client);
    else
        sendMessage(client, "\nUNKNOWN COMMAND, PLEASE ENTER ANOTHER ONE OR TYPE HELP\n");
}

