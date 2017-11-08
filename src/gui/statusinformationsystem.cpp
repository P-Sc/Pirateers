#include "statusinformationsystem.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "sound/soundsystem.h"
#include "ship/weaponloader.h"


/**
 * @brief Fenster neupositionieren
 */
void StatusInformationSystem::reposition() {
    statusMenu.setPosition(playerPos);
    weaponMenu.setPosition(playerPos);
    //sf::Vector2f position = sf::Vector2f(menu.getGlobalBounds().left,
    //                                     menu.getGlobalBounds().top);
    setStatusTextPosition(titleText, 0);
    setStatusTextPosition(shipNameText, 2);
    setStatusTextPosition(propulsionText, 3);
    setStatusTextPosition(torqueText, 4);
    setStatusTextPosition(energyText, 5);
    setStatusTextPosition(shieldText, 6);
    setStatusTextPosition(hullText, 7);

    for (size_t i = 0; i < weaponTexts.size(); i++) {
        setWeaponTextPosition(weaponTexts[i], i * 8 + 1);
        setWeaponTextPosition(damageTexts[i], i * 8 + 3);
        setWeaponTextPosition(rangeTexts[i], i * 8 + 4);
        setWeaponTextPosition(fireRateTexts[i], i * 8 + 5);
        setWeaponTextPosition(projectileVelocityTexts[i], i * 8 + 6);
        setWeaponTextPosition(scatterTexts[i], i * 8 + 7);
        setWeaponTextPosition(energyConsumptionTexts[i], i * 8 + 8);
    }
}

/**
 * @brief Aktuelle Werte in jedes Textfeld eingeben
 */
void StatusInformationSystem::setTexts() {
    titleText.setString("Ship Status: ");
    shipNameText.setString("Ship name: " + shipSettings.shipname);
    propulsionText.setString("Propulsion: " + std::to_string(shipSettings.propulsion));
    torqueText.setString("Max. torque: " + std::to_string(shipSettings.maxTorque));
    hullText.setString("Hull: " + std::to_string(hull) + " / "
                       + std::to_string(shipSettings.shieldSettings.maxHull));
    shieldText.setString("Shield: " + std::to_string(shield) + " / "
                         + std::to_string(shipSettings.shieldSettings.maxShield));
    energyText.setString("Energy: " + std::to_string(energy) + " / "
                         + std::to_string(shipSettings.energySettings.maxEnergy));

    for (size_t i = 0; i < shipSettings.weapons.size(); i++) {
        weaponTexts[i].setString(shipSettings.weapons[i].gunName);
        damageTexts[i].setString("Damage: "
                                 + std::to_string(weaponSettings[i].ammoSettings.damage));
        rangeTexts[i].setString("Range: "
                                + std::to_string(weaponSettings[i].ammoSettings.range) + "m");
        fireRateTexts[i].setString("ROF: "
                                   + std::to_string(weaponSettings[i].ammoSettings.rateOfFire) + " shots/s");
        projectileVelocityTexts[i].setString("Projectile velocity: "
                                             + std::to_string(weaponSettings[i].ammoSettings.velocity)
                                             + "m/s");
        scatterTexts[i].setString("Scatter: "
                                  + std::to_string(weaponSettings[i].ammoSettings.scatter) + " deg.");
        energyConsumptionTexts[i].setString("Energy Consumption: "
                                            + std::to_string(weaponSettings[i].ammoSettings.energyConsumption));
    }
}


/**
 * @brief positioniert einen Text im Schiffsstatusfenster
 * @param text Das Textfeld
 * @param index Der Index  des Textfelds.
 */
void StatusInformationSystem::setStatusTextPosition(sf::Text& text, unsigned int index) {
    sf::Vector2f position = sf::Vector2f(statusMenu.getGlobalBounds().left,
                                         statusMenu.getGlobalBounds().top);
    position += sf::Vector2f(fontSize * 0.5f, index * fontSize);
    text.setPosition(position);
}

/**
 * @brief Positioniert einen Text im Waffenstatusfenster
 * @param text Das Textfeld
 * @param index Der Index des Textfelds
 */
void StatusInformationSystem::setWeaponTextPosition(sf::Text& text, unsigned int index) {
    sf::Vector2f position = sf::Vector2f(weaponMenu.getGlobalBounds().left,
                                         weaponMenu.getGlobalBounds().top);
    position += sf::Vector2f(fontSize * 0.5f, index * fontSize);
    text.setPosition(position);
}

/**
 * @brief Erzeugt ein Textfeld
 * @param fontSize Schriftgröße
 * @return Das erzeugte Textfeld
 */
sf::Text StatusInformationSystem::createText(float fontSize) {
    sf::Text text;
    text.setFont(textFont);
    text.setCharacterSize(fontSize);
    text.setColor(fontColor);
    text.setString("Test");
    return text;
}


/**
 * @brief Zeichnet das Schiffsstatusmenü
 */
void StatusInformationSystem::drawStatusMenu() {
    window->draw(statusMenu);
    window->draw(titleText);
    window->draw(shipNameText);
    window->draw(propulsionText);
    window->draw(torqueText);
    window->draw(energyText);
    window->draw(shieldText);
    window->draw(hullText);
}


/**
 * @brief Zeichnet das Waffenstatusmenü
 */
void StatusInformationSystem::drawWeaponMenu() {
    window->draw(weaponMenu);

    for (size_t i = 0; i < 3; i++) {
        window->draw(weaponTexts[i]);
        window->draw(damageTexts[i]);
        window->draw(rangeTexts[i]);
        window->draw(fireRateTexts[i]);
        window->draw(projectileVelocityTexts[i]);
        window->draw(scatterTexts[i]);
        window->draw(energyConsumptionTexts[i]);
    }
}


/**
 * @brief Öffnungs-Sound abspielen
 */
void StatusInformationSystem::playOpenSound() {
    EventSoundMessage* soundMessage = new EventSoundMessage;
    soundMessage->event = cmPlaySound;
    soundMessage->file = "menu_open.wav";
    soundMessage->receiverId = openSoundHandle->id;
    soundSystem.notifyComponent(soundMessage);
}


/**
 * @brief Schließ-Sound abspielen
 */
void StatusInformationSystem::playCloseSound() {
    EventSoundMessage* soundMessage = new EventSoundMessage;
    soundMessage->event = cmPlaySound;
    soundMessage->file = "menu_close.ogg";
    soundMessage->receiverId = closeSoundHandle->id;
    soundSystem.notifyComponent(soundMessage);
}


/**
 * @brief Neue Schiffseinstellungen setzen
 * @param settings Die Schiffseinstellungen
 */
void StatusInformationSystem::setShipSettings(ShipSettings settings) {
    this->shipSettings = settings;
    energy = shipSettings.energySettings.maxEnergy;
    shield = shipSettings.shieldSettings.maxShield;
    hull = shipSettings.shieldSettings.maxHull;

    for (size_t i = 0; i < shipSettings.weapons.size(); i++) {
        WeaponSettings settings;

        if (shipSettings.weapons[i].gunName == "plasma") {
            settings = WeaponLoader::plasma;
        } else if (shipSettings.weapons[i].gunName == "neutron") {
            settings = WeaponLoader::neutron;
        } else if (shipSettings.weapons[i].gunName == "taychon") {
            settings = WeaponLoader::taychon;
        } else {
            settings = WeaponLoader::laser;
        }

        settings.ammoSettings.damage *= shipSettings.weapons[i].damageMultiplier;
        settings.ammoSettings.rateOfFire *= shipSettings.weapons[i].rateOfFireMultiplier;
        settings.ammoSettings.velocity *= shipSettings.weapons[i].velocityMultiplier;
        settings.ammoSettings.scatter *= shipSettings.weapons[i].scatterMultiplier;

        weaponSettings.push_back(settings);
    }

    setTexts();
}

/**
 * @copydoc GameSystem::update
 * Zeichnet Menüs
 */
void StatusInformationSystem::update(float dt) {
    GameSystem::update(dt);

    if (statusOpen) {
        drawStatusMenu();
    }

    if (weaponsOpen) {
        drawWeaponMenu();
    }
}


/**
 * @copydoc GameSystem::notify
 * - ::evKeyPressed Fenster öffnen/schließen
 * - ::evMove Position aktualisieren
 * - ::evShield Schildstatus aktualisieren
 * - ::evEnergyStatus Energiestatus aktualisieren
 * - ::cmUpgrade Upgrade ausführen bzw. aktualieren
 */
void StatusInformationSystem::notify(EventMessage* message) {
    switch (message->event) {
    case evKeyPressed: {
        EventKeyMessage* keyMessage = (EventKeyMessage*) message;

        if (keyMessage->key == Keyboard::K) {
            if (statusOpen) {
                statusOpen = false;
                playOpenSound();
            } else {
                statusOpen = true;
                playOpenSound();
            }
        } else if (keyMessage->key == Keyboard::J) {
            if (weaponsOpen) {
                weaponsOpen = false;
                playOpenSound();
            } else {
                weaponsOpen = true;
                playOpenSound();
            }
        }

        break;
    }

    case evMove: {
        EventPosMessage* posMessage = (EventPosMessage*) message;
        playerPos.x = posMessage->center.x * 30.f;
        playerPos.y = posMessage->center.y * 30.f;
        reposition();
        break;
    }

    case evShield: {
        EventShieldMessage* shieldMessage = (EventShieldMessage*) message;
        shield = shieldMessage->shield;
        hull = shieldMessage->hull;
        setTexts();
        break;
    }

    case evEnergyStatus: {
        energy = message->value;
        setTexts();
        break;
    }

    case cmUpgrade: {
        EventUpgradeMessage* upMessage = (EventUpgradeMessage*) message;
        std::transform(upMessage->upgrade.begin(), upMessage->upgrade.end(),
                       upMessage->upgrade.begin(), ::tolower);

        if (upMessage->upgrade == "hull") {
            shipSettings.shieldSettings.maxHull += upMessage->value;
        } else if (upMessage->upgrade == "shield") {
            shipSettings.shieldSettings.maxShield += upMessage->value;
            shipSettings.shieldSettings.regenPerSecond
                    += shipSettings.shieldSettings.regenPerSecond
                    * upMessage->value/shipSettings.shieldSettings.maxShield;
        } else if (upMessage->upgrade == "energy") {
            shipSettings.energySettings.maxEnergy += upMessage->value;
            shipSettings.energySettings.regenPerSecond
                    += shipSettings.energySettings.regenPerSecond
                    * upMessage->value/shipSettings.energySettings.maxEnergy;
        } else if (upMessage->upgrade == "damage") {
            weaponSettings[upMessage->slot].ammoSettings.damage += upMessage->value;
        } else if (upMessage->upgrade == "range") {
            weaponSettings[upMessage->slot].ammoSettings.range += upMessage->value;
        } else if (upMessage->upgrade == "fire rate") {
            weaponSettings[upMessage->slot].ammoSettings.rateOfFire += upMessage->value;
        } else if (upMessage->upgrade == "projectile velocity") {
            weaponSettings[upMessage->slot].ammoSettings.velocity += upMessage->value;
        } else if (upMessage->upgrade == "scatter") {
            weaponSettings[upMessage->slot].ammoSettings.scatter *= upMessage->value;
        }
        setTexts();

        break;
    }
    }


    delete message;;
}

StatusInformationSystem::StatusInformationSystem(sf::RenderWindow* window, SoundSystem& soundSystem)
    : window(window), soundSystem(soundSystem) {

    statusMenu.setFillColor(menuColor);
    statusMenu.setOutlineColor(sf::Color(255, 255, 255, 150));
    statusMenu.setOutlineThickness(4);
    statusMenu.setSize(sf::Vector2f(300, 200));
    statusMenu.setOrigin(sf::Vector2f(-20, 0));

    weaponMenu.setFillColor(menuColor);
    weaponMenu.setOutlineColor(sf::Color(255, 255, 255, 150));
    weaponMenu.setOutlineThickness(4);
    weaponMenu.setSize(sf::Vector2f(500, 3 * 9 * fontSize));
    weaponMenu.setOrigin(sf::Vector2f(520, 0.5f * weaponMenu.getSize().y));

    SoundSettings soundSettings;
    soundSettings.filename = "menu_open.wav";
    openSoundHandle = soundSystem.createComponent(soundSettings);
    soundSettings.filename = "menu_close.ogg";
    closeSoundHandle = soundSystem.createComponent(soundSettings);

    textFont.loadFromFile("../resources/FreeMono.otf");

    titleText = createText(fontSize * 1.5f);
    shipNameText = createText(fontSize);
    propulsionText = createText(fontSize);
    torqueText = createText(fontSize);
    energyText = createText(fontSize);
    shieldText = createText(fontSize);
    hullText = createText(fontSize);

    weaponTexts.clear();

    for (int i = 0; i < 3; i++) {
        sf::Text test = createText(fontSize * 1.5f);
        weaponTexts.push_back(test);
        damageTexts.push_back(createText(fontSize));
        rangeTexts.push_back(createText(fontSize));
        fireRateTexts.push_back(createText(fontSize));
        projectileVelocityTexts.push_back(createText(fontSize));
        scatterTexts.push_back(createText(fontSize));
        energyConsumptionTexts.push_back(createText(fontSize));
    }

    setTexts();

    //resize();
    reposition();
}
