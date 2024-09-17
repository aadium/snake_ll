#include <GLFW/glfw3.h>
#include <iostream>
#include <thread>

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
        int dx, dy; // Direction of movement
    public:
        Snake(int startX, int startY);
        void move();
        void grow();
        bool checkSelfCollision();
        void display();
        void setDirection(int dx, int dy);
};

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
    // // Traverse to find the second-to-last node
    // NodePtr current = head;
    // while (current->next != tail) {
    //     current = current->next;
    // }
    // // Update the tail and delete the old tail
    // delete tail;
    // tail = current;
    // tail->next = nullptr;
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
    // Set the x-motion
    this->dx = dx;
    // Set the y-motion
    this->dy = dy;
}

Snake snake(1, 5);

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_UP:
                snake.setDirection(0, 1);
                break;
            case GLFW_KEY_DOWN:
                snake.setDirection(0, -1);
                break;
            case GLFW_KEY_LEFT:
                snake.setDirection(-1, 0);
                break;
            case GLFW_KEY_RIGHT:
                snake.setDirection(1, 0);
                break;
        }
    }
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Snake Game", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyCallback);

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 30, 0, 30, -1, 1);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        snake.move();
        if (snake.checkSelfCollision()) {
            break; // Game over
        }
        snake.display();
        glfwPollEvents();
        glfwSwapBuffers(window);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    glfwDestroyWindow(window);
    glfwPollEvents();
    glfwTerminate();
    return 0;
}