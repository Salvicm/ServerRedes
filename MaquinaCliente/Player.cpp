#include "Player.h"

Player::Player(){
    playerPos(0,0);

}

void::Player::Movement(int direccion){
if(direccion = 1){
    SendPacket(socket, "MOVE_UP");
}
else if(direccion = 2){
    SendPacket(socket, "MOVE_RIGHT");

}
else if(direccion = 3){
    SendPacket(socket, "MOVE_DOWN");
}
else if(direccion = 4){
    SendPacket(socket, "MOVE_LEFT);
}
}

void::Player::CollectGem{
///habria que añadir al invetario la gema del enemigo
    SendPacket(socket, "GEMINFO_power");

}

void::Player::Inventario{
///ver las gemas que tienes

    SendPacket(socket, "GETGEMS");

}
