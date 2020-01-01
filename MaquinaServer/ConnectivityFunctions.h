#include "Globals.h"

void analyzeMessage(sf::TcpSocket* client, std::string message);
void gameFunct(sf::TcpSocket* client);
void getNewConnections();
void sendMessage(sf::TcpSocket* client, std::string message);
void sendMessage(sf::TcpSocket* client, int message);
void receiveMessages(sf::TcpSocket* client);

void verifyUser(sf::TcpSocket* client, std::string userName, std::string password);
void spinRoulette(sf::TcpSocket* client);
void getGems(sf::TcpSocket* client);
void selectMap(sf::TcpSocket* client);
void moveCharacter(sf::TcpSocket* client);
void battleAction(sf::TcpSocket* client);
void getPlayers(sf::TcpSocket* client);
void updateEnemies(sf::TcpSocket* client);

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
    std::cout << "Message sent succesfully to: " << client <<" With ID: " << std::to_string(sockets[client]) << std::endl;
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
            analyzeMessage(client, tmp);

        }
    }
}

void analyzeMessage(sf::TcpSocket* client, std::string message)
{
    std::string tmpString = "";
    char tmpChar;
    int index = 0; // Guarda el indice fuera del scope para usarlo mas adelante leyendo mas del mensaje
    do
    {
        tmpChar = message[index];
        if(tmpChar != ' ' && tmpChar != '_')
            tmpString += toupper(tmpChar);
        index++;
    }
    while((tmpChar != ' ' && tmpChar != '_') && index < message.length());

    std::cout << tmpString << std::endl;

    if(tmpString == "HELP" || tmpString ==  "help"){
        std::string helpMsg = ">> Help:\nType VERIFY to verify an account.\nType ROULETTE to spin the roulette.\nType GETGEMS to get all disponible gems.\nType SELECTMAP to get select a map.\nType MOVE to... well, move.\nType BATTLE to send a Battle Action.\nType USERS to get all disponible players.\nType UPDATEENEMIES to move the enemies.\n";
        sendMessage(client, helpMsg);
    }


    else if(tmpString == "VERIFY"){
        std::string user = "";
        std::string password = "";
        do
        {
            tmpChar = message[index];
            if(tmpChar != ' ' && tmpChar != '_')
                user += tmpChar;
            index++;
        }
        while((tmpChar != ' ' && tmpChar != '_') && index < message.length());

        do
        {
            tmpChar = message[index];
            if(tmpChar != ' ' && tmpChar != '_')
                password += tmpChar;
            index++;
        }
        while((tmpChar != ' ' && tmpChar != '_') && index < message.length());
        verifyUser(client, user, password);
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
    else if(tmpString ==  "USERS")
        getPlayers(client);
    else if(tmpString ==  "UPDATEENEMIES")
        updateEnemies(client);
    else
        sendMessage(client, "\nUNKNOWN COMMAND, PLEASE ENTER ANOTHER ONE OR TYPE HELP\n");
}

