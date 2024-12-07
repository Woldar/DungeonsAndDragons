#include "Screens/Dungeon.h"


Dungeon::Dungeon(ScreenManager& screenManager) 
	: screenManager(screenManager)/*, enemyLoader("Enemies/Enemies.lua")*/
{
	initMusic();
	initText();
	initBackground();
}
Dungeon::~Dungeon()
{

}

void Dungeon::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
	// Check if the event is a key press
	if (event.type == sf::Event::KeyPressed) {
		// Check if the key pressed is "Enter"
		if (event.key.code == sf::Keyboard::Enter) {
			// Handle the Enter key press
			std::cout << "Switching to Map Screen!" << std::endl;
			screenManager.switchScreen("Map");
		}
	}
}

void Dungeon::update(float deltaTime)
{
}

void Dungeon::updateGameState()
{
	initTextures();
}

void Dungeon::draw(sf::RenderWindow& target)
{
	// Draw the background normally without shader if no button is hovered
	target.draw(backgroundSprite);

	target.draw(playerSprite);
	target.draw(enemySprite);
}

int Dungeon::initMusic()
{
	if (!music.openFromFile("assets/music/o-recinto-amaldicoado-189324.mp3"))
		return -1; // error
	music.setLoop(true);
}

void Dungeon::initText()
{

}

void Dungeon::initBackground()
{
	// Load the background image from a file
	if (!backgroundTexture.loadFromFile("assets/backgrounds/backgroundFight.png")) {
		std::cerr << "Error loading background image!" << std::endl;
	}

	// Set the texture to the sprite
	backgroundSprite.setTexture(backgroundTexture);

	// Optionally scale the background to fit the window size
	sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
	int maxWidth = desktopMode.width;
	int maxHeight = desktopMode.height;
	sf::Vector2u textureSize = backgroundTexture.getSize(); // Get size of the texture
	sf::Vector2u windowSize(maxWidth, maxHeight);                      // Assuming window size is 800x600

	// Scale the background to cover the window
	backgroundSprite.setScale(
		float(windowSize.x) / textureSize.x,
		float(windowSize.y) / textureSize.y
	);
}

void Dungeon::initTextures()
{
	sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
	int maxWidth = desktopMode.width;
	int maxHeight = desktopMode.height;

	if (playerTexture.loadFromFile(GameState::getInstance().getPlayer()->getClass()->getIconPath())) {
		playerSprite.setTexture(playerTexture);

		//icon.setScale(iconScale, iconScale);

		// Get the scaled icon's size
		sf::FloatRect iconBounds = playerSprite.getGlobalBounds();

		// Position the icon in the center of the button
		playerSprite.setPosition(0, maxHeight/2-0.5*iconBounds.height);
	}
	else {
		std::cerr << "Failed to load icon texture\n";
	}

	if (enemyTexture.loadFromFile(GameState::getInstance().getEnemy()->getIconPath())) {
		enemySprite.setTexture(enemyTexture);

		//icon.setScale(iconScale, iconScale);

		// Get the scaled icon's size
		sf::FloatRect iconBounds = enemySprite.getGlobalBounds();

		// Position the icon in the center of the button
		enemySprite.setPosition(maxWidth-iconBounds.width, maxHeight / 2 - 0.5 * iconBounds.height);
	}
	else {
		std::cerr << "Failed to load icon texture\n";
	}

}