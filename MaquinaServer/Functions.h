#include "ConnectivityFunctions.h"






void verifyUser(sf::TcpSocket* client){
    sendMessage(client, "Verifying account...");
}
void spinRoulette(sf::TcpSocket* client){
    sendMessage(client,"Spinning Roulette...");
}
void getGems(sf::TcpSocket* client){
    sendMessage(client, "Getting available gems...");
}
void selectMap(sf::TcpSocket* client){
    sendMessage(client, "Selecting map...");

}
void moveCharacter(sf::TcpSocket* client){
    sendMessage(client, "Moving Character...");
}
void battleAction(sf::TcpSocket* client){
    sendMessage(client, "Using battle command...");
}
void getPlayers(sf::TcpSocket* client){
    sendMessage(client, "Getting available players...");
}

void updateEnemies(sf::TcpSocket* client){
        sendMessage(client, "Updating enemies...");
}






