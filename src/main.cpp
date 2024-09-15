#include "Game.h"

int main()
{
    //Initialize random seed
    srand(static_cast<unsigned>(time(0)));

    //Initialize objects
    Game game;

    //Game loop
    while (game.window->isOpen())
    {
        sf::Event event;
        while (game.window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                game.window->close();

            Screen* currentScreen = game.screenManager.getCurrentScreen();
            if (currentScreen) {
                currentScreen->handleEvent(event, *game.window);
            }
        }

        float deltaTime = game.clock.restart().asSeconds();

        Screen* currentScreen = game.screenManager.getCurrentScreen();
        if (currentScreen) {
            currentScreen->update(deltaTime);
        }

        game.window->clear();
        if (currentScreen) {
            currentScreen->draw(*game.window);
        }
        game.window->display();
    }

    //while (window.isOpen())
    //{
    //    for (auto event = sf::Event{}; window.pollEvent(event);)
    //    {
    //        if (event.type == sf::Event::Closed)
    //        {
    //            window.close();
    //        }
    //    }

    //    // 8. Update the text with a typing effect
    //    if (clock.getElapsedTime().asSeconds() > typingSpeed && displayedText.length() < textLength)
    //    {
    //        displayedText += wrappedText[displayedText.length()];
    //        text.setString(displayedText);
    //        clock.restart();  // Restart the clock for the next letter
    //    }

    //    // 9. Center the text
    //    sf::FloatRect textBounds = text.getLocalBounds();
    //    float centerX = (window.getSize().x - textBounds.width) / 2 - textBounds.left;
    //    float centerY = (window.getSize().y - textBounds.height) / 2 - textBounds.top;
    //    text.setPosition(centerX, centerY);

    //    window.clear();
    //    window.draw(text);
    //    window.display();

    //    //std::unique_ptr<Loch> mLoch;
    //    //mLoch = std::make_unique<Loch>();
    //    //mLoch->generujLoch();
    //    //system("cls");
    //    //mLoch->start();
    //    ////Loch.walka();
    //}
	return (0);
}
