#ifndef SNAKE_H
#define SNAKE_H

struct Node {
    int x, y;
    Node* next;
    Node(int x, int y) : x(x), y(y), next(nullptr) {}
};

typedef Node* NodePtr;

class Snake {
    private:
        NodePtr head;
        NodePtr tail;
        int length;
        int collisionCount;
        int dx, dy;
    public:
        Snake(int startX, int startY);
        void move();
        void grow();
        bool checkSelfCollision();
        void checkWallCollision();
        void changeDirectionOnCollision(int& dx, int& dy);
        void display();
        void heal();
        void setDirection(int dx, int dy);
        int getHeadX() const { return head->x; }
        int getHeadY() const { return head->y; }
        int getLength() const { return length; }
        int getCollisionCount() const { return collisionCount; }
};

#endif