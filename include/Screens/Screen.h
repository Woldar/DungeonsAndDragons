// Screen.h
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Objects/GameState.h"

class Screen {
public:
    virtual ~Screen() = default;

    // Handle events like keyboard and mouse input
    virtual void handleEvent(const sf::Event& event, sf::RenderWindow& window) = 0;

    // Update the screen's state
    virtual void update(float deltaTime) = 0;

    virtual void updateGameState() = 0;

    // Draw the screen
    virtual void draw(sf::RenderWindow& target) = 0;

    virtual void pauseMusic() = 0;

    virtual void resumeMusic() = 0;

    virtual void resetScreen() = 0;

    virtual void setScreen(const std::string& aView) = 0;
};