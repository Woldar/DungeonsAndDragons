#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <random>
#include "Card.h"
#include "PlayerHand.h"

class Deck {
public:
    Deck();

    // Adds a card to the deck
    void addCard(std::shared_ptr<Card> card);

    // Shuffles the deck
    void shuffle();

    // Draws a card and adds it to the player's hand
    void drawCard(PlayerHand& hand);

    // Resets the deck (clears all cards)
    void reset();

    // Displays the deck (for debugging purposes)
    void displayDeck() const;

    // Returns the size of the deck
    size_t getDeckSize() const;

private:
    std::vector<std::shared_ptr<Card>> mDeck;
};
