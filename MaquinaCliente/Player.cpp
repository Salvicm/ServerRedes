#include "Player.h"

Player::Player(){
    playerPos(0,0);

}

void::Player::Movement(int direccion){
/// TODO enviar tambien la posicion del player --> MOVE_<direction>_<playerX>_<playerY>
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
/// TODO Modificar el mensaje por COLLECT_<GemID>
    SendPacket(socket, "GEMINFO_power");

}

void::Player::Inventario{
    ///ver las gemas que tienes

    SendPacket(socket, "GETGEMS");

}
