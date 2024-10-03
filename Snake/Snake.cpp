#include "Snake.h"
#include <GLFW/glfw3.h>
#include <chrono>
#include <thread>

Snake::Snake(int startX, int startY) {
    head = new Node(startX, startY);
    tail = head;
    length = 1;
    collisionCount = 0;
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
    length++;
}

void Snake::changeDirectionOnCollision(int& dx, int& dy) {
    // Change the direction of the snake when it collides with itself
    if (dx == 1) {
        dx = 0;
        dy = -1;
    } else if (dx == -1) {
        dx = 0;
        dy = 1;
    } else if (dy == 1) {
        dx = -1;
        dy = 0;
    } else if (dy == -1) {
        dx = 1;
        dy = 0;
    }
}

bool Snake::checkSelfCollision() {
    // Starting with the 2nd node in the list
    NodePtr current = head->next;
    while (current != nullptr) {
        // Collision occurs if the head and current node have the same coordinates
        if (head->x == current->x && head->y == current->y) {
            
            for (int i = 0; i < 3; ++i) {  // Flash
                // Flash red to indicate collision
                glColor3f(1.0f, 0.0f, 0.0f);
                glRecti(head->x, head->y, head->x + 1, head->y + 1);
                glFlush();  // Make sure the drawing is completed
                glfwSwapBuffers(glfwGetCurrentContext());  // Swap the buffers to show the red flash
                std::this_thread::sleep_for(std::chrono::milliseconds(50));

                // Optional: Reset the snake color to normal after each flash
                glColor3f(1.0f, 1.0f, 1.0f);  // Normal snake color (e.g., green)
                glRecti(head->x, head->y, head->x + 1, head->y + 1);
                glFlush();
                glfwSwapBuffers(glfwGetCurrentContext());  // Swap the buffers again to reset the color
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }

            collisionCount++;
            if (collisionCount == 3) {
                return true;  // End game if collision count reaches 3
            }
        }
        // If no collision is detected, we move to the next element in the list
        current = current->next;
    }
    return false;
}

void Snake::checkWallCollision() {
    if (head->x < 0 || head->x >= 30 || head->y < 0 || head->y >= 30) {
        // Change direction by 90 degrees
        if (dx == 1) { // Moving right
            dx = 0;
            dy = 1; // Turn down
        } else if (dx == -1) { // Moving left
            dx = 0;
            dy = -1; // Turn up
        } else if (dy == 1) { // Moving down
            dx = -1;
            dy = 0; // Turn left
        } else if (dy == -1) { // Moving up
            dx = 1;
            dy = 0; // Turn right
        }
    }
}

void Snake::display() {
    // Start with the head of the snake
    NodePtr current = head;
    bool isLightRed = true; // Flag to alternate colors
    // Iterate through each segment of the snake
    while (current != nullptr) {
        if (current == head) {
            glColor3f(5.0f, 0.0f, 0.0f); // Set color for the head
        } else {
            if (isLightRed) {
                glColor3f(1.0f, 0.8f, 0.8f); // Light red color
            } else {
                glColor3f(1.0f, 1.0f, 1.0f); // White color
            }
            isLightRed = !isLightRed; // Toggle the flag
        }

        glRecti(current->x, current->y, current->x + 1, current->y + 1);
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
