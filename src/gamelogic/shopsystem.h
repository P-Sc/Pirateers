/**
 * @file shopsystem.h
 */

#ifndef SHOPSYSTEM_H
#define SHOPSYSTEM_H

#include <SFML/Graphics/Font.hpp>
#include "base/gamesystem.h"
#include "gamelogic/shopcomponent.h"
#include "gamelogic/shopsettings.h"

namespace sf {
    class RenderWindow;
}

class GraphicsSystem;
class InputSystem;
class SoundSystem;
class RewardSystem;
class ShipSystem;


/**
 * @class ShopSystem
 * @brief System zur Verwaltung von Shops.
 *
 * Erzeugt Shops, malt diese und deren Menüs, und leitet
 * ::cmUpgrade Messages weiter.
 */
class ShopSystem : public GameSystem<ShopComponent, ShopSettings> {
private:
    sf::RenderWindow* window;
    GraphicsSystem& graphicsSystem;
    InputSystem& inputSystem;
    SoundSystem& soundSystem;
    RewardSystem& rewardSystem;
    ShipSystem& shipSystem;
    sf::Font menuFont;
    b2Vec2 playerPos;
    Handle* playerHandle = nullptr;
    bool playerAlive = false;

    void drawMainMenu(unsigned int index);
    void drawSubMenu(unsigned int index);
    void sendUpgradeMessages(unsigned int index);
public:
    virtual void update(float dt);
    virtual void notify(EventMessage *message);
    virtual Handle* createComponent(ShopSettings settings);
    virtual void eraseComponent(unsigned int id);
    void setPlayerHandle(Handle* shipHandle);
    ShopSystem(sf::RenderWindow* window, GraphicsSystem& graphicsSystem,
               InputSystem& inputSystem, SoundSystem& soundSystem,
               RewardSystem& rewardSystem, ShipSystem& shipSystem);
};

#endif // SHOPSYSTEM_H
