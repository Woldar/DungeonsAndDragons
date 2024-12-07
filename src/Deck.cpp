#include "Deck.h"
#include <iostream>

Deck::Deck() {
    // Constructor, can initialize with predefined cards if needed
}

void Deck::addCard(std::shared_ptr<Card> card) {
    mDeck.push_back(card);
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(mDeck.begin(), mDeck.end(), rng);
}

void Deck::drawCard(PlayerHand& hand) {
    if (!mDeck.empty()) {
        hand.addCard(mDeck.back());
        mDeck.pop_back();
    }
    else {
        std::cerr << "Deck is empty! Cannot draw a card.\n";
    }
}

void Deck::reset() {
    mDeck.clear();
}

void Deck::displayDeck() const {
    std::cout << "Deck: \n";
    for (size_t i = 0; i < mDeck.size(); ++i) {
        std::cout << i + 1 << ": " << mDeck[i]->getName() << "\n";
    }
}

size_t Deck::getDeckSize() const {
    return mDeck.size();
}