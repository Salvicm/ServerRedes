#ifndef ENEMY2_H
#define ENEMY2_H
#include "Player2.h"


class Enemy2
{
    public:
        int gem;
        int health;
        int attack;
        int defense;
        int gemPower;
        Vec2 enemyPos;
        Enemy2(int x, int y, int power);
        Enemy2();
        ~Enemy2();


    private:
        void PlayerDetection();
        void Fight();
        void EnemyDies();
        void EnemyDrop();
};



#endif // ENEMY2_H
