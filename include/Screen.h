// Screen.h
#pragma once

#include <SFML/Graphics.hpp>

class Screen {
public:
    virtual ~Screen() = default;

    // Handle events like keyboard and mouse input
    virtual void handleEvent(const sf::Event& event) = 0;

    // Update the screen's state
    virtual void update(float deltaTime) = 0;

    // Draw the screen
    virtual void draw(sf::RenderWindow& target) = 0;
};