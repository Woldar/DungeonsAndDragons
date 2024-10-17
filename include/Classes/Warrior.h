// Warrior.h
#pragma once
#include "CharacterClass.h"

class Warrior : public CharacterClass {
public:
    Warrior() : CharacterClass("Warrior") {
        // Add cards to the Warrior's deck
        mDeck.push_back(Card("Sword Strike", "A powerful strike with a sword."));
        mDeck.push_back(Card("Shield Bash", "Stun the enemy with a shield bash."));
        mDeck.push_back(Card("Battle Cry", "Increases attack power temporarily."));

        mHealth = 100;
        mWill = 1;
        mGold = 1;

        mResistanceBleed = 30;
        mResistanceBlight = 0;
        mResistanceStun = 30;
        mResistanceDebuff = 20;
        mReistanceMark = 30;
        mReistanceFire = -10;
        mResistanceFrost = -10;
        mResistanceShadow = -10;

        mIconPath = "assets/classes/WarriorMale.png";
        mSpecialAbilities = "Zdolnosci Specjalne:\n- Podczas walki rzucasz dwiema koscmi i wybierasz wynik\n- Mozesz korzystac z dwoch broni jednoczesnie\n\n";
        mStartingStatistics = std::format(
            "Zdrowie:    {:>3}\n"
            "Sila Woli:  {:>3}\n"
            "Zloto:      {:>3}",
            mHealth, mWill, mGold);
        // Format the string with fixed-width columns for alignment
        mStartingResistances = std::format(
            "Odpornosci:\n"
            "-Krwawienie : {:>3}%   -Uroki      : {:>3}%\n"
            "-Ogluszenie : {:>3}%   -Oslabienie : {:>3}%\n"
            "-Oznaczenie : {:>3}%   -Ogien      : {:>3}%\n"
            "-Mroz       : {:>3}%   -Mrok       : {:>3}%",
            mResistanceBleed, mResistanceBlight,
            mResistanceStun, mResistanceDebuff,
            mReistanceMark, mReistanceFire,
            mResistanceFrost, mResistanceShadow
        );
    }
};