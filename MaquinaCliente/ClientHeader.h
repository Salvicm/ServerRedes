#ifndef CLIENT_H
#define CLIENT_H
#include "Enemy.h"


enum class ClientStates{LOGIN, ROULETTE, GAME_SELECTION, GEMS, GAME};

class GameClient{
public:
    ClientStates states;
    Player* player;
    std::vector<Enemy*> enemigos;
    GameClient();
    ~GameClient();
    void WhoIsConnected(sf::TcpSocket* socket);
    void SaveGems(sf::TcpSocket* socket);
    void Exit();

};


#endif
