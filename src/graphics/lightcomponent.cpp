#include "lightcomponent.h"
#include "graphics/textures.h"

LightSettings& LightComponent::getSettings() {
    return settings;
}

/**
 * @brief Aktualisiert Komponente
 * @param dt Zeit in ms
 * @return True, falls Komponente gelöscht werden kann.
 */
bool LightComponent::tick(float dt) {
    if (duration > 0 || delay > 0) {
        if (delay > 0) {
            delay -= dt / 1000.f;
        } else {
            duration = std::max(duration - dt / 1000.f, 0.f);
            fadeDelay -= dt / 1000.f;
            if (fadeDelay <= 0) {
                float iFactor = duration / fadeDuration;
                sf::Color iColor = settings.color;
                iColor.a *= iFactor;
                light.setColor(iColor);
            }
        }
        return false;
    } else if (duration == 0) {
        return true;
    }

    return false;
}


/**
 * @copydoc Component::notify
 * - ::evMove Position aktualisieren
 * - ::cmActivate Licht aktivieren
 * - ::cmDeactivate Licht deaktivieren
 */
void LightComponent::notify(EventMessage* message) {
    switch(message->event) {
    case evMove: {
        EventPosMessage* posMessage = (EventPosMessage*) message;
        //this->settings.pos = posMessage->pos;
        light.setPosition(posMessage->pos.x * 30.f * resolutionFactor,
                          posMessage->pos.y * 30.f * resolutionFactor);
        break;
    }

    case cmActivate: {
        settings.active = true;
        break;
    }

    case cmDeactivate: {
        settings.active = false;
        break;
    }
    }

    delete message;;
}

LightComponent::LightComponent(LightSettings settings, Handle* handle)
    : settings(settings), Component(settings, handle) {

    light.setTexture(Textures::get("light.png"));
    light.setOrigin(0.5f * light.getTexture()->getSize().x,
                    0.5f * light.getTexture()->getSize().y);
    if (delay > 0) {
        light.setColor(sf::Color(0,0,0,0));
    } else {
        light.setColor(settings.color);
    }
    sf::Vector2f lightPos;
    lightPos.x = settings.pos.x;
    lightPos.y = settings.pos.y;
    lightPos *= 30.f * resolutionFactor;
    light.setPosition(lightPos);
    float scale = settings.size / light.getTexture()->getSize().x * 30.f * resolutionFactor;
    light.setScale(scale, scale);
}
