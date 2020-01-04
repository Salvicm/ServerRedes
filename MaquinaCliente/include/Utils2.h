#ifndef UTILS2_H_INCLUDED
#define UTILS2_H_INCLUDED
#include <unistd.h>
#include <vector>
#include <iostream>
#include <thread>
#include <SFML/Network.hpp>
#include "Types.h"

extern LOGINSTATE logState;
void ReceiveMsg(sf::TcpSocket* client);
bool SendMsg(sf::TcpSocket* _socket, std::string msg);
void WaitTime();

#endif // UTILS2_H_INCLUDED
