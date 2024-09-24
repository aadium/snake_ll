#include "Bomb.h"
#include <cstdlib>
#include <GLFW/glfw3.h>
#include <math.h>
#include <chrono>
#include <thread>

Bomb::Bomb() {
    generateNewPosition();
}

void Bomb::generateNewPosition() {
    x = rand() % 30;
    y = rand() % 30;
}


void Bomb::display() {
    // Draw the base of the landmine (smaller, fitting within 1x1 size)
    glColor3f(0.3f, 0.0f, 0.0f);  // Dark grey for the landmine base
    glRecti(x, y, x + 1, y + 1);  // Base is 1x1 in size

    // Draw the border around the base (to emphasize the landmine shape)
    glColor3f(1.0f, 0.5f, 0.0f);  // White border
    glLineWidth(4.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2i(x, y);
    glVertex2i(x + 1, y);
    glVertex2i(x + 1, y + 1);
    glVertex2i(x, y + 1);
    glEnd();

    // Draw the trigger plate (centered, small portion of the landmine)
    glColor3f(0.8f, 0.8f, 0.8f);  // Light grey for the trigger plate
    glRecti(x + 0.3f, y + 0.3f, x + 0.7f, y + 0.7f);  // Trigger plate smaller and centered
}

void Bomb::explode() {
    for (int i = 0; i < 20; ++i) {  // Animate the explosion over 20 frames
        float size = i * 0.5f;  // Gradually increase the size of the explosion
        float alpha = 1.0f - (i / 20.0f);  // Fade out the explosion
        
        glColor4f(1.0f, 0.5f * alpha, 0.0f, alpha);  // Color transitions from red to orange with fading
        glBegin(GL_POLYGON);  // Draw a circle for a smoother explosion effect
        int numSegments = 100;  // Number of segments for the circle
        float radius = size;
        for (int j = 0; j < numSegments; ++j) {
            float angle = 2.0f * M_PI * float(j) / float(numSegments);
            float dx = radius * cosf(angle);
            float dy = radius * sinf(angle);
            glVertex2f(x + dx, y + dy);
        }
        glEnd();

        glFlush();
        glfwSwapBuffers(glfwGetCurrentContext());
        std::this_thread::sleep_for(std::chrono::milliseconds(50));  // Slow down the animation for dramatic effect
    }
}
