/**
 * @file energycomponent.h
 */
#ifndef ENERGYCOMPONENT_H
#define ENERGYCOMPONENT_H

#include "base/component.h"
#include "ship/energysettings.h"


/**
 * @class EnergyComponent
 * @brief Energykomponente. Waffenenergie.
 *
 * Wird mit EnergySettings und EnergySystem benutzt.
 */
class EnergyComponent : public Component {
private:
    EnergySettings settings;
    float energy = 0;
    bool changed = false;
public:
    void reportChange();
    bool regenEnergy(float value);
    void tick(float dt);
    virtual void notify(EventMessage *message);
    EnergyComponent(EnergySettings settings, Handle* handle);
};

#endif // ENERGYCOMPONENT_H
