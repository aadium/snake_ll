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
    // Draw the base of the bomb (1x1 square)
    glColor3f(0.3f, 0.0f, 0.0f);  // Dark grey base
    glRecti(x, y, x + 1, y + 1);

    // Draw a border around the base
    glColor3f(1.0f, 0.5f, 0.0f);  // Orange border
    glLineWidth(4.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2i(x, y);
    glVertex2i(x + 1, y);
    glVertex2i(x + 1, y + 1);
    glVertex2i(x, y + 1);
    glEnd();

    // Draw the trigger plate (centered)
    glColor3f(0.8f, 0.8f, 0.8f);  // Light grey
    glRecti(x + 0.3f, y + 0.3f, x + 0.7f, y + 0.7f);

    // Draw a warning triangle (yellow with black outline)
    glColor3f(1.0f, 1.0f, 0.0f);  // Yellow triangle
    glBegin(GL_TRIANGLES);
    glVertex2f(x + 0.5f, y + 0.8f);  // Top vertex
    glVertex2f(x + 0.2f, y + 0.2f);  // Bottom-left vertex
    glVertex2f(x + 0.8f, y + 0.2f);  // Bottom-right vertex
    glEnd();

    // Draw black outline for the warning triangle
    glColor3f(0.0f, 0.0f, 0.0f);  // Black outline
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x + 0.5f, y + 0.8f);  
    glVertex2f(x + 0.2f, y + 0.2f);  
    glVertex2f(x + 0.8f, y + 0.2f);  
    glEnd();

    // Draw a lightning bolt inside the triangle (optional)
    glColor3f(0.0f, 0.0f, 0.0f);  // Black lightning bolt
    glBegin(GL_LINES);
    glVertex2f(x + 0.45f, y + 0.75f);  // Top segment
    glVertex2f(x + 0.55f, y + 0.55f);
    glVertex2f(x + 0.55f, y + 0.55f);  // Bottom segment
    glVertex2f(x + 0.4f, y + 0.3f);
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f);  // Reset color (optional)
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
