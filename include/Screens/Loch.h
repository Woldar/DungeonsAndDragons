#pragma once
#include "Bohater.h"
#include "Poziom_Lochu.h"
#include "Text.h"
#include "Screen.h"
#include "Managers/ScreenManager.h"
#include "Button.h"

#include <string>
#include <string.h>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Loch : public Screen
{
public:
	Loch(ScreenManager& screenManager);
	~Loch();

	void start();
	void generujLoch();

	void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& target) override;
private:
	sf::Music music;
	Text mText;
	std::unique_ptr<Bohater> mBohater;
	std::unique_ptr<Poziom_Lochu> mPoziom[10];
	std::unique_ptr<Button> mPlayButton[2];

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
