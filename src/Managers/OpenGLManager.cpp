#include "OpenGLManager.h"
#include <iostream>

// Constructor
OpenGLManager::OpenGLManager() {
    // Optionally, initialize resources here
}

// Destructor
OpenGLManager::~OpenGLManager() {
    cleanup(); // Cleanup OpenGL resources if necessary
}

// Initialize OpenGL settings
void OpenGLManager::initOpenGL() {
    glEnable(GL_BLEND);  // Enable blending for transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  // Set blend function

    // Set up the clear color (optional, could be adjusted per screen)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Black background
}

// Render a dimmable background (e.g., a fade effect for the menu)
void OpenGLManager::renderBackground(float alpha) {
    // Ensure the alpha value is clamped between 0 and 1
    alpha = std::max(0.0f, std::min(1.0f, alpha));

    // Clear the screen (optional, based on your needs)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render a full-screen quad with alpha blending for dimming effect
    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, alpha);  // Set white color with transparency
    glVertex2f(-1.0f, -1.0f);  // Bottom-left
    glVertex2f(1.0f, -1.0f);   // Bottom-right
    glVertex2f(1.0f, 1.0f);    // Top-right
    glVertex2f(-1.0f, 1.0f);   // Top-left
    glEnd();
}

// Cleanup OpenGL resources
void OpenGLManager::cleanup() {
    // Free OpenGL resources if you have any (textures, shaders, etc.)
}