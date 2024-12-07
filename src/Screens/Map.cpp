#include "Screens/Map.h"

Map::Map(ScreenManager& screenManager) : screenManager(screenManager), mDice(sf::Vector2f(0, 0), sf::Vector2f(100, 100)), mEnemyLoader("assets/data/Enemies.lua")
{
    initMusic();
    initBackground();
    initDice();
    initShader();
}
Map::~Map()
{

}

void Map::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::MouseButtonReleased) {

        mDice.getButton().checkClick(event, window);
        if (mMapInitialized)
        {
            mTarget[mDice.getRollResult() - 1]->mButton->checkClick(event, window);
        }
    }
}

void Map::update(float deltaTime)
{
    mDice.update();

    if (mDice.getState() && !mMapInitialized)
    {
        sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
        int maxWidth = desktopMode.width;
        int maxHeight = desktopMode.height;
        initMap();
        initText();
        mDice.setScale(0.5);
        mDice.setPostition(sf::Vector2f(maxWidth/2 - mDice.getSize().x/2, mCharacterCircle.getPosition().y + mCharacterCircle.getRadius()/2 - 2 * mDice.getSize().x));
    }
    // Loop through the array of RouteToPlace and draw each route and place
    else if (mMapInitialized)
    {
        if (std::find(rolledValues.begin(), rolledValues.end(), mDice.getRollResult() - 1) == rolledValues.end()) {
            // If not found, add the value
            if (rolledValues.size() != 0)
            {
                mTarget[rolledValues.back()]->mButton->setAlternativeIcon("assets/icons/DoorsClosed.png", mTarget[rolledValues.back()]->doorScale);
            }

            rolledValues.push_back(mDice.getRollResult() - 1);
            mTarget[mDice.getRollResult() - 1]->mButton->setAlternativeIcon("assets/icons/DoorsOpened.png", mTarget[mDice.getRollResult() - 1]->doorScale);
        }

        std::string buffor = "Will: ";
        std::string mWillValue = GameState::getInstance().getPlayer()->getWillString();
        buffor += mWillValue;
        mText[1]->setText(buffor);

        mText[0]->update();
        mText[1]->update();
        for (int i = 0; i < 6; ++i) {
            // Update the progress of each route over time
            mTarget[i]->update(deltaTime, 0.4f);  // Update with a speed factor of 0.1
            mTarget[i]->mText->update();
        }

        bool check = false;
        blurScreen = false;
        for (int value : rolledValues)
        {
            if (mTarget[value]->mButton->mMouseIsOver)
            {
                check = true;
                mouseIsOver = value;
            }
        }

        if (check)
        {
            blurScreen = true;
        }
    }
}

void Map::updateGameState()
{
}

void Map::draw(sf::RenderWindow& target)
{
    //renderTexture.clear();
    if (!renderTexture.create(target.getSize().x, target.getSize().y)) {
        std::cerr << "Failed to create RenderTexture" << std::endl;
    }

    if (mMapInitialized && !blurScreen)
    {
        // Loop through the array of RouteToPlace and draw each route and place
        for (int i = 0; i < 6; ++i) {

            // Draw the progressively appearing route (horizontal then vertical)
            if (i != mDice.getRollResult()-1)
            {
                mTarget[i]->drawRouteWhite(target, sf::Vector2f(mCharacterCircle.getPosition().x + mCharacterCircle.getRadius(), mCharacterCircle.getPosition().y + mCharacterCircle.getRadius()));
            }

            if (mTarget[i]->progress == 1.f)
            {
                mTarget[i]->mButton->draw(target);
            }
        }
        mTarget[mDice.getRollResult() - 1]->drawRouteGreen(target, sf::Vector2f(mCharacterCircle.getPosition().x + mCharacterCircle.getRadius(), mCharacterCircle.getPosition().y + mCharacterCircle.getRadius()));
        target.draw(mCharacterCircle);
        target.draw(mText[0]->getText());
        target.draw(mText[1]->getText());

        previousFrameBlured = false;
    }
    mDice.draw(target);

    if (mMapInitialized && blurScreen && !previousFrameBlured)
    {
        previousFrameBlured = true;
        for (int i = 0; i < 6; ++i)
        {
            // Draw the progressively appearing route (horizontal then vertical)
            if (i != mDice.getRollResult() - 1)
            {
                mTarget[i]->drawRouteWhite(renderTexture, sf::Vector2f(mCharacterCircle.getPosition().x + mCharacterCircle.getRadius(), mCharacterCircle.getPosition().y + mCharacterCircle.getRadius()));
            }

            if (i == mouseIsOver)
            {
                continue;
            }
            renderTexture.draw(mTarget[i]->mButton->icon);
        }

        mTarget[mDice.getRollResult() - 1]->drawRouteGreen(renderTexture, sf::Vector2f(mCharacterCircle.getPosition().x + mCharacterCircle.getRadius(), mCharacterCircle.getPosition().y + mCharacterCircle.getRadius()));
        renderTexture.draw(mCharacterCircle);
        renderTexture.draw(mText[0]->getText());
        renderTexture.draw(mText[1]->getText());
        mDice.draw(renderTexture);

        // Apply blur effect to the texture
        sf::Sprite screenSprite(renderTexture.getTexture()); // Create a sprite from the RenderTexture
        mBlurShader->setUniform("texture", sf::Shader::CurrentTexture); // Use the RenderTexture's texture
        renderTexture.display();

        target.draw(screenSprite, mBlurShader.get()); // Apply the shader to the entire scene

        target.draw(enemySprite[mouseIsOver]);

        target.draw(mTarget[mouseIsOver]->mText->getText());
    }
    else if(mMapInitialized && blurScreen && previousFrameBlured)
    {
        previousFrameBlured = true;
        // Apply blur effect to the texture
        sf::Sprite screenSprite(renderTexture.getTexture()); // Create a sprite from the RenderTexture
        mBlurShader->setUniform("texture", sf::Shader::CurrentTexture); // Use the RenderTexture's texture
        renderTexture.draw(mTarget[mouseIsOver]->mText->getText());
        renderTexture.display(); 

        target.draw(screenSprite, mBlurShader.get()); // Apply the shader to the entire scene

        target.draw(enemySprite[mouseIsOver]);
        
        mTarget[mouseIsOver]->mButton->draw(target);

        target.draw(mTarget[mouseIsOver]->mText->getText());
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
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    int maxWidth = desktopMode.width;
    int maxHeight = desktopMode.height;

    mText[0] = std::make_unique<Text>();
    mText[0]->initText("YOU",false,32, sf::Vector2f(mCharacterCircle.getPosition().x + mCharacterCircle.getRadius(), mCharacterCircle.getPosition().y + mCharacterCircle.getRadius()));

    std::string buffor = "Will: ";
    std::string mWillValue = GameState::getInstance().getPlayer()->getWillString();
    buffor += mWillValue;
    
    mText[1] = std::make_unique<Text>();
    mText[1]->initText(buffor, false, 32, sf::Vector2f(maxWidth / 2, maxHeight * 0.75));
}

void Map::initDice()
{
    mDice.setButton();
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

    mBlurShader = std::make_shared<sf::Shader>();

    if (!mBlurShader->loadFromFile("shaders/blurShader.frag", sf::Shader::Fragment)) {
        // Handle shader loading error
        std::cerr << "Error loading shader!" << std::endl;
    }
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    int maxWidth = desktopMode.width;
    int maxHeight = desktopMode.height;
    mBlurShader->setUniform("resolution", sf::Vector2f(maxWidth, maxHeight));
    mBlurShader->setUniform("radius", 5.0f);

    mGlowShader = std::make_shared<sf::Shader>();
    if (!mGlowShader->loadFromFile("shaders/glowShader.frag", sf::Shader::Fragment)) {
        std::cerr << "Failed to load shader!" << std::endl;
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
    mMapInitialized = true;

    initEnemiesSprites();
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
        sf::Vector2f targetPosition = polarToCartesian(currentAngle, distanceFromCharacter, sf::Vector2f(mCharacterCircle.getPosition().x + mCharacterCircle.getRadius(), mCharacterCircle.getPosition().y + mCharacterCircle.getRadius()));  // Convert polar coordinates to Cartesian
        mTarget[i] = std::make_shared<Target>(Target(targetPosition));

        mTarget[i]->mButton->setOnClick([this,i]() {
            GameState::getInstance().setEnemy(mEnemy[i]);
            screenManager.switchScreen("Loch");
            screenManager.getCurrentScreen()->updateGameState();
            });
    }
}

void Map::initEnemiesSprites()
{
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    int maxWidth = desktopMode.width;
    int maxHeight = desktopMode.height;

    // 10 20 40 20 10
    // 3 9 19 38 19 9 3

    for (int i = 0; i < 6; i++)
    {
        // Generate a random number between 0 and 100
        int roll = GameState::getInstance().rollRandomNumber(0,100);
        int rollRange = 0;
        int enemyLevel = 0;
        
        // Define ranges
        if (roll < 10) {
            std::cout << "Selected range: [0-10)" << std::endl;
            rollRange = -2;
        }
        else if (roll < 30) { // 10 + 20 = 30
            std::cout << "Selected range: [10-30)" << std::endl;
            rollRange = -1;
        }
        else if (roll < 70) { // 30 + 40 = 70
            std::cout << "Selected range: [30-70)" << std::endl;
            rollRange = 0;
        }
        else if (roll < 90) { // 70 + 20 = 90
            std::cout << "Selected range: [70-90)" << std::endl;
            rollRange = 1;
        }
        else {
            std::cout << "Selected range: [90-100]" << std::endl;
            rollRange = 2;
        }

        if ((GameState::getInstance().getDungeonLevel() + rollRange) < 0)
        {
            enemyLevel = 0;
        }
        else
        {
            enemyLevel = GameState::getInstance().getDungeonLevel() + rollRange;
        }

        mEnemy[i] = std::make_shared<Enemy>();
        mEnemy[i] = mEnemyLoader.getRandomEnemyByLevel(enemyLevel);
        if (enemyTexture[i].loadFromFile(mEnemy[i]->getIconPath())) {
            enemySprite[i].setTexture(enemyTexture[i]);

            // Calculate the scale to ensure the icon fits within the button
            //float iconScale = aScale;          // Choose the smaller scale to keep proportions
            //enemySprite[i].setScale(iconScale, iconScale);

            // Get the scaled icon's size
            sf::FloatRect iconBounds = enemySprite[i].getGlobalBounds();

            if (i < 3)
            {
                enemySprite[i].setPosition(
                    maxWidth - iconBounds.width,   // Button's horizontal center
                    maxHeight - iconBounds.height    // Button's vertical center
                );
            }

            else
            {
                enemySprite[i].setPosition(
                    0,   // Button's horizontal center
                    maxHeight - iconBounds.height    // Button's vertical center
                );
            }
        }
        else {
            std::cerr << "Failed to load icon texture\n";
        }
        mTarget[i]->mText->getText().setOutlineThickness(1); // Positive value for outline
        if (mEnemy[i]->getLevel() > GameState::getInstance().getDungeonLevel())
        {
            mTarget[i]->mText->setText("SUPERIOR OPPONENT");
            mTarget[i]->mText->getText().setOutlineColor(sf::Color::Red);
        }
        else if (mEnemy[i]->getLevel() == GameState::getInstance().getDungeonLevel())
        {
            mTarget[i]->mText->setText("WORTHY OPPONENT");
            mTarget[i]->mText->getText().setOutlineColor(sf::Color::Yellow);
        }
        else
        {
            mTarget[i]->mText->setText("INFERIOR OPPONENT");
            mTarget[i]->mText->getText().setOutlineColor(sf::Color::Green);
        }
    }
}

// Function to convert polar coordinates to Cartesian coordinates
sf::Vector2f Map::polarToCartesian(float angleInDegrees, float radius, const sf::Vector2f & origin) {
    float angleInRadians = angleInDegrees * PI / 180.f;
    float x = radius * std::cos(angleInRadians);
    float y = radius * std::sin(angleInRadians);
    return sf::Vector2f(origin.x + x, origin.y + y);
}