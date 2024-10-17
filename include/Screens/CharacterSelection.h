#pragma once
#include "Text.h"
#include "Screen.h"
#include "Managers/ScreenManager.h"
#include "Managers/ClassManager.h"
#include "Objects/Button.h"
#include "Objects/ClassTab.h"

#include <string>
#include <string.h>
#include <iostream>
#include <functional>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

//class CharacterSelectionButton {
//public:
//    CharacterSelectionButton(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& textString, sf::Font& font)
//    {
//        // Create a rectangle for the button
//        shape.setSize(size);
//        shape.setPosition(position);
//        shape.setFillColor(sf::Color::Blue);  // Default color
//
//        // Create the button's text
//        text.setFont(font);
//        text.setString(textString);
//        text.setCharacterSize(24);
//        text.setFillColor(sf::Color::White);
//
//        // Center the text on the button
//        sf::FloatRect textBounds = text.getLocalBounds();
//        text.setOrigin(textBounds.width / 2, textBounds.height / 2);
//        text.setPosition(
//            position.x + size.x / 2,
//            position.y + size.y / 2 - textBounds.height / 2
//        );
//    }
//
//    // Draw the button
//    void draw(sf::RenderWindow& window) {
//        window.draw(shape);
//        window.draw(text);
//    }
//
//    // Check if the button is clicked
//    bool isClicked(const sf::Vector2i& mousePos) const {
//        return shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
//    }
//
//    // Set callback when clicked (optional)
//    void onClick(std::function<void()> callback) {
//        clickCallback = callback;
//    }
//
//    // Call click handler
//    void handleMouseClick(const sf::Vector2i& mousePos) {
//        if (isClicked(mousePos) && clickCallback) {
//            clickCallback();
//        }
//    }
//
//private:
//    sf::RectangleShape shape;
//    sf::Text text;
//    std::function<void()> clickCallback;
//};

class CharacterSelection : public Screen
{
public:
	CharacterSelection(ScreenManager& screenManager);
	~CharacterSelection();

	void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& target) override;

	void pauseMusic() override{
		music.pause();
	}

	void resumeMusic() override {
		music.play();
	}

	void resetScreen() override {

	}

	void setScreen(const std::string& aView) override {

	}
private:
	ScreenManager& screenManager;
	ClassManager classManager;
	sf::Music music;
	std::vector<std::unique_ptr<Button>> mClassesButtons;
	std::unique_ptr<ClassTab> mExtendedClassView;

	bool mExtendedView;
	//std::unique_ptr<Button> mButtons;

	float backgroundAlpha;  // Control the fade effect for the background

	int initMusic();
	void initText();
	void initClassesRectangles();
};
