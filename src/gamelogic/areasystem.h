/**
 * @file areasystem.h
 */

#ifndef AREASYSTEM_H
#define AREASYSTEM_H

#include <random>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "base/gamesystem.h"
#include "gamelogic/areacomponent.h"

namespace sf {
    class RenderWindow;
}

class EnemyShip;
class ShipSystem;
class AISystem;
class GraphicsSystem;
class ShopSystem;
class StatusInformationSystem;
class TeleportSystem;
class RewardSystem;
class Player;


/**
 * @class AreaSystem
 * @brief System zur Verwaltung der Gebiete, der Gegner, des Spielers und des derzeitigen
 *        Level-Multiplikators
 *
 * Erstellt jedes Mal, wenn der Spieler sich teleportiert, ein neues Gebiet
 * mit Gegnern, die mit dem Level-Multiplikator skalieren, oder ein Shop-Gebiet.
 * Für jeden erzeugten Gegner steigt der Level-Multiplikator.
 */
class AreaSystem : public GameSystem<AreaComponent, Settings> {
private:
    sf::RenderWindow* window;
    ShipSystem& shipSystem;
    AISystem& aiSystem;
    GraphicsSystem& graphicsSystem;
    ShopSystem& shopSystem;
    StatusInformationSystem& statusInformationSystem;
    TeleportSystem& teleportSystem;
    RewardSystem& rewardSystem;
    Player* player;
    std::vector<Handle*> objects;
    std::vector<EnemyShip*> ships;
    b2Vec2 playerPos;
    Area currentArea = Area::StartArea;
    sf::Font font;
    sf::Text levelText, tutorialText;
    std::random_device r;
    std::seed_seq seed{r(), r(), r(), r(), r(), r()};
    std::mt19937 eng{seed};
    float level = 1.f;
    int gunshipScore = 40, freighterScore = 30, fighterScore = 20, droneScore = 10;

    void sendAreaMessage(Area area);
    void dumpArea();
    void createArea();
    void createShopArea();
    void createBretoniaArea();
    void createBanditArea();
    void createTaulanArea();
    void createAlienArea();
    void createXuruArea();
    void createStartArea();
    virtual Handle* createComponent(Settings settings);
public:
    void setPlayer(Player* player);
    void restart(std::string slot1, std::string slot2, std::string slot3);
    void drawTutorialText();
    virtual void update(float dt);
    virtual void notify(EventMessage *message);
    AreaSystem(sf::RenderWindow* window, ShipSystem& shipSystem, AISystem& aiSystem,
               GraphicsSystem& graphicsSystem, ShopSystem& shopSystem,
               StatusInformationSystem& statusInformationSystem, TeleportSystem& teleportSystem,
               RewardSystem& rewardSystem);
};

#endif // AREASYSTEM_H
