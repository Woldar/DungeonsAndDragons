#pragma once
#include "Text.h"
#include "Screen.h"
#include "Managers/ScreenManager.h"
#include "Objects/Button.h"
#include "Enemies/EnemyLoader.h"

#include <string>
#include <string.h>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Dungeon : public Screen
{
public:
	Dungeon(ScreenManager& screenManager);
	~Dungeon();

	void start();
	void generujLoch();

	void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
	void update(float deltaTime) override;
	void updateGameState() override;
	void draw(sf::RenderWindow& target) override;
	void pauseMusic() override {
		music.pause();
	}

	void resumeMusic() override{
		music.play();
	}

	void resetScreen() override {

	}

	void setScreen(const std::string& aView) override {

	}

private:
	sf::Music music;
	Text mText;

	sf::Texture backgroundTexture; // Texture to hold the background image
	sf::Sprite backgroundSprite;   // Sprite to display the texture

	sf::Texture enemyTexture; // Texture to hold the background image
	sf::Sprite enemySprite;   // Sprite to display the texture

	sf::Sprite playerSprite;              // Icon sprite
	sf::Texture playerTexture;      // Texture for the icon

	int initMusic();
	void initText();
	void initBackground();

	void initTextures();

	ScreenManager& screenManager;
	//EnemyLoader enemyLoader;
};
