#include "sounds.h"
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

std::map<std::string, sf::SoundBuffer> Sounds::sounds = Sounds::initializeSounds();


/**
 * @brief Initialisiert alle Sounds im "resources/sounds/"-Ordner (rekursiv)
 * @return Eine Map der Sounds mit den relativen Pfaden als Schlüssel
 */
std::map<std::string, sf::SoundBuffer> Sounds::initializeSounds() {
    std::map<std::string, sf::SoundBuffer> tmp;
    for (directory_entry it : recursive_directory_range("./../resources/sounds/")) {
        std::string relativePath = it.path().string();

        // Textur laden
        sf::SoundBuffer soundBuffer;

        if(it.status().type() == directory_file || !soundBuffer.loadFromFile(relativePath)) {
            std::cout << "Loading sound file failed: " << relativePath << std::endl;
            continue;
        }

        // Textur hinzufügen
        relativePath.erase(0,22);
        tmp.insert(std::pair<std::string,sf::SoundBuffer>(relativePath, soundBuffer));
        std::cout << "Sound added: " << relativePath << std::endl;
    }
    return tmp;
}


/**
 * @brief Gibt Referenz auf Sound zurück
 * @param path Der Pfad der gewünschten Sounddatei, relativ zu "resources/sounds/"
 * @return Eine Referenz auf den SoundBuffer
 */
sf::SoundBuffer& Sounds::get(std::string path) {
    return Sounds::sounds.at(path);
}
