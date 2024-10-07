// Mage.h
#pragma once
#include "CharacterClass.h"

class Druid : public CharacterClass {
public:
    Druid() : CharacterClass("Druid") {
        // Add cards to the Mage's deck
        mDeck.push_back(Card("Plague", "Cast a powerful fireball at the enemy."));
        mDeck.push_back(Card("Heal", "Freeze the enemy with an ice blast."));
        mDeck.push_back(Card("Disease", "Protect yourself with a magical shield."));

        mHealth = 80;
        mLuck = 4;
        mGold = 1;

        mResistanceBleed = 0;
        mResistanceBlight = 20;
        mResistanceStun = 20;
        mResistanceDebuff = 20;
        mReistanceMark = 0;
        mReistanceFire = -10;
        mResistanceFrost = 10;
        mResistanceShadow = -10;

        mIconPath = "assets/classes/DruidMale.png";
        mSpecialAbilities = "Zdolnosci Specjalne:\n- Gdy dotrzesz do lasu mozesz rzucic zaklecia\n- Mozesz dobierac swoj charakter do swoich potrzeb";
        mStartingStatistics = std::format(
            "Zdrowie:    {:>3}\n"
            "Szczescie:  {:>3}\n"
            "Zloto:      {:>3}",
            mHealth, mLuck, mGold);
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