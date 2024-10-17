#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <functional> // For std::function

class Dice
{
private:
	Dice()
	{
		// Seed random number generator
		std::srand(static_cast<unsigned>(std::time(0)));

		for (int i = 0; i < 6; ++i) {
			diceFaces[i].loadFromFile("dice_face_" + std::to_string(i + 1) + ".png");
		}

		diceSprite.setTexture(diceFaces[0]);
		diceSprite.setPosition(400, 300); // Center of the window
	}

	std::vector<sf::Texture> diceFaces(6);
	sf::Sprite diceSprite;
	sf::Clock rollClock;
	bool isRolling = false;
	int rollResult = 0;
public:
	void draw(sf::RenderWindow& window)
	{

	}

};