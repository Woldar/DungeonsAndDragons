// Player.h
#pragma once
#include <memory>
#include "CharacterClass.h"
#include "PlayerHand.h"
#include "EffectTarget.h"
#include "Deck.h"

class Player : public EffectTarget {
public:
    // Constructor accepting a unique_ptr to CharacterClass
    Player()
    {
        mPlayerHand = std::make_shared<PlayerHand>();
        mDeck = std::make_shared<Deck>();;
    }

    // Get the player's name
    std::string getPlayerName() const { return mPlayerName; }

    // Get the player's character class
    std::shared_ptr<CharacterClass> getClass() const { return mCharacterClass; }

    // Set the player's character class
    void setClass(CharacterClass aCharacterClass)
    {
        mCharacterClass = std::make_unique<CharacterClass>(aCharacterClass);
        initDeck();

        mHealth = mCharacterClass->getHealth();
        mWill = mCharacterClass->getWill();
        mGold = mCharacterClass->getGold();

        mResistanceBleed = mCharacterClass->getResistanceBleed();
        mResistanceBlight = mCharacterClass->getResistanceBlight();
        mResistanceStun = mCharacterClass->getResistanceStun();
        mResistanceDebuff = mCharacterClass->getResistanceDebuff();
        mReistanceMark = mCharacterClass->getReistanceMark();
        mReistanceFire = mCharacterClass->getReistanceFire();
        mResistanceFrost = mCharacterClass->getResistanceFrost();
        mResistanceShadow = mCharacterClass->getResistanceShadow();
    }

    // Get the deck from the player's class
    std::shared_ptr <Deck> getDeck() const { return mDeck; }

    int getWill() { return mWill; }
    void setWill(int aWill)
    {
        mWill = aWill;
        mHealth -= 1;
    }

    std::string getWillString() const { return std::to_string(mWill); }

    void dealDamage(int amount) override {
        mHealth -= amount;
        if (mHealth < 0) mHealth = 0;
    }

    void addArmor(int amount) override {
        //mArmor += amount;
    }

    int getHealth() const { return mHealth; }
    //int getArmor() const { return mArmor; }

    void initDeck()
    {
        mDeck = mCharacterClass->getClassCards();
    }

private:
    std::string mPlayerName;
    std::shared_ptr<CharacterClass> mCharacterClass;  // Player's selected character class
    std::shared_ptr <PlayerHand> mPlayerHand;
    std::shared_ptr <Deck> mDeck;

protected:
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