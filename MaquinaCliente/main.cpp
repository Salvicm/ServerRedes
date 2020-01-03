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
bool SendPacket(sf::TcpSocket* _socket, std::string msg)
{
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
    size_t received;
    sf::TcpSocket* socket = new sf::TcpSocket();
    sf::Socket::Status status = socket->connect("127.0.0.1", 50001, sf::seconds(15.f)); //establcemos conexion con el server
    bool hasVerified;

    std::string user;
    std::string password;
    if (status != sf::Socket::Done)
    {
        //No se puede vincular al puerto 5000
    }
    else
    {
        int eleccion;
        std::thread listener(&ReceivePacket, socket);
        listener.detach();

        ///CLIENTE
        std::cout << "Cliente iniciado\n" << "Porfavor, introduzca su usuario: "<<  std::endl;
        std::cin >> user;
        std::cout << "Ahora introduzca su contraseña: " << std::endl;
        std::cin >> password;
        std::string verify = "VERIFY_"+user+"_"+password;
        SendPacket(socket, verify);



        std::cout << "Logging in...\n" << std::endl;
       /// wait(1);


        //si no es correcto ALOMEJOR tendriamos que hacer un while(SendMessage(socket, msg) y hasta que no sea true ir repitiendo el cin de password y user
        ///std::cout << "Error en el inicio de sesión, porfavor, introduzca de nuevo su usuario y contraseña."
        ///std::cin << user;
        ///std::cin << password;
        //si el verify es correcto
        std::cout << "1. Selección de mapa\n" << "2. Gemas\n" << "3. Salir\n" << std::endl;
        std::cin >> eleccion;
        if(eleccion == 1){
            int mapa;
            std::cout << "1. Mapa 1\n" << "2. Mapa 2\n" << std::endl;
            if(mapa == 1){
                SendPacket(socket, "SELECTMAP_"+mapa);
                //selección mapa 1
                //funcion de inicio de partida?
            }
            else if(mapa == 2){
                SendPacket(socket, "SELECTMAP_"+mapa);
                //selección mapa 2
                //funcion de inicio de partida?
            }
        }
        else if (eleccion == 2){
            SendPacket(socket, "GETGEMS");
            //mostrar gemas
        }
        else if(eleccion = 3){
            exit(0);
        }
    }
    std::cout << "Cliente Terminado" << std::endl;

    return 0;
}
