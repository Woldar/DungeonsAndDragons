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
	if (event.type == sf::Event::MouseButtonReleased) {
		for (auto& button : mClassesButtons) {
			if (button->checkClickBool(event, window))
			{
				const auto& classes = classManager.getAvailableClasses();
				for (auto& classCharacter : classes)
				{
					if (classCharacter->getName() == button->text.getString())
					{
						mExtendedClassView->setIcon(classCharacter->getIconPath());
						mExtendedClassView->textSpecialAbilities.setString(classCharacter->getSpecialAbilities());
						mExtendedClassView->textStartingStatistics.setString(classCharacter->getStartingStatistics());
						mExtendedClassView->setTextsPositions();
					}
				}
			}
		}
	}
}

void CharacterSelection::update(float deltaTime)
{
}

void CharacterSelection::draw(sf::RenderWindow& target)
{
	if (mExtendedView == false)
	{
		for (auto& button : mClassesButtons) {
			button->draw(target);
		}
	}
	else
	{
		for (auto& button : mClassesButtons) {
			button->mIsActive = false;
		}
		
		mExtendedClassView->draw(target);
	}
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
	sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
	int maxWidth = desktopMode.width;
	int maxHeight = desktopMode.height;
	mExtendedView = false;

	mExtendedClassView = std::make_unique<ClassTab>(sf::Vector2f(maxWidth * 0.9,maxHeight * 0.9), sf::Vector2f(0.05 * maxWidth,0.05 * maxHeight), "Class info");
	mExtendedClassView->shape.setOutlineColor(sf::Color::White); // Ensure shape is publicly accessible
	mExtendedClassView->shape.setOutlineThickness(3.0f); // Adjust this thickness as needed

	const auto& classes = classManager.getAvailableClasses();
	// Define button size (same as a card size: 240px x 336px)
	sf::Vector2f buttonSize(240.0f, 336.0f);
	float padding = 30.0f;

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
			mClassesButtons.push_back(std::make_unique<Button>(buttonSize, sf::Vector2f(x, y), classes[i]->getName()));

			// Set the outline color and thickness of the button
			mClassesButtons.back()->shape.setOutlineColor(sf::Color::White); // Ensure shape is publicly accessible
			mClassesButtons.back()->shape.setOutlineThickness(3.0f); // Adjust this thickness as needed

			mClassesButtons.back()->glowEffect.setFillColor(sf::Color::White); // White glow, semi-transparent
			mClassesButtons.back()->mTextColorMouseOver = sf::Color::Black;
			// Set onClick event for the button
			mClassesButtons.back()->setOnClick([this]() {
				mExtendedView = true;
				});
		}
	}
}