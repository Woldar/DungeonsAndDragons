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
        mIconPath = "assets/classes/WarriorMale.png";
        mSpecialAbilities = "Zdolnosci Specjalne:\n\n- Podczas walki rzucasz dwiema koscmi i wybierasz wynik\n- Mozesz korzystac z dwoch broni jednoczesnie";
        mStartingStatistics = "Zdrowie: 100\nSzczescie : 1\nZloto : 1";
    }
};