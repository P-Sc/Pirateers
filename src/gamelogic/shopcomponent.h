/**
 * @file shopcomponent.h
 */

#ifndef SHOPCOMPONENT_H
#define SHOPCOMPONENT_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include "base/component.h"
#include "gamelogic/shopsettings.h"


/**
 * @class ShopComponent
 * @brief Ein Shop.
 */
class ShopComponent : public Component {
private:
    enum Menu {MainMenu, SubMenu, NoMenu};

    Menu activeMenu = Menu::MainMenu;
    sf::Color menuColor = sf::Color(0, 40, 0, 200),
              menuHighlightColor = sf::Color(255, 255, 255, 200),
              fontColor = sf::Color::White,
              fontHighlightColor = sf::Color(0, 40, 0, 255);
    unsigned int menuPointHeight = 40, menuPointWidth = 650, subMenuPointWidth = 200;
    int mainIndex = 0, subIndex = 0;
    int credits = 0;

    void buyRepair();
    void buyUpgrade(std::string upgrade, int slot = -2);
    void playSound(std::string filename);
    void setMainIndex(int index);
    void setSubIndex(int index);
    void enter();
    void cancel();
public:
    ShopSettings settings;
    Handle* graphicsHandle = nullptr;
    Handle* selectSoundHandle = nullptr;
    Handle* enterSoundHandle = nullptr;
    Handle* openSoundHandle = nullptr;
    Handle* closeSoundHandle = nullptr;
    Handle* errorSoundHandle = nullptr;
    Handle* upgradeSoundHandle = nullptr;
    std::vector<EventMessage*> playerMessages;
    std::vector<sf::RectangleShape> mainBackgrounds;
    std::vector<sf::RectangleShape> subBackgrounds;
    std::vector<sf::Text> mainTexts;
    std::vector<sf::Text> subTexts;
    std::string selectedUpgrade;
    int prices[9];
    float upgradeValues[8];

    bool isOpen();
    bool isSubMenuOpen();
    void open();
    void close();
    void setCredits(int credits);
    virtual void notify(EventMessage *message);
    ShopComponent(ShopSettings settings, Handle* handle);
};

#endif // SHOPCOMPONENT_H
