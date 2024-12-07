#pragma once

#include <vector>
#include <memory>
#include "Objects/Card.h"
#include "EffectTarget.h"

class PlayerHand {
public:
    PlayerHand() = default;

    // Adds a card to the player's hand
    void addCard(std::shared_ptr<Card> card);

    // Removes a card from the player's hand by index
    void removeCard(size_t index);

    // Plays a card and applies its effect to the target
    void playCard(size_t index, EffectTarget& target);

    // Displays the hand (for now, simple console output)
    void displayHand() const;

    // Returns the number of cards in hand
    size_t getCardCount() const;

    //void dealDamage(int damage);  // Apply damage to an enemy

    //void addArmor(int armor);     // Increase player's armor

private:
    std::vector<std::shared_ptr<Card>> mHand;
};


