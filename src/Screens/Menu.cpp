#include "Screens/Menu.h"


Menu::Menu(ScreenManager& screenManager) : screenManager(screenManager)
{
	initMusic();
    initBackground();
	initText();
	initButtons();
}
Menu::~Menu()
{

}

void Menu::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::MouseButtonReleased) {
        mPlayButton->checkClick(event, window);
    }
}

void Menu::update(float deltaTime)
{
}

void Menu::draw(sf::RenderWindow& target)
{
    target.draw(backgroundSprite);
	mPlayButton->draw(target);
	mExitButton->draw(target);
    mSettingsButton->draw(target);
}

int Menu::initMusic()
{
	if (!music.openFromFile("assets/music/o-recinto-amaldicoado-189324.mp3"))
		return -1; // error
	music.play();
	music.setLoop(true);
}

void Menu::initBackground()
{
    // Load the background image from a file
    if (!backgroundTexture.loadFromFile("assets/backgrounds/StartBackground.png")) {
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

void Menu::initText()
{
}

void Menu::initButtons()
{
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    int maxWidth = desktopMode.width;
    int maxHeight = desktopMode.height;
	mPlayButton = std::make_unique<Button>(sf::Vector2f(maxWidth*5/64, maxHeight*23/144), sf::Vector2f(maxWidth*0.525, maxHeight*0.55), "Play");
    // Set the button click callback
    mPlayButton->setOnClick([this]() {
        screenManager.switchScreen("Cutscene");
        });


	mExitButton = std::make_unique<Button>(sf::Vector2f(maxWidth*0.75, maxHeight*5/144), sf::Vector2f(maxWidth * 0.125, maxHeight- (maxHeight * 5 / 144)), "Run away!");
    mSettingsButton = std::make_unique<Button>(sf::Vector2f(maxWidth * 0.1, maxHeight * 36 / 144), sf::Vector2f(maxWidth * 0.025, maxHeight*0.05), "Settings");
}