#include "Player.h"

Player::Player(){
    playerPos = {0,0};

}

void::Player::Movement(int direccion,  sf::TcpSocket* socket){
    /// TODO enviar tambien la posicion del player --> MOVE_<direction>_<playerX>_<playerY>
    if(direccion = 1){
        //SendPacket(socket, "MOVE_UP_" + std::to_string(playerPos.x) + "_" + std::to_string(playerPos.y));
    }
    else if(direccion = 2){
        //SendPacket(socket, "MOVE_RIGHT_" + std::to_string(playerPos.x) + "_" + std::to_string(playerPos.y));

    }
    else if(direccion = 3){
        //SendPacket(socket, "MOVE_DOWN_" + std::to_string(playerPos.x) + "_" + std::to_string(playerPos.y));
    }
    else if(direccion = 4){
       // SendPacket(socket, "MOVE_LEFT_" + std::to_string(playerPos.x) + "_" + std::to_string(playerPos.y));
    }
}

void::Player::CollectGem( sf::TcpSocket* socket){
///habria que añadir al invetario la gema del enemigo
/// TODO Modificar el mensaje por COLLECT_<GemID>
//    SendPacket(socket, "GEMINFO_power");

}

void::Player::Inventario( sf::TcpSocket* socket){
    ///ver las gemas que tienes

   // SendPacket(socket, "GETGEMS");

}
