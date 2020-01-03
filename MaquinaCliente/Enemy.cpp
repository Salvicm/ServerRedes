#include "Enemy.h"

Enemy::Enemy(int x, int y, int power){
    enemyPos(x,y);
    gemPower = power;

}

void::Enemy::PlayerDetection(){


}

void::Enemy::Fight(){

    while(SendPacket(socket, "BATTLESTATE_ALIVE")){

        SendPacket(socket, "BATTLE_fight");

    }

}

void::Enemy::EnemyDies(){
//no es necesario creo
    EnemyDrop();
}

void::Enemy::EnemyDrop(){
    SendPacket(socket, "GEM_power");


}
