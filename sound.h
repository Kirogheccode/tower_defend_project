#ifndef SOUND_H
#define SOUND_H

#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>

using namespace std;
using namespace sf;

class SoundManager {
public:
    SoundManager();

    void loadSound(const string& name, const string& filepath);
    void playSound(const string& name);

    void playMusic(const string& filepath, bool loop = true);
    void stopMusic();
    void setMusicVolume(float volume);
    void toggleMusic(); 

private:
    unordered_map<string, SoundBuffer> soundBuffers;
    unordered_map<string, Sound> sounds;

    Music backgroundMusic;
    bool musicOn;
};

#endif
