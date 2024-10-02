// Player.h
#pragma once
#include <memory>
#include "CharacterClass.h"

class Player {
public:
    // Constructor accepting a unique_ptr to CharacterClass
    Player(const std::string& playerName, std::unique_ptr<CharacterClass> characterClass)
        : mPlayerName(playerName), mCharacterClass(std::move(characterClass)) {}

    // Get the player's name
    std::string getPlayerName() const { return mPlayerName; }

    // Get the player's character class name
    std::string getClassName() const { return mCharacterClass->getName(); }

    // Get the deck from the player's class
    const std::vector<Card>& getDeck() const { return mCharacterClass->getDeck(); }

private:
    std::string mPlayerName;
    std::unique_ptr<CharacterClass> mCharacterClass;  // Player's selected character class
};