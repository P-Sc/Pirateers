/**
 * @file highscoreloader.h
 */
#ifndef HIGHSCORELOADER_H
#define HIGHSCORELOADER_H

#include <string>
#include <vector>

/**
 * @class HighScoreLoader
 * @brief Lädt Highscores aus der "highscores.txt"-Datei.
 */
class HighScoreLoader {
private:
    std::vector<int> highscores;
    void loadFile(std::string filename);
    void saveToFile(std::string filename);
public:
    void addHighScore(int highscore);
    std::vector<int> getHighScores();
    HighScoreLoader();
};

#endif // HIGHSCORELOADER_H
