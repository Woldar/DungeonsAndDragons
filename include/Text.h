#pragma once

#include <string>
#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Text
{
public:
    Text();
    ~Text();
    sf::Text getText();
    void setText(std::string aText);
    void update();
    void initText(std::string aString, bool aAnimate, int aSize, std::string aPlacement);
    bool state;
    float mPadding = 10.0f;
private:
    sf::Text mText;
    sf::Font font;

    bool mAnimate;
    int maxWidth;
    int maxHeight;
    std::string mPlacement;
    std::string displayedText = "";
    std::string wrappedText;
    size_t textLength;
    float typingSpeed = 0.05f;  // Time between letters (in seconds)
    sf::Clock clock;  // Clock to measure time

    int initFont();

    std::string wrapText(const std::string& str, sf::Font& font, unsigned int characterSize, float maxWidth);
    void place();
};