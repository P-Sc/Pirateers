#include "mainmenusystem.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "sound/soundsystem.h"
#include "gamelogic/areasystem.h"

/**
 * @brief Erstellt das Hauptmenü neu
 */
void MainMenuSystem::createMenu() {
    // Skalierung
    menuPointWidth = window->getSize().x * 0.3;
    menuPointHeight = menuPointWidth * 0.08;

    /*
     * Titeltext
     */
    titleText.setFillColor(sf::Color::Transparent);
    titleText.setOutlineColor(fontColor);
    titleText.setOutlineThickness(1);
    titleText.setString("Pirateers");
    titleText.setCharacterSize((unsigned int) menuPointHeight * 2);
    /*
     * Waffenauswahl-Text
     */
    shipInfoText.setFont(menuFont);
    shipInfoText.setCharacterSize((unsigned int) menuPointHeight);
    shipInfoText.setColor(fontColor);
    shipInfoText.setString("Select your weapons");
    /*
     * Highscores
     */
    highScoreText.setFont(menuFont);
    highScoreText.setCharacterSize((unsigned int) menuPointHeight);
    highScoreText.setColor(fontColor);
    highScoreText.setString("");
    /*
     * Highscore-Hintergrund
     */
    highScoreBackground.setFillColor(menuColor);
    highScoreBackground.setOutlineColor(sf::Color(255, 255, 255, 150));
    highScoreBackground.setOutlineThickness(outlineThickness);
    highScoreBackground.setSize(sf::Vector2f(menuPointWidth, menuPointHeight * 17));
    highScoreBackground.setOrigin(0.5 * highScoreBackground.getSize().x,
                                  0.5 * highScoreBackground.getSize().y);

    mainBackgrounds.clear();
    mainTexts.clear();
    shipBackgrounds.clear();
    shipTexts.clear();

    /*
     * Hauptmenü-Punkte
     */
    for (int i = 0; i < 4; i++) {
        sf::RectangleShape shape;
        shape.setFillColor(menuColor);
        shape.setOutlineColor(sf::Color(255, 255, 255, 150));
        shape.setOutlineThickness(outlineThickness);
        shape.setSize(sf::Vector2f(menuPointWidth, menuPointHeight));
        mainBackgrounds.push_back(shape);

        sf::Text text;
        text.setFont(menuFont);
        text.setCharacterSize((unsigned int) menuPointHeight * 0.7);
        text.setColor(fontColor);
        mainTexts.push_back(text);
    }

    /*
     * Slotmenü-Punkte
     */
    for (int i = 0; i < 4; i++) {
        sf::RectangleShape shape;
        shape.setFillColor(menuColor);
        shape.setOutlineColor(sf::Color(255, 255, 255, 150));
        shape.setOutlineThickness(2);
        shape.setSize(sf::Vector2f(menuPointWidth, menuPointHeight));
        shipBackgrounds.push_back(shape);

        sf::Text text;
        text.setFont(menuFont);
        text.setCharacterSize((unsigned int) menuPointHeight * 0.7);
        text.setColor(fontColor);
        shipTexts.push_back(text);
    }

    /*
     * Texte setzen
     */
    mainTexts[0].setString("New Game");
    mainTexts[1].setString("Highscores");
    mainTexts[2].setString("Toggle Fullscreen");
    mainTexts[3].setString("Exit");
    shipTexts[0].setString("laser");
    shipTexts[1].setString("laser");
    shipTexts[2].setString("laser");
    shipTexts[3].setString("Start");

    highscores = highScoreLoader.getHighScores();
    std::string highscoreString;
    for (int i = 0; i < 10; i++) {
        if (i < highscores.size()) {
            highscoreString += std::to_string(highscores[i]);
            highscoreString += "\n";
        } else {
            highscoreString += "-\n";
        }
    }

    highScoreText.setString(highscoreString);

    /*
     * Mittelpunkte setzen
     */
    highScoreText.setScale(1,1);
    highScoreText.setOrigin(highScoreText.getGlobalBounds().width / 2.f,
                            highScoreText.getGlobalBounds().height / 2.f);
    //highScoreText.setOrigin(highScoreText.getGlobalBounds().width / 2.f,0);

    mainTexts[0].setOrigin(mainTexts[0].getGlobalBounds().width / 2.f,
                           mainTexts[0].getGlobalBounds().height / 2.f);
    mainTexts[1].setOrigin(mainTexts[1].getGlobalBounds().width / 2.f,
                           mainTexts[1].getGlobalBounds().height / 2.f);
    mainTexts[2].setOrigin(mainTexts[2].getGlobalBounds().width / 2.f,
                           mainTexts[2].getGlobalBounds().height / 2.f);
    mainTexts[3].setOrigin(mainTexts[3].getGlobalBounds().width / 2.f,
                           mainTexts[3].getGlobalBounds().height / 2.f);

    shipTexts[0].setOrigin(shipTexts[0].getGlobalBounds().width / 2.f,
                           shipTexts[0].getGlobalBounds().height / 2.f);
    shipTexts[1].setOrigin(shipTexts[1].getGlobalBounds().width / 2.f,
                           shipTexts[1].getGlobalBounds().height / 2.f);
    shipTexts[2].setOrigin(shipTexts[2].getGlobalBounds().width / 2.f,
                           shipTexts[2].getGlobalBounds().height / 2.f);
    shipTexts[3].setOrigin(shipTexts[3].getGlobalBounds().width / 2.f,
                           shipTexts[3].getGlobalBounds().height / 2.f);
}

/**
 * @brief Passt Menü dem Zoom-Faktor an
 */
void MainMenuSystem::resize() {
    /*
    sf::Vector2f size(cameraSize.x * 0.4, cameraSize.y * 0.4);
    statusMenu.setSize(size);
    statusMenu.setOrigin(size * 0.5f);
    statusMenu.setOutlineThickness(4 * scale);*/

    for (int i = 0; i < mainTexts.size(); i++) {
        mainBackgrounds[i].setScale(scale, scale);
        mainTexts[i].setScale(scale, scale);
    }

    for (int i = 0; i < shipTexts.size(); i++) {
        shipBackgrounds[i].setScale(scale, scale);
        shipTexts[i].setScale(scale, scale);
    }

    titleText.setScale(scale, scale);
    shipInfoText.setScale(scale, scale);
    highScoreBackground.setScale(scale, scale);
    highScoreText.setScale(scale, scale);
}

/**
 * @brief Positioniert Menü neu anhand der Kamera-Position
 */
void MainMenuSystem::reposition() {
    for (int i = 0; i < mainTexts.size(); i++) {
        setMainPointPosition(mainTexts[i], mainBackgrounds[i], i);
    }

    for (int i = 0; i < shipTexts.size() - 1; i++) {
        setShipPointPosition(shipTexts[i], shipBackgrounds[i], i);
    }

    setShipPointPosition(shipTexts[3], shipBackgrounds[3], 4);

    sf::Vector2f position
        = sf::Vector2f(cameraView.getCenter().x - 0.5f * cameraView.getSize().x,
                       cameraView.getCenter().y - 0.5f * cameraView.getSize().y
                       + 0.3 * cameraView.getSize().y);
    position += sf::Vector2f(menuPointHeight * scale * 0.5f, 0);
    position -= sf::Vector2f(0, 1.5f * 2 * menuPointHeight * scale);
    titleText.setPosition(position);
    position += sf::Vector2f(menuPointHeight * scale + menuPointWidth * scale,
                             1.5f * 1 * menuPointHeight * scale);
    shipInfoText.setPosition(position);

    sf::Vector2f textPos = cameraView.getCenter();
    //textPos.y -= 0.4 * highScoreBackground.getSize().y * scale;
    highScoreBackground.setPosition(cameraView.getCenter());
    highScoreText.setPosition(textPos);
}


/**
 * @brief Setzt einen Hauptmenü-Punkt
 * @param text Der sf::Text des Punktes
 * @param shape Das sf::RectangleShape des Punktes
 * @param index Der Index des Punktes
 */
void MainMenuSystem::setMainPointPosition(sf::Text& text, sf::RectangleShape& shape,
        unsigned int index) {
    sf::Vector2f position
        = sf::Vector2f(cameraView.getCenter().x - 0.5f * cameraView.getSize().x,
                       cameraView.getCenter().y - 0.5f * cameraView.getSize().y
                       + 0.3 * cameraView.getSize().y);
    position += sf::Vector2f(menuPointHeight * scale * 0.5f,
                             1.5 * index * menuPointHeight * scale);
    shape.setPosition(position);
    sf::Vector2f textPos = position;
    textPos += sf::Vector2f(0.5 * shape.getSize().x * scale, 0.3 * shape.getSize().y * scale);
    text.setPosition(textPos);
}

/**
 * @brief Setzt einen Slotmenü-Punkt
 * @param text Der sf::Text des Punktes
 * @param shape Das sf::RectangleShape des Punktes
 * @param index Der Index des Punktes
 */
void MainMenuSystem::setShipPointPosition(sf::Text& text, sf::RectangleShape& shape,
        unsigned int index) {
    sf::Vector2f position
        = sf::Vector2f(cameraView.getCenter().x - 0.5f * cameraView.getSize().x,
                       cameraView.getCenter().y - 0.5f * cameraView.getSize().y
                       + 0.3 * cameraView.getSize().y);
    position += sf::Vector2f(menuPointHeight * scale * 0.5f,
                             1.5 * index * menuPointHeight * scale);
    position += sf::Vector2f(menuPointHeight * scale + menuPointWidth * scale, 0);
    shape.setPosition(position);
    sf::Vector2f textPos = position;
    textPos += sf::Vector2f(0.5 * shape.getSize().x * scale, 0.3 * shape.getSize().y * scale);
    text.setPosition(textPos);
}

/**
 * @brief Spielt einen Sound ab
 * @param filename Name der Datei
 */
void MainMenuSystem::playSound(std::string filename) {
    EventSoundMessage* soundMessage = new EventSoundMessage;
    soundMessage->event = cmPlaySound;
    soundMessage->file = filename;
    componentList[0].notifyListeners(soundMessage);
    delete soundMessage;
}

/**
 * @brief Setzt die derzeitige Auswahl der Hauptmenü-Punkte
 * @param index Der Index des neuen ausgewählten Punktes
 */
void MainMenuSystem::setMainIndex(int index) {
    if (index < 0) {
        index = 3;
    }

    index = index % 4;
    mainBackgrounds[mainIndex].setFillColor(menuColor);
    mainTexts[mainIndex].setColor(fontColor);
    mainBackgrounds[index].setFillColor(menuHighlightColor);
    mainTexts[index].setColor(fontHighlightColor);
    mainIndex = index;
    playSound("menu_select.wav");
}

/**
 * @brief Setzt die derzeitige Auswahl der Slotmenü-Punktes
 * @param index Der Index des neuen ausgewählten Punktes
 */
void MainMenuSystem::setShipIndex(int index) {

    if (index < 0) {
        index = 3;
    }

    index = index % 4;

    shipBackgrounds[shipIndex].setFillColor(menuColor);
    shipTexts[shipIndex].setColor(fontColor);
    shipBackgrounds[index].setFillColor(menuHighlightColor);
    shipTexts[index].setColor(fontHighlightColor);
    shipIndex = index;
    playSound("menu_select.wav");
}

/**
 * @brief Loggt die Auswahl ein. "Drückt den Knopf"
 */
void MainMenuSystem::enter() {
    if (activeMenu == Menu::MainMenu) {
        switch (mainIndex) {
        case 0:
            activeMenu = Menu::ShipMenu;
            break;

        case 1:
            activeMenu = Menu::HighscoreMenu;
            createMenu();
            resize();
            break;

        case 2:
            if (!fullscreen) {
                std::vector<sf::VideoMode> fullscreenModes = sf::VideoMode::getFullscreenModes();
                window->create(fullscreenModes[0], "Pirateers", sf::Style::None);
                fullscreen = true;
            } else {
                window->create(sf::VideoMode(1200, 800, 32), "Pirateers");
                fullscreen = false;
            }

            break;

        case 3:
            window->close();
            break;

        }

        playSound("menu_enter.wav");
    } else if (activeMenu == Menu::ShipMenu) {
        switch (shipIndex) {
        case 0:
            slotIndices[shipIndex] = (slotIndices[shipIndex] + 1) % 4;
            shipTexts[shipIndex].setString(weapons[slotIndices[shipIndex]]);
            playSound("menu_enter.wav");
            break;

        case 1:
            slotIndices[shipIndex] = (slotIndices[shipIndex] + 1) % 4;
            shipTexts[shipIndex].setString(weapons[slotIndices[shipIndex]]);
            playSound("menu_enter.wav");
            break;

        case 2:
            slotIndices[shipIndex] = (slotIndices[shipIndex] + 1) % 4;
            shipTexts[shipIndex].setString(weapons[slotIndices[shipIndex]]);
            playSound("menu_enter.wav");
            break;

        case 3:
            setOpen(false);
            playSound("menu_enter.wav");
            areaSystem.restart(weapons[slotIndices[0]], weapons[slotIndices[1]], weapons[slotIndices[2]]);
            break;
        }
    }
}

/**
 * @brief Abbruch/ zum vorigen Menü zurückkehren
 */
void MainMenuSystem::cancel() {
    if (activeMenu == Menu::MainMenu) {
        setOpen(false);
    } else if (activeMenu == Menu::ShipMenu) {
        activeMenu = Menu::MainMenu;
        playSound("menu_select.wav");
    } else if (activeMenu == Menu::HighscoreMenu) {
        activeMenu = Menu::MainMenu;
        playSound("menu_select.wav");
    }
}

Handle* MainMenuSystem::createComponent(Settings settings) {
    return GameSystem::createComponent(settings);
}


/**
 * @brief Hauptmenü öffnen/schließen
 * @param value Öffnet das Menü, falls True.
 */
void MainMenuSystem::setOpen(bool value) {
    if ((activeMenu == Menu::MainMenu || activeMenu == Menu::ShipMenu
            || activeMenu == Menu::HighscoreMenu) && !value) {
        activeMenu = Menu::NoMenu;
        EventMessage* message = new EventMessage;
        message->event = evMainMenuClosed;
        componentList[0].notifyListeners(message);
        delete message;
        playSound("menu_close.ogg");
    } else if ((activeMenu == Menu::NoMenu) && value) {
        activeMenu = Menu::MainMenu;
        EventMessage* message = new EventMessage;
        message->event = evMainMenuOpened;
        componentList[0].notifyListeners(message);
        delete message;
        playSound("menu_open.wav");
    }
}

/**
 * @brief Überprüft, ob das Hauptmenü geöffnet ist
 * @return True, falls irgendein Menü geöffnet ist.
 */
bool MainMenuSystem::isOpen() {
    return (activeMenu == Menu::MainMenu || activeMenu == Menu::ShipMenu
            || activeMenu == Menu::HighscoreMenu);
}


/**
 * @copydoc GameSystem::update
 * Zeichnet Menüs
 */
void MainMenuSystem::update(float dt) {
    GameSystem::update(dt);

    if (activeMenu != Menu::NoMenu) {
        for (int i = 0; i < mainTexts.size(); i++) {
            window->draw(mainBackgrounds[i]);
            window->draw(mainTexts[i]);
        }

        window->draw(titleText);

        if (activeMenu == Menu::ShipMenu) {
            for (int i = 0; i < shipTexts.size(); i++) {
                window->draw(shipBackgrounds[i]);
                window->draw(shipTexts[i]);
            }

            window->draw(shipInfoText);
        }

        if (activeMenu == Menu::HighscoreMenu) {
            window->draw(highScoreBackground);
            window->draw(highScoreText);
        }
    }
}

/**
 * @copydoc GameSystem::notify
 * - ::evKeyPressed Eingabe
 * - ::evCameraChanged Menü der Kamera anpassen
 * - ::evWindowResized Menü dem Fenster anpassen
 */
void MainMenuSystem::notify(EventMessage* message) {
    switch (message->event) {
    case evKeyPressed: {
        EventKeyMessage* keyMessage = (EventKeyMessage*) message;

        if (keyMessage->key == Keyboard::Up) {
            if (activeMenu == Menu::MainMenu) {
                setMainIndex(mainIndex - 1);
            } else if (activeMenu == Menu::ShipMenu) {
                setShipIndex(shipIndex - 1);
            }
        } else if (keyMessage->key == Keyboard::Down) {
            if (activeMenu == Menu::MainMenu) {
                setMainIndex(mainIndex + 1);
            } else if (activeMenu == Menu::ShipMenu) {
                setShipIndex(shipIndex + 1);
            }
        } else if (keyMessage->key == Keyboard::Return
                   || keyMessage->key == Keyboard::Right) {
            enter();
        } else if (activeMenu == Menu::NoMenu && keyMessage->key == Keyboard::Escape) {
            setOpen(true);
        } else if (keyMessage->key == Keyboard::Escape
                   || keyMessage->key == Keyboard::BackSpace
                   || keyMessage->key == Keyboard::Left) {
            cancel();
        }

        break;
    }

    case evCameraChanged: {
        EventCameraMessage* cameraMessage = (EventCameraMessage*) message;

        cameraView.setCenter(cameraMessage->center.x, cameraMessage->center.y);
        cameraView.setSize(cameraMessage->size.x, cameraMessage->size.y);

        if (scale != cameraMessage->scale) {
            scale = cameraMessage->scale;
            resize();
        }

        reposition();
        break;
    }

    case evWindowResized: {
        menuPointWidth = std::max(window->getSize().x * 0.3, 300.0);
        createMenu();
        resize();
        break;
    }
    }

    delete message;
}

MainMenuSystem::MainMenuSystem(sf::RenderWindow* window, SoundSystem& soundSystem,
                               AreaSystem& areaSystem, HighScoreLoader& highScoreLoader)
    : window(window), soundSystem(soundSystem), areaSystem(areaSystem),
      highScoreLoader(highScoreLoader) {

    createComponent(Settings());
    menuFont.loadFromFile("../resources/BebasNeue.otf");
    titleFont.loadFromFile("../resources/TERMINAT.TTF");
    titleText.setFont(titleFont);
    createMenu();
    setMainIndex(0);
    setShipIndex(0);

    SoundSettings soundSettings;
    soundSettings.filename = "menu_select.wav";
    selectSoundHandle = soundSystem.createComponent(soundSettings);
    soundSettings.filename = "menu_enter.wav";
    enterSoundHandle = soundSystem.createComponent(soundSettings);
    soundSettings.filename = "menu_open.wav";
    openSoundHandle = soundSystem.createComponent(soundSettings);
    soundSettings.filename = "menu_close.ogg";
    closeSoundHandle = soundSystem.createComponent(soundSettings);
    soundSettings.filename = "menu_error.wav";
    soundSettings.volume = 50;
    errorSoundHandle = soundSystem.createComponent(soundSettings);

    registerComponentAsListener(0, cmPlaySound, selectSoundHandle->id,
                                soundSystem.getEventManager());
    registerComponentAsListener(0, cmPlaySound, enterSoundHandle->id,
                                soundSystem.getEventManager());
    registerComponentAsListener(0, cmPlaySound, openSoundHandle->id,
                                soundSystem.getEventManager());
    registerComponentAsListener(0, cmPlaySound, closeSoundHandle->id,
                                soundSystem.getEventManager());
    registerComponentAsListener(0, cmPlaySound, errorSoundHandle->id,
                                soundSystem.getEventManager());

    weapons[0] = "laser";
    weapons[1] = "plasma";
    weapons[2] = "neutron";
    weapons[3] = "taychon";

    for (int i = 0; i < 3; i++) {
        slotIndices[i] = 0;
    }


}
