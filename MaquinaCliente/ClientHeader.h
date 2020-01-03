enum class ClientStates{LOGIN, ROULETTE, GAME_SELECTION, GEMS, GAME};

class GameClient{
public:
    ClientStates states;
    Player player;
    std::vector<Enemy> enemigos;
    Client();

private:

    void WhoIsConnected();
    void SaveGems();
    void Exit();

};

