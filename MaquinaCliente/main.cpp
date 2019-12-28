#include <iostream>
#include <SFML/Network.hpp>

bool ReceivePacket(sf::TcpSocket& _socket)
{
    sf::Packet infoToReceive;
    sf::Socket::Status receiveStatus = _socket.receive(infoToReceive);//leemos el mensaje que viene del server
    if(receiveStatus == sf::Socket::Disconnected)
        return false;
    if (receiveStatus != sf::Socket::Done)
    {
        infoToReceive.clear();
        std::cout << "Recepción de datos fallida" << std::endl;
    }
    else//pasamos el mensaje a una string y lo  printeamos
    {
        std::string msg;
        infoToReceive >> msg;
        infoToReceive.clear();
        std::cout << " >> " << msg << std::endl;
    }
    return true;
}
bool SendPacket(sf::TcpSocket& _socket)
{
    std::string msg;
    std::cout << "Insert message to send:" << std::endl;;
    std::getline(std::cin, msg);
    sf::Packet infoToSend;
    infoToSend << msg;
    sf::Socket::Status sendStatus = _socket.send(infoToSend);
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
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("127.0.0.1", 50000, sf::seconds(15.f)); //establcemos conexion con el server

    if (status != sf::Socket::Done)
    {
        //No se puede vincular al puerto 5000
    }
    while(SendPacket(socket))
    {
     //   SendPacket(socket);
    }
    std::cout << "Cliente Terminado" << std::endl;

    return 0;
}
