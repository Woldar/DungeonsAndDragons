#pragma once

#include <vector>
#include <memory>
#include <string>
#include <stdexcept>
#include <iostream>
#include <filesystem>
#include <random>
#include <algorithm>
#include <ctime>

#include "Enemy.h"
#include "GameState.h"
#include <sol/sol.hpp>  // Include Sol2 library

class EnemyLoader {
public:
    explicit EnemyLoader(const std::string& luaFilePath);  // Constructor with Lua file path

    // Loads enemies from the Lua file
    void loadEnemies();

    // Get an enemy by index
    std::shared_ptr<Enemy> getEnemyByIndex(size_t index) const;

    // Get an enemy by name
    std::shared_ptr<Enemy> getEnemyByName(const std::string& name) const;

    std::shared_ptr<Enemy> getRandomEnemyByLevel(int level);



private:
    sol::state lua;  // Lua state
    std::string dataPath;  // Path to the Lua file
    std::vector<std::shared_ptr<Enemy>> enemies;  // List of loaded enemies
};
