#include "Globals.h"
void game();
void getNewConnections();
void sendMessage();
void receiveMessage();



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
            std::thread t(&game, temp);
            t.detach();
        }
    }
}

void game(sf::TcpSocket* client){ // Esto se ejecutará en cada thread de nuevo user, controla el juego
        sf::Packet pack;
        sf::Socket::Status receiveStatus;
    while(gameRunning){
        receiveStatus = client->receive(pack);
        if(receiveStatus == sf::Socket::Disconnected){
           // enviar info del jugador desconectado
           // Eliminar al jugador de la lista de sockets
            return;
        }
        if (receiveStatus != sf::Socket::Done)
        {
            std::cout << "Recepción de datos fallida" << std::endl;
        }else{
            std::cout << "Has recibido: " << pack << std::endl;
        }
    }

}
void sendMessage(){

}
void receiveMessage(){

}
