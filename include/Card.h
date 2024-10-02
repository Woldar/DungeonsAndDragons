// Card.h
#pragma once
#include <string>

class Card {
public:
    Card(const std::string& name, const std::string& description)
        : mName(name), mDescription(description) {}

    std::string getName() const { return mName; }
    std::string getDescription() const { return mDescription; }

private:
    std::string mName;
    std::string mDescription;
    // You can add other properties like damage, healing, mana cost, etc.
};