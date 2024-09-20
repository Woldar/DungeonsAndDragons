#pragma once

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

class OpenGLManager {
public:
    OpenGLManager();
    ~OpenGLManager();

    void initOpenGL();             // Initialize OpenGL settings
    void renderBackground(float alpha);  // Render the background with a dimming effect
    void cleanup();                // Cleanup OpenGL resources if needed

private:
    // Any OpenGL-specific resources can be declared here (like textures, shaders, etc.)
};