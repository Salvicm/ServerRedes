#ifndef CLIENTHEADER2_H
#define CLIENTHEADER2_H
#include "Enemy2.h"
enum class ClientStates{LOGIN, ROULETTE, GAME_SELECTION, GEMS, GAME};

class clientHeader2
{
    public:
        clientHeader2();
        ~clientHeader2();
         ClientStates states;
        Player2* player;
        std::vector<Enemy2*> enemigos;

        void WhoIsConnected(sf::TcpSocket* socket);
        void SaveGems(sf::TcpSocket* socket);
        void Exit();


    private:
};





#endif // CLIENTHEADER2_H
