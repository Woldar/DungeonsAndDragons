#include "Screens/Cutscene.h"


Cutscene::Cutscene(ScreenManager& screenManager, std::string aView) : screenManager(screenManager)
{
	mView = aView;
	initMusic();
	initText();
}
Cutscene::~Cutscene()
{

}

void Cutscene::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
	if (mText[0]->state == true)
	{
		// Check if the event is a key press
		if (event.type == sf::Event::KeyPressed) {
			// To clear the objects
			for (int i = 0; i < 2; ++i) {
				mText[i].reset();  // Reset smart pointer, freeing the memory
			}

			if (mView == "Start")
			{
				std::cout << "Switching to CharacterSelection Screen!" << std::endl;
				screenManager.switchScreen("CharacterSelection");
			}
			else if (mView == "Wakeup")
			{
				std::cout << "Switching to CharacterSelection Screen!" << std::endl;
				screenManager.switchScreen("Map");
			}

		}
		else if (event.type == sf::Event::MouseButtonReleased)
		{
			// To clear the objects
			for (int i = 0; i < 2; ++i) {
				mText[i].reset();  // Reset smart pointer, freeing the memory
			}

			if (mView == "Start")
			{
				std::cout << "Switching to CharacterSelection Screen!" << std::endl;
				screenManager.switchScreen("CharacterSelection");
			}
			else if (mView == "Wakeup")
			{
				std::cout << "Switching to Loch Screen!" << std::endl;
				screenManager.switchScreen("Map");
			}
		}
	}
}

void Cutscene::update(float deltaTime)
{
	mText[0]->update();
	mText[1]->update();
}

void Cutscene::draw(sf::RenderWindow& target)
{
	target.draw(mText[0]->getText());
	if (mText[0]->state == true)
	{
		target.draw(mText[1]->getText());
	}
	target.draw(icon);
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
	mText[0] = std::make_unique<Text>();
	mText[1] = std::make_unique<Text>();

	if (mView == "Start")
	{
		mText[0]->initText("Budzisz sie w ciemnym pomieszczeniu, nie wiesz jak sie tu znalazles.. niczego nie pamietasz..", true, 46, "LeftSide");
		mText[1]->initText("Nacisnij dowolny klawisz by kontynuowac", false, 24, "RightDownCorner");
	}
	else if (mView == "Wakeup")
	{
		mText[0]->initText("Czujesz niewyobrazalny bol.. na Twojej skorze wypalono pieczec, masz wrazenie, ze na Ciebie wplywa i prowadzi w jakims kierunku..", true, 46, "LeftSide");
		mText[1]->initText("Nacisnij dowolny klawisz by kontynuowac", false, 24, "RightDownCorner");
	}
	else
	{
		mText[0]->initText("Error - Wrong screen mView", true, 46, "LeftSide");
	}

}

void Cutscene::initIcon()
{
	if (mView == "Wakeup")
	{
		// Optionally scale the background to fit the window size
		sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
		int maxWidth = desktopMode.width;
		int maxHeight = desktopMode.height;

		if (iconTexture.loadFromFile("assets/pictures/sigil.jpg")) {
			icon.setTexture(iconTexture);

			// Calculate the scale to ensure the icon fits within the button
			float iconScaleX = maxWidth / iconTexture.getSize().x * 0.4f;  // 50% of button width
			float iconScaleY = maxHeight / iconTexture.getSize().y * 0.4f;  // 50% of button height
			float iconScale = std::min(iconScaleX, iconScaleY);          // Choose the smaller scale to keep proportions
			icon.setScale(iconScale, iconScale);

			// Get the scaled icon's size
			sf::FloatRect iconBounds = icon.getGlobalBounds();

			// Position the icon in the center of the button
			icon.setPosition(
				maxWidth / 2.0f - (0.5f * iconBounds.width),   // Button's horizontal center
				maxHeight / 4.0f - (0.5f * iconBounds.height)    // Button's vertical center
			);
		}
		else {
			std::cerr << "Failed to load icon texture\n";
		}
	}

}
