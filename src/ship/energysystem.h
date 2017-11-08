/**
 * @file energysystem.h
 */
#ifndef ENERGYSYSTEM_H
#define ENERGYSYSTEM_H

#include "base/gamesystem.h"
#include "ship/energycomponent.h"
#include "ship/energysettings.h"


/**
 * @class EnergySystem
 * @brief System zur Verwaltung von Energie.
 *
 * Erstellt lediglicht jedes EnergyComponent und aktualisiert diese.
 */
class EnergySystem : public GameSystem<EnergyComponent, EnergySettings> {
public:
    virtual void update(float dt);
    virtual Handle* createComponent(EnergySettings settings);
    EnergySystem();
};

#endif // ENERGYSYSTEM_H
