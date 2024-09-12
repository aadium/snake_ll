#include <iostream>

using namespace std;

// We first define the node (a piece of the snake)
struct Node {
    int x, y;
    Node* next;
    Node(int x, int y) : x(x), y(y), next(nullptr) {}
};
// We define the NodePtr data type to avoid confusion between Node and Node*
typedef Node* NodePtr;

// We define the snake class with functions to initialize, mode, grow, check collision, and display the snake
class Snake {
    private:
        NodePtr head;
        NodePtr tail;
        int length;
    public:
        Snake(int startX, int startY); // Constructor
        void move(int dx, int dy);
        void grow();
        bool checkSelfCollision();
        void display();
};

void clearScreen() {
    cout << "\033[2J\033[1;1H" << endl;
}

// We initialize the snake with starting coordinates, and a length of 1 node
Snake::Snake(int startX, int startY) {
    head = new Node(startX, startY);
    tail = head;
    length = 1;
}

void Snake::move(int dx, int dy) {
    // This part adds a head to the list
    NodePtr newHead = new Node(head->x + dx, head->y + dy);
    newHead->next = head;
    head = newHead;
    // This part removes the tail from the list
    NodePtr tempTail = tail;
    // Tail is updated to the next item in the list (node before the old tail)
    tail = tail->next;
    delete tempTail;
}

// This function simply adds a tail to the list
void Snake::grow() {
    NodePtr newTail = new Node(tail->x, tail->y);
    tail->next = newTail;
    tail = newTail;
}

// This function checks if the snake has collided with itself
bool Snake::checkSelfCollision() {
    // We consider the node after the head
    NodePtr current = head->next;
    while (current != nullptr) {
        // If the 'current' coordinates match the 'head' coordinates, true is returned (head collided with the node)
        if (head->x == current->x && head->y == current->y) {
            return true;
        }
        // 'Current' points to the next node in the list
        current = current->next;
    }
    return false;
}

void Snake::display() {
    clearScreen();
    // Start from the head
    NodePtr current = head;
    while (current != nullptr) {
        // Move the cursor to the position of the current node
        cout << "\033[" << current->y << ";" << current->x << "H" << "O";
        current = current->next;
    }
    cout.flush();
}
