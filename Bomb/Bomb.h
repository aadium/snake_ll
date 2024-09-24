#ifndef BOMB_H
#define BOMB_H

class Bomb {
    private:
        int x, y;
    public:
        Bomb();
        void generateNewPosition();
        void display();
        void explode();
        int getX() const { return x; }
        int getY() const { return y; }
};

#endif