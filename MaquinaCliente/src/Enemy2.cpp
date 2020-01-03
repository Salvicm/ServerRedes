#include "Enemy2.h"

Enemy2::Enemy2()
{
    //ctor
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
