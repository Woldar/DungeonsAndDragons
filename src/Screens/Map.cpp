#include "Screens/Map.h"

Map::Map(ScreenManager& screenManager) : screenManager(screenManager)
{
    initMusic();
    initBackground();
    initMap();
    initText();
    initButtons();
    initShader();
}
Map::~Map()
{

}

void Map::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
}

void Map::update(float deltaTime)
{
    mText[0]->update();
    // Loop through the array of RouteToPlace and draw each route and place
    for (int i = 0; i < 6; ++i) {
        // Update the progress of each route over time
        mTarget[i]->update(deltaTime, 0.2f);  // Update with a speed factor of 0.2
    }
}

void Map::draw(sf::RenderWindow& target)
{
    target.draw(mCharacterCircle);

    // Loop through the array of RouteToPlace and draw each route and place
    for (int i = 0; i < 6; ++i) {
        // Draw the line (route) first
        //mTarget[i].drawDashedLine(target, sf::Vector2f(mCharacterCircle.getPosition().x + mCharacterCircle.getRadius(), mCharacterCircle.getPosition().y + mCharacterCircle.getRadius()), mTarget[i].place.getPosition() + sf::Vector2f(15.f, 15.f));  // Offset to center the circle

        // Draw the progressively appearing route (horizontal then vertical)
        mTarget[i]->drawRoute(target, sf::Vector2f(mCharacterCircle.getPosition().x + mCharacterCircle.getRadius(), mCharacterCircle.getPosition().y + mCharacterCircle.getRadius()));

        // Draw the place (circle)
        //target.draw(mTarget[i]->place);
        target.draw(mText[0]->getText());

        if (mTarget[i]->progress == 1.f)
        {
            mTarget[i]->mButton->draw(target);
        }
    }
}

int Map::initMusic()
{
    if (!music.openFromFile("assets/music/o-recinto-amaldicoado-189324.mp3"))
        return -1; // error
    //music.play();
    music.setLoop(true);
}

void Map::initBackground()
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

void Map::initText()
{
    mText[0] = std::make_unique<Text>();
    mText[0]->initText("YOU",false,32, "Below", sf::Vector2f(mCharacterCircle.getPosition().x + mCharacterCircle.getRadius(), mCharacterCircle.getPosition().y + mCharacterCircle.getRadius()));
}

void Map::initButtons()
{
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    int maxWidth = desktopMode.width;
    int maxHeight = desktopMode.height;
}

void Map::initShader()
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

void Map::initMap()
{
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    int maxWidth = desktopMode.width;
    int maxHeight = desktopMode.height;

    mCharacterCircle.setRadius(15.f);

    mCharacterCircle.setFillColor(sf::Color::White);  // Color it red
    mCharacterCircle.setPosition(maxWidth/2-mCharacterCircle.getRadius(), maxHeight*0.9f - mCharacterCircle.getRadius());  // Place it near the bottom

    initTargets();
}

void Map::initTargets()
{
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    int maxWidth = desktopMode.width;
    int maxHeight = desktopMode.height;

    // Define parameters for the 120° range and distance of targets from character
    float angleRange = 120.f;  // 120 degrees
    float distanceFromCharacter = std::min((float) maxWidth * 0.7f, (float) maxHeight * 0.7f);  // Distance of each place from character
    int numTargets = 6;  // Number of places
    float startingAngle = -(180.f+angleRange)/2;  // Start from -180 degrees (leftmost point)

    // Calculate the angle step between each target
    float angleStep = angleRange / (numTargets - 1);

    // Loop to create the routes and place targets in the 120° range
    for (int i = 0; i < numTargets; ++i) {
        float currentAngle = startingAngle + i * angleStep;  // Calculate the current angle for this target
        sf::Vector2f targetPosition = polarToCartesian(currentAngle, distanceFromCharacter, sf::Vector2f(mCharacterCircle.getPosition().x, mCharacterCircle.getPosition().y));  // Convert polar coordinates to Cartesian
        mTarget[i] = std::make_shared<Target>(Target(targetPosition));
    }
}

// Function to convert polar coordinates to Cartesian coordinates
sf::Vector2f Map::polarToCartesian(float angleInDegrees, float radius, const sf::Vector2f & origin) {
    float angleInRadians = angleInDegrees * PI / 180.f;
    float x = radius * std::cos(angleInRadians);
    float y = radius * std::sin(angleInRadians);
    return sf::Vector2f(origin.x + x, origin.y + y);
}