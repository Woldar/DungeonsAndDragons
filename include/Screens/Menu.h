#pragma once
#include "Text.h"
#include "Button.h"
#include "Screen.h"
#include "Managers/ScreenManager.h"
//#include "Managers/MusicManager.h"

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
	void draw(sf::RenderWindow& target) override;

	void pauseMusic() override{
		music.pause();
		playButtonSoundEffect.pause();
		exitButtonSoundEffect.pause();
	}

	void resumeMusic() override {
		music.play();
	}
private:
	ScreenManager& screenManager;
	sf::Music music;
	sf::Music playButtonSoundEffect;
	sf::Music exitButtonSoundEffect;
	sf::Texture backgroundTexture; // Texture to hold the background image
	sf::Sprite backgroundSprite;   // Sprite to display the texture
	std::unique_ptr<sf::Shader> dimmingShader; // Shader for screen dimming 
	std::unique_ptr<sf::Shader> brighteningShader; // Shader for screen brightning
	Text mText[2];
	std::unique_ptr<Button> mPlayButton;
	std::unique_ptr<Button> mExitButton;
	std::unique_ptr<Button> mSettingsButton;

	float backgroundAlpha;  // Control the fade effect for the background

	int initMusic();
	void initBackground();
	void initText();
	void initButtons();
	void initShader();
};
