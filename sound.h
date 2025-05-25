#ifndef SOUND_H
#define SOUND_H

#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>

class SoundManager {
public:
    SoundManager();

    void loadSound(const std::string& name, const std::string& filepath);
    void playSound(const std::string& name);

    void playMusic(const std::string& filepath, bool loop = true);
    void stopMusic();
    void setMusicVolume(float volume);
    void toggleMusic(); // bat/tat nhac nen

private:
    std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
    std::unordered_map<std::string, sf::Sound> sounds;

    sf::Music backgroundMusic;
    bool musicOn;
};

#endif
