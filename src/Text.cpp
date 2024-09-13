#include "Text.h"

Text::Text()
{
    initFont();
    //initText();
}

Text::~Text()
{

}


std::string Text::wrapText(const std::string& str, sf::Font& font, unsigned int characterSize, float maxWidth) {
    std::istringstream words(str);  // Stream s³ów z tekstu
    std::string word;
    std::string result;
    std::string line;

    sf::Text text;  // Tymczasowy obiekt sf::Text do mierzenia rozmiarów
    text.setFont(font);
    text.setCharacterSize(characterSize);

    while (words >> word) {
        sf::Text testLine = text;  // Skopiuj obiekt sf::Text
        testLine.setString(line + word + " ");  // Przetestuj aktualn¹ liniê z dodanym s³owem

        // Jeœli dodanie s³owa przekroczy szerokoœæ okna, dodaj now¹ liniê
        if (testLine.getLocalBounds().width > maxWidth) {
            result += line + "\n";  // Dodaj istniej¹c¹ liniê do wyniku z now¹ lini¹
            line = word + " ";      // Rozpocznij now¹ liniê
        }
        else {
            line += word + " ";  // Kontynuuj dodawanie s³ów do bie¿¹cej linii
        }
    }

    result += line;  // Dodaj ostatni¹ liniê

    return result;
}

void Text::initText(std::string aString,bool aAnimate, int aSize, std::string aPlacement)
{
    mAnimate = aAnimate;
    state = false;
    std::string temporaryString = aString;
    mPlacement = aPlacement;
    int mCharacterSize = aSize;

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    this->maxWidth = desktopMode.width - 40;
    this->maxHeight = desktopMode.height - 40;
    this->wrappedText = wrapText(temporaryString, font, mCharacterSize, maxWidth); //size of monitor
    this->textLength = wrappedText.length();

    this->mText.setFont(font);
    this->mText.setCharacterSize(mCharacterSize);  // Text size
    this->mText.setFillColor(sf::Color::White);
    this->mText.setStyle(sf::Text::Regular);
}

int Text::initFont()
{
    if (!font.loadFromFile("assets/fonts/MoriaCitadel.ttf"))  // Adjust the path to where your font is located
    {
        std::cerr << "Error loading font!" << std::endl;
        return -1;
    }
}

sf::Text Text::getText()
{
    return this->mText;
}

void Text::setText(std::string aText)
{
    mText.setString(aText);
    this->wrappedText = "";
    this->displayedText = "";
}

void Text::update()
{
    if (mAnimate == true)
    {
        if (clock.getElapsedTime().asSeconds() > typingSpeed && displayedText.length() < textLength)
        {
            displayedText += wrappedText[displayedText.length()];
            mText.setString(displayedText);
            clock.restart();  // Restart the clock for the next letter
        }
        place();
        if (displayedText.length() == wrappedText.length())
        {
            state = true;
        }
    }
    else
    {
        displayedText = wrappedText;
        mText.setString(displayedText);
        state = true;
        place();
    }
}

void Text::place()
{
    if (mPlacement == "Middle")
    {
        sf::FloatRect textBounds = mText.getLocalBounds();
        float centerX = (maxWidth - textBounds.width) / 2 - textBounds.left;
        float centerY = (maxHeight - textBounds.height) / 2 - textBounds.top;
        mText.setPosition(centerX, centerY);
    }
    if (mPlacement == "RightDownCorner")
    {
        sf::FloatRect textBounds = mText.getLocalBounds();
        float rightX = maxWidth - textBounds.width - textBounds.left;  // Position for right alignment
        float bottomY = maxHeight - textBounds.height - textBounds.top; // Position for bottom alignment
        mText.setPosition(rightX, bottomY);
    }

}