#include "Screens/CharacterSelection.h"

CharacterSelection::CharacterSelection(ScreenManager& screenManager) : screenManager(screenManager)
{
	initMusic();
	initClassesRectangles();
}
CharacterSelection::~CharacterSelection()
{

}

void CharacterSelection::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
	//if (mText[0].state == true)
	//{
	//	// Check if the event is a key press
	//	if (event.type == sf::Event::KeyPressed) {
	//			// Handle the Enter key press
	//			std::cout << "Switching to Loch Screen!" << std::endl;
	//			screenManager.switchScreen("Loch");

	//			// Implement specific logic here, like changing screens
	//			// screenManager.pushScreen(std::make_unique<GameScreen>());
	//	}
	//	else if (event.type == sf::Event::MouseButtonReleased)
	//	{
	//		// Handle the Enter key press
	//		std::cout << "Switching to Loch Screen!" << std::endl;
	//		screenManager.switchScreen("Loch");
	//	}
	//}
}

void CharacterSelection::update(float deltaTime)
{
}

void CharacterSelection::draw(sf::RenderWindow& target)
{
	for (auto& button : mButtons) {
		button->draw(target);
	}

	//mButtons->draw(target);
}

int CharacterSelection::initMusic()
{
	if (!music.openFromFile("assets/music/male-heavy-breathing-67325.mp3"))
		return -1; // error
	//music.play();
	music.setLoop(true);

	//MusicManager::getInstance().playMusic("assets/music/male-heavy-breathing-67325.mp3");
	//MusicManager::getInstance().pauseMusic();
	//return 0;
}

void CharacterSelection::initText()
{

}

void CharacterSelection::initClassesRectangles()
{
	const auto& classes = classManager.getAvailableClasses();
	sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
	int maxWidth = desktopMode.width;
	int maxHeight = desktopMode.height;

	// Define button size (same as a card size: 240px x 336px)
	sf::Vector2f buttonSize(240.0f, 336.0f);
	float padding = 20.0f;

	// Calculate how many buttons fit per row
	size_t buttonsPerRow = maxWidth / (buttonSize.x + padding);
	size_t numClasses = classes.size(); // Get the total number of classes

	if (numClasses > 0) { // Check if there are any classes to display
		// Calculate the width of buttons including padding
		float buttonWidthWithPadding = buttonSize.x + padding;

		// Calculate the total number of rows needed based on the number of classes
		size_t totalRows = (numClasses + buttonsPerRow - 1) / buttonsPerRow; // Total number of rows needed
		float totalHeight = totalRows * (buttonSize.y + padding) - padding; // Total height of all buttons
		float startY = (maxHeight - totalHeight) / 2.0f; // Centering vertically

		// Calculate total width of all buttons in the first row
		size_t actualButtonsInFirstRow = std::min(numClasses, buttonsPerRow); // How many buttons can fit in the first row
		float totalWidth = actualButtonsInFirstRow * buttonWidthWithPadding - padding; // Total width of buttons in the first row

		// Calculate starting x position for centering horizontally
		float startX = (maxWidth - totalWidth) / 2.0f; // Centering horizontally

		// Start creating buttons
		for (size_t i = 0; i < numClasses; ++i) {
			size_t row = i / buttonsPerRow; // Determine the current row
			size_t col = i % buttonsPerRow; // Determine the current column

			// Calculate button position
			float x = startX + col * buttonWidthWithPadding; // Horizontal position
			float y = startY + row * (buttonSize.y + padding); // Vertical position

			// Create button
			mButtons.push_back(std::make_unique<Button>(buttonSize, sf::Vector2f(x, y), classes[i]->getName()));

			// Set the outline color and thickness of the button
			mButtons.back()->shape.setOutlineColor(sf::Color::White); // Ensure shape is publicly accessible
			mButtons.back()->shape.setOutlineThickness(3.0f); // Adjust this thickness as needed

			// Set onClick event for the button
			mButtons.back()->setOnClick([this]() {
				screenManager.switchScreen("Cutscene");
				});
		}
	}
}