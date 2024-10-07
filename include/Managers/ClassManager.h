// ClassManager.h
#pragma once
#include <memory>
#include <vector>
#include "Classes/Warrior.h"
#include "Classes/Druid.h"

class ClassManager {
public:
    ClassManager() {
        // Initialize the available character classes
        availableClasses.push_back(std::make_unique<Warrior>());
        availableClasses.push_back(std::make_unique<Druid>());
    }

    const std::vector<std::unique_ptr<CharacterClass>>& getAvailableClasses() const {
        return availableClasses;
    }

private:
    std::vector<std::unique_ptr<CharacterClass>> availableClasses;
};