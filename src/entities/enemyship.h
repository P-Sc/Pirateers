#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H

#include <random>
#include "ship/shipsystem.h"
#include "gamelogic/aisystem.h"

class EnemyShip {
private:
    void multiply(float factor);
protected:
    AISystem& aiSystem;
    ShipSystem& shipSystem;
    Handle* shipHandle = nullptr;
    Handle* aiHandle = nullptr;
    ShipSettings shipSettings;
    AISettings aiSettings;
    std::random_device r;
    std::seed_seq seed{r(), r(), r(), r(), r(), r()};
    std::mt19937 eng{seed};
    void create(float factor);
public:
    EnemyShip(ShipSystem& shipSystem, AISystem& aiSystem);
    virtual ~EnemyShip();
};

#endif // ENEMYSHIP_H
