#pragma once

#include <iostream>
#include <ctime>
#include <time.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Dungeon.h"
#include "Cutscene.h"
#include "Menu.h"
#include "CharacterSelection.h"
#include "Map.h"
#include "Managers/ScreenManager.h"
#include "Objects/GameState.h"

class Game
{
private:
	sf::VideoMode videoMode;
	sf::Event sfmlEvent;

	void initWindow();
	void initVariables();

public:
	//Constructors and destructors
	Game();
	~Game();
	sf::RenderWindow* window;
	ScreenManager screenManager;
	sf::Clock clock;

	//Accessors

	//Modifiers

	//Functions
	void pollEvents();

	void update();
	void render();
};