#include "Enemy2.h"

Enemy2::Enemy2()
{
    gem = rand()% 3+1;
    health = 30;
    attack = rand() % 15+1;
    defense = rand()% 15+1;
    switch(gem){
        case 1:
            gemPower = 10;
            break;
        case 2:
            gemPower = 15;
            break;
        case 3:
            gemPower = 9;
            break;
        default:
            gemPower = 69;
            break;
    }
}

Enemy2::~Enemy2()
{
    //dtor
}
Enemy2::Enemy2(int x, int y, int power){
    enemyPos = {x,y};
    gemPower = power;

}

void Enemy2::PlayerDetection(){


}

void Enemy2::Fight(){


}

void Enemy2::EnemyDies(){
//no es necesario creo
    EnemyDrop();
}

void Enemy2::EnemyDrop(){


}
