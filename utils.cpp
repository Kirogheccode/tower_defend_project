#include "utils.h"

bool loadTexture(sf::Texture& texture, const std::string& filename) {
    std::string path = "../../IMGS/" + filename;
    if (!texture.loadFromFile(path)) {
        std::cerr << "Failed to load image: " << path << std::endl;
        return false;
    }
    return true;
}

bool loadSoundBuffer(sf::SoundBuffer& buffer, const std::string& filename) {
    std::string path = "../../SOUNDS/" + filename;
    if (!buffer.loadFromFile(path)) {
        std::cerr << "Failed to load sound: " << path << std::endl;
        return false;
    }
    return true;
}
