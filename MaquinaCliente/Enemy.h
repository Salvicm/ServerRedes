#ifndef ENEMY_H
#define ENEMY_H
#include "Player.h"
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

#endif // ENEMY_H
