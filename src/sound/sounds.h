/**
 * @file sounds.h
 */

#ifndef SOUNDS_H
#define SOUNDS_H

#include <map>
#include <string>
#include <SFML/Audio/SoundBuffer.hpp>


/**
 * @class Sounds
 * @brief Statische Klasse zum laden von Sounds im "resources/sounds/"-Ordner
 *
 * Muss nicht manuell initialisiert werden.
 */
class Sounds
{
private:
    static std::map<std::string, sf::SoundBuffer> sounds;
    static std::map<std::string, sf::SoundBuffer> initializeSounds();
    Sounds() {}
public:
    static sf::SoundBuffer& get(std::string path);
};

#endif // SOUNDS_H
