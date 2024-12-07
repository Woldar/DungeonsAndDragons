#pragma once

#include <string>

class Enemy {
public:
    Enemy()
    {

    }

    Enemy(const std::string& name, int level, const std::string& iconPath, int health, int damage, int defense, int speed)
        : name(name), level(level), iconPath(iconPath), health(health), damage(damage), defense(defense), speed(speed) {}

    // Accessors
    std::string getName() const { return name; }
    int getLevel() const { return level; }
    std::string getIconPath() const { return iconPath; }
    int getHealth() const { return health; }
    int getDamage() const { return damage; }
    int getDefense() const { return defense; }
    int getSpeed() const { return speed; }

private:
    std::string name;
    int level;
    std::string iconPath;
    int health;
    int damage;
    int defense;
    int speed;
};