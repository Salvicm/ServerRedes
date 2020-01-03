class Enemy{
public:
    int gemPower;
    Vec2 enemyPos;
    Enemy(int x, int y, int power);
private:
    void PlayerDetection();
    void Fight();
    void EnemyDies();
    void EnemyDrop();


};

