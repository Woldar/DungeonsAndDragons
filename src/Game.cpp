#include "Game.h"

void Game::initWindow()
{
	this->videoMode = sf::VideoMode::getDesktopMode();
	this->window = new sf::RenderWindow(videoMode, "Dungeons&Dragons", sf::Style::Fullscreen);
	this->window->setFramerateLimit(144);

	//this->screenManager.getOpenGLManager()->initOpenGL();

	screenManager.addScreen("Loch", std::make_unique<Dungeon>(screenManager));
	screenManager.addScreen("Cutscene", std::make_unique<Cutscene>(screenManager, "Start"));
	screenManager.addScreen("Menu", std::make_unique<Menu>(screenManager));
	screenManager.addScreen("CharacterSelection", std::make_unique<CharacterSelection>(screenManager));
	screenManager.addScreen("Map", std::make_unique<Map>(screenManager));

	screenManager.switchScreen("Menu");
	//music.setLoop(true);
	this->screenManager.getCurrentScreen()->resumeMusic();
}

void Game::initVariables()
{
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
}

Game::~Game()
{
	delete this->window;
}

void Game::update()
{
	this->pollEvents();
	//mLoch.update();
}

void Game::render()
{
	this->window->clear();

	//Render
	//this->mLoch.render(this->window);

	this->window->display();

	this->window->popGLStates();  // Restore OpenGL state
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->sfmlEvent))
	{
		switch (this->sfmlEvent.type)
		{
			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::KeyPressed:
				if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
					this->window->close();
				break;
		}
	}
}