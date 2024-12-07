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

class CharacterSelection : public Screen
{
public:
	CharacterSelection(ScreenManager& screenManager);
	~CharacterSelection();

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

	}

	void setScreen(const std::string& aView) override {

	}
private:
	ScreenManager& screenManager;
	ClassManager classManager;
	sf::Music music;
	std::vector<std::unique_ptr<Button>> mClassesButtons;
	std::unique_ptr<ClassTab> mExtendedClassView;
	//std::unique_ptr <CharacterClass> mCharacterClass;

	bool mExtendedView;

	int initMusic();
	void initText();
	void initClassesRectangles();
};
