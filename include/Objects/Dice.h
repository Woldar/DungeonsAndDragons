#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <Button.h>

#include <iostream>
#include <functional> // For std::function

class Dice
{
private:
	Button mButton;
	std::vector<sf::Texture> diceFaces;
	sf::Sprite diceSprite;
	sf::Clock rollClock;
	bool isRolling = false;
	int rollResult = 0;
public:
	Dice(sf::Vector2f size, sf::Vector2f position)
		: mButton(size, position, "")
	{
		diceFaces.resize(6);
		// Seed random number generator
		std::srand(static_cast<unsigned>(std::time(0)));

		for (int i = 0; i < 6; ++i) {
			diceFaces[i].loadFromFile("assets/dice/dice-six-faces-" + std::to_string(i + 1) + ".png");
		}

		diceSprite.setTexture(diceFaces[0]);
		diceSprite.setPosition(position);
	}
	void draw(sf::RenderWindow& window)
	{
		window.draw(diceSprite);
	}

	void startRolling() {
		isRolling = true;
		rollClock.restart();
	}

	void update() {
		// Update the dice rolling animation
		if (isRolling && rollClock.getElapsedTime().asSeconds() > 0.1f) {
			rollResult = std::rand() % 6; // Random face
			diceSprite.setTexture(diceFaces[rollResult]);
			rollClock.restart();

			// Stop rolling after a certain time
			if (rollClock.getElapsedTime().asSeconds() > 1.5f) {
				isRolling = false;
			}
		}
	}
};