/**
 * @file mainmenusystem.h
 */
#ifndef MAINMENUSYSTEM_H
#define MAINMENUSYSTEM_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/View.hpp>
#include "base/gamesystem.h"
#include "gui/mainmenucomponent.h"
#include "base/settings.h"
#include "utils/highscoreloader.h"

namespace sf {
    class RenderWindow;
}

class SoundSystem;
class AreaSystem;

/**
 * @class MainMenuSystem
 * @brief System zur Anzeige des Hauptmenüs
 *
 * Zeigt das Hauptmenü, die Highscores und das Startmenü an. Die Highscores werden aus dem
 * HighScoreLoader entnommen. Beim drücken der Start-Taste ruft das MainMenuSystem
 * AreaSystem::restart() auf und gibt dabei die Waffenwahl weiter.
 */
class MainMenuSystem : public GameSystem<MainMenuComponent, Settings> {
private:
    enum Menu {MainMenu, ShipMenu, HighscoreMenu, NoMenu};

    sf::RenderWindow* window;
    SoundSystem& soundSystem;
    AreaSystem& areaSystem;
    HighScoreLoader& highScoreLoader;
    sf::Font menuFont, titleFont;
    sf::Color menuColor = sf::Color(0, 40, 0, 200),
              menuHighlightColor = sf::Color(255, 255, 255, 200),
              fontColor = sf::Color::White,
              fontHighlightColor = sf::Color(0, 40, 0, 255);
    std::vector<sf::RectangleShape> mainBackgrounds;
    std::vector<sf::RectangleShape> shipBackgrounds;
    std::vector<sf::Text> mainTexts;
    std::vector<sf::Text> shipTexts;
    sf::RectangleShape highScoreBackground;
    sf::Text titleText, shipInfoText, highScoreText;
    sf::View cameraView;
    Handle* selectSoundHandle = nullptr;
    Handle* enterSoundHandle = nullptr;
    Handle* openSoundHandle = nullptr;
    Handle* closeSoundHandle = nullptr;
    Handle* errorSoundHandle = nullptr;
    Menu activeMenu = Menu::NoMenu;
    std::vector<int> highscores;
    float outlineThickness = 2.f, scale = 1.f;
    unsigned int menuPointHeight = 40, menuPointWidth = 400;
    int mainIndex = 0, shipIndex = 0;
    int slotIndices[3];
    bool fullscreen = false;
    std::string weapons[4];

    void createMenu();
    void resize();
    void reposition();
    void setMainPointPosition(sf::Text& text, sf::RectangleShape& shape, unsigned int index);
    void setShipPointPosition(sf::Text& text, sf::RectangleShape& shape, unsigned int index);
    void playSound(std::string filename);
    void setMainIndex(int index);
    void setShipIndex(int index);
    void enter();
    void cancel();
    virtual Handle* createComponent(Settings settings);
public:
    void setOpen(bool value);
    bool isOpen();
    virtual void update(float dt);
    virtual void notify(EventMessage *message);
    MainMenuSystem(sf::RenderWindow* window, SoundSystem& soundSystem, AreaSystem& areaSystem,
                   HighScoreLoader& highScoreLoader);
};

#endif // MAINMENUSYSTEM_H
