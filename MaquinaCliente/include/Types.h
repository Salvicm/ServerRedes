#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

struct Vec2{
    int x;
    int y;
    Vec2(){
        x = 0;
        y = 0;
    }
    Vec2(int _x, int _y){
        x = _x;
        y = _y;
    }
};
enum class GAMESTATE{LOGIN, RUNNING, ROULETTE, EXIT};
enum class LOGINSTATE{LOGIN, VERIFYING, ROULETTE, SUCCESS};


#endif // TYPES_H_INCLUDED
