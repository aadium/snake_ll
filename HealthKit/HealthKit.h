#ifndef HEALTHKIT_H
#define HEALTHKIT_H

class HealthKit {
    private:
        int x, y;
    public:
        HealthKit();
        void generateNewPosition();
        void display();
        int getX() const { return x; }
        int getY() const { return y; }
};

#endif