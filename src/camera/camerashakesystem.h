/**
 * @file camerashakesystem.h
 */

#ifndef CAMERASHAKESYSTEM_H
#define CAMERASHAKESYSTEM_H

#include "base/gamesystem.h"
#include "camera/camerashakecomponent.h"
#include "camera/camerashakesettings.h"

/**
 * @class CameraShakeSystem
 * @brief System zum Verwalten von Kamera-Wackeln
 *
 * Erstellt und aktualisiert jedes CameraShakeComponent. Gibt außerdem
 * die derzeitige Verschiebung der Kamera durch das Wackeln an.
 */
class CameraShakeSystem : public GameSystem<CameraShakeComponent, CameraShakeSettings> {
private:
    sf::Vector2f totalOffset;
    float scale = 1.f;
public:
    sf::Vector2f getShakeOffset();
    virtual void update(float dt);
    virtual void notify(EventMessage *message);
    virtual Handle* createComponent(CameraShakeSettings settings);
};

#endif // CAMERASHAKESYSTEM_H
