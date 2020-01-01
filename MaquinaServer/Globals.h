#include <SFML/Network.hpp>
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


void init(){
    driver = get_driver_instance();
    con = driver->connect(HOST, USER, PASSWORD);
    con->setSchema(DATABASE);
    stmt = con->createStatement();
}

