#include "HealthKit.h"
#include <cstdlib>
#include <GLFW/glfw3.h>

HealthKit::HealthKit() {
    generateNewPosition();
}

void HealthKit::generateNewPosition() {
    x = rand() % 30;
    y = rand() % 30;
}

void HealthKit::display() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glRecti(x, y, x + 1, y + 1);

    glColor3f(1.0f, 0.0f, 0.0f);
    glRectf(x + 0.3f, y + 0.45f, x + 0.7f, y + 0.55f);
    glRectf(x + 0.45f, y + 0.3f, x + 0.55f, y + 0.7f);

    glColor3f(0.0f, 1.0f, 0.0f);
}