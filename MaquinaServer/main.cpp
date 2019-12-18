#include <iostream>
#include <iostream>
#include <SFML/Network.hpp>
#include <unistd.h>
#include <wait.h>
#include <vector>
#include <thread>

void getNewConnections();
bool gameRunning = true;
std::vector<sf::TcpSocket*> sockets;
sf::TcpListener dispatcher;

int main()
{
    sf::Socket::Status status = dispatcher.listen(50000);
    std::thread t(&getNewConnections);
    t.detach();

    while(gameRunning)
    {
        std::cout << "Hey, inserta E para cerrar: \n";
        char exitChar;
        std::cin >> exitChar;
        if(exitChar == 'E' || exitChar == 'e')
        {
            gameRunning = false;
        }
    }
    std::vector<sf::TcpSocket*>::iterator it;
    for (it = sockets.begin(); it != sockets.end(); ++it){
        (*it)->disconnect();
    }
    dispatcher.close();
    return 0;
}


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

