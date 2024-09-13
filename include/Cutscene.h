#pragma once
#include "Text.h"
#include "Screen.h"
#include "ScreenManager.h"

#include <string>
#include <string.h>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Cutscene : public Screen
{
public:
	Cutscene(ScreenManager& screenManager);
	~Cutscene();

	void handleEvent(const sf::Event& event) override;
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& target) override;
private:
	ScreenManager& screenManager;
	sf::Music music;
	Text mText[2];

	int initMusic();
	void initText();
};
