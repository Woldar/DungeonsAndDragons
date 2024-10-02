// CharacterClass.h
#pragma once
#include <string>
#include <vector>
#include "Card.h"

class CharacterClass {
public:
    CharacterClass(const std::string& name) : mName(name) {}

    virtual ~CharacterClass() = default;

    std::string getName() const { return mName; }

    // Return the deck of cards for this character class
    const std::vector<Card>& getDeck() const { return mDeck; }

protected:
    std::string mName;
    std::vector<Card> mDeck;  // Deck of cards specific to the character class
};