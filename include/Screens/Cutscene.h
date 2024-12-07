#pragma once
#include "Text.h"
#include "Screen.h"
#include "Managers/ScreenManager.h"
#include "Objects/Button.h"
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
	Cutscene(ScreenManager& screenManager, std::string aView);
	~Cutscene();

	void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
	void update(float deltaTime) override;
	void updateGameState() override;
	void draw(sf::RenderWindow& target) override;

	void pauseMusic() override{
		music.pause();
	}

	void resumeMusic() override {
		music.play();
	}

	void resetScreen() override {
		initText();
		initIcon();
	}

	void setScreen(const std::string& aView) override {
		mView = aView;
	}


private:
	ScreenManager& screenManager;
	sf::Music music;
	std::unique_ptr<Text> mText[2];
	sf::Sprite icon;              // Icon sprite
	sf::Texture iconTexture;      // Texture for the icon

	std::string mView;
	int initMusic();
	void initText();
	void initIcon();
};
