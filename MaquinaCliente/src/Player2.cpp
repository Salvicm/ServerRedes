#include "Player2.h"

Player2::Player2()
{
    attack = rand()% 14+5;
    defense = rand()% 14+5;

}

Player2::~Player2()
{
    //dtor
}


void Player2::Movement(int direccion,  sf::TcpSocket* socket){
    /// TODO enviar tambien la posicion del player --> MOVE_<direction>_<playerX>_<playerY>
    if(direccion = 1){
        SendMsg(socket, "MOVE_UP_" + std::to_string(playerPos.x) + "_" + std::to_string(playerPos.y));
    }
    else if(direccion = 2){
        SendMsg(socket, "MOVE_RIGHT_" + std::to_string(playerPos.x) + "_" + std::to_string(playerPos.y));

    }
    else if(direccion = 3){
        SendMsg(socket, "MOVE_DOWN_" + std::to_string(playerPos.x) + "_" + std::to_string(playerPos.y));
    }
    else if(direccion = 4){
        SendMsg(socket, "MOVE_LEFT_" + std::to_string(playerPos.x) + "_" + std::to_string(playerPos.y));
    }
}

void Player2::CollectGem( sf::TcpSocket* socket){
///habria que añadir al invetario la gema del enemigo
/// TODO Modificar el mensaje por COLLECT_<GemID>
    SendMsg(socket, "GEMINFO_power");

}

void Player2::Inventario( sf::TcpSocket* socket){
    ///ver las gemas que tienes

    SendMsg(socket, "GETGEMS");

}

