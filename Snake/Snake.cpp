#include "Snake.h"
#include <GLFW/glfw3.h>

Snake::Snake(int startX, int startY) {
    head = new Node(startX, startY);
    tail = head;
    length = 1;
    dx = 1; dy = 0; // Initial direction to the right
}

void Snake::move() {
    // Adding a new head
    NodePtr newHead = new Node(head->x + dx, head->y + dy);
    newHead->next = head;
    head = newHead;
    // Traverse to find the second-to-last node
    NodePtr current = head;
    while (current->next != tail) {
        current = current->next;
    }
    // Update the tail and delete the old tail
    delete tail;
    tail = current;
    tail->next = nullptr;
}

void Snake::grow() {
    // Adding a new tail
    NodePtr newTail = new Node(tail->x, tail->y);
    tail->next = newTail;
    tail = newTail;
}

bool Snake::checkSelfCollision() {
    // Starting with the 2nd node in the list
    NodePtr current = head->next;
    while (current != nullptr) {
        // Collision occurs if the head and current node have the same coordinates
        if (head->x == current->x && head->y == current->y) {
            return true;
        }
        // If no collision is detected, we move to the next element in the list
        current = current->next;
    }
    return false;
}

void Snake::display() {
    // Start with the head of the snake
    NodePtr current = head;
    // Iterate through each segment of the snake
    while (current != nullptr) {
        if (current == head) {
            glColor3f(5.0f, 0.0f, 0.0f); //sets color
            glRecti(current->x, current->y, current->x + 1, current->y + 1);
        } else {
            glColor3f(1.0f, 1.0f, 1.0f); //sets color
            glRecti(current->x, current->y, current->x + 1, current->y + 1);
        }
        current = current->next;
    }
}

void Snake::setDirection(int dx, int dy) {
    // Prevent setting the direction to the opposite of the current direction
    if ((this->dx == 1 && dx == -1) || (this->dx == -1 && dx == 1) ||
        (this->dy == 1 && dy == -1) || (this->dy == -1 && dy == 1)) {
        return;
    }
    this->dx = dx;
    this->dy = dy;
}

int Snake::getLength() {
    return this->length;
}
