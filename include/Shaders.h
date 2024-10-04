#pragma once

inline void dimmingShader(std::shared_ptr<sf::Shader> dimmingShader, std::shared_ptr<Button> mButton, sf::RenderWindow& target, sf::Sprite backgroundSprite)
{
	// Get the size of the window to calculate the flipped Y-axis
	float windowHeight = target.getSize().y;

	sf::Vector2f exitButtonCenter = mButton->getCenter();
	// Flip the y-axis coordinate
	exitButtonCenter.y = windowHeight - exitButtonCenter.y;
	dimmingShader->setUniform("buttonCenter", exitButtonCenter);
	dimmingShader->setUniform("buttonRadius", (mButton->mSize.x + mButton->mSize.y) / 8);

	// Set the screen size for the shader
	dimmingShader->setUniform("screenSize", sf::Vector2f(target.getSize().x, target.getSize().y));
	// Set the button radius (optional, adjust based on your button size)

	dimmingShader->setUniform("maxDimFactor", 0.99f);              // Maximum dimming factor (e.g., 70% dimming)

	// Bind the texture to the shader
	dimmingShader->setUniform("texture", sf::Shader::CurrentTexture);  // Bind the background texture

	// Draw the background with the shader
	sf::RenderStates states;
	states.shader = dimmingShader.get();  // Apply the shader
	target.draw(backgroundSprite, states);  // Draw the background with the shader applied

	mButton->draw(target);
}

inline void brighteningShader(std::shared_ptr<sf::Shader> brighteningShader, std::shared_ptr<Button> mButton, sf::RenderWindow& target, sf::Sprite backgroundSprite)
{
	// Get the size of the window to calculate the flipped Y-axis
	float windowHeight = target.getSize().y;

	sf::Vector2f playButtonCenter = mButton->getCenter();
	// Flip the y-axis coordinate
	playButtonCenter.y = windowHeight - playButtonCenter.y;
	brighteningShader->setUniform("buttonCenter", playButtonCenter);
	brighteningShader->setUniform("buttonRadius", (mButton->mSize.x + mButton->mSize.y));

	// Set the screen size for the shader
	brighteningShader->setUniform("screenSize", sf::Vector2f(target.getSize().x, target.getSize().y));
	// Set the button radius (optional, adjust based on your button size)

	brighteningShader->setUniform("maxBrightFactor", 2.0f);              // Maximum brightening factor (e.g., 70% dimming)

	// Bind the texture to the shader
	brighteningShader->setUniform("texture", sf::Shader::CurrentTexture);  // Bind the background texture

	// Draw the background with the shader
	sf::RenderStates states;
	states.shader = brighteningShader.get();  // Apply the shader
	target.draw(backgroundSprite, states);  // Draw the background with the shader applied

	mButton->draw(target);
}

inline void dimmingShader(sf::Shader& dimmingShader, sf::RenderWindow& target, sf::Sprite iconSprite)
{
	sf::Vector2f iconCenter = { iconSprite.getGlobalBounds().getPosition().x + 0.5f * iconSprite.getGlobalBounds().getSize().x, iconSprite.getGlobalBounds().getPosition().y + 0.5f * iconSprite.getGlobalBounds().getSize().y };
	// Flip the y-axis coordinate
	//iconCenter.y = windowHeight - iconCenter.y;
	dimmingShader.setUniform("buttonCenter", iconCenter);
	dimmingShader.setUniform("buttonRadius", (iconSprite.getGlobalBounds().getSize().x + iconSprite.getGlobalBounds().getSize().y) / 8);

	// Set the screen size for the shader
	dimmingShader.setUniform("screenSize", sf::Vector2f(target.getSize().x, target.getSize().y));
	// Set the button radius (optional, adjust based on your button size)

	dimmingShader.setUniform("maxDimFactor", 0.99f);              // Maximum dimming factor (e.g., 70% dimming)

	// Bind the texture to the shader
	dimmingShader.setUniform("texture", sf::Shader::CurrentTexture);  // Bind the background texture

	// Draw the background with the shader
	//sf::RenderStates states;
	//states.shader = &dimmingShader;  // Apply the shader
	//target.draw(backgroundSprite, states);  // Draw the background with the shader applied

	//aIcon->draw(target);
}

inline void brighteningShader(sf::Shader& brighteningShader, sf::RenderWindow& target, sf::Sprite iconSprite)
{
	sf::Vector2f iconCenter = iconSprite.getGlobalBounds().getPosition();
	// Flip the y-axis coordinate
	//iconCenter.y = windowHeight - iconCenter.y;
	brighteningShader.setUniform("buttonCenter", iconCenter);
	brighteningShader.setUniform("buttonRadius", (iconSprite.getGlobalBounds().getSize().x + iconSprite.getGlobalBounds().getSize().y) / 8);

	// Set the screen size for the shader
	brighteningShader.setUniform("screenSize", sf::Vector2f(target.getSize().x, target.getSize().y));
	// Set the button radius (optional, adjust based on your button size)

	brighteningShader.setUniform("maxBrightFactor", 2.0f);              // Maximum brightening factor (e.g., 70% dimming)

	// Bind the texture to the shader
	brighteningShader.setUniform("texture", sf::Shader::CurrentTexture);  // Bind the background texture

	// Draw the background with the shader
	//sf::RenderStates states;
	//states.shader = &brighteningShader;  // Apply the shader
	//target.draw(backgroundSprite, states);  // Draw the background with the shader applied

	//aIcon->draw(target);
}