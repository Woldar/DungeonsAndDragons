#include "EnemyLoader.h"

EnemyLoader::EnemyLoader(const std::string& luaFilePath) : dataPath(luaFilePath) {
    lua.open_libraries(sol::lib::base);

    // Resolve path using std::filesystem
    std::filesystem::path basePath = std::filesystem::current_path(); // Get the current working directory
    std::filesystem::path fullPath = basePath / luaFilePath;

    // Load the Lua script
    lua.script_file(fullPath.string());
    loadEnemies();
}

void EnemyLoader::loadEnemies() {
    enemies.clear();  // Clear any previously loaded enemies

    sol::table enemyTable = lua["enemies"];  // Access 'enemies' table in Lua
    if (!enemyTable.valid()) {
        throw std::runtime_error("Failed to load 'enemies' table from Lua file");
    }

    for (auto& enemyData : enemyTable) {
        sol::table data = enemyData.second.as<sol::table>();

        // Extract enemy properties
        std::string name = data["name"];
        int level = data["level"];
        std::string iconPath = data["iconPath"];
        int health = data["health"];
        int damage = data["damage"];
        int defense = data["defense"];
        int speed = data["speed"];

        // Add enemy to the list
        enemies.push_back(std::make_shared<Enemy>(name, level, iconPath, health, damage, defense, speed));
    }
}

std::shared_ptr<Enemy> EnemyLoader::getEnemyByIndex(size_t index) const {
    if (index >= enemies.size()) {
        throw std::out_of_range("Invalid enemy index");
    }
    return enemies[index];
}

std::shared_ptr<Enemy> EnemyLoader::getRandomEnemyByLevel(int level) {
    std::vector<std::shared_ptr<Enemy>> matchingEnemies;
    for (const auto& enemy : enemies) {
        if ((enemy->getLevel() == level)) {
            matchingEnemies.push_back(enemy);
        }
    }
    if (matchingEnemies.empty()) {
        throw std::runtime_error("No matching enemies found!");
    }
    
    // Randomly select one of the matching enemies
    int randomIndex = GameState::getInstance().rollRandomNumber(0, matchingEnemies.size() - 1);
    return matchingEnemies[randomIndex];
}

std::shared_ptr<Enemy> EnemyLoader::getEnemyByName(const std::string& name) const {
    for (const auto& enemy : enemies) {
        if (enemy->getName() == name) {
            return enemy;
        }
    }
    throw std::runtime_error("Enemy with the given name not found");
}