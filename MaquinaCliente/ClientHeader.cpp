#include "ClientHeader.h"

ClientHeader::Client(){
    states = LOGIN;
    player = new Player();
    enemies = new Enemy(); ///wrong

}

void::ClientHeader::WhoIsConnected(){

///no se que poner porque es algo que tiene que ver con el server
SendPacket(socket, "USERS");

}

void::ClientHeader::SaveGems(){

    SendPacket(socket, "GETGEMS");


}

void::ClientHeader::Exit(){

///exit()?

}
