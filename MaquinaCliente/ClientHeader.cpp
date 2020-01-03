#include "ClientHeader.h"

GameClient::GameClient(){
    states = ClientStates::LOGIN;
    player = new Player();
   // enemies = new Enemy(); ///wrong
}

GameClient::~GameClient(){
    delete player;
}

void GameClient::WhoIsConnected(sf::TcpSocket* socket){

    ///no se que poner porque es algo que tiene que ver con el server
    //SendPacket(socket, "USERS");

}

void GameClient::SaveGems(sf::TcpSocket* socket){

    //SendPacket(socket, "GETGEMS");


}

void GameClient::Exit(){

///exit()?

}
