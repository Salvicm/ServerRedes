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


class Player{
public:
    Vec2 playerPos;
    Player();

private:
    void Movement();
    void CollectGem();
    void Inventario();

};
