// ScreenManager.h
#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include "Screen.h"
#include "Objects/GameState.h"
#include "OpenGLManager.h"

class ScreenManager {
public:

    void addScreen(const std::string& name, std::unique_ptr<Screen> screen) {
        screens[name] = std::move(screen);
        currentScreen = screens[name].get();
    }

    // Switch to a different screen
    void switchScreen(const std::string& name) {
        if (screens.find(name) != screens.end()) {
            currentScreen->pauseMusic();
            currentScreen = screens[name].get();
            currentScreen->resumeMusic();
        }
    }

    // Get the current screen
    Screen* getCurrentScreen() {
        return currentScreen;
    }

    OpenGLManager* getOpenGLManager()
    {
        return &openGLManager;
    }

private:
    std::unordered_map<std::string, std::unique_ptr<Screen>> screens;  // Store screens
    Screen* currentScreen = nullptr;  // Pointer to the current screen

    OpenGLManager openGLManager;  // Manage OpenGL rendering across screens
};