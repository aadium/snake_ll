#ifndef FOOD_H
#define FOOD_H

class Food {
    private:
        int x, y;
    public:
        Food();
        void generateNewPosition();
        void display();
        int getX() const { return x; }
        int getY() const { return y; }
};

#endif