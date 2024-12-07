#include "Screens/Menu.h"


Menu::Menu(ScreenManager& screenManager) : screenManager(screenManager)
{
	initMusic();
    initBackground();
	initText();
	initButtons();
    initShader();
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

void Menu::updateGameState()
{
}

void Menu::draw(sf::RenderWindow& target)
{
    // Get the size of the window to calculate the flipped Y-axis
    float windowHeight = target.getSize().y;

    // Check if the mouse is over any button and set shader accordingly
    if (mPlayButton->mMouseIsOver) {
        brighteningShader(mBrighteningShader, mPlayButton, target, backgroundSprite);
        if (playButtonSoundEffect.getStatus() <= 1)
        {
            playButtonSoundEffect.play();
            music.setVolume(music.getVolume() / 2);
        }
    }
    else if (mExitButton->mMouseIsOver) {
        dimmingShader(mDimmingShader, mExitButton, target, backgroundSprite);
        if (exitButtonSoundEffect.getStatus() <= 1)
        {
            exitButtonSoundEffect.play();
            music.setVolume(music.getVolume() / 2);
        }
    }
    else if (mSettingsButton->mMouseIsOver) {
        dimmingShader(mDimmingShader, mSettingsButton, target, backgroundSprite);
    }
    else {
        if (exitButtonSoundEffect.getStatus() == 2)
        {
            exitButtonSoundEffect.pause();
            music.setVolume(music.getVolume() * 2);
        }
        if (playButtonSoundEffect.getStatus() == 2)
        {
            playButtonSoundEffect.pause();
            music.setVolume(music.getVolume() * 2);
        }

        // Draw the background normally without shader if no button is hovered
        target.draw(backgroundSprite);

        mPlayButton->draw(target);
        mExitButton->draw(target);
        mSettingsButton->draw(target);
    }
}

int Menu::initMusic()
{
	if (!music.openFromFile("assets/music/o-recinto-amaldicoado-189324.mp3"))
		return -1; // error
	//music.play();
	music.setLoop(true);

    if (!playButtonSoundEffect.openFromFile("assets/music/no-evidence-of-disease-144022.mp3"))
        return -1; // error
    //music.play();
    playButtonSoundEffect.setLoop(true);
    playButtonSoundEffect.pause();

    if (!exitButtonSoundEffect.openFromFile("assets/music/ghost-whispers-6030.mp3"))
        return -1; // error
    //music.play();
    exitButtonSoundEffect.setLoop(true);
    exitButtonSoundEffect.pause();

    //MusicManager::getInstance().playMusic("assets/music/o-recinto-amaldicoado-189324.mp3");
    //MusicManager::getInstance().pauseMusic();
    //return 0;
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
	mPlayButton = std::make_shared<Button>(sf::Vector2f(maxWidth*5/64, maxHeight*23/144), sf::Vector2f(maxWidth*0.525, maxHeight*0.55), "Play");
    // Set the button click callback
    mPlayButton->setOnClick([this]() {
        screenManager.switchScreen("Cutscene");
        });

	mExitButton = std::make_shared<Button>(sf::Vector2f(maxWidth*0.75, maxHeight*5/144), sf::Vector2f(maxWidth * 0.125, maxHeight- (maxHeight * 5 / 144)), "Run away!");
    mSettingsButton = std::make_shared<Button>(sf::Vector2f(maxWidth * 0.06, maxHeight * 1 / 9), sf::Vector2f(maxWidth * 0.035, maxHeight*0.05), "Settings");
    mSettingsButton->setIcon("assets/icons/settings-gears.png");
}

void Menu::initShader()
{
    if (!sf::Shader::isAvailable()) {
        std::cerr << "Shaders are not supported on this system." << std::endl;
    }

    mDimmingShader = std::make_shared<sf::Shader>();

    if (!mDimmingShader->loadFromFile("shaders/radialDimShader.frag", sf::Shader::Fragment)) {
        // Handle shader loading error
        std::cerr << "Error loading shader!" << std::endl;
    }

    mBrighteningShader = std::make_shared<sf::Shader>();

    if (!mBrighteningShader->loadFromFile("shaders/radialBrighteningShader.frag", sf::Shader::Fragment)) {
        // Handle shader loading error
        std::cerr << "Error loading shader!" << std::endl;
    }
}