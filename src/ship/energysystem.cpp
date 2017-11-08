#include "energysystem.h"

void EnergySystem::update(float dt) {
    GameSystem::update(dt);

    for (unsigned int i = 0; i < componentList.size(); i++) {
        componentList[i].tick(dt);
    }
}

Handle* EnergySystem::createComponent(EnergySettings settings) {
    return GameSystem::createComponent(settings);
}

EnergySystem::EnergySystem() {

}
