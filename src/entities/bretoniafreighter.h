#ifndef SMALLTRADER_H
#define SMALLTRADER_H

#include "entities/enemyship.h"
#include "ship/shipsettings.h"

class BretoniaFreighter : public EnemyShip {
public:
    BretoniaFreighter(ShipSystem& shipSystem, AISystem& aiSystem, ShipSettings shipSettings,
                      float multiplier = 1.f);
};

#endif // SMALLTRADER_H
