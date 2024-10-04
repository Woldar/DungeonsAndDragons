// Mage.h
#pragma once
#include "CharacterClass.h"

class Mage : public CharacterClass {
public:
    Mage() : CharacterClass("Druid") {
        // Add cards to the Mage's deck
        mDeck.push_back(Card("Plague", "Cast a powerful fireball at the enemy."));
        mDeck.push_back(Card("Heal", "Freeze the enemy with an ice blast."));
        mDeck.push_back(Card("Disease", "Protect yourself with a magical shield."));
        mIconPath = "assets/classes/DruidMale.png";
        mSpecialAbilities = "Zdolnosci Specjalne:\n\n- Gdy dotrzesz do lasu mo¿esz rzucic zaklecia\n- Mozesz dobieraæ swoj charakter do swoich potrzeb\n\n";
        mStartingStatistics = "Zdrowie: 80\nSzczescie : 4\nZloto : 1";
    }
};