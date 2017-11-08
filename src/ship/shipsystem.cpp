#include "shipsystem.h"
#include "physics/physicssystem.h"
#include "graphics/graphicssystem.h"
#include "input/inputsystem.h"
#include "debug/modeldisplaysystem.h"
#include "ship/weaponsystem.h"
#include "ship/weapon.h"
#include "camera/camerasystem.h"
#include "gui/tagsystem.h"
#include "ship/shieldsystem.h"
#include "ship/energysystem.h"
#include "ship/explosionsystem.h"
#include "ship/engineeffectsystem.h"
#include "gamelogic/rewardsystem.h"

/**
 * @brief Credits spawnen
 * @param pos Position, an der Credits gespawnt werden sollen
 * @param count Anzahl an Credits
 * @param areaSize Bereich, in dem Credits spawnen sollen
 */
void ShipSystem::spawnRewards(b2Vec2 pos, int count, int areaSize) {
    for (int i = 0; i < count; i++) {
        b2Vec2 spawnPos = pos;
        spawnPos -= b2Vec2((rand() % areaSize) - areaSize / 2.f, (rand() % areaSize) - areaSize / 2.f);
        RewardSettings rewardSettings;
        rewardSettings.pos = spawnPos;
        rewardSystem.createComponent(rewardSettings);
    }
}

/**
 * @brief Alle nötigen Listener-Registrierungen einer Komponente vornehmen
 * @param handle Das Handle der Komponente
 */
void ShipSystem::registerListeners(Handle* handle) {
    editLock.lock();
    const Handle* graphicsHandle = getComponent(handle->id)->graphicsHandle;
    const Handle* physicsHandle = getComponent(handle->id)->physicsHandle;
    const Handle* modelHandle = getComponent(handle->id)->modelHandle;
    const Handle* tagHandle = getComponent(handle->id)->tagHandle;
    const Handle* shieldHandle = getComponent(handle->id)->shieldHandle;
    const Handle* energyHandle = getComponent(handle->id)->energyHandle;
    const Handle* engineEffectHandle = getComponent(handle->id)->engineEffectHandle;
    const std::vector<Handle*> weaponHandles = getComponent(handle->id)->weaponHandles;
    editLock.unlock();

    // Aktivieren / Deaktivieren

    registerComponentAsListener(handle->id, cmActivate, graphicsHandle->id,
                                graphicsSystem.getEventManager());
    registerComponentAsListener(handle->id, cmActivate, physicsHandle->id,
                                physicsSystem.getEventManager());
    registerComponentAsListener(handle->id, cmActivate, modelHandle->id,
                                modelDisplaySystem.getEventManager());
    registerComponentAsListener(handle->id, cmActivate, tagHandle->id,
                                tagSystem.getEventManager());
    registerComponentAsListener(handle->id, cmActivate, engineEffectHandle->id,
                                engineEffectSystem.getEventManager());

    registerComponentAsListener(handle->id, cmDeactivate, graphicsHandle->id,
                                graphicsSystem.getEventManager());
    registerComponentAsListener(handle->id, cmDeactivate, physicsHandle->id,
                                physicsSystem.getEventManager());
    registerComponentAsListener(handle->id, cmDeactivate, modelHandle->id,
                                modelDisplaySystem.getEventManager());
    registerComponentAsListener(handle->id, cmDeactivate, tagHandle->id,
                                tagSystem.getEventManager());
    registerComponentAsListener(handle->id, cmDeactivate, engineEffectHandle->id,
                                engineEffectSystem.getEventManager());

    // Grafik
    physicsSystem.registerComponentAsListener(physicsHandle->id, evMove,
            graphicsHandle->id, graphicsSystem.getEventManager());
    physicsSystem.registerComponentAsListener(physicsHandle->id, evMove,
            modelHandle->id, modelDisplaySystem.getEventManager());
    physicsSystem.registerComponentAsListener(physicsHandle->id, evMove,
            tagHandle->id, tagSystem.getEventManager());
    //if (handle->id == 0)
    registerComponentAsListener(handle->id, cmPowerEngines, engineEffectHandle->id,
                                engineEffectSystem.getEventManager());
    physicsSystem.registerComponentAsListener(physicsHandle->id, evMove,
            engineEffectHandle->id,
            engineEffectSystem.getEventManager());

    physicsSystem.registerComponentAsListener(physicsHandle->id, evMove,
            handle->id, getEventManager());

    // Treffer
    physicsSystem.registerComponentAsListener(physicsHandle->id, evHit,
            graphicsHandle->id, graphicsSystem.getEventManager());
    physicsSystem.registerComponentAsListener(physicsHandle->id, evHit,
            shieldHandle->id, shieldSystem.getEventManager());
    shieldSystem.registerComponentAsListener(shieldHandle->id, evShield,
            tagHandle->id, tagSystem.getEventManager());
    shieldSystem.registerComponentAsListener(shieldHandle->id, evShield,
            handle->id, getEventManager());
    shieldSystem.registerComponentAsListener(shieldHandle->id, evDestroyed,
            handle->id, handle->system->getEventManager());

    // Energie
    energySystem.registerComponentAsListener(energyHandle->id, evEnergyStatus,
            tagHandle->id, tagSystem.getEventManager());
    energySystem.registerComponentAsListener(energyHandle->id, evEnergyStatus,
            handle->id, getEventManager());


    // Steuerung von PhysicsComponent
    registerComponentAsListener(handle->id, cmApplyForce, physicsHandle->id,
                                physicsSystem.getEventManager());
    registerComponentAsListener(handle->id, cmRotateTo, physicsHandle->id,
                                physicsSystem.getEventManager());


    // Upgrades & Repair
    registerComponentAsListener(handle->id, cmRepair, shieldHandle->id,
                                shieldSystem.getEventManager());
    registerComponentAsListener(handle->id, cmUpgrade, shieldHandle->id,
                                shieldSystem.getEventManager());
    registerComponentAsListener(handle->id, cmUpgrade, energyHandle->id,
                                energySystem.getEventManager());

    // Waffen
    for (auto& weaponHandle : weaponHandles) {
        registerComponentAsListener(handle->id, cmAimAt, weaponHandle->id,
                                    weaponSystem.getEventManager());
        registerComponentAsListener(handle->id, cmOpenFire, weaponHandle->id,
                                    weaponSystem.getEventManager());
        registerComponentAsListener(handle->id, cmCeaseFire, weaponHandle->id,
                                    weaponSystem.getEventManager());
        energySystem.registerComponentAsListener(energyHandle->id, evEnergyStatus,
                weaponHandle->id, weaponSystem.getEventManager());
        weaponSystem.registerComponentAsListener(weaponHandle->id, evEnergyUsed,
                energyHandle->id, energySystem.getEventManager());
        registerComponentAsListener(handle->id, cmUpgrade, weaponHandle->id,
                                    weaponSystem.getEventManager());

        registerComponentAsListener(handle->id, cmActivate, weaponHandle->id,
                                    weaponSystem.getEventManager());
        registerComponentAsListener(handle->id, cmDeactivate, weaponHandle->id,
                                    weaponSystem.getEventManager());
    }
}

Handle * ShipSystem::getGraphicsHandle(unsigned int shipId) {
    editLock.lock();
    Handle* handle = componentList[indices.get(shipId)].graphicsHandle;
    editLock.unlock();
    return handle;
}

Handle * ShipSystem::getPhysicsHandle(unsigned int shipId) {
    editLock.lock();
    Handle* handle = componentList[indices.get(shipId)].physicsHandle;
    editLock.unlock();
    return handle;
}

Handle * ShipSystem::getModelHandle(unsigned int shipId) {
    editLock.lock();
    Handle* handle = componentList[indices.get(shipId)].modelHandle;
    editLock.unlock();
    return handle;
}

/**
 * @copydoc GameSystem::update
 * Explosionen erstellen
 */
void ShipSystem::update(float dt) {
    GameSystem::update(dt);

    /*
     * Update explosions
     */
    for (unsigned int i = 0; i < componentList.size(); i++) {
        if (componentList[i].settings.active && componentList[i].exploding) {

            /*
             * Zufällig Explosionen spawnen. Wahrscheinlichkeit für Explosion wird höher
             * je länger es keine gab.
             */
            componentList[i].explosionDelayThreshold += dt;
            componentList[i].settings.explosionDelay -= dt / 1000.f;
            int dice = rand() % 3000;
            if (dice < (int) componentList[i].explosionDelayThreshold) {
                componentList[i].explosionDelayThreshold = 0;
                ExplosionSettings explosionSettings;
                explosionSettings.size = componentList[i].explosionSize * 2;
                b2Vec2 pos = b2Vec2(componentList[i].explosionSize,
                                    componentList[i].explosionSize);
                pos.x *= (rand() % 50 - 25) / 100.f;
                pos.y *= (rand() % 50 - 25) / 100.f;
                pos += componentList[i].pos;
                explosionSettings.pos = pos;
                SoundSettings soundSettings;
                soundSettings.filename = "explosion_small1.ogg";
                explosionSettings.soundSettings = soundSettings;
                explosionSystem.spawnExplosion(explosionSettings);
            }

            /*
             * "Endexplosion" spawnen und Komponente löschen, falls eingestellte
             * Verzögerung erreicht
             */
            if (componentList[i].settings.explosionDelay <= 0) {
                ExplosionSettings explosionSettings;
                explosionSettings.size = componentList[i].explosionSize * 8;
                explosionSettings.pos = componentList[i].pos;
                SoundSettings soundSettings;
                soundSettings.filename = "explosion_big2.ogg";
                explosionSettings.soundSettings = soundSettings;
                explosionSystem.spawnExplosion(explosionSettings);

                // Spawn rewards
                int rewardCount = componentList[i].settings.rewardCount;
                b2Vec2 pos = componentList[i].pos;
                spawnRewards(pos, rewardCount, componentList[i].explosionSize);

                EventMessage* message = new EventMessage(evDestroyed);
                componentList[i].notifyListeners(message);
                delete message;
                eraseComponent(componentList[i].getId());
            }
        }
    }
}


void ShipSystem::notify(EventMessage *message) {
    delete message;;
}


Handle* ShipSystem::createComponent(ShipSettings& settings) {

    if (settings.shipname != "" && parser.isShipStored(settings.shipname)) {

        // Settings laden
        ShipSettings shipSettings = parser.ships[settings.shipname];
        settings.propulsion = shipSettings.propulsion;
        settings.maxTorque = shipSettings.maxTorque;
        GraphicsSettings graphicsSettings = parser.shipGraphics[settings.shipname];
        graphicsSettings.layer = 2;
        PhysicsSettings physicsSettings = parser.shipPhysics[settings.shipname];
        physicsSettings.pos = settings.pos;
        physicsSettings.rotation = settings.rotation;
        ModelSettings modelSettings;
        modelSettings.shapes = physicsSettings.shapes;
        TagSettings tagSettings;
        tagSettings.height = std::max(graphicsSettings.rectWidth / 30.f,
                                      graphicsSettings.rectHeight / 30.f)
                             * graphicsSettings.scale;
        tagSettings.gap = std::min(graphicsSettings.rectWidth / 30.f,
                                   graphicsSettings.rectHeight / 30.f)
                          * graphicsSettings.scale;
        tagSettings.color = sf::Color(250, 0, 0, 150);

        Handle* handle = GameSystem::createComponent(settings);
        Handle* graphicsHandle = graphicsSystem.createComponent(graphicsSettings);
        Handle* physicsHandle = physicsSystem.createComponent(physicsSettings);
        Handle* modelHandle = modelDisplaySystem.createComponent(modelSettings);
        Handle* tagHandle = tagSystem.createComponent(tagSettings);
        Handle* shieldHandle = shieldSystem.createComponent(settings.shieldSettings);
        Handle* energyHandle = energySystem.createComponent(settings.energySettings);
        Handle* engineEffectHandle = engineEffectSystem.createComponent(settings.engineEffectSettings);

        int slot = 0;

        for (auto& weapon : settings.weapons) {
            weapon.slot = slot;
            slot++;
            Handle* weaponHandle = weaponSystem.createComponent(weapon, physicsHandle);
            editLock.lock();
            getComponent(handle->id)->weaponHandles.push_back(weaponHandle);
            editLock.unlock();
        }

        editLock.lock();
        getComponent(handle->id)->graphicsHandle = graphicsHandle;
        getComponent(handle->id)->physicsHandle = physicsHandle;
        getComponent(handle->id)->modelHandle = modelHandle;
        getComponent(handle->id)->tagHandle = tagHandle;
        getComponent(handle->id)->shieldHandle = shieldHandle;
        getComponent(handle->id)->energyHandle = energyHandle;
        getComponent(handle->id)->engineEffectHandle = engineEffectHandle;
        getComponent(handle->id)->explosionSize = std::max(graphicsSettings.rectWidth / 30.f,
                graphicsSettings.rectHeight / 30.f) * graphicsSettings.scale;
        editLock.unlock();

        registerListeners(handle);

        return handle;
    } else {
        return nullptr;
    }
}

void ShipSystem::eraseComponent(unsigned int id) {
    if (indices.isUsed(id)) {
        editLock.lock();
        Handle* graphicsHandle = getComponent(id)->graphicsHandle;
        Handle* physicsHandle = getComponent(id)->physicsHandle;
        Handle* modelHandle = getComponent(id)->modelHandle;
        Handle* tagHandle = getComponent(id)->tagHandle;
        Handle* shieldHandle = getComponent(id)->shieldHandle;
        Handle* energyHandle = getComponent(id)->energyHandle;
        Handle* engineEffectHandle = getComponent(id)->engineEffectHandle;
        std::vector<Handle*> weaponHandles = getComponent(id)->weaponHandles;
        editLock.unlock();

        delete graphicsHandle;
        delete tagHandle;
        delete energyHandle;
        delete shieldHandle;
        delete modelHandle;
        delete physicsHandle;
        delete engineEffectHandle;

        for (unsigned int i = weaponHandles.size() - 1; i != static_cast<unsigned>(-1); --i) {
            delete weaponHandles[i];
        }

        GameSystem::eraseComponent(id);
    }
}


ShipSystem::ShipSystem(PhysicsSystem& physicsSystem, GraphicsSystem& graphicsSystem,
                       ModelDisplaySystem & modelDisplaySystem, WeaponSystem &weaponSystem,
                       TagSystem &tagSystem, ShieldSystem& shieldSystem, EnergySystem& energySystem,
                       ExplosionSystem& explosionSystem, RewardSystem& rewardSystem,
                       EngineEffectSystem& engineEffectSystem)
    : GameSystem(), physicsSystem(physicsSystem), graphicsSystem(graphicsSystem)
    , modelDisplaySystem(modelDisplaySystem), weaponSystem(weaponSystem), tagSystem(tagSystem)
    , shieldSystem(shieldSystem), energySystem(energySystem), explosionSystem(explosionSystem)
    , rewardSystem(rewardSystem), engineEffectSystem(engineEffectSystem), parser(true) {

    parser.parseDirectory("./../resources/ships/");
}
