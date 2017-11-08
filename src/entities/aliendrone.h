#ifndef ALIENDRONE_H
#define ALIENDRONE_H

#include "entities/enemyship.h"
#include "ship/shipsettings.h"

/**
 * @class AlienDrone
 */
class AlienDrone : public EnemyShip {
public:
    AlienDrone(ShipSystem& shipSystem, AISystem& aiSystem, ShipSettings shipSettings,
               float multiplier = 1.f);
};

#endif // ALIENDRONE_H
