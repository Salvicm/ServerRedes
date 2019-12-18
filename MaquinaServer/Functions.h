#include "Globals.h"
void getNewConnections();
void game();
void sendMessage();
void receiveMessage();



void getNewConnections()
{
    while(gameRunning)
    {
        sf::TcpSocket* temp = new sf::TcpSocket();
        if (dispatcher.accept(*temp) != sf::Socket::Done)
        {
            std::cout << "Conexión no aceptada" << std::endl;
        }
        else
        {
            std::cout << "Conexión establecida con : " << temp << std::endl;
            sockets.push_back(temp);
            sf::Packet pack;
            pack << "Hola \n";
            sf::Socket::Status sendStatus = temp->send(pack);
            if(sendStatus == sf::Socket::Disconnected)
            {
            }
            if (sendStatus != sf::Socket::Done)
            {
                std::cout << "Envio de datos fallido" << std::endl;
            }
        }
    }
}
