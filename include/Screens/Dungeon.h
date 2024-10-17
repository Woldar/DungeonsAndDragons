#pragma once
#include "Bohater.h"
#include "Poziom_Lochu.h"
#include "Text.h"
#include "Screen.h"
#include "Managers/ScreenManager.h"
//#include "Managers/MusicManager.h"
#include "Objects/Button.h"

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
	std::unique_ptr<Bohater> mBohater;
	std::unique_ptr<Poziom_Lochu> mPoziom[10];
	std::unique_ptr<Button> mPlayButton[2];

	float backgroundAlpha;  // Control the fade effect for the background

	int wybor=0;
	int poziomLochu=0;
	void wybierzBohatera();
	void menuGracza();

	void menuPrzeciwnika();
	void walka();
	void grabujPrzeciwnika(int iloscP, int iloscB);
	void wyjatek();
	void zwolnijPamiec();

	int initMusic();
	void initText();

	ScreenManager& screenManager;
};
