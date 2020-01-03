#ifndef PLAYER_H
#define PLAYER_H
#include "Utils.h"


class Player{
public:
    Vec2 playerPos;
    Player();

private:
    void Movement(int direccion, sf::TcpSocket* socket);
    void CollectGem( sf::TcpSocket* socket);
    void Inventario( sf::TcpSocket* socket);

};
#endif // PLAYER_H
