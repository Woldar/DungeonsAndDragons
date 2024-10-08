#include "Screens/Cutscene.h"


Cutscene::Cutscene(ScreenManager& screenManager) : screenManager(screenManager)
{
	initMusic();
	initText();
}
Cutscene::~Cutscene()
{

}

void Cutscene::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
	if (mText[0].state == true)
	{
		// Check if the event is a key press
		if (event.type == sf::Event::KeyPressed) {
				// Handle the Enter key press
				std::cout << "Switching to CharacterSelection Screen!" << std::endl;
				screenManager.switchScreen("CharacterSelection");

				// Implement specific logic here, like changing screens
				// screenManager.pushScreen(std::make_unique<GameScreen>());
		}
		else if (event.type == sf::Event::MouseButtonReleased)
		{
			// Handle the Enter key press
			std::cout << "Switching to CharacterSelection Screen!" << std::endl;
			screenManager.switchScreen("CharacterSelection");
		}
	}
}

void Cutscene::update(float deltaTime)
{
	mText[0].update();
	mText[1].update();
}

void Cutscene::draw(sf::RenderWindow& target)
{
	target.draw(mText[0].getText());
	if (mText[0].state == true)
	{
		target.draw(mText[1].getText());
	}

}

int Cutscene::initMusic()
{
	if (!music.openFromFile("assets/music/male-heavy-breathing-67325.mp3"))
		return -1; // error
	//music.play();
	music.setLoop(true);

	//MusicManager::getInstance().playMusic("assets/music/male-heavy-breathing-67325.mp3");
	//MusicManager::getInstance().pauseMusic();
	//return 0;
}

void Cutscene::initText()
{
	mText[0].initText("Budzisz sie w ciemnym pomieszczeniu, nie wiesz jak sie tu znalazles.. niczego nie pamietasz..", true, 46, "LeftSide");
	mText[1].initText("Nacisnij dowolny klawisz by kontynuowac", false, 24,"RightDownCorner");
}