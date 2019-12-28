#include <iostream>
#include <thread>
#include <SFML/Network.hpp>

void ReceivePacket(sf::TcpSocket* client)
{
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
            std::cout << " Se ha recibido: " << tmp << std::endl;
        }
    }
}
bool SendPacket(sf::TcpSocket* _socket)
{
    std::string msg;
    std::cout << "Insert message to send:" << std::endl;;
    std::getline(std::cin, msg);
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
int main()
{
    ///CLIENTE
    std::cout << "Cliente iniciado" << std::endl;
    size_t received;
    sf::TcpSocket* socket = new sf::TcpSocket();
    sf::Socket::Status status = socket->connect("127.0.0.1", 50001, sf::seconds(15.f)); //establcemos conexion con el server

    if (status != sf::Socket::Done)
    {
        //No se puede vincular al puerto 5000
    }
    else
    {
        std::thread listener(&ReceivePacket, socket);
        listener.detach();
        while(SendPacket(socket))
        {
            //   SendPacket(socket);
        }
    }
    std::cout << "Cliente Terminado" << std::endl;

    return 0;
}
