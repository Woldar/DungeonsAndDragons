#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <functional> // For std::function
#include "Shaders.h"

// ClassTab class to encapsulate ClassTab properties and behavior
class ClassTab {
public:
    sf::Vector2f mSize;            // Size of the ClassTab
    sf::RectangleShape shape;
    sf::RectangleShape glowEffect; // This will be the glow around the ClassTab
    sf::Text textSpecialAbilities;
    sf::Text textStartingStatistics;
    sf::Font font;
    sf::Sprite icon;              // Icon sprite
    sf::Texture iconTexture;      // Texture for the icon
    sf::Color mTextColorMouseOver;
    sf::Color mTextColorMouseNotOver;
    bool mMouseIsOver = false;
    bool mIsActive = true;

    std::function<void()> onClick; // Callback function for click event

    // Sound variables
    sf::SoundBuffer clickSoundBuffer;
    sf::Sound clickSound;

    sf::Shader mDimmingShader;  // Shader for dimming effect

    ClassTab(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& label/*, std::string aType*/) {
        initFont();
        mSize = size;
        shape.setSize(size);
        shape.setPosition(position);
        shape.setFillColor(sf::Color(0, 0, 0, 0));
        
        sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
        int maxWidth = desktopMode.width;
        int maxHeight = desktopMode.height;

        textSpecialAbilities.setFont(font);
        textSpecialAbilities.setString(label);
        textSpecialAbilities.setCharacterSize(32);
        textSpecialAbilities.setFillColor(sf::Color::White);
        mTextColorMouseOver = sf::Color::White;
        mTextColorMouseNotOver = sf::Color::White;
        // Center text inside the ClassTab
        sf::FloatRect textRectSpecialAbilities = textSpecialAbilities.getLocalBounds();
        textSpecialAbilities.setOrigin(textRectSpecialAbilities.left + textRectSpecialAbilities.width / 2.0f, textRectSpecialAbilities.top + textRectSpecialAbilities.height / 2.0f);
        textSpecialAbilities.setPosition(sf::Vector2f(maxWidth * 0.1f, maxHeight * 0.1f));

        textStartingStatistics.setFont(font);
        textStartingStatistics.setString(label);
        textStartingStatistics.setCharacterSize(32);
        textStartingStatistics.setFillColor(sf::Color::White);
        mTextColorMouseOver = sf::Color::White;
        mTextColorMouseNotOver = sf::Color::White;
        // Center text inside the ClassTab
        sf::FloatRect textRectStartingStatistics = textStartingStatistics.getLocalBounds();
        //textStartingStatistics.setOrigin(textRectStartingStatistics.left + textRectStartingStatistics.width / 2.0f, textRectStartingStatistics.top + textRectStartingStatistics.height / 2.0f);

        // Glow effect setup (a larger rectangle surrounding the ClassTab)
        glowEffect.setSize({ size.x + 20.0f, size.y + 20.0f }); // Slightly larger than the ClassTab
        glowEffect.setPosition({ position.x - 10.0f, position.y - 10.0f }); // Centered around the ClassTab
        glowEffect.setFillColor(sf::Color(0, 0, 0, 100)); // Yellow glow, semi-transparent

        if (!clickSoundBuffer.loadFromFile("assets/music/old-radio-button-click-97549.mp3")) {
            // Handle error
            std::cerr << "Failed to load sound: " << "assets/music/old-radio-button-click-97549.mp3" << std::endl;
        }

        // Load the dimming shader
        if (!mDimmingShader.loadFromFile("shaders/radialDimShader.frag", sf::Shader::Fragment)) {
            // Handle shader loading error
            std::cerr << "Error loading shader!" << std::endl;
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

    // Draw the ClassTab
    void draw(sf::RenderWindow& window) {
        if (isMouseOver(window)) {
            mMouseIsOver = true;
            textSpecialAbilities.setFillColor(mTextColorMouseOver);
            window.draw(glowEffect); // Draw the glow effect behind the ClassTab
            window.draw(shape);
            //dimmingShader(mDimmingShader, window, icon);
            window.draw(icon); // Draw the icon with the shader applied
            window.draw(textSpecialAbilities);
            window.draw(textStartingStatistics);
        }
        else
        {
            mMouseIsOver = false;
            textSpecialAbilities.setFillColor(mTextColorMouseNotOver);
            window.draw(shape);
            //dimmingShader(mDimmingShader, window, icon);
            window.draw(icon); // Draw the icon with the shader applied
            window.draw(textSpecialAbilities);
            window.draw(textStartingStatistics);
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

    // Check if the ClassTab was clicked
    void checkClick(const sf::Event& event, const sf::RenderWindow& window) {
        if (isMouseOver(window) && event.type == sf::Event::MouseButtonReleased && mIsActive) {
            if (onClick) {
                onClick(); // Trigger the callback if set
                clickSound.play();
            }
        }
    }

    // Set the callback function for ClassTab click
    void setOnClick(std::function<void()> callback) {
        onClick = callback;
    }

    // Set the sound for the ClassTab click
    void initClickSound(const std::string& soundFile) {
        if (!clickSoundBuffer.loadFromFile(soundFile)) {
            // Handle error
            std::cerr << "Failed to load sound: " << soundFile << std::endl;
        }
        clickSound.setBuffer(clickSoundBuffer);
    }

    void setIcon(const std::string& iconPath)
    {
        if (iconTexture.loadFromFile(iconPath)) {
            icon.setTexture(iconTexture);

            //icon.setScale(iconScale, iconScale);

            // Get the scaled icon's size
            sf::FloatRect iconBounds = icon.getGlobalBounds();

            // Position the icon in the center of the button
            icon.setPosition(
                shape.getPosition().x + mSize.x  - (1.05f * iconBounds.width),   // ClassTab's horizontal center
                shape.getPosition().y + mSize.y / 2.0f - (0.5f * iconBounds.height)    // ClassTab's vertical center
            );
        }
        else {
            std::cerr << "Failed to load icon texture\n";
        }
    }

    sf::Vector2f getCenter() const {
        sf::FloatRect bounds = shape.getGlobalBounds();  // Assuming `shape` is your ClassTab shape
        return sf::Vector2f(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    }

    sf::RectangleShape getShape() const {
        return shape;
    }

    void setTextsPositions()
    {
        sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
        int maxWidth = desktopMode.width;
        int maxHeight = desktopMode.height;

        textStartingStatistics.setPosition(maxWidth * 0.1f, textSpecialAbilities.getGlobalBounds().getPosition().y + textSpecialAbilities.getGlobalBounds().getSize().y);
    }
};