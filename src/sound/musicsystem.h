/**
 * @file musicsystem.h
 */
#ifndef MUSICSYSTEM_H
#define MUSICSYSTEM_H

#include <SFML/Audio/Music.hpp>
#include "base/gamesystem.h"
#include "base/component.h"
#include "base/settings.h"


/**
 * @class MusicSystem
 * @brief System zur Verwaltung von Musik
 *
 * Ändert Musik je nach dem, ob der Spieler gerade im Kampf ist oder ob er sich im
 * Menü befindet.
 */
class MusicSystem : public GameSystem<Component, Settings> {
private:
    sf::Music calmMusic, battleMusic;
    sf::Music* prev = nullptr;
    sf::Music* next = nullptr;
    bool crossfading = false, inBattle = false;
    float crossfadeTime = 4, crossfadeThreshold = 0;
    int volume = 50;

    void crossfade(sf::Music* prev, sf::Music* next);
public:
    virtual void update(float dt);
    virtual void notify(EventMessage *message);
    MusicSystem();
};

#endif // MUSICSYSTEM_H
