#include <GLFW/glfw3.h>
#include <GL/freeglut.h>
#include <iostream>
#include <thread>
#include "Snake/Snake.h"
#include "Food/Food.h"

Snake snake(1, 5);
Food food;

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

void renderText(float x, float y, const std::string& text) {
    glRasterPos2f(x, y);
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

int main(int argc, char** argv) {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glutInit(&argc, argv);

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
            break;
        }

        // Check for collision with food
        if (snake.getHeadX() == food.getX() && snake.getHeadY() == food.getY()) {
            snake.grow();
            food.generateNewPosition();
        }

        snake.display();
        food.display();

        renderText(0.0f, 2.0f, "Press R to Restart");

        glfwPollEvents();
        glfwSwapBuffers(window);
        std::this_thread::sleep_for(std::chrono::milliseconds(75));
    }

    glfwDestroyWindow(window);
    glfwPollEvents();
    glfwTerminate();
    return 0;
}