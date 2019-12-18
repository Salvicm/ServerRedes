#include <iostream>
#include <iostream>
#include <SFML/Network.hpp>
#include <unistd.h>
#include <wait.h>

int main()
{

    sf::TcpListener dispatcher;


    sf::Socket::Status status = dispatcher.listen(50000);

    sf::TcpSocket client;


    if(status != sf::Socket::Done)
    {
    }


    if(dispatcher.accept(client) != sf::Socket::Done)
    {
    }
    else
    {



            sf::Packet pack;
            pack << "Hola \n";
            sf::Socket::Status sendStatus = client.send(pack);
            if(sendStatus == sf::Socket::Disconnected)
            {
            }
            if (sendStatus != sf::Socket::Done)
            {
                std::cout << "Envio de datos fallido" << std::endl;
            }


    }

    client.disconnect();
    dispatcher.close();
    return 0;
}

