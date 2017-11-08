/**
 * @file textures.h
 */
#ifndef TEXTURES_H
#define TEXTURES_H

#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <string>

/**
 * @class Textures
 * @brief Statische Klasse zum laden von Texturen im "resources/textures/"-Ordner
 *
 * Muss nicht manuell initialisiert werden.
 */
class Textures {
private:
    //static bool isInitialized = false;
    static std::map<std::string, sf::Texture> textures;
    static std::map<std::string, sf::Texture> initializeTextures();
    Textures() {}
public:
    static sf::Texture & get(std::string path);
};

#endif // TEXTURES_H
