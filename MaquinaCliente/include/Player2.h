#ifndef PLAYER2_H
#define PLAYER2_H
#include "Utils2.h"


class Player2
{
public:
    Vec2 playerPos;

    Player2();
    ~Player2();



private:
    void Movement(int direccion, sf::TcpSocket* socket);
    void CollectGem( sf::TcpSocket* socket);
    void Inventario( sf::TcpSocket* socket);
};
#endif // PLAYER2_H
