#include <iostream>
#include <vector>
#include <memory>
#include <thread>
#include <chrono>
#include "graphics/graphicssystem.h"
#include "graphics/backgroundsystem.h"
#include "graphics/lightsystem.h"
#include "graphics/stardustsystem.h"
#include "physics/physicssystem.h"
#include "input/inputsystem.h"
#include "input/shipinputsystem.h"
#include "ship/shipsystem.h"
#include "ship/weaponsystem.h"
#include "ship/ammosystem.h"
#include "ship/shieldsystem.h"
#include "ship/energysystem.h"
#include "ship/explosionsystem.h"
#include "ship/engineeffectsystem.h"
#include "camera/camerasystem.h"
#include "camera/camerashakesystem.h"
#include "debug/modeldisplaysystem.h"
#include "debug/modelsettings.h"
#include "gui/tagsystem.h"
#include "gui/statusinformationsystem.h"
#include "gui/mainmenusystem.h"
#include "sound/soundsystem.h"
#include "sound/musicsystem.h"
#include "gamelogic/aisystem.h"
#include "gamelogic/rewardsystem.h"
#include "gamelogic/shopsystem.h"
#include "gamelogic/areasystem.h"
#include "gamelogic/teleportsystem.h"
#include "handle.h"
#include "utils/highscoreloader.h"
#include "entities/player.h"

#include "tests/completetest.h"

// TODO: debug Ordner umbenennen

const int initWindowWidth = 1200;
const int initWindowHeight = 800;

int main(int argc, char *argv[]) {
    srand(time(NULL));
    CompleteTest tester;
    tester.start();

    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(initWindowWidth, initWindowHeight, 32), "Pirateers");
    window->setFramerateLimit(100);

    HighScoreLoader highScoreLoader;
    LightSystem lightSystem(window);
    SoundSystem soundSystem;
    MusicSystem musicSystem;
    GraphicsSystem graphicsSystem(window, lightSystem.getLightMap());
    BackgroundSystem backgroundSystem(window, lightSystem.getLightMap());
    StarDustSystem starDustSystem(window);
    CameraShakeSystem cameraShakeSystem;
    CameraSystem cameraSystem(window, cameraShakeSystem);
    ModelDisplaySystem modelDisplaySystem(window);
    PhysicsSystem physicsSystem;
    InputSystem inputSystem(window);
    TagSystem tagSystem(window);
    StatusInformationSystem statusInformationSystem(window, soundSystem);
    EnergySystem energySystem;
    AISystem aiSystem(window);
    EngineEffectSystem engineEffectSystem(lightSystem, soundSystem);
    RewardSystem rewardSystem(window, graphicsSystem, lightSystem, soundSystem, highScoreLoader);
    ExplosionSystem explosionSystem(lightSystem, soundSystem, cameraShakeSystem);
    ShieldSystem shieldSystem(soundSystem, lightSystem);
    AmmoSystem ammoSystem(physicsSystem, graphicsSystem, lightSystem, cameraShakeSystem, soundSystem);
    WeaponSystem weaponSystem(physicsSystem, graphicsSystem, modelDisplaySystem, ammoSystem);
    ShipSystem shipSystem(physicsSystem, graphicsSystem, modelDisplaySystem, weaponSystem,
                          tagSystem, shieldSystem,energySystem ,explosionSystem, rewardSystem,
                          engineEffectSystem);
    ShopSystem shopSystem(window, graphicsSystem, inputSystem, soundSystem, rewardSystem,
                          shipSystem);
    TeleportSystem teleportSystem(soundSystem, lightSystem);
    ShipInputSettings shipInputSettings;
    ShipInputSystem shipInputSystem(shipInputSettings, inputSystem, cameraSystem);
    AreaSystem areaSystem(window, shipSystem, aiSystem, graphicsSystem, shopSystem,
                          statusInformationSystem, teleportSystem, rewardSystem);
    MainMenuSystem mainMenuSystem(window, soundSystem, areaSystem, highScoreLoader);

    inputSystem.registerSystemAsListener(0, evWindowClosed, graphicsSystem.getEventManager());
    inputSystem.registerSystemAsListener(0, evWindowResized, backgroundSystem.getEventManager());
    inputSystem.registerSystemAsListener(0, evWindowResized, cameraSystem.getEventManager());
    inputSystem.registerSystemAsListener(0, evWindowResized, lightSystem.getEventManager());
    inputSystem.registerSystemAsListener(0, evWindowResized, starDustSystem.getEventManager());
    inputSystem.registerSystemAsListener(0, evWindowResized, mainMenuSystem.getEventManager());
    inputSystem.registerSystemAsListener(0, evMouseWheelScrolled, cameraSystem.getEventManager());
    inputSystem.registerSystemAsListener(0, evKeyPressed, modelDisplaySystem.getEventManager());
    inputSystem.registerSystemAsListener(0, evKeyPressed, statusInformationSystem.getEventManager());
    inputSystem.registerSystemAsListener(0, evKeyPressed, aiSystem.getEventManager());
    inputSystem.registerSystemAsListener(0, evKeyPressed, areaSystem.getEventManager());
    inputSystem.registerSystemAsListener(0, evKeyPressed, mainMenuSystem.getEventManager());
    cameraSystem.registerSystemAsListener(0, evCameraChanged,
                                          backgroundSystem.getEventManager());
    cameraSystem.registerSystemAsListener(0, evCameraChanged,
                                          graphicsSystem.getEventManager());
    cameraSystem.registerSystemAsListener(0, evCameraChanged,
                                          tagSystem.getEventManager());
    cameraSystem.registerSystemAsListener(0, evCameraChanged,
                                          lightSystem.getEventManager());
    cameraSystem.registerSystemAsListener(0, evCameraChanged,
                                          starDustSystem.getEventManager());
    cameraSystem.registerSystemAsListener(0, evCameraChanged,
                                          cameraShakeSystem.getEventManager());
    cameraSystem.registerSystemAsListener(0, evCameraChanged,
                                          rewardSystem.getEventManager());
    cameraSystem.registerSystemAsListener(0, evCameraChanged,
                                          areaSystem.getEventManager());
    cameraSystem.registerSystemAsListener(0, evCameraChanged,
                                          mainMenuSystem.getEventManager());
    areaSystem.registerSystemAsListener(0, evAreaChanged, backgroundSystem.getEventManager());
    areaSystem.registerSystemAsListener(0, evAreaChanged, musicSystem.getEventManager());
    areaSystem.registerSystemAsListener(0, evPlayerSet, aiSystem.getEventManager());
    areaSystem.registerSystemAsListener(0, evNoPlayerSet, aiSystem.getEventManager());
    areaSystem.registerSystemAsListener(0, evNoPlayerSet, musicSystem.getEventManager());
    mainMenuSystem.registerSystemAsListener(0, evMainMenuOpened, engineEffectSystem.getEventManager());
    mainMenuSystem.registerSystemAsListener(0, evMainMenuOpened, musicSystem.getEventManager());
    mainMenuSystem.registerSystemAsListener(0, evMainMenuClosed, engineEffectSystem.getEventManager());
    mainMenuSystem.registerSystemAsListener(0, evMainMenuClosed, musicSystem.getEventManager());


    Player player(shipSystem, shipInputSystem, physicsSystem, cameraSystem, aiSystem, rewardSystem,
                  shopSystem, statusInformationSystem, teleportSystem);
    areaSystem.setPlayer(&player);

    mainMenuSystem.setOpen(true);
    sf::Clock clock;
    int dt = 1;
    /*
     * Main loop
     */
    while (graphicsSystem.isOpen()) {

        while (!mainMenuSystem.isOpen() && graphicsSystem.isOpen()) {
            inputSystem.update(dt);
            physicsSystem.update(dt);

            window->clear();
            cameraShakeSystem.update(dt);
            cameraSystem.update(dt);
            lightSystem.update(dt);
            backgroundSystem.update(dt);
            areaSystem.drawTutorialText();
            graphicsSystem.update(dt);
            starDustSystem.update(dt);
            tagSystem.update(dt);
            modelDisplaySystem.update(dt);
            aiSystem.update(dt);
            rewardSystem.update(dt);
            cameraSystem.drawCursor();
            shopSystem.update(dt);
            statusInformationSystem.update(dt);
            areaSystem.update(dt);
            mainMenuSystem.update(dt);
            window->display();

            shipInputSystem.update(dt);
            shipSystem.update(dt);
            weaponSystem.update(dt);
            ammoSystem.update(dt);
            shieldSystem.update(dt);
            energySystem.update(dt);
            explosionSystem.update(dt);
            soundSystem.update(dt);
            musicSystem.update(dt);
            engineEffectSystem.update(dt);
            teleportSystem.update(dt);

            dt = clock.getElapsedTime().asMilliseconds();
            clock.restart();
        }

        while (mainMenuSystem.isOpen() && graphicsSystem.isOpen()) {
            inputSystem.update(dt);
            physicsSystem.discardMessages();

            window->clear();
            cameraShakeSystem.discardMessages();
            cameraSystem.update(dt);
            lightSystem.update(dt);
            backgroundSystem.update(dt);
            areaSystem.drawTutorialText();
            graphicsSystem.update(dt);
            starDustSystem.update(dt);
            tagSystem.update(dt);
            modelDisplaySystem.update(dt);
            aiSystem.update(dt);
            rewardSystem.discardMessages();
            shopSystem.discardMessages();
            shopSystem.update(dt);
            statusInformationSystem.discardMessages();
            statusInformationSystem.update(dt);
            areaSystem.discardMessages();
            mainMenuSystem.update(dt);
            cameraSystem.drawCursor();
            window->display();

            shipInputSystem.discardMessages();
            shipSystem.discardMessages();
            weaponSystem.discardMessages();
            ammoSystem.discardMessages();
            shieldSystem.discardMessages();
            energySystem.discardMessages();
            explosionSystem.update(dt);
            soundSystem.update(dt);
            musicSystem.update(dt);
            engineEffectSystem.update(dt);
            teleportSystem.discardMessages();

            dt = clock.getElapsedTime().asMilliseconds();
            clock.restart();
        }


    }

}
