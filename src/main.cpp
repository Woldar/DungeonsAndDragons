#include "Game.h"

int main()
{
    //Initialize random seed
    srand(static_cast<unsigned>(time(0)));

    // Enable anti-aliasing (multisampling) via context settings
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;  // Use 8x antialiasing (or 4x for lower quality)

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
	return (0);
}