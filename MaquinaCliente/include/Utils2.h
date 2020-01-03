#ifndef UTILS2_H_INCLUDED
#define UTILS2_H_INCLUDED
#include <vector>
#include <iostream>
#include <thread>
#include <SFML/Network.hpp>

struct Vec2{
    int x;
    int y;
    Vec2(){
        x = 0;
        y = 0;
    }
    Vec2(int _x, int _y){
        x = _x;
        y = _y;
    }
};

void ReceiveMsg(sf::TcpSocket* client);
bool SendMsg(sf::TcpSocket* _socket, std::string msg);

#endif // UTILS2_H_INCLUDED
