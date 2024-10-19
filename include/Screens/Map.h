#pragma once
#include "Text.h"
#include "Objects/Button.h"
#include "Screen.h"
#include "Managers/ScreenManager.h"
#include "Shaders.h"
#include "Dice.h"
//#include "Managers/MusicManager.h"

#include <string>
#include <string.h>
#include <iostream>
#include <cmath> // for sin, cos

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#define PI 3.14159265358979323846f

class Map : public Screen
{
public:
	Map(ScreenManager& screenManager);
	~Map();

	void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& target) override;

	void pauseMusic() override {
		music.pause();
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
	sf::Texture backgroundTexture; // Texture to hold the background image
	sf::Sprite backgroundSprite;   // Sprite to display the texture
	std::shared_ptr<sf::Shader> mDimmingShader; // Shader for screen dimming 
	std::shared_ptr<sf::Shader> mBrighteningShader; // Shader for screen brightning
    std::unique_ptr<Text> mText[2];
    Dice mDice;

	sf::CircleShape mCharacterCircle;  // Character is represented as a circle

	// Define a structure to represent a route to a place

	struct Target
	{
		sf::CircleShape place;   // Circle representing the place
        std::unique_ptr<sf::Texture> doorTexture;
        std::shared_ptr<Button> mButton;

		float progress = 0.f;    // Progress of the route (from 0 to 1)

		// Constructor with place initialization
        Target(const sf::Vector2f& endPosition)
        {

            // Initialize the CircleShape for the place
            place.setRadius(0);
            place.setFillColor(sf::Color::White);
            place.setPosition(endPosition);

            // Load the door texture
            doorTexture = std::make_unique<sf::Texture>();
            if (doorTexture->loadFromFile("assets/icons/DoorsClosed.png"))
            {
                // Get the texture size
                sf::Vector2f textureSize(doorTexture->getSize().x, doorTexture->getSize().y);

                // Calculate scale to fit the screen size (if needed)
                sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
                int maxWidth = desktopMode.width;
                int maxHeight = desktopMode.height;
                float scale = std::min(
                    static_cast<float>(maxWidth) / textureSize.x / 8.f,
                    static_cast<float>(maxHeight) / textureSize.y / 8.f
                );

                // Calculate the size of the button based on the texture and scale
                sf::Vector2f buttonSize(textureSize.x * scale, textureSize.y * scale);

                // Calculate the position so that the bottom-middle of the Button matches the center of the place
                sf::Vector2f buttonPosition(
                    endPosition.x - buttonSize.x / 2.f,    // Center the button horizontally at the place's position
                    endPosition.y - buttonSize.y           // Align the bottom of the button with the top of the place
                );

                // Create the Button with the calculated position and size
                mButton = std::make_shared<Button>(buttonSize, buttonPosition, "");

                // Set the texture as the icon of the Button and apply the scale
                mButton->setIcon("assets/icons/DoorsClosed.png", scale);
                //mButton->setSize(sf::Vector2f(textureSize.x * scale, textureSize.y * scale));
            }
        }

        // Function to draw a dashed route with horizontal then vertical movement
        void drawRoute(sf::RenderWindow& window, const sf::Vector2f& startPosition, float dashLength = 10.f, float gapLength = 5.f, float thickness = 3.f) {
            sf::Vector2f endPosition = place.getPosition(); // Adjust to center the place

            // Calculate current progress and draw two-stage dashed lines
            sf::Vector2f currentPosition = startPosition;

            // First stage: Horizontal movement to align with the target's x-coordinate
            if (progress < 0.5f) {
                float t = progress / 0.5f;  // Progress for the horizontal stage
                currentPosition.x = startPosition.x + t * (endPosition.x - startPosition.x);
                drawDashedLine(window, startPosition, currentPosition, dashLength, gapLength, thickness);
            }
            // Second stage: Vertical movement once x-coordinates are aligned
            else {
                currentPosition.x = endPosition.x;  // Lock the x position to target's x
                float t = (progress - 0.5f) / 0.5f;  // Progress for the vertical stage
                currentPosition.y = startPosition.y + t * (endPosition.y - startPosition.y);
                drawDashedLine(window, startPosition, sf::Vector2f(endPosition.x, startPosition.y), dashLength, gapLength, thickness);  // Draw horizontal dashed line
                drawDashedLine(window, sf::Vector2f(endPosition.x, startPosition.y), currentPosition, dashLength, gapLength, thickness);  // Draw vertical dashed line
            }
        }

        // Helper function to draw a dashed line between two points
        void drawDashedLine(sf::RenderWindow& window, const sf::Vector2f& start, const sf::Vector2f& end, float dashLength, float gapLength, float thickness) {
            sf::Vector2f delta = end - start;
            float totalDistance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
            sf::Vector2f direction = delta / totalDistance;  // Unit direction vector

            // Iterate over the length of the line, drawing dashes and gaps
            float currentLength = 0.f;
            bool drawingDash = true;

            while (currentLength < totalDistance) {
                float segmentLength = (drawingDash) ? dashLength : gapLength;
                if (currentLength + segmentLength > totalDistance) {
                    segmentLength = totalDistance - currentLength;  // Adjust last segment length if it exceeds total distance
                }

                if (drawingDash) {
                    sf::RectangleShape segment(sf::Vector2f(segmentLength, thickness));
                    segment.setFillColor(sf::Color::White);
                    segment.setPosition(start + direction * currentLength);
                    segment.setRotation(std::atan2(delta.y, delta.x) * 180.f / PI);  // Rotate to match the direction
                    window.draw(segment);
                }

                // Move to the next dash or gap
                currentLength += segmentLength;
                drawingDash = !drawingDash;  // Alternate between dash and gap
            }
        }

        // Update the progress of the route over time
        void update(float deltaTime, float speed = 0.5f) {
            if (progress < 1.f) {
                progress += speed * deltaTime;  // Increment progress based on time
            }
            if (progress > 1.f) {
                progress = 1.f;  // Cap the progress at 1 (full route drawn)
            }
        }
	};

    std::shared_ptr<Target> mTarget[6];

	float backgroundAlpha;  // Control the fade effect for the background

	int initMusic();
	void initBackground();
	void initText();
	void initButtons();
	void initShader();
	void initMap();
	void initTargets();

	sf::Vector2f polarToCartesian(float angleInDegrees, float radius, const sf::Vector2f& origin);
};