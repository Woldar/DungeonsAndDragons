// Mage.h
#pragma once
#include "CharacterClass.h"

class Mage : public CharacterClass {
public:
    Mage() : CharacterClass("Mage") {
        // Add cards to the Mage's deck
        mDeck.push_back(Card("Fireball", "Cast a powerful fireball at the enemy."));
        mDeck.push_back(Card("Ice Blast", "Freeze the enemy with an ice blast."));
        mDeck.push_back(Card("Arcane Shield", "Protect yourself with a magical shield."));
        mIconPath = "assets/classes/MageMale.png";
    }
};