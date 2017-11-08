/**
 * @statusinformationsystem.h
 */

#ifndef STATUSINFORMATIONSYSTEM_H
#define STATUSINFORMATIONSYSTEM_H

#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "base/gamesystem.h"
//#include "gui/statusinformationcomponent.h"
#include "ship/shipsettings.h"
#include "ship/weaponsettings.h"

namespace sf {
class RenderWindow;
}

class SoundSystem;


/**
 * @class StatusInformationSystem
 * @brief System zur Verwaltung und Anzeige StatusInformationen des Spielers.
 *
 * Die StatusInformationen werden mit setShipSettings() weitergegeben und jedes Mal
 * bei Erhalt von cmUpgrade aktualisiert. Zeigt diese Informationen in zwei separaten
 * Fenstern beim Spieler an.
 */
class StatusInformationSystem : public GameSystem<Component, Settings> {
private:
    sf::RenderWindow* window;
    SoundSystem& soundSystem;
    sf::Color menuColor = sf::Color(0, 40, 0, 200),
              fontColor = sf::Color::White;
    sf::RectangleShape statusMenu, weaponMenu;
    sf::Font textFont;
    sf::Text titleText, shipNameText, propulsionText, torqueText, energyText, shieldText, hullText;
    std::vector<sf::Text> weaponTexts;
    std::vector<sf::Text> damageTexts;
    std::vector<sf::Text> rangeTexts;
    std::vector<sf::Text> fireRateTexts;
    std::vector<sf::Text> projectileVelocityTexts;
    std::vector<sf::Text> scatterTexts;
    std::vector<sf::Text> energyConsumptionTexts;
    ShipSettings shipSettings;
    std::vector<WeaponSettings> weaponSettings;
    sf::Vector2f playerPos;
    Handle* openSoundHandle = nullptr;
    Handle* closeSoundHandle = nullptr;
    float scale = 1.f, fontSize = 20;
    int shield = 0, hull = 0, energy = 0;
    bool statusOpen = false, weaponsOpen = false;

    void reposition();
    void setTexts();
    void setStatusTextPosition(sf::Text& text, unsigned int index);
    void setWeaponTextPosition(sf::Text& text, unsigned int index);
    sf::Text createText(float fontSize);
    void drawStatusMenu();
    void drawWeaponMenu();
    void playOpenSound();
    void playCloseSound();
public:
    void setShipSettings(ShipSettings settings);
    virtual void update(float dt);
    virtual void notify(EventMessage *message);
    StatusInformationSystem(sf::RenderWindow* window, SoundSystem& soundSystem);
};

#endif // STATUSINFORMATIONSYSTEM_H
