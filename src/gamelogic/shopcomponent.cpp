#include "shopcomponent.h"
#include <cstdio>


/**
 * @brief Kauft eine Reparatur
 */
void ShopComponent::buyRepair() {
    if (credits >= prices[mainIndex]) {
        EventMessage* message = new EventMessage(cmRepair);
        playerMessages.push_back(message);

        EventMessage* purchaseMessage = new EventMessage(evPurchase);
        purchaseMessage->value = prices[mainIndex];
        notifyListeners(purchaseMessage);
        delete purchaseMessage;
        playSound("menu_upgrade.wav");
    } else {
        playSound("menu_error.wav");
    }
}

/**
 * @brief Kauft ein Upgrade
 * @param upgrade Das Upgrade
 * @param slot Der Waffenslot, falls nötig
 */
void ShopComponent::buyUpgrade(std::string upgrade, int slot) {
    if (credits >= prices[mainIndex]) {
        EventUpgradeMessage* upMessage = new EventUpgradeMessage;
        upMessage->upgrade = upgrade;
        upMessage->value = upgradeValues[mainIndex];
        upMessage->slot = slot;
        playerMessages.push_back((EventMessage*) upMessage);
        notifyListeners(upMessage);

        EventMessage* purchaseMessage = new EventMessage(evPurchase);
        purchaseMessage->value = prices[mainIndex];
        notifyListeners(purchaseMessage);
        delete purchaseMessage;

        playSound("menu_upgrade.wav");
    } else {
        playSound("menu_error.wav");
    }
}

/**
 * @brief Spielt einen Sound
 * @param filename Der Dateiname
 */
void ShopComponent::playSound(std::string filename) {
    EventSoundMessage* soundMessage = new EventSoundMessage;
    soundMessage->event = cmPlaySound;
    soundMessage->file = filename;
    notifyListeners(soundMessage);
    delete soundMessage;
}


/**
 * @brief Setzt neuen aktiven Punkt im Menü
 * @param index Der neue Index
 */
void ShopComponent::setMainIndex(int index) {

    if (index < 0) {
        index = 8;
    }

    index = index % 9;
    mainBackgrounds[mainIndex].setFillColor(menuColor);
    mainTexts[mainIndex].setColor(fontColor);
    mainBackgrounds[index].setFillColor(menuHighlightColor);
    mainTexts[index].setColor(fontHighlightColor);
    mainIndex = index;
    playSound("menu_select.wav");
}


/**
 * @brief Setzt neuen aktiven Punkt im Slot-Menp
 * @param index Der neue Index
 */
void ShopComponent::setSubIndex(int index) {
    if (index < 0) {
        index = 2;
    }

    index = index % 3;
    subBackgrounds[subIndex].setFillColor(menuColor);
    subTexts[subIndex].setColor(fontColor);
    subBackgrounds[index].setFillColor(menuHighlightColor);
    subTexts[index].setColor(fontHighlightColor);
    subIndex = index;
    playSound("menu_select.wav");
}


/**
 * @brief Verarbeitet das einloggen
 */
void ShopComponent::enter() {
    if (activeMenu == Menu::MainMenu) {
        switch (mainIndex) {
        case 0:
            selectedUpgrade = "damage";
            break;

        case 1:
            selectedUpgrade = "range";
            break;

        case 2:
            selectedUpgrade = "fire rate";
            break;

        case 3:
            selectedUpgrade = "projectile velocity";
            break;

        case 4:
            selectedUpgrade = "scatter";
            break;

        case 5:
            selectedUpgrade = "hull";
            break;

        case 6:
            selectedUpgrade = "shield";
            break;

        case 7:
            selectedUpgrade = "energy";
            break;
        }

        if (mainIndex <= 4) {
            activeMenu = Menu::SubMenu;
            setSubIndex(subIndex);
        } else if (mainIndex == 8) {
            buyRepair();
        } else {
            buyUpgrade(selectedUpgrade);
        }
    } else if (activeMenu == Menu::SubMenu) {
        buyUpgrade(selectedUpgrade, subIndex);
    }

    playSound("menu_enter.wav");
}

/**
 * @brief Verarbeitet das abbrechen
 */
void ShopComponent::cancel() {
    activeMenu = Menu::MainMenu;
    playSound("menu_select.wav");
}

/**
 * @brief Gibt an, ob Menü offen ist
 * @return True, falls ein Menü offen
 */
bool ShopComponent::isOpen() {
    if (activeMenu == Menu::MainMenu || activeMenu == Menu::SubMenu) {
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Gibt an, ob Slot-Menü offen
 */
bool ShopComponent::isSubMenuOpen() {
    return (activeMenu == Menu::SubMenu);
}


/**
 * @brief Öffnet Menü
 */
void ShopComponent::open() {
    playSound("menu_open.wav");
    activeMenu = Menu::MainMenu;
}


/**
 * @brief Schließt Menü
 */
void ShopComponent::close() {
    playSound("menu_close.ogg");
    activeMenu = Menu::NoMenu;
}


/**
 * @brief Aktualisiert Credits
 * @param credits Spielercredits
 */
void ShopComponent::setCredits(int credits) {
    this->credits = credits;
}

/**
 * @copydoc Component::notify
 * - ::evKeyPressed Navigation
 */
void ShopComponent::notify(EventMessage* message) {
    if (activeMenu != Menu::NoMenu) {
        switch(message->event) {
        case evKeyPressed: {
            EventKeyMessage* keyMessage = (EventKeyMessage*) message;

            if (keyMessage->key == Keyboard::Up) {
                if (activeMenu == Menu::MainMenu) {
                    setMainIndex(mainIndex - 1);
                } else if (activeMenu == Menu::SubMenu) {
                    setSubIndex(subIndex - 1);
                }
            } else if (keyMessage->key == Keyboard::Down) {
                if (activeMenu == Menu::MainMenu) {
                    setMainIndex(mainIndex + 1);
                } else if (activeMenu == Menu::SubMenu) {
                    setSubIndex(subIndex + 1);
                }
            } else if (keyMessage->key == Keyboard::Return
                       || keyMessage->key == Keyboard::Right) {
                enter();
            } else if (keyMessage->key == Keyboard::Escape
                       || keyMessage->key == Keyboard::BackSpace
                       || keyMessage->key == Keyboard::Left) {
                cancel();
            }

            break;
        }
        }
    }

    delete message;;
}

ShopComponent::ShopComponent(ShopSettings settings, Handle* handle)
    : settings(settings), Component(settings, handle) {

    for (int i = 0; i < 9; i++) {
        sf::RectangleShape shape;
        shape.setFillColor(menuColor);
        shape.setOutlineColor(sf::Color(255, 255, 255, 150));
        shape.setOutlineThickness(2);
        shape.setSize(sf::Vector2f(menuPointWidth, menuPointHeight));
        shape.setPosition(sf::Vector2f(settings.pos.x * 30.f,
                                       settings.pos.y * 30.f + i * menuPointHeight));
        mainBackgrounds.push_back(shape);

        sf::Text text;
        text.setCharacterSize((unsigned int) menuPointHeight * 0.7);
        text.setColor(fontColor);
        text.setPosition(sf::Vector2f(settings.pos.x * 30.f + 5,
                                      settings.pos.y * 30.f + i * menuPointHeight));
        mainTexts.push_back(text);
    }

    for (int i = 0; i < 3; i++) {
        sf::RectangleShape shape;
        shape.setFillColor(menuColor);
        shape.setOutlineColor(sf::Color(255, 255, 255, 150));
        shape.setOutlineThickness(2);
        shape.setSize(sf::Vector2f(subMenuPointWidth, menuPointHeight));
        shape.setPosition(sf::Vector2f(settings.pos.x * 30.f + menuPointWidth,
                                       settings.pos.y * 30.f + i * menuPointHeight));
        subBackgrounds.push_back(shape);

        sf::Text text;
        text.setCharacterSize((unsigned int) menuPointHeight * 0.7);
        text.setColor(fontColor);
        text.setPosition(sf::Vector2f(settings.pos.x * 30.f + 5 + menuPointWidth,
                                      settings.pos.y * 30.f + i * menuPointHeight));
        subTexts.push_back(text);
    }

    prices[0] = 2000;
    prices[1] = 500;
    prices[2] = 2000;
    prices[3] = 1000;
    prices[4] = 2000;
    prices[5] = 3000;
    prices[6] = 5000;
    prices[7] = 3000;
    prices[8] = 100;

    upgradeValues[0] = 10;
    upgradeValues[1] = 10;
    upgradeValues[2] = 0.2;
    upgradeValues[3] = 20;
    upgradeValues[4] = 0.5;
    upgradeValues[5] = 50;
    upgradeValues[6] = 50;
    upgradeValues[7] = 50;
    upgradeValues[8] = 10;

    mainTexts[0].setString("Upgrade damage");
    mainTexts[1].setString("Upgrade range");
    mainTexts[2].setString("Upgrade fire rate");
    mainTexts[3].setString("Upgrade projectile velocity");
    mainTexts[4].setString("Upgrade precision");
    mainTexts[5].setString("Upgrade hull");
    mainTexts[6].setString("Upgrade shield");
    mainTexts[7].setString("Upgrade energy");
    mainTexts[8].setString("Repair hull");
    subTexts[0].setString("Slot 1");
    subTexts[1].setString("Slot 2");
    subTexts[2].setString("Slot 3");

    for (int i = 0; i < 9; i++) {
        char buf[20];
        std::snprintf(buf, sizeof(buf), "$%-6d ", prices[i]);
        mainTexts[i].setString(buf + mainTexts[i].getString());
    }


    Event events[3] = {cmPlaySound, evPurchase, cmUpgrade};
    initializeEvents(events, 3);
}
