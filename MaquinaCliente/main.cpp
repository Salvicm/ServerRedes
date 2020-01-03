#include "ClientHeader.h"


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
        //std::thread listener(&ReceivePacket, socket);
       // listener.detach();

        ///CLIENTE
        std::cout << "Cliente iniciado\n" << "Porfavor, introduzca su usuario: "<<  std::endl;
        std::cin >> user;
        std::cout << "Ahora introduzca su contraseña: " << std::endl;
        std::cin >> password;
        std::string verify = "VERIFY_"+user+"_"+password;
        //SendPacket(socket, verify);



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
                //SendPacket(socket, "SELECTMAP_"+mapa);
                //selección mapa 1
                //funcion de inicio de partida?
            }
            else if(mapa == 2){
                //SendPacket(socket, "SELECTMAP_"+mapa);
                //selección mapa 2
                //funcion de inicio de partida?
            }
        }
        else if (eleccion == 2){
            //SendPacket(socket, "GETGEMS");
            //mostrar gemas
        }
        else if(eleccion = 3){
            exit(0);
        }
    }
    std::cout << "Cliente Terminado" << std::endl;

    return 0;
}
