#include "PlayerHand.h"
#include <iostream>

void PlayerHand::addCard(std::shared_ptr<Card> card) {
    mHand.push_back(card);
}

void PlayerHand::removeCard(size_t index) {
    if (index < mHand.size()) {
        mHand.erase(mHand.begin() + index);
    }
    else {
        std::cerr << "Invalid index: Cannot remove card\n";
    }
}

void PlayerHand::playCard(size_t index, EffectTarget& target) {
    if (index < mHand.size()) {
        mHand[index]->applyEffect(target); // Apply card effect to target
        mHand.erase(mHand.begin() + index); // Remove card from hand
    }
    else {
        std::cerr << "Invalid index: Cannot play card\n";
    }
}

void PlayerHand::displayHand() const {
    std::cout << "Player's Hand:\n";
    for (size_t i = 0; i < mHand.size(); ++i) {
        std::cout << i + 1 << ": " << mHand[i]->getName()
            << " (" << mHand[i]->getDescription() << ")\n";
    }
}

size_t PlayerHand::getCardCount() const {
    return mHand.size();
}
