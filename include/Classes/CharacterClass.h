// CharacterClass.h
#pragma once
#include <string>
#include <vector>
#include <format>  // For std::format (C++20)
#include "Objects/Card.h"
#include "Deck.h"

class CharacterClass {
public:
    CharacterClass() 
    {
        mDeck = std::make_shared<Deck>();
    };
    CharacterClass(const std::string& name) : mName(name) 
    {
        mDeck = std::make_shared<Deck>();
    }

    virtual ~CharacterClass() = default;

    std::string getName() const { return mName; }
    std::string getIconPath() const { return mIconPath; }
    int getHealth() const { return mHealth; }
    int getWill() const { return mWill; }
    int getGold() const { return mGold; }

    float getResistanceBleed() const { return mResistanceBleed; }
    float getResistanceBlight() const { return mResistanceBlight; }
    float getResistanceStun() const { return mResistanceStun; }
    float getResistanceDebuff() const{ return mResistanceDebuff; }
    float getReistanceMark() const { return mReistanceMark; }
    float getReistanceFire() const{ return mReistanceFire; }
    float getResistanceFrost() const{ return mResistanceFrost; }
    float getResistanceShadow() const{ return mResistanceShadow; }

    std::string getWillString() const { return std::to_string(mWill); }
    std::string getSpecialAbilities() const { return mSpecialAbilities; }
    std::string getStartingStatistics() const { return mStartingStatistics; }
    std::string getStartingResistances() const { return mStartingResistances; }
    std::shared_ptr<Deck> getClassCards() { return mDeck; }

protected:
    std::shared_ptr<Deck> mDeck;
    std::string mName;
    std::string mIconPath;
    std::string mSpecialAbilities;
    std::string mStartingStatistics;
    std::string mStartingResistances;
    int mHealth;
    int mWill;
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