#include "Globals.h"
void gameFunct(sf::TcpSocket* client);
void getNewConnections();
void sendMessage();
void receiveMessage();



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

void gameFunct(sf::TcpSocket* client){ // Esto se ejecutará en cada thread de nuevo user, controla el juego

        sf::Packet pack;
        sf::Socket::Status receiveStatus;
    while(gameRunning){
        receiveStatus = client->receive(pack);
        if(receiveStatus == sf::Socket::Disconnected){
            std::cout << "Is Disconnected\n";
            return;
        }
        if (receiveStatus != sf::Socket::Done)
        {
            std::cout << "Recepción de datos fallida" << std::endl;
        }else if(receiveStatus == sf::Socket::Done){
            std::string tmp;
            pack >> tmp;
            std::cout << "Has recibido: " << tmp << std::endl;
        }
    }

}
void sendMessage(){

}
void receiveMessage(){

}
