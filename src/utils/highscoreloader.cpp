#include "highscoreloader.h"
#include <iostream>
#include <fstream>
#include <algorithm>


/**
 * @brief Lädt Highscore-Datei
 * @param filename Dateiname
 */
void HighScoreLoader::loadFile(std::string filename) {
    std::string line;
    std::ifstream file(filename);

    if (file.is_open() ) {
        while ( std::getline(file, line)) {
            try {
                highscores.push_back(std::stoi(line));
            } catch (std::exception e) {

            }
        }
    }

    std::sort(highscores.rbegin(), highscores.rend());
    file.close();
}

/**
 * @brief Highscores speichern
 * @param filename Dateiname
 */
void HighScoreLoader::saveToFile(std::string filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < highscores.size(); i++) {
            file << highscores[i] << std::endl;
        }
    }
    file.close();
}

/**
 * @brief Highscore hinzufügen
 * @param highscore Der Punktestand
 */
void HighScoreLoader::addHighScore(int highscore) {
    highscores.push_back(highscore);
    std::sort(highscores.rbegin(), highscores.rend());
    saveToFile("highscores.txt");
}

std::vector<int> HighScoreLoader::getHighScores() {
    return highscores;
}

HighScoreLoader::HighScoreLoader() {
    loadFile("highscores.txt");
}
