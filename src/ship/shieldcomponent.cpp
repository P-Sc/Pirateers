#include "shieldcomponent.h"
#include "graphics/lightsystem.h"


/**
 * @brief Erzeugt einen Schild-Treffer-Effekt
 * @param hitMessage Die EventHitMessage des Treffers.
 */
void ShieldComponent::spawnShieldHit(EventHitMessage* hitMessage) {
    float size = rand() % 5 + 10;
    float duration = size / 50.f;
    b2Vec2 pos = hitMessage->pos;

    EventLightMessage* light = new EventLightMessage;
    light->color = shieldHit1;
    light->duration = duration;
    light->fadeDelay = duration - duration * 0.7f;
    light->pos.Set(pos.x, pos.y);
    light->size = size;
    lightSystem->notify(light);

    light = new EventLightMessage;
    light->color = shieldHit2;
    light->duration = duration;
    light->fadeDelay = duration - duration * 0.7f;
    light->pos = pos;
    light->size = size * 1 / 3.f;
    lightSystem->notify(light);

    /*
    light = new EventLightMessage;
    light->color = shieldHit3;
    light->duration = duration;
    light->fadeDelay = duration - duration * 0.7f;
    light->pos = pos;
    light->size = size * 1 / 3.f;
    lightSystem->notify(light); */
}

/**
 * @brief Erzeugt einen Rumpf-Treffer-Effekt
 * @param hitMessage Die EventHitMessage des Treffers.
 */
void ShieldComponent::spawnHullHit(EventHitMessage* hitMessage) {
    float size = rand() % 5 + 10;
    float duration = size / 50.f;
    b2Vec2 pos = hitMessage->pos;

    EventLightMessage* light = new EventLightMessage;
    light->color = hullHit1;
    light->duration = duration;
    light->fadeDelay = duration - duration * 0.7f;
    light->pos.Set(pos.x, pos.y);
    light->size = size;
    lightSystem->notify(light);

    light = new EventLightMessage;
    light->color = hullHit2;
    light->duration = duration;
    light->fadeDelay = duration - duration * 0.7f;
    light->pos = pos;
    light->size = size * 2 / 3.f;
    lightSystem->notify(light);

    light = new EventLightMessage;
    light->color = hullHit3;
    light->duration = duration;
    light->fadeDelay = duration - duration * 0.7f;
    light->pos = pos;
    light->size = size * 1 / 3.f;
    lightSystem->notify(light);
}


/**
 * @brief Versendet EventSoundMessages.
 * @param filename Name der zu spielenden Datei.
 */
void ShieldComponent::playSound(std::string filename) {
    EventSoundMessage* soundMessage = new EventSoundMessage;
    soundMessage->file = filename;
    notifyListeners(soundMessage);
    delete soundMessage;
}


/**
 * @brief Regeneriert Schild
 * @param value Schild-Wert
 * @return True, falls eine Änderung, sonst False.
 */
bool ShieldComponent::regenShield(float value) {
    int oldValue = shield;
    shield = std::min(shield + value, (float) settings.maxShield);

    if (oldValue == shield) {
        return false;
    } else {
        if (oldValue == 0) {
            playSound("shield_up.ogg");
        }

        return true;
    }
}

/**
 * @brief Regeneriert Rumpf
 * @param value Regenerier-Wert
 * @return True, falls eine Änderung, sonst False.
 */
bool ShieldComponent::regenHull(float value) {
    int oldValue = hull;
    hull = std::min(hull + value, (float) settings.maxHull);

    if (oldValue == hull) {
        return false;
    } else {
        return true;
    }
}

/**
 * @brief Fügt Schaden hinzu
 * @param damage Der hinzugefügt Schaden (positiv)
 */
void ShieldComponent::applyDamage(int damage) {
    if (damage > 0) {
        if (damage < shield) {
            shield -= damage;
        } else {
            hull -= (damage - shield);

            if (shield != 0) {
                shield = 0;
                playSound("shield_down.ogg");
            }

            if (hull < 0) {
                hull = 0;
            }
        }
    }
}

/**
 * @brief Versendet EventShieldMessages
 */
void ShieldComponent::reportChange() {
    EventShieldMessage* shieldMessage = new EventShieldMessage();

    if (hull == 0) {
        shieldMessage->event = evDestroyed;
    }

    shieldMessage->shield = shield;
    shieldMessage->hull = hull;
    shieldMessage->maxShield = settings.maxShield;
    shieldMessage->maxHull = settings.maxHull;
    notifyListeners(shieldMessage);
    delete shieldMessage;
}

/**
 * @brief Setzt das LightSystem.
 * @param lightSystem Das LightSystem.
 */
void ShieldComponent::setLightSystem(LightSystem* lightSystem) {
    this->lightSystem = lightSystem;
}


/**
 * @brief Aktualisiert Komponente.
 * @param dt Zeit in ms.
 */
void ShieldComponent::tick(float dt) {
    if (regenPause == 0) {
        if (regenShield(settings.regenPerSecond * dt / 1000.f)) {
            reportChange();
        }
    } else {
        regenPause = std::max(regenPause - dt / 1000.f, 0.f);
    }
}


/**
 * @copydoc Component::notify
 * - ::evHit Schaden nehmen
 * - ::cmUpgrade Upgraden
 * - ::cmRepair Reparieren
 */
void ShieldComponent::notify(EventMessage* message) {
    switch (message->event) {
    case evHit: {
        EventHitMessage* hitMessage = (EventHitMessage*) message;
        regenPause = settings.maxRegenPause;
        applyDamage(hitMessage->damage);
        reportChange();

        if (shield > 0) {
            spawnShieldHit(hitMessage);
            playSound("shield_hit.wav");
        } else {
            spawnHullHit(hitMessage);
            playSound("hull_hit.wav");
        }

        break;
    }

    case cmUpgrade: {
        EventUpgradeMessage* upMessage = (EventUpgradeMessage*) message;

        if (upMessage->upgrade == "hull") {
            settings.maxHull += upMessage->value;
        } else if (upMessage->upgrade == "shield") {
            settings.maxShield += upMessage->value;
            settings.regenPerSecond += settings.regenPerSecond
                                       * upMessage->value / settings.maxShield;
        }

        break;
    }

    case cmRepair: {
        regenHull(settings.maxHull);
        regenShield(settings.maxShield);
        reportChange();
        break;
    }
    }

    delete message;;
}

ShieldComponent::ShieldComponent(ShieldSettings settings, Handle* handle)
    : Component(settings, handle) {

    shield = settings.maxShield;
    hull = settings.maxHull;
    this->settings = settings;

    Event events[3] = {evShield, evDestroyed, cmPlaySound};
    initializeEvents(events, 3);

}
