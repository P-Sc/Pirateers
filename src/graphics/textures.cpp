#include "textures.h"
#include <boost/filesystem.hpp>
#include <iostream>

// Credit: https://stackoverflow.com/questions/67273
using namespace boost::filesystem;

/**
 * @brief Hilfsklasse zum Durchsuchen von Ordnern
 */
struct recursive_directory_range
{
    typedef recursive_directory_iterator dirIterator;
    recursive_directory_range(path p) : p_(p) {}

    dirIterator begin() { return recursive_directory_iterator(p_); }
    dirIterator end() { return recursive_directory_iterator(); }

    path p_;
};

std::map<std::string, sf::Texture> Textures::textures = Textures::initializeTextures();


/**
 * @brief Initialisiert alle Texturen im "resources/textures/"-Ordner (rekursiv)
 * @return Eine Map der Texturen mit den relativen Pfaden als Schlüssel
 */
std::map<std::string, sf::Texture> Textures::initializeTextures() {
    std::map<std::string, sf::Texture> tmp;
    for (directory_entry it : recursive_directory_range("./../resources/textures/")) {
        std::string relativePath = it.path().string();

        // Textur laden
        sf::Texture texture;

        if(it.status().type() == directory_file || !texture.loadFromFile(relativePath)) {
            continue;
        }
        texture.setSmooth(true);

        // Textur hinzufügen
        relativePath.erase(0,24);
        tmp.insert(std::pair<std::string,sf::Texture>(relativePath, texture));
        std::cout << "Texture added: " << relativePath << std::endl;
    }
    return tmp;
}


/**
 * @brief Gibt Referenz auf Textur zurück
 * @param path Der Pfad der gewünschten Textur, relativ zu "resources/textures/"
 * @return Eine Referenz auf die Textur
 */
sf::Texture & Textures::get(std::string path) {
    return Textures::textures.at(path);
}
