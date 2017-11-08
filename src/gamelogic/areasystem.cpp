#include "areasystem.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "ship/shipsystem.h"
#include "gamelogic/aisystem.h"
#include "graphics/graphicssystem.h"
#include "gamelogic/shopsystem.h"
#include "gamelogic/teleportsystem.h"
#include "gamelogic/rewardsystem.h"
#include "gui/statusinformationsystem.h"
#include "entities/enemyship.h"
#include "entities/bretoniafighter.h"
#include "entities/bretoniafreighter.h"
#include "entities/bretoniagunship.h"
#include "entities/aliendrone.h"
#include "entities/alienfighter.h"
#include "entities/banditdrone.h"
#include "entities/banditfreighter.h"
#include "entities/taulonfreighter.h"
#include "entities/xurufreighter.h"
#include "entities/xurugunship.h"
#include "entities/player.h"


/**
 * @brief Versendet evAreaCHanged mit einer Area
 * @param area Die Area
 */
void AreaSystem::sendAreaMessage(Area area) {
    EventAreaMessage* areaMessage = new EventAreaMessage;
    areaMessage->area = area;
    componentList[0].notifyListeners(areaMessage);
    delete areaMessage;
}

/**
 * @brief Löscht alles in dem Areal
 */
void AreaSystem::dumpArea() {
    for (auto &object : objects) {
        delete object;
    }

    for (auto &ship : ships) {
        delete ship;
    }

    objects.clear();
    ships.clear();
}


/**
 * @brief Erstellt ein zufälliges Areal, welches nicht mit dem derzeitigen übereinstimmt.
 */
void AreaSystem::createArea() {
    dumpArea();
    Area dice;
    std::uniform_int_distribution<> dist(0,5);
    do {
        dice = static_cast<Area>(dist(eng));
    } while (dice == currentArea);

    currentArea = dice;

    switch (dice) {
    case ShopArea:
        createShopArea();
        break;

    case BretoniaArea:
        createBretoniaArea();
        break;

    case BanditArea:
        createBanditArea();
        break;

    case TaulanArea:
        createTaulanArea();
        break;

    case AlienArea:
        createAlienArea();
        break;

    case XuruArea:
        createXuruArea();
        break;
    }

    sendAreaMessage(dice);

    this->levelText.setString("Level: " + std::to_string((int)level));
}


/**
 * @brief Erstellt ein Shop-Gebiet
 */
void AreaSystem::createShopArea() {
    b2Vec2 spawnCenter(rand() % 300 - 150, rand() % 300 - 150);
    spawnCenter += playerPos;
    ShopSettings shopSettings;
    shopSettings.pos = spawnCenter;
    Handle* shopHandle = shopSystem.createComponent(shopSettings);
    objects.push_back(shopHandle);
    shopSystem.registerSystemAsListener(shopHandle->id, cmUpgrade,
                                        statusInformationSystem.getEventManager());

    GraphicsSettings graphicsSettings;

    for (int i = 0; i < 20; i++) {
        graphicsSettings.pos.x = rand() % 100 - 50 + spawnCenter.x;
        graphicsSettings.pos.y = rand() % 100 - 50 + spawnCenter.y;
        graphicsSettings.rotation = rand() % 360;
        graphicsSettings.layer = 0;
        graphicsSettings.scale = 0.4f + (rand() % 6) / 10.f;
        graphicsSettings.texture = "environment/shop1.png";
        float brightness = (rand() % 50 + 50) / 100.f;
        graphicsSettings.color = sf::Color(255 * brightness,  255 * brightness, 255 * brightness);
        objects.push_back(graphicsSystem.createComponent(graphicsSettings));
    }
}


/**
 * @brief Erstellt ein Bretonia-Gebiet
 */
void AreaSystem::createBretoniaArea() {
    int freighterCount = 1 + rand() % 2 + rand() % (int) level;

    ShipSettings shipSettings;
    b2Vec2 spawnCenter(rand() % 300 - 150, rand() % 300 - 150);
    spawnCenter += playerPos;
    shipSettings.rotation = (rand() % ((int)M_PI * 100)) / 100.f;

    for (int i = 0; i < freighterCount; i++) {
        shipSettings.pos = spawnCenter;
        shipSettings.pos += b2Vec2(rand() % 15 - 30, rand() % 15 - 30);
        ships.emplace_back(new BretoniaFreighter(shipSystem, aiSystem, shipSettings));
    }

    int score = freighterCount * freighterScore;
    level += score * 0.003;

    while (score > 0) {
        shipSettings.pos.Set(rand() % 300 - 150, rand() % 300 - 150);
        shipSettings.pos += spawnCenter;
        shipSettings.rotation = (rand() % ((int)M_PI * 100)) / 100.f;

        int dice = rand() % 10;

        if (dice <= 1) {
            ships.emplace_back(new BretoniaGunship(shipSystem, aiSystem, shipSettings, level));
            score -= gunshipScore;
        } else if (dice <= 3) {
            ships.emplace_back(new BretoniaFreighter(shipSystem, aiSystem, shipSettings, level));
            score -= freighterScore;
        } else {
            ships.emplace_back(new BretoniaFighter(shipSystem, aiSystem, shipSettings, level));
            score -= fighterScore;
        }
    }

    GraphicsSettings graphicsSettings;

    for (int i = 0; i < 20; i++) {
        graphicsSettings.pos.x = rand() % 500 - 250 + spawnCenter.x;
        graphicsSettings.pos.y = rand() % 500 - 250 + spawnCenter.y;
        graphicsSettings.rotation = rand() % 360;
        graphicsSettings.layer = 0;
        graphicsSettings.scale = 0.9f + (rand() % 6) / 10.f;
        graphicsSettings.texture = "environment/bretonia" + std::to_string(rand() % 4) + ".png";
        float brightness = (rand() % 60 + 40) / 100.f;
        graphicsSettings.color = sf::Color(255 * brightness,  150 * brightness, 0);
        objects.push_back(graphicsSystem.createComponent(graphicsSettings));
    }
}


/**
 * @brief Erstellt ein Banditen-Gebiet
 */
void AreaSystem::createBanditArea() {
    int freighterCount = 1 + rand() % 2 + rand() % (int) level;
    b2Vec2 spawnCenter(rand() % 300 - 150, rand() % 300 - 150);
    spawnCenter += playerPos;

    ShipSettings shipSettings;
    shipSettings.rotation = (rand() % ((int)M_PI * 100)) / 100.f;

    for (int i = 0; i < freighterCount; i++) {
        shipSettings.pos = spawnCenter;
        shipSettings.pos += b2Vec2(rand() % 15 - 30, rand() % 15 - 30);
        ships.emplace_back(new BanditFreighter(shipSystem, aiSystem, shipSettings));
    }

    int score = freighterCount * freighterScore;
    level += score * 0.003;

    while (score > 0) {
        shipSettings.pos.Set(rand() % 300 - 150, rand() % 300 - 150);
        shipSettings.pos += spawnCenter;
        shipSettings.rotation = (rand() % ((int)M_PI * 100)) / 100.f;

        int dice = rand() % 10;

        if (dice <= 2) {
            ships.emplace_back(new BanditFreighter(shipSystem, aiSystem, shipSettings, level));
            score -= freighterScore;
        } else {
            ships.emplace_back(new BanditDrone(shipSystem, aiSystem, shipSettings, level));
            score -= droneScore;
        }
    }


    GraphicsSettings graphicsSettings;

    for (int i = 0; i < 20; i++) {
        graphicsSettings.pos.x = rand() % 500 - 250 + spawnCenter.x;
        graphicsSettings.pos.y = rand() % 500 - 250 + spawnCenter.y;
        graphicsSettings.rotation = rand() % 360;
        graphicsSettings.layer = 0;
        graphicsSettings.scale = 0.3f + (rand() % 5) / 10.f;
        graphicsSettings.texture = "environment/bandits" + std::to_string(rand() % 2) + ".png";
        float brightness = (rand() % 30 + 30) / 100.f;
        graphicsSettings.color = sf::Color(255 * brightness,  255 * brightness, 255 * brightness);
        objects.push_back(graphicsSystem.createComponent(graphicsSettings));
    }
}


/**
 * @brief Erstellt ein Taulan-Gebiet
 */
void AreaSystem::createTaulanArea() {

    int freighterCount = 1 + rand() % (int) level;
    b2Vec2 spawnCenter(rand() % 300 - 150, rand() % 300 - 150);
    spawnCenter += playerPos;

    ShipSettings shipSettings;
    shipSettings.rotation = (rand() % ((int)M_PI * 100)) / 100.f;

    for (int i = 0; i < freighterCount; i++) {
        shipSettings.pos = spawnCenter;
        shipSettings.pos += b2Vec2(rand() % 15 - 30, rand() % 15 - 30);
        ships.emplace_back(new TaulonFreighter(shipSystem, aiSystem, shipSettings));
    }

    int score = freighterCount * freighterScore * 1.5f;
    level += score * 0.003;


    GraphicsSettings graphicsSettings;

    for (int i = 0; i < 10; i++) {
        graphicsSettings.pos.x = rand() % 500 - 250 + spawnCenter.x;
        graphicsSettings.pos.y = rand() % 500 - 250 + spawnCenter.y;
        graphicsSettings.layer = 0;
        graphicsSettings.scale = 3.f + (rand() % 6) / 10.f;
        graphicsSettings.texture = "environment/taulan" + std::to_string(rand() % 6) + ".png";
        float brightness = (rand() % 50 + 50) / 100.f;
        graphicsSettings.color = sf::Color(255 * brightness,  255 * brightness, 255 * brightness);
        objects.push_back(graphicsSystem.createComponent(graphicsSettings));
    }

    for (int i = 0; i < 10; i++) {
        graphicsSettings.pos.x = rand() % 500 - 250 + spawnCenter.x;
        graphicsSettings.pos.y = rand() % 500 - 250 + spawnCenter.y;
        graphicsSettings.layer = 0;
        graphicsSettings.scale = 1.f + (rand() % 6) / 10.f;
        graphicsSettings.texture = "environment/taulan" + std::to_string(rand() % 2 + 4) + ".png";
        float brightness = (rand() % 50 + 50) / 100.f;
        graphicsSettings.color = sf::Color(255 * brightness,  255 * brightness, 255 * brightness);
        objects.push_back(graphicsSystem.createComponent(graphicsSettings));
    }
}


/**
 * @brief Erstellt ein Alien-Gebiet
 */
void AreaSystem::createAlienArea() {
    int freighterCount = 1 + rand() % 3 + rand() % (int) level;
    b2Vec2 spawnCenter(rand() % 300 - 150, rand() % 300 - 150);
    spawnCenter += playerPos;

    ShipSettings shipSettings;

    int score = freighterCount * freighterScore;
    level += score * 0.003;

    while (score > 0) {
        shipSettings.pos.Set(rand() % 300 - 150, rand() % 300 - 150);
        shipSettings.pos += spawnCenter;
        shipSettings.rotation = (rand() % ((int)M_PI * 100)) / 100.f;

        int dice = rand() % 10;

        if (dice <= 5) {
            ships.emplace_back(new AlienFighter(shipSystem, aiSystem, shipSettings, level));
            score -= freighterScore;
        } else {
            ships.emplace_back(new AlienDrone(shipSystem, aiSystem, shipSettings, level));
            score -= droneScore;
        }
    }

    GraphicsSettings graphicsSettings;
    graphicsSettings.rotation = rand() % 360;

    for (int i = 0; i < 35; i++) {
        graphicsSettings.pos.x = rand() % 500 - 250 + spawnCenter.x;
        graphicsSettings.pos.y = rand() % 500 - 250 + spawnCenter.y;
        graphicsSettings.layer = 0;
        graphicsSettings.scale = 0.9f + (rand() % 6) / 10.f;
        graphicsSettings.texture = "environment/alien1.png";
        float brightness = (rand() % 70 + 30) / 100.f;
        graphicsSettings.color = sf::Color(255 * brightness,  255 * brightness, 255 * brightness);
        objects.push_back(graphicsSystem.createComponent(graphicsSettings));
    }
}


/**
 * @brief Erstellt ein Xuru-Gebiet
 */
void AreaSystem::createXuruArea() {
    int freighterCount = 1 + rand() % (int) level;
    b2Vec2 spawnCenter(rand() % 300 - 150, rand() % 300 - 150);
    spawnCenter += playerPos;

    ShipSettings shipSettings;
    shipSettings.rotation = (rand() % ((int)M_PI * 100)) / 100.f;

    for (int i = 0; i < freighterCount; i++) {
        shipSettings.pos = spawnCenter;
        shipSettings.pos += b2Vec2(rand() % 15 - 30, rand() % 15 - 30);
        ships.emplace_back(new XuruFreighter(shipSystem, aiSystem, shipSettings));
    }

    int score = freighterCount * freighterScore;
    level += score * 0.003;

    while (score > 0) {
        shipSettings.pos.Set(rand() % 300 - 150, rand() % 300 - 150);
        shipSettings.pos += spawnCenter;
        shipSettings.rotation = (rand() % ((int)M_PI * 100)) / 100.f;

        int dice = rand() % 10;

        if (dice <= 2) {
            ships.emplace_back(new XuruFreighter(shipSystem, aiSystem, shipSettings, level));
            score -= freighterScore * 1.5;
        } else {
            ships.emplace_back(new XuruGunship(shipSystem, aiSystem, shipSettings, level));
            score -= droneScore * 2.f;
        }
    }

    GraphicsSettings graphicsSettings;

    for (int i = 0; i < 20; i++) {
        graphicsSettings.pos.x = rand() % 500 - 250 + spawnCenter.x;
        graphicsSettings.pos.y = rand() % 500 - 250 + spawnCenter.y;
        graphicsSettings.rotation = rand() % 360;
        graphicsSettings.layer = 0;
        graphicsSettings.scale = 0.4f + (rand() % 7) / 10.f;
        graphicsSettings.texture = "environment/xuru1.png";
        float brightness = (rand() % 80 + 10) / 100.f;
        graphicsSettings.color = sf::Color(255 * brightness,  255 * brightness, 255 * brightness);
        objects.push_back(graphicsSystem.createComponent(graphicsSettings));
    }
}


/**
 * @brief Erstellt ein Start-Gebiet (Hat nur Anleitung)
 */
void AreaSystem::createStartArea() {
    b2Vec2 spawnCenter(rand() % 10 - 5, rand() % 10 - 5);
    spawnCenter += playerPos;

    tutorialText.setString("Controls: \nW,S : Power engine\nLeft mouse button: Hold and move the mouse to steer\nRight mouse button: Fire weapons\nG: Teleport\nJ: Show weapon information\nK: Show ship information\nF2: Show hitboxes\nF3: Show AI debug\nF4: Switch AI accuracy mode\nF5: Fast-switch to next area");
    tutorialText.setPosition(spawnCenter.x, spawnCenter.y);
}

Handle* AreaSystem::createComponent(Settings settings) {
    return GameSystem::createComponent(settings);
}


/**
 * @brief Setzt den Spieler
 */
void AreaSystem::setPlayer(Player* player) {
    this->player = player;
}


/**
 * @brief Startet das Spiel neu
 * @param slot1 Waffe in Slot 1
 * @param slot2 Waffe in Slot 2
 * @param slot3 Waffe in Slot 3
 */
void AreaSystem::restart(std::string slot1, std::string slot2, std::string slot3) {
    dumpArea();
    playerPos.Set(0,0);
    createStartArea();
    sendAreaMessage(Area::StartArea);
    level = 1;
    this->levelText.setString("Level: " + std::to_string((int)level));
    player->destroy();
    player->setWeapons(slot1, slot2, slot3);
    player->setPosition(b2Vec2(0,0));
    player->create();
    shipSystem.registerSystemAsListener(player->getShipHandle()->id, evMove, getEventManager());
    shipSystem.registerSystemAsListener(player->getShipHandle()->id, evDestroyed, getEventManager());
    shipSystem.registerSystemAsListener(player->getShipHandle()->id, evDestroyed, rewardSystem.getEventManager());
    registerComponentAsListener(0, evAreaChanged, player->getTeleportHandle()->id,
                                           teleportSystem.getEventManager());
    teleportSystem.registerSystemAsListener(player->getTeleportHandle()->id, evTeleported,
                                            getEventManager());
    teleportSystem.registerSystemAsListener(player->getTeleportHandle()->id, evTeleported,
                                            rewardSystem.getEventManager());
    teleportSystem.registerSystemAsListener(player->getTeleportHandle()->id, evPlayerSet,
                                            aiSystem.getEventManager());
    teleportSystem.registerSystemAsListener(player->getTeleportHandle()->id, evNoPlayerSet,
                                            aiSystem.getEventManager());

    EventMessage* message = new EventMessage(evPlayerSet);
    componentList[0].notifyListeners(message);
    delete message;
}


/**
 * @brief Zeichnet den Tutorial-Text (nur im Startgebiet)
 */
void AreaSystem::drawTutorialText() {
    if (currentArea == Area::StartArea) {
        window->draw(tutorialText);
    }
}


/**
 * @brief AreaSystem::update
 * @param dt
 */
void AreaSystem::update(float dt) {
    GameSystem::update(dt);
    window->draw(levelText);
}


/**
 * @copydoc GameSystem::notify
 * - ::evKeyPressed Debug
 * - ::evMove Spielerposition
 * - ::evTelported Wechselt das Areal
 * - ::evCameraChanged Aktualisiert Level-Text-Position
 * - ::evDestroyed Versendet evNoPlayerSet
 */
void AreaSystem::notify(EventMessage* message) {
    switch(message->event) {
    case evKeyPressed: {
        EventKeyMessage* keyMessage = (EventKeyMessage*) message;

        if (keyMessage->key == Keyboard::F5) {
            createArea();
        }

        break;
    }

    case evMove: {
        EventPosMessage* posMessage = (EventPosMessage*) message;
        playerPos = posMessage->center;
        break;
    }

    case evTeleported: {
        createArea();
        break;
    }

    case evCameraChanged: {
        EventCameraMessage* cameraMessage = (EventCameraMessage*) message;
        levelText.setScale(cameraMessage->scale, cameraMessage->scale);
        sf::Vector2f pos(cameraMessage->center.x, cameraMessage->center.y);
        pos -= sf::Vector2f(cameraMessage->size.x / 2.f
                            - 20 * cameraMessage->scale,
                            cameraMessage->size.y / 2.f - 20 * cameraMessage->scale);
        //creditText.setPosition(cameraMessage->center.x, cameraMessage->center.y);
        levelText.setPosition(pos);
        break;
    }

    case evDestroyed: {
        EventMessage* message = new EventMessage(evNoPlayerSet);
        componentList[0].notifyListeners(message);
        delete message;
        break;
    }
    }

    delete message;
}

AreaSystem::AreaSystem(sf::RenderWindow* window, ShipSystem& shipSystem, AISystem& aiSystem,
                       GraphicsSystem& graphicsSystem, ShopSystem& shopSystem,
                       StatusInformationSystem& statusInformationSystem,
                       TeleportSystem& teleportSystem, RewardSystem& rewardSystem)
    : window(window), shipSystem(shipSystem), aiSystem(aiSystem), graphicsSystem(graphicsSystem)
    , shopSystem(shopSystem), statusInformationSystem(statusInformationSystem),
      teleportSystem(teleportSystem), rewardSystem(rewardSystem) {
    createComponent(Settings());

    font.loadFromFile("../resources/FreeMono.otf");
    //levelText.setStyle(sf::Text::Bold);
    levelText.setFont(font);
    levelText.setCharacterSize(35);
    levelText.setColor(sf::Color::White);
    levelText.setString("Level: " + std::to_string((int)level));
    tutorialText.setFont(font);
    tutorialText.setCharacterSize(35);
    tutorialText.setColor(sf::Color::White);
}
