#include <iostream>
#include <SFML/Network.hpp>
#include <unistd.h>
#include <wait.h>

int main()
{

    sf::TcpListener dispatcher;

    sf::Socket::Status status = dispatcher.listen(50000);

    sf::TcpSocket incoming;


    if(status != sf::Socket::Done)
    {
        std::cout << "A\n";
    }


    if(dispatcher.accept(incoming) != sf::Socket::Done)
    {
        std::cout << "B\n";

    }

    incoming.disconnect();
    dispatcher.close();
    return 0;
}
