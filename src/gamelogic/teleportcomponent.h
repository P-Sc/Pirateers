/**
 * @file teleportcomponent.h
 */

#ifndef TELEPORTCOMPONENT_H
#define TELEPORTCOMPONENT_H

#include "base/component.h"
#include "base/settings.h"

/**
 * @class TeleportComponent
 * @brief Komponente zur Teleportation.
 *
 * Beinhaltet Effekte und versendet ::evTeleported, ::cmActivate und ::cmDeactivate
 */
class TeleportComponent : public Component {
private:
    enum TeleportStatus {teleportingIn, teleportingOut, notTeleporting, inTransit};

    b2Vec2 playerPos;
    float maxOutDelay = 2.f, maxInDelay = 2.5f, delay = 0, flashThreshold = 0, cooldown = 0, maxCooldown = 15;
    TeleportStatus status = notTeleporting;

    void playSound(std::string filename);
    void spawnLight(float size, b2Vec2 offset);
    void setActive(bool active);
    void sendTeleportMessage();
    void sendPlayerSetMessage(bool playerSet);
public:
    Handle* teleportSoundHandle = nullptr;
    Handle* errorSoundHandle = nullptr;
    Handle* flashSoundHandle = nullptr;
    Handle* transitSoundHandle = nullptr;

    void tick(float dt);
    virtual void notify(EventMessage *message);
    TeleportComponent(Settings settings, Handle* handle);
};

#endif // TELEPORTCOMPONENT_H
