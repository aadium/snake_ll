#include <GLFW/glfw3.h>
#include <iostream>
#include <thread>
#include "Snake/Snake.h"

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