#pragma once
#include "Player.h"
#include "Enemies/EnemyLoader.h"

#include <SFML/Graphics.hpp>

#include <random>
#include <ctime>
#include <cmath>
#include <iostream>

class GameState {
public:
    static GameState& getInstance() {
        static GameState instance;
        return instance;
    }

    void setPlayerClass(CharacterClass &aCharacter)
    {
        this->mPlayer->setClass(aCharacter);
    }

    void setWill(int& aWill)
    {
        this->mPlayer->setWill(aWill);
    }

    int getDungeonLevel() {
        return this->dungeonLevel;
    }

    void setSeed(unsigned int seed) {
        randomEngine.seed(seed);
    }

    // Optionally, initialize with a random seed based on the current time
    void initializeRandomSeed() {
        unsigned int seed = static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count());
        setSeed(seed);
    }

    int rollRandomNumber(int min, int max) {
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(randomEngine);
    }

    sf::Clock getGameClock()
    {
        return mClock;
    }

    std::shared_ptr<Enemy> getEnemy()
    {
        return this->mEnemy;
    }

    void setEnemy(std::shared_ptr<Enemy> aEnemy)
    {
        mEnemy = aEnemy;
    }

    std::shared_ptr<Player> getPlayer()
    {
        return mPlayer;
    }
private:
    GameState()
    {
        // Optional: initialize with a time-based seed
        initializeRandomSeed();

        mPlayer = std::make_shared<Player>();
        mEnemy = std::make_shared<Enemy>();
    };

    std::shared_ptr<Player> mPlayer;
    std::shared_ptr <Enemy> mEnemy;
    int dungeonLevel = 1;
    std::mt19937 randomEngine;
    sf::Clock mClock;

    // Prevent copying and assignment
    GameState(const GameState&) = delete;
    GameState& operator=(const GameState&) = delete;
};
