#pragma once
#include "Text.h"
#include "Screen.h"
#include "Managers/ScreenManager.h"
#include "Button.h"
//#include "Managers/MusicManager.h"

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

	void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& target) override;

	void pauseMusic() override{
		music.pause();
	}

	void resumeMusic() override {
		music.play();
	}
private:
	ScreenManager& screenManager;
	sf::Music music;
	Text mText[2];
	std::unique_ptr<Button> mPlayButton[2];

	int initMusic();
	void initText();
};
