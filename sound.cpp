#include "sound.h"
#include <iostream>

SoundManager::SoundManager() : musicOn(true) {}

void SoundManager::loadSound(const std::string& name, const std::string& filepath) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filepath)) {
        std::cerr << "Failed to load sound: " << filepath << std::endl;
        return;
    }
    soundBuffers[name] = buffer;

    sf::Sound sound;
    sound.setBuffer(soundBuffers[name]);
    sounds[name] = sound;
}

void SoundManager::playSound(const std::string& name) {
    if (sounds.count(name)) {
        sounds[name].play();
    }
}

void SoundManager::playMusic(const std::string& filepath, bool loop) {
    if (!backgroundMusic.openFromFile(filepath)) {
        std::cerr << "Failed to load music: " << filepath << std::endl;
        return;
    }
    backgroundMusic.setLoop(loop);
    backgroundMusic.setVolume(50);
    if (musicOn) backgroundMusic.play();
}

void SoundManager::stopMusic() {
    backgroundMusic.stop();
}

void SoundManager::setMusicVolume(float volume) {
    backgroundMusic.setVolume(volume);
}

void SoundManager::toggleMusic() {
    musicOn = !musicOn;
    if (musicOn) backgroundMusic.play();
    else backgroundMusic.stop();
}
