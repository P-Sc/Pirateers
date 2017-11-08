#include "musicsystem.h"

/**
 * @brief Musik wechseln. Vorherhige Musik ausblenden, nächste Musik einblenden
 * @param prev Vorherige Musik
 * @param next Nächste Musik
 */
void MusicSystem::crossfade(sf::Music* prev, sf::Music* next) {
    crossfading = true;
    crossfadeThreshold = 0;
    next->setVolume(0);
    next->play();
    this->prev = prev;
    this->next = next;
}

/**
 * @copydoc GameSystem::update
 * Crossfading durchführen, falls nötig
 */
void MusicSystem::update(float dt) {
    GameSystem::update(dt);

    if (crossfading) {
        crossfadeThreshold += dt / 1000.f;

        if (crossfadeThreshold >= crossfadeTime) {
            crossfading = false;
            prev->pause();
            next->setVolume(50);
        } else {
            next->setVolume(crossfadeThreshold / crossfadeTime * volume);
            prev->setVolume( (1 - crossfadeThreshold / crossfadeTime) * volume);
        }
    }
}

/**
 * @copydoc GameSystem::notify
 * - ::evAreaChanged Musik ändern
 * - ::evMainMenuOpened Ruhige Musik einschalten
 * - ::evMainMenuClosed Ggf. zur Kampfmusik zurückkehren
 * - ::evNoPlayerSet Ruhige Musik einschalten
 */
void MusicSystem::notify(EventMessage* message) {
    switch (message->event) {
    case evAreaChanged: {
        EventAreaMessage* areaMessage = (EventAreaMessage*) message;

        if ((areaMessage->area == ShopArea || areaMessage->area == StartArea)
                && inBattle == true) {
            crossfade(&battleMusic, &calmMusic);
            inBattle = false;
        } else if (!inBattle && (areaMessage->area != ShopArea && areaMessage->area != StartArea)) {
            crossfade(&calmMusic, &battleMusic);
            inBattle = true;
        }

        break;
    }

    case evMainMenuOpened: {
        if (inBattle) {
            crossfade(&battleMusic, &calmMusic);
        }

        break;
    }

    case evMainMenuClosed: {
        if (inBattle) {
            crossfade(&calmMusic, &battleMusic);
        }

        break;
    }

    case evNoPlayerSet: {
        if (inBattle) {
            crossfade(&battleMusic, &calmMusic);
            inBattle = false;
        }
    }
    }

    delete message;
}

MusicSystem::MusicSystem() {
    calmMusic.openFromFile("../resources/music/calm.ogg");
    calmMusic.setLoop(true);
    calmMusic.setVolume(volume);
    calmMusic.play();

    battleMusic.openFromFile("../resources/music/battle.ogg");
    battleMusic.setLoop(true);
    battleMusic.setVolume(volume);
}
