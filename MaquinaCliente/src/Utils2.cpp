#include "Utils2.h"


LOGINSTATE logState;

void ReceiveMsg(sf::TcpSocket* client){
    sf::Packet pack;
    sf::Socket::Status receiveStatus;
    while(true)
    {
        pack.clear();
        receiveStatus = client->receive(pack);
        if(receiveStatus == sf::Socket::Disconnected)
        {
            std::cout << "Is Disconnected\n";
            return;
        }
        if (receiveStatus != sf::Socket::Done)
        {
            std::cout << "Recepción de datos fallida" << std::endl;
        }
        else if(receiveStatus == sf::Socket::Done)
        {
            std::string tmp;
            pack >> tmp;
            std::cout << " >>  " << tmp << std::endl;
            if(logState == LOGINSTATE::VERIFYING){
                if(tmp == "CONNECTED")
                    logState = LOGINSTATE::SUCCESS;
                else if(tmp == "ALREADYCON"){
                    std::cout << "Already connected\n";
                    logState = LOGINSTATE::LOGIN;
                }
                else if( tmp == "INEXISTENT"){
                    std::cout << "Username doesn't exist\n";
                    logState = LOGINSTATE::LOGIN;
                }
            }
        }
    }
}

bool SendMsg(sf::TcpSocket* _socket, std::string msg)
{
    sf::Packet infoToSend;
    infoToSend << msg;
    sf::Socket::Status sendStatus = _socket->send(infoToSend);
    infoToSend.clear();
    std::cout << "Message sent: " << msg << std::endl;
    if(sendStatus == sf::Socket::Disconnected)
        return false;
    if(sendStatus != sf::Socket::Done)
    {
        std::cout << "Envio de datos fallido" << std::endl;
        return false;
    }
    return true;

}

void WaitTime(){
    sleep(5);
    if(logState == LOGINSTATE::VERIFYING){
        logState = LOGINSTATE::LOGIN;
        std::cout << "Login out of time" << std::endl;
    }
}
