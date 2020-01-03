#include <SFML/Network.hpp>
#include <ctime>
#include <thread>
#include <iostream>
#include <resultset.h>
#include <statement.h>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <unistd.h>
#include <wait.h>
#include <vector>
#include <map>

std::string path = "../Assets/Map_1.xml";
enum class directions {UP, DOWN, LEFT, RIGHT, NONE};
const uint32_t maxTimeStamp = 5*60*1000; // 5 minutos en milisegundos
bool gameRunning = true;
std::map<sf::TcpSocket*, int> sockets;
sf::TcpListener dispatcher;
char* HOST = "tcp://127.0.0.1";
char* DATABASE = "AA1_Practica1_Bloque2";
char* USER = "root";
char* PASSWORD = "salvi123";
sql::Driver* driver;
sql::Connection* con;
sql::Statement* stmt;
sql::ResultSet* res;
