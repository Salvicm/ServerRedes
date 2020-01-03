#include "clientHeader2.h"

clientHeader2::clientHeader2(){
    states = ClientStates::LOGIN;
    player = new Player2();
    // enemies = new Enemy(); ///wrong
}

clientHeader2::~clientHeader2(){
    delete player;
}

void clientHeader2::WhoIsConnected(sf::TcpSocket* socket){

    ///no se que poner porque es algo que tiene que ver con el server
    SendMsg(socket, "USERS");

}

void clientHeader2::SaveGems(sf::TcpSocket* socket){

    SendMsg(socket, "GETGEMS");


}

void clientHeader2::Exit(){

///exit()?

}
