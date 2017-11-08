#include "rewardsystem.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "graphics/graphicssystem.h"
#include "graphics/lightsystem.h"
#include "sound/soundsystem.h"


/**
 * @brief Spielt Einsammel-Sound
 */
void RewardSystem::playCollectSound() {
    EventSoundMessage* soundMessage = new EventSoundMessage;
    soundMessage->file = "reward.flac";
    soundMessage->receiverId = soundHandle->id;
    soundSystem.notifyComponent(soundMessage);
}

/**
 * @brief Gibt derzeitige Credits zurück
 */
int RewardSystem::getCreditStatus() {
    return credits;
}

/**
 * @copydoc GameSystem::update
 *
 * Überprüft, ob Spieler Credits eingesammelt hat und löscht alle Komponenten,
 * falls das Gebiet gewechselt wurde.
 */
void RewardSystem::update(float dt) {
    GameSystem::update(dt);

    if (areaChanged) {
        for (unsigned int i = 0; i < componentList.size(); i++) {
            if (componentList[i].alive) {
                eraseComponent(componentList[i].getId());
            }
        }
        areaChanged = false;
    } else {
        for (unsigned int i = 0; i < componentList.size(); i++) {
            b2Vec2 distance = componentList[i].settings.pos;
            distance -= playerPos;

            if (distance.Length() <= 4) {
                playCollectSound();
                credits += componentList[i].settings.credits;
                totalCollected += componentList[i].settings.credits;
                eraseComponent(componentList[i].getId());
                creditText.setString("Credits: " + std::to_string(credits));
            }
        }
    }


    window->draw(creditText);
}

Handle* RewardSystem::createComponent(RewardSettings settings) {
    Handle* handle = GameSystem::createComponent(settings);

    GraphicsSettings graphicsSettings;
    graphicsSettings.texture = "reward.png";
    graphicsSettings.layer = 1;
    graphicsSettings.pos.x = settings.pos.x;
    graphicsSettings.pos.y = settings.pos.y;
    //graphicsSettings.rectWidth = 60;
    //graphicsSettings.rectHeight = 60;
    Handle* graphicsHandle = graphicsSystem.createComponent(graphicsSettings);

    LightSettings lightSettings;
    lightSettings.color = sf::Color(0, 255, 0, 150);
    lightSettings.size = 5;
    lightSettings.pos = settings.pos;
    Handle* lightHandle = lightSystem.createComponent(lightSettings);

    editLock.lock();
    getComponent(handle->id)->graphicsHandle = graphicsHandle;
    getComponent(handle->id)->lightHandle = lightHandle;
    editLock.unlock();

    return handle;
}


/**
 * @copydoc GameSystem::notify
 * - ::evMove Spielerposition
 * - ::evCameraChanged Passt CreditText an
 * - ::evPurchase Aktualisiert Credits
 * - ::evTeleported Löscht alle rumliegenden Credits
 * - ::evDestroyed Speichert Kontostand als Highscore und setzt Kontostand zurück
 */
void RewardSystem::notify(EventMessage* message) {
    switch (message->event) {
    case evMove: {
        EventPosMessage* posMessage = (EventPosMessage*) message;
        playerPos = posMessage->center;
        break;
    }

    case evCameraChanged: {
        EventCameraMessage* cameraMessage = (EventCameraMessage*) message;
        creditText.setScale(cameraMessage->scale, cameraMessage->scale);
        sf::Vector2f pos(cameraMessage->center.x, cameraMessage->center.y);
        pos += sf::Vector2f(cameraMessage->size.x / 2.f
                            - creditText.getGlobalBounds().width - 20 * cameraMessage->scale,
                            -cameraMessage->size.y / 2.f + 20 * cameraMessage->scale);
        //creditText.setPosition(cameraMessage->center.x, cameraMessage->center.y);
        creditText.setPosition(pos);
        break;
    }

    case evPurchase: {
        if (message->value <= credits) {
            credits -= message->value;
            creditText.setString("Credits: " + std::to_string(credits));
        }

        break;
    }

    case evTeleported: {
        areaChanged = true;
        break;
    }

    case evDestroyed: {
        highScoreLoader.addHighScore(totalCollected);
        credits = 0;
        totalCollected = 0;
        creditText.setString("Credits: " + std::to_string(credits));
        break;
    }
    }

    delete message;;
}


void RewardSystem::eraseComponent(unsigned int id) {
    if (indices.isUsed(id)) {
        editLock.lock();
        Handle* graphicsHandle = getComponent(id)->graphicsHandle;
        Handle* lightHandle = getComponent(id)->lightHandle;
        editLock.unlock();

        delete graphicsHandle;
        delete lightHandle;

        GameSystem::eraseComponent(id);
    }
}

RewardSystem::RewardSystem(sf::RenderWindow* window, GraphicsSystem& graphicsSystem,
                           LightSystem& lightSystem, SoundSystem& soundSystem,
                           HighScoreLoader& highScoreLoader)
    : window(window), graphicsSystem(graphicsSystem), lightSystem(lightSystem),
      soundSystem(soundSystem), highScoreLoader(highScoreLoader) {

    SoundSettings soundSettings;
    soundSettings.filename = "reward.flac";
    soundSettings.volume = 50;

    soundHandle = soundSystem.createComponent(soundSettings);

    creditFont.loadFromFile("../resources/FreeMono.otf");
    creditText.setStyle(sf::Text::Bold);
    creditText.setFont(creditFont);
    creditText.setCharacterSize(35);

    creditText.setFillColor(sf::Color::White);
    creditText.setString("Credits: " + std::to_string(credits));

}
