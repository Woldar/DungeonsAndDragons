// Mage.h
#pragma once
#include "CharacterClass.h"

class Druid : public CharacterClass {
public:
    Druid() : CharacterClass("Druid") {
        // Add cards to the Mage's deck
        mDeck->addCard(std::make_shared<Card>("Plague", "Cast a powerful fireball at the enemy.", Card::CardType::DAMAGE, 5));
        mDeck->addCard(std::make_shared<Card>("Heal", "Freeze the enemy with an ice blast.", Card::CardType::ARMOR, 5));
        mDeck->addCard(std::make_shared<Card>("Disease", "Protect yourself with a magical shield.", Card::CardType::ARMOR, 5));

        mHealth = 80;
        mWill = 4;
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
            "Sila woli:  {:>3}\n"
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