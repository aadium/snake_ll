#include "Food.h"
#include <cstdlib>
#include <GLFW/glfw3.h>

Food::Food() {
    generateNewPosition();
}

void Food::generateNewPosition() {
    x = rand() % 30;
    y = rand() % 30;
}

void Food::display() {
    glColor3f(0.0f, 1.0f, 0.0f);
    glRecti(x, y, x + 1, y + 1);
}