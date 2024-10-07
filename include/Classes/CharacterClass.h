// CharacterClass.h
#pragma once
#include <string>
#include <vector>
#include <format>  // For std::format (C++20)
#include "Card.h"

class CharacterClass {
public:
    CharacterClass(const std::string& name) : mName(name) {}

    virtual ~CharacterClass() = default;

    std::string getName() const { return mName; }
    std::string getIconPath() const { return mIconPath; }
    std::string getSpecialAbilities() const { return mSpecialAbilities; }
    std::string getStartingStatistics() const { return mStartingStatistics; }
    std::string getStartingResistances() const { return mStartingResistances; }

    // Return the deck of cards for this character class
    const std::vector<Card>& getDeck() const { return mDeck; }

protected:
    std::string mName;
    std::vector<Card> mDeck;  // Deck of cards specific to the character class
    std::string mIconPath;
    std::string mSpecialAbilities;
    std::string mStartingStatistics;
    std::string mStartingResistances;
    int mHealth;
    int mLuck;
    int mGold;

    float mResistanceBleed;
    float mResistanceBlight;
    float mResistanceStun;
    float mResistanceDebuff;
    float mReistanceMark;
    float mReistanceFire;
    float mResistanceFrost;
    float mResistanceShadow;
};