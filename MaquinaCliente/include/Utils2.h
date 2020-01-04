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
void analyzeMessage(std::string message);
int getNextInt(int *index, std::string message);
std::string getNextString(int *index, std::string message);
void inventory(sf::TcpSocket* _socket);
void showUsers(sf::TcpSocket* _socket);
void keyPressed(char key, sf::TcpSocket* _socket);

#endif // UTILS2_H_INCLUDED
