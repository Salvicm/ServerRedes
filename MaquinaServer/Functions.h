#include "Globals.h"
void gameFunct(sf::TcpSocket* client);
void getNewConnections();
void sendMessage(sf::TcpSocket* client, std::string message);
void receiveMessages(sf::TcpSocket* client);



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
            sockets.push_back(newClient);
            std::thread gameThread(&gameFunct, newClient);
            gameThread.detach();
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
    infoToSend.clear();
    sf::Socket::Status sendStatus = client->send(infoToSend);
    std::cout << "Message sent: " << message << std::endl;
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
            std::cout << " >> " << tmp << std::endl;
            if(tmp[0] == 'A' || tmp[0] == 'a')
                sendMessage(client, tmp);
        }
    }
}
