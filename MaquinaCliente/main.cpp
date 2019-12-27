#include <iostream>
#include <SFML/Network.hpp>


int main()
{
    ///CLIENTE
    std::cout << "ola" << std::endl;
    size_t received;
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("127.0.0.1", 50000, sf::seconds(15.f)); //establcemos conexion con el server
    sf::TcpListener dispatcher;

    if (status != sf::Socket::Done)
    {
        //No se puede vincular al puerto 5000
    }
    while(true)
    {
        sf::Packet pack;
        sf::Socket::Status receiveStatus = socket.receive(pack);//leemos el mensaje que viene del server
        if(receiveStatus == sf::Socket::Disconnected)
            break;
        if (receiveStatus != sf::Socket::Done)
        {
            std::cout << "Recepción de datos fallida" << std::endl;
        }
        else//pasamos el mensaje a una string y lo  printeamos
        {
            std::string msg;
            pack >> msg;
            std::cout << " >> " << msg << std::endl;
        }
    }

    dispatcher.close();

    return 0;
}
