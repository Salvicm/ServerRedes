#include <SFML/Network.hpp>
#include <thread>
bool gameRunning = true;
std::vector<sf::TcpSocket*> sockets;
sf::TcpListener dispatcher;
