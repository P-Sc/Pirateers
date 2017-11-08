/**
 * @file weaponcomponent.h
 */
#ifndef WEAPONCOMPONENT_H
#define WEAPONCOMPONENT_H

#include "base/component.h"
#include "ship/weaponsettings.h"

/**
 * @class WeaponComponent
 * @brief Waffenkomponente. Verwaltet Waffe.
 *
 * Beinhaltet nicht die Logik für das Schießen der Projektile selbst(@see AmmoComponent), sondern nur für
 * die Waffe.
 * Wird mit WeaponSettings und WeaponSystem benutzt.
 */
class WeaponComponent : public Component {
private:
    WeaponSettings settings;
public:
    Handle* physicsHandle = nullptr;
    Handle* graphicsHandle = nullptr;
    Handle* modelHandle = nullptr;
    Handle* ammoHandle = nullptr;
    virtual void notify(EventMessage *message);
    WeaponComponent(WeaponSettings settings, Handle* handle);
};

#endif // WEAPONCOMPONENT_H
