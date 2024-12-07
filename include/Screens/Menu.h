#pragma once
#include "Text.h"
#include "Objects/Button.h"
#include "Screen.h"
#include "Managers/ScreenManager.h"
#include "Shaders.h"

#include <string>
#include <string.h>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Menu : public Screen
{
public:
	Menu(ScreenManager& screenManager);
	~Menu();

	void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
	void update(float deltaTime) override;
	void updateGameState() override;
	void draw(sf::RenderWindow& target) override;

	void pauseMusic() override{
		music.pause();
		playButtonSoundEffect.pause();
		exitButtonSoundEffect.pause();
	}

	void resumeMusic() override {
		music.play();
	}

	void resetScreen() override {

	}

	void setScreen(const std::string& aView) override {

	}
private:
	ScreenManager& screenManager;
	sf::Music music;
	sf::Music playButtonSoundEffect;
	sf::Music exitButtonSoundEffect;
	sf::Texture backgroundTexture; // Texture to hold the background image
	sf::Sprite backgroundSprite;   // Sprite to display the texture
	std::shared_ptr<sf::Shader> mDimmingShader; // Shader for screen dimming 
	std::shared_ptr<sf::Shader> mBrighteningShader; // Shader for screen brightning
	Text mText[2];
	std::shared_ptr<Button> mPlayButton;
	std::shared_ptr<Button> mExitButton;
	std::shared_ptr<Button> mSettingsButton;

	float backgroundAlpha;  // Control the fade effect for the background

	int initMusic();
	void initBackground();
	void initText();
	void initButtons();
	void initShader();
};
