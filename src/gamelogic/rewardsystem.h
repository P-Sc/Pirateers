/**
 * @file rewardsystem.h
 */

#ifndef REWARDSYSTEM_H
#define REWARDSYSTEM_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include "base/gamesystem.h"
#include "gamelogic/rewardcomponent.h"
#include "gamelogic/rewardsettings.h"
#include "utils/highscoreloader.h"

namespace sf {
    class RenderWindow;
}

class GraphicsSystem;
class LightSystem;
class SoundSystem;


/**
 * @class RewardSystem
 * @brief System zur Verwaltung von Credits
 *
 * Speichert und zeigt den derzeitigen Kontostand des Spielers
 * und erzeugt Loot von Gegnern (RewardComponent).
 */
class RewardSystem : public GameSystem<RewardComponent, RewardSettings> {
private:
    sf::RenderWindow* window;
    sf::Font creditFont;
    sf::Text creditText;
    GraphicsSystem& graphicsSystem;
    LightSystem& lightSystem;
    SoundSystem& soundSystem;
    HighScoreLoader& highScoreLoader;
    b2Vec2 playerPos;
    Handle* soundHandle;
    int credits = 0, totalCollected = 0;
    bool areaChanged = false;

    void playCollectSound();
public:
    int getCreditStatus();
    virtual void update(float dt);
    virtual Handle* createComponent(RewardSettings settings);
    virtual void notify(EventMessage *message);
    virtual void eraseComponent(unsigned int id);
    RewardSystem(sf::RenderWindow* window, GraphicsSystem& graphicsSystem, LightSystem& lightSystem,
                 SoundSystem& soundSystem, HighScoreLoader& highScoreLoader);
};

#endif // REWARDSYSTEM_H
