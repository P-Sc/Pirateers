#include "shopsystem.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "graphics/graphicssystem.h"
#include "input/inputsystem.h"
#include "sound/soundsystem.h"
#include "gamelogic/rewardsystem.h"
#include "ship/shipsystem.h"

/**
 * @brief Zeichnet das Auswahlmenü einer Komponente
 * @param index Der Index der Komponente
 */
void ShopSystem::drawMainMenu(unsigned int index) {
    //for (size_t i = 0; i < componentList[index].mainBackgrounds.)
    for (auto& shape : componentList[index].mainBackgrounds) {
        window->draw(shape);
    }

    for (auto& text : componentList[index].mainTexts) {
        window->draw(text);
    }
}

/**
 * @brief Zeichnet das Slotmenü einer Komponente
 * @param index Der Index der Komponente
 */
void ShopSystem::drawSubMenu(unsigned int index) {
    for (auto& shape : componentList[index].subBackgrounds) {
        window->draw(shape);
    }

    for (auto& text : componentList[index].subTexts) {
        window->draw(text);
    }
}


/**
 * @brief Verschickt die cmUpgrade-Messages einer Komponente
 * @param index Der Index der Komponente
 */
void ShopSystem::sendUpgradeMessages(unsigned int index) {
    if (playerAlive) {
        for (int i = 0; i < componentList[index].playerMessages.size(); i++) {
            EventMessage* playerMessage = componentList[index].playerMessages[i];
            playerMessage->receiverId = playerHandle->id;
            //EventUpgradeMessage* informationMessage = (EventUpgradeMessage*)
            //        MessageCloner::cloneMessage(componentList[index].upgradeMessages[i]);
            //informationMessage->gameSystemListener = true;
            shipSystem.getEventManager()->sendMessage(playerMessage);
        }
        componentList[index].playerMessages.clear();
    }
}

/**
 * @copydoc GameSystem::update
 * Aktualisiert Komponenten
 */
void ShopSystem::update(float dt) {
    GameSystem::update(dt);
    int credits = rewardSystem.getCreditStatus();

    for (unsigned int i = 0; i < componentList.size(); i++) {
        b2Vec2 v = componentList[i].settings.pos;
        v -= playerPos;
        float distance = v.Length();

        if (componentList[i].isOpen()) {
            sendUpgradeMessages(i);
            componentList[i].setCredits(credits);

            if (distance > 40) {
                componentList[i].close();
            } else {
                drawMainMenu(i);

                if (componentList[i].isSubMenuOpen()) {
                    drawSubMenu(i);
                }
            }

            return;
        } else if (distance < 40) {
            componentList[i].setCredits(credits);
            componentList[i].open();
            return;
        }
    }
}

/**
 * @copydoc GameSystem::notify
 * - ::evMove Spielerposition
 * - ::evDestroyed Deaktiviert Shops
 */
void ShopSystem::notify(EventMessage* message) {
    switch (message->event) {
    case evMove: {
        EventPosMessage* posMessage = (EventPosMessage*) message;
        playerPos = posMessage->pos;
        break;
    }
    case evDestroyed: {
        playerAlive = false;
        break;
    }
    }

    delete message;;
}

Handle* ShopSystem::createComponent(ShopSettings settings) {
    Handle* handle = GameSystem::createComponent(settings);
    GraphicsSettings graphicsSettings;
    graphicsSettings.layer = 0;
    graphicsSettings.texture = "shop.png";
    graphicsSettings.pos.x = settings.pos.x;
    graphicsSettings.pos.y = settings.pos.y;
    Handle* graphicsHandle = graphicsSystem.createComponent(graphicsSettings);
    SoundSettings soundSettings;
    soundSettings.filename = "menu_select.wav";
    Handle* selectSoundHandle = soundSystem.createComponent(soundSettings);
    soundSettings.filename = "menu_enter.wav";
    Handle* enterSoundHandle = soundSystem.createComponent(soundSettings);
    soundSettings.filename = "menu_open.wav";
    Handle* openSoundHandle = soundSystem.createComponent(soundSettings);
    soundSettings.filename = "menu_close.ogg";
    Handle* closeSoundHandle = soundSystem.createComponent(soundSettings);
    soundSettings.filename = "menu_upgrade.wav";
    Handle* upgradeSoundHandle = soundSystem.createComponent(soundSettings);
    soundSettings.filename = "menu_error.wav";
    soundSettings.volume = 50;
    Handle* errorSoundHandle = soundSystem.createComponent(soundSettings);

    inputSystem.registerComponentAsListener(0, evKeyPressed, handle->id, getEventManager());
    registerComponentAsListener(handle->id, cmPlaySound, selectSoundHandle->id,
                                soundSystem.getEventManager());
    registerComponentAsListener(handle->id, cmPlaySound, enterSoundHandle->id,
                                soundSystem.getEventManager());
    registerComponentAsListener(handle->id, cmPlaySound, openSoundHandle->id,
                                soundSystem.getEventManager());
    registerComponentAsListener(handle->id, cmPlaySound, closeSoundHandle->id,
                                soundSystem.getEventManager());
    registerComponentAsListener(handle->id, cmPlaySound, errorSoundHandle->id,
                                soundSystem.getEventManager());
    registerComponentAsListener(handle->id, cmPlaySound, upgradeSoundHandle->id,
                                soundSystem.getEventManager());
    registerSystemAsListener(handle->id, evPurchase, rewardSystem.getEventManager());

    editLock.lock();
    getComponent(handle->id)->graphicsHandle = graphicsHandle;
    getComponent(handle->id)->selectSoundHandle = selectSoundHandle;
    getComponent(handle->id)->enterSoundHandle = enterSoundHandle;
    getComponent(handle->id)->openSoundHandle = openSoundHandle;
    getComponent(handle->id)->closeSoundHandle = closeSoundHandle;
    getComponent(handle->id)->errorSoundHandle = errorSoundHandle;
    getComponent(handle->id)->upgradeSoundHandle = upgradeSoundHandle;

    for (auto& text : getComponent(handle->id)->mainTexts) {
        text.setFont(menuFont);
    }

    for (auto& text : getComponent(handle->id)->subTexts) {
        text.setFont(menuFont);
    }

    editLock.unlock();
    return handle;
}

void ShopSystem::eraseComponent(unsigned int id) {
    editLock.lock();
    Handle* graphicsHandle = getComponent(id)->graphicsHandle;
    Handle* selectSoundHandle = getComponent(id)->selectSoundHandle;
    Handle* enterSoundHandle = getComponent(id)->enterSoundHandle;
    Handle* openSoundHandle = getComponent(id)->openSoundHandle;
    Handle* closeSoundHandle = getComponent(id)->closeSoundHandle;
    Handle* errorSoundHandle = getComponent(id)->errorSoundHandle;
    Handle* upgradeSoundHandle = getComponent(id)->upgradeSoundHandle;
    editLock.unlock();
    delete graphicsHandle;
    delete selectSoundHandle;
    delete enterSoundHandle;
    delete openSoundHandle;
    delete closeSoundHandle;
    delete errorSoundHandle;
    delete upgradeSoundHandle;
    GameSystem::eraseComponent(id);
}

void ShopSystem::setPlayerHandle(Handle* shipHandle) {
    playerHandle = shipHandle;
    playerAlive = true;
}


ShopSystem::ShopSystem(sf::RenderWindow* window, GraphicsSystem& graphicsSystem,
                       InputSystem& inputSystem, SoundSystem& soundSystem,
                       RewardSystem& rewardSystem, ShipSystem& shipSystem)
    : window(window), graphicsSystem(graphicsSystem), inputSystem(inputSystem)
    , soundSystem(soundSystem), rewardSystem(rewardSystem), shipSystem(shipSystem) {

    menuFont.loadFromFile("../resources/FreeMono.otf");

}
