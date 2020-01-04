#include "clientHeader2.h"


int main()
{
    size_t received;
    sf::TcpSocket* socket = new sf::TcpSocket();
    sf::Socket::Status status = socket->connect("127.0.0.1", 50000, sf::seconds(15.f)); //establcemos conexion con el server
    bool hasVerified;
    GAMESTATE state = GAMESTATE::LOGIN;
    logState = LOGINSTATE::LOGIN;

    std::string user;
    std::string password;
    if (status != sf::Socket::Done)
    {
        //No se puede vincular al puerto 5000
    }
    else
    {
        int eleccion;
        std::thread listener(&ReceiveMsg, socket);
        listener.detach();
        while(state != GAMESTATE::EXIT)
        {
            ///CLIENTE
            switch(state)
            {
            case GAMESTATE::LOGIN:
                switch (logState)
                {
                case LOGINSTATE::LOGIN:
                {
                    std::cout << "Cliente iniciado\n" << "Porfavor, introduzca su usuario: "<<  std::endl;
                    std::cin >> user;
                    std::cout << "Ahora introduzca su contraseña: " << std::endl;
                    std::cin >> password;
                    std::string verify = "VERIFY_"+user+"_"+password;
                    SendMsg(socket, verify);
                    logState = LOGINSTATE::VERIFYING;
                    std::cout << "Logging in...\n" << std::endl;
                }
                break;
                case LOGINSTATE::VERIFYING:
                    // Verificando la conexion
                    break;
                case LOGINSTATE::SUCCESS:
                    state = GAMESTATE::RUNNING;
                    break;
                default:
                    break;
                }
                break;
            case GAMESTATE::RUNNING:
                // state = GAMESTATE::EXIT;
                break;
            case GAMESTATE::EXIT:
                break;
            default:
                break;
            }
        }



        std::cout << "1. Selección de mapa\n" << "2. Gemas\n" << "3. Salir\n" << std::endl;
        std::cin >> eleccion;
        if(eleccion == 1)
        {
            int mapa;
            std::cout << "1. Mapa 1\n" << "2. Mapa 2\n" << std::endl;
            if(mapa == 1)
            {
                SendMsg(socket, "SELECTMAP_"+mapa);
                //selección mapa 1
                //funcion de inicio de partida?
            }
            else if(mapa == 2)
            {
                SendMsg(socket, "SELECTMAP_"+mapa);
                //selección mapa 2
                //funcion de inicio de partida?
            }
        }
        else if (eleccion == 2)
        {
            SendMsg(socket, "GETGEMS");
            //mostrar gemas
        }
        else if(eleccion = 3)
        {
            exit(0);
        }
    }


    std::cout << "Cliente Terminado" << std::endl;

    return 0;
}
