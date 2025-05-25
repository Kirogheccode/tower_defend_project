#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>

// Tai texture tu thu muc IMGS
bool loadTexture(sf::Texture& texture, const std::string& filename);

// Tai sound tu thu muc SOUNDS
bool loadSoundBuffer(sf::SoundBuffer& buffer, const std::string& filename);
