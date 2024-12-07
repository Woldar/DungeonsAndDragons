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
	sf::Clock rollTimer;
	sf::Vector2f mPosition;
	bool isRolling = false;
	int rollResult = 0;
	bool finishedRolling = false;
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

		// Optionally scale the background to fit the window size
		sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
		int maxWidth = desktopMode.width;
		int maxHeight = desktopMode.height;

		diceSprite.setPosition(sf::Vector2f(desktopMode.width / 2 - diceSprite.getTexture()->getSize().x / 2, desktopMode.height / 2 - diceSprite.getTexture()->getSize().y / 2));
		mPosition = position;
		mButton.setPosition(sf::Vector2f(desktopMode.width / 2 - diceSprite.getTexture()->getSize().x / 2, desktopMode.height / 2 - diceSprite.getTexture()->getSize().y / 2));
		mButton.setSize(sf::Vector2f(diceSprite.getTexture()->getSize().x, diceSprite.getTexture()->getSize().y));
	}
	void draw(sf::RenderWindow& window)
	{
		window.draw(diceSprite);
		mButton.draw(window);
	}

	void draw(sf::RenderTexture& renderTexture)
	{
		renderTexture.draw(diceSprite);
		//renderTexture.draw(mButton.icon());
		//mButton.draw(renderTexture);
	}

	void startRolling() {
		isRolling = true;
		rollClock.restart();
		rollTimer.restart();
		finishedRolling = false;
	}

	void update() {
		// Update the dice rolling animation
		int temporaryRoll = 0;
		if (isRolling && rollClock.getElapsedTime().asSeconds() > 0.1f && finishedRolling != true) {
			temporaryRoll = (std::rand() % 6) + 1; // Random face
			diceSprite.setTexture(diceFaces[temporaryRoll -1]);
			rollClock.restart();

			// Stop rolling after a certain time
			if (rollTimer.getElapsedTime().asSeconds() > 2.f) {
				rollResult = temporaryRoll;
				isRolling = false;
				finishedRolling = true;
			}
		}
	}

	void setPostition(sf::Vector2f vector)
	{
		diceSprite.setPosition(vector);
		mButton.setPosition(vector);
	}

	void setButton()
	{
		mButton.setOnClick([this]() {
			if (finishedRolling == false)
			{
				startRolling();
			}
			else
			{
				if (GameState::getInstance().getPlayer()->getWill() > 0)
				{
					GameState::getInstance().getPlayer()->setWill(GameState::getInstance().getPlayer()->getWill()-1);
					startRolling();
				}
			}
		});
	}
	
	void setScale(float aScale)
	{
		diceSprite.setScale(sf::Vector2f(aScale, aScale));
		mButton.setSize(sf::Vector2f( mButton.getSize().x * diceSprite.getScale().x, mButton.getSize().y * diceSprite.getScale().y));
	}

	Button getButton()
	{
		return mButton;
	}

	bool getState()
	{
		return finishedRolling;
	}

	sf::Vector2f getSize()
	{
		return mButton.getSize();
	}

	sf::Vector2f getPosition()
	{
		return mPosition;
	}

	int getRollResult()
	{
		return rollResult;
	}
};