// Card.h
#pragma once
#include <string>
#include "EffectTarget.h"

class Card {
public:
    enum class CardType { DAMAGE, ARMOR }; // Define card types


    Card(const std::string& name, const std::string& description, CardType type, int value)
        : mName(name), mDescription(description), mType(type), mValue(value) {}

    std::string getName() const { return mName; }
    std::string getDescription() const { return mDescription; }
    CardType getType() const { return mType; }
    int getValue() const { return mValue; }

    void applyEffect(EffectTarget& target) const {
        switch (mType) {
        case CardType::DAMAGE:
            target.dealDamage(mValue);
            break;
        case CardType::ARMOR:
            target.addArmor(mValue);
            break;
        }
    }

private:
    std::string mName;
    std::string mDescription;
    CardType mType;
    int mValue;
    // You can add other properties like damage, healing, mana cost, etc.
};