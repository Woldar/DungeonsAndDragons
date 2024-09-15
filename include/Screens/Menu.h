#pragma once
#include "Text.h"
#include "Button.h"
#include "Screen.h"
#include "Managers/ScreenManager.h"

#include <string>
#include <string.h>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Menu : public Screen
{
public:
	Menu(ScreenManager& screenManager);
	~Menu();

	void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& target) override;
private:
	ScreenManager& screenManager;
	sf::Music music;
	sf::Texture backgroundTexture; // Texture to hold the background image
	sf::Sprite backgroundSprite;   // Sprite to display the texture
	Text mText[2];
	std::unique_ptr<Button> mPlayButton;
	std::unique_ptr<Button> mExitButton;
	std::unique_ptr<Button> mSettingsButton;

	int initMusic();
	void initBackground();
	void initText();
	void initButtons();
};
