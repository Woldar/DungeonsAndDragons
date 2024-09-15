#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <functional> // For std::function

// Button class to encapsulate button properties and behavior
class Button {
public:
    sf::RectangleShape shape;
    sf::RectangleShape glowEffect; // This will be the glow around the button
    sf::Text text;
    sf::Font font;
    std::function<void()> onClick; // Callback function for click event

    // Sound variables
    sf::SoundBuffer clickSoundBuffer;
    sf::Sound clickSound;

    Button();

    Button(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& label/*, std::string aType*/) {
        initFont();
        shape.setSize(size);
        shape.setPosition(position);
        shape.setFillColor(sf::Color(0, 0, 0, 0));
        
        text.setFont(font);
        text.setString(label);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        // Center text inside the button
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(shape.getPosition().x + size.x / 2.0f, shape.getPosition().y + size.y / 2.0f);

        // Glow effect setup (a larger rectangle surrounding the button)
        glowEffect.setSize({ size.x + 20.0f, size.y + 20.0f }); // Slightly larger than the button
        glowEffect.setPosition({ position.x - 10.0f, position.y - 10.0f }); // Centered around the button
        glowEffect.setFillColor(sf::Color(0, 0, 0, 100)); // Yellow glow, semi-transparent

        if (!clickSoundBuffer.loadFromFile("assets/music/old-radio-button-click-97549.mp3")) {
            // Handle error
            std::cerr << "Failed to load sound: " << "assets/music/old-radio-button-click-97549.mp3" << std::endl;
        }
        clickSound.setBuffer(clickSoundBuffer);
    }

    bool isMouseOver(const sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        return shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    }

    void setFillColor(const sf::Color& color) {
        shape.setFillColor(color);
    }

    // Draw the button
    void draw(sf::RenderWindow& window) {
        if (isMouseOver(window)) {
            window.draw(glowEffect); // Draw the glow effect behind the button
            window.draw(shape);
            window.draw(text);
            //shape.setFillColor(sf::Color::Green);
        }
        else
        {
            window.draw(shape);
            window.draw(text);
            //shape.setFillColor(sf::Color::Blue);
        }

    }

    int initFont()
    {
        if (!font.loadFromFile("assets/fonts/MoriaCitadel.ttf"))  // Adjust the path to where your font is located
        {
            std::cerr << "Error loading font!" << std::endl;
            return -1;
        }
    }

    // Check if the button was clicked
    void checkClick(const sf::Event& event, const sf::RenderWindow& window) {
        if (isMouseOver(window) && event.type == sf::Event::MouseButtonReleased) {
            if (onClick) {
                onClick(); // Trigger the callback if set
                clickSound.play();
            }
        }
    }

    // Set the callback function for button click
    void setOnClick(std::function<void()> callback) {
        onClick = callback;
    }

    // Set the sound for the button click
    void initClickSound(const std::string& soundFile) {
        if (!clickSoundBuffer.loadFromFile(soundFile)) {
            // Handle error
            std::cerr << "Failed to load sound: " << soundFile << std::endl;
        }
        clickSound.setBuffer(clickSoundBuffer);
    }
};