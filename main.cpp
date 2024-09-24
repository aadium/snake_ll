#include <GLFW/glfw3.h>
#include <GL/freeglut.h>
#include <iostream>
#include <thread>
#include "Snake/Snake.h"
#include "Food/Food.h"
#include "Bomb/Bomb.h"

Snake snake(1, 5);
Food food;
Bomb bomb;

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

void drawHealthBar(float x, float y, float width, float height, float healthPercentage) {
    // Set the color for the health bar (green)
    glColor3f(0.0f, 0.3f, 0.0f);

    // Draw the background of the health bar (gray)
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.15f, 0.15f);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    // Draw the foreground of the health bar (green) based on health percentage
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.3f, 0.0f);
    glVertex2f(x, y);
    glVertex2f(x + width * healthPercentage, y);
    glVertex2f(x + width * healthPercentage, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

bool displayBomb = false;

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

        renderText(0.0f, 2.0f, "Score: " + std::to_string(snake.getLength() - 1));
        renderText(0.0f, 6.0f, "Health:");
        
        // Calculate health percentage (assuming max health is 3)
        float healthPercentage = (3.0f - snake.getCollisionCount()) / 3.0f;
        drawHealthBar(0.0f, 4.0f, 10.0f, 1.0f, healthPercentage);

        snake.move();
        snake.checkWallCollision();
        if (snake.checkSelfCollision()) {
            break;
        }

        // Check for collision with food
        if (snake.getHeadX() == food.getX() && snake.getHeadY() == food.getY()) {
            snake.grow();
            food.generateNewPosition();
            int randInt = rand() % 2;
            displayBomb = (randInt == 0);
        }

        // Check for collision with bomb
        if (snake.getHeadX() == bomb.getX() && snake.getHeadY() == bomb.getY()) {
            bomb.explode();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            break;
        }

        snake.display();
        food.display();
        if (displayBomb) {
            bomb.display();
        }

        glfwPollEvents();
        glfwSwapBuffers(window);
        std::this_thread::sleep_for(std::chrono::milliseconds(75));
    }

    glfwDestroyWindow(window);
    glfwPollEvents();
    glfwTerminate();
    return 0;
}