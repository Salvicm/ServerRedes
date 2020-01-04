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
                    singularidadPlayer = 0;
                    sleep(2);
                    std::cout << "Singularidad del Usuario: " << singularidadPlayer << std::endl;
                    break;
                case LOGINSTATE::ROULETTE:
                    state = GAMESTATE::ROULETTE;
                default:
                    break;
                }
                break;
            case GAMESTATE::RUNNING:
                char pressed;
                std::cin >> pressed;
                keyPressed(pressed, socket);

                // state = GAMESTATE::EXIT;
                break;
            case GAMESTATE::ROULETTE:
                int decision;
                std::cout << "1. Tirar ruleta\n" << "2. Ignorar" << std::endl;
                std::cin >> decision;
                if(decision == 1){
                    SendMsg(socket, "ROULETTE");
                    sleep(2);
                    state = GAMESTATE::RUNNING;
                }
                else{
                    state = GAMESTATE::RUNNING;
                }
                break;
            case GAMESTATE::EXIT:
                break;
            default:
                break;
            }
        }




    }


    std::cout << "Cliente Terminado" << std::endl;

    return 0;
}
