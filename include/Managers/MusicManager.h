#pragma once

#include <SFML/Audio.hpp>
#include <iostream>

class MusicManager {
public:
    static MusicManager& getInstance() {
        static MusicManager instance;
        return instance;
    }

    // Loads and plays a different music file
    void playMusic(const std::string& musicFile) {
        if (currentMusicFile != musicFile) {  // Only load if it's a different file
            if (!backgroundMusic.openFromFile(musicFile)) {
                std::cerr << "Failed to load music file: " << musicFile << std::endl;
                return;
            }
            currentMusicFile = musicFile;
            backgroundMusic.setLoop(true);
            backgroundMusic.play();
        }
    }

    void pauseMusic() {
        if (backgroundMusic.getStatus() == sf::SoundSource::Playing) {
            backgroundMusic.pause();
        }
    }

    void resumeMusic() {
        if (backgroundMusic.getStatus() == sf::SoundSource::Paused) {
            backgroundMusic.play();
        }
    }

    void stopMusic() {
        backgroundMusic.stop();
    }

    void setVolume(float volume) {
        backgroundMusic.setVolume(volume);
    }

    std::string getCurrentMusicFile() const {
        return currentMusicFile;
    }

private:
    sf::Music backgroundMusic;
    std::string currentMusicFile; // Stores the currently playing music file

    // Private constructor to prevent instantiation
    MusicManager() : currentMusicFile("") {}

    // Delete copy constructor and assignment operator
    MusicManager(const MusicManager&) = delete;
    MusicManager& operator=(const MusicManager&) = delete;
};
