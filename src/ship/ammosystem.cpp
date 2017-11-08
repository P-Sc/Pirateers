#include "ammosystem.h"
#include "physics/physicssystem.h"
#include "graphics/graphicssystem.h"
#include "graphics/lightsystem.h"
#include "camera/camerashakesystem.h"
#include "sound/soundsystem.h"

/**
 * @brief Projektile für eine Komponente neu erstellen
 * @param index Der Index der Komponente
 */
void AmmoSystem::createComponentProjectiles(unsigned int index) {
    AmmoSettings settings = componentList[index].settings;
    float maxProjectileLifetime = settings.range / settings.velocity;
    unsigned int vectorSize = settings.rateOfFire * maxProjectileLifetime + 1;
    componentList[index].idleProjectiles.reserve(vectorSize);
    componentList[index].activeProjectiles.reserve(vectorSize);
    componentList[index].maxProjectileLifetime = maxProjectileLifetime;
    componentList[index].firingGap = 1.f / settings.rateOfFire;

    for (size_t i = 0; i < componentList[index].idleProjectiles.size(); i++) {
        delete componentList[index].idleProjectiles[i];
    }

    for (size_t i = 0; i < componentList[index].activeProjectiles.size(); i++) {
        delete componentList[index].activeProjectiles[i];
    }

    componentList[index].idleProjectiles.clear();
    componentList[index].activeProjectiles.clear();

    for (unsigned int i = 0; i < vectorSize; i++) {
        Projectile* p = new Projectile;
        p->graphicsHandle = graphicsSystem.createComponent(settings.graphicsSettings);
        p->lightHandle = lightSystem.createComponent(settings.lightSettings);
        p->notColliding = settings.notColliding;
        componentList[index].idleProjectiles.push_back(p);
        componentList[index].setVisible(p, false);
    }
}

void AmmoSystem::update(float dt) {
    GameSystem::update(dt);

    for (unsigned int i = 0; i < componentList.size(); i++) {
        if (componentList[i].settings.active) {
            if (componentList[i].requiresNewSize) {
                createComponentProjectiles(i);
                componentList[i].requiresNewSize = false;
            }

            componentList[i].tick(dt);

            if (componentList[i].isFiring()) {
                componentList[i].fire(dt);
            }
        }
    }
}


void AmmoSystem::notify(EventMessage *message) {
    delete message;;
}


Handle *AmmoSystem::createComponent(AmmoSettings settings) {
    Handle* handle = GameSystem::createComponent(settings);
    Handle* soundHandle = soundSystem.createComponent(settings.soundSettings);
    registerComponentAsListener(handle->id, cmPlaySound, soundHandle->id,
                                soundSystem.getEventManager());
    Handle* cameraShakeHandle = cameraShakeSystem.createComponent(settings.cameraShakeSettings);
    registerComponentAsListener(handle->id, cmShake, cameraShakeHandle->id,
                                cameraShakeSystem.getEventManager());

    editLock.lock();
    getComponent(handle->id)->soundHandle = soundHandle;
    getComponent(handle->id)->setPhysicsSystem(&physicsSystem);
    getComponent(handle->id)->cameraShakeHandle = cameraShakeHandle;
    createComponentProjectiles(indices.get(handle->id));

    editLock.unlock();
    return handle;
}

void AmmoSystem::eraseComponent(unsigned int id) {
    editLock.lock();
    std::vector<Projectile*> idleProjectiles = getComponent(id)->idleProjectiles;
    std::vector<Projectile*> activeProjectiles = getComponent(id)->activeProjectiles;
    Handle* soundHandle = getComponent(id)->soundHandle;
    Handle* cameraShakeHandle = getComponent(id)->cameraShakeHandle;
    editLock.unlock();

    for (unsigned int i = idleProjectiles.size() - 1; i != static_cast<unsigned>(-1); --i) {
        delete idleProjectiles[i];
    }

    for (unsigned int i = activeProjectiles.size() - 1; i != static_cast<unsigned>(-1); --i) {
        delete activeProjectiles[i];
    }

    delete soundHandle;
    delete cameraShakeHandle;

    GameSystem::eraseComponent(id);
}

AmmoSystem::AmmoSystem(PhysicsSystem &physicsSystem, GraphicsSystem &graphicsSystem,
                       LightSystem& lightSystem, CameraShakeSystem& cameraShakeSystem,
                       SoundSystem& soundSystem)
    : physicsSystem(physicsSystem), graphicsSystem(graphicsSystem), lightSystem(lightSystem)
    , cameraShakeSystem(cameraShakeSystem), soundSystem(soundSystem) {
}
