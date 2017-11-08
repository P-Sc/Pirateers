#include "gamesystem.h"
#include <memory>
#include <algorithm>
#include <vector>
#include "handle.h"
#include "events/listener.h"
#include "events/eventmanager.h"
#include "base/component.h"
#include "base/settings.h"

#include "graphics/graphicscomponent.h"
#include "graphics/graphicssettings.h"

#include "graphics/backgroundcomponent.h"
#include "graphics/backgroundsettings.h"

#include "graphics/lightcomponent.h"
#include "graphics/lightsettings.h"

#include "physics/physicscomponent.h"
#include "physics/physicssettings.h"

#include "ship/shipcomponent.h"
#include "ship/shipsettings.h"

#include "ship/weaponcomponent.h"
#include "ship/weaponsettings.h"

#include "ship/ammocomponent.h"
#include "ship/ammosettings.h"

#include "ship/shieldcomponent.h"
#include "ship/shieldsettings.h"

#include "ship/energycomponent.h"
#include "ship/energysettings.h"

#include "ship/explosioncomponent.h"
#include "ship/explosionsettings.h"

#include "ship/engineeffectcomponent.h"
#include "ship/engineeffectsettings.h"

#include "input/inputcomponent.h"

#include "input/shipinputcomponent.h"
#include "input/shipinputsettings.h"

#include "debug/modelcomponent.h"
#include "debug/modelsettings.h"

#include "camera/cameracomponent.h"

#include "camera/camerashakecomponent.h"
#include "camera/camerashakesettings.h"

#include "gui/tagcomponent.h"
#include "gui/tagsettings.h"

#include "gui/mainmenucomponent.h"

#include "sound/soundcomponent.h"
#include "sound/soundsettings.h"

#include "gamelogic/aicomponent.h"
#include "gamelogic/aisettings.h"

#include "gamelogic/rewardcomponent.h"
#include "gamelogic/rewardsettings.h"

#include "gamelogic/shopcomponent.h"
#include "gamelogic/shopsettings.h"

#include "gamelogic/areacomponent.h"

#include "gamelogic/teleportcomponent.h"


#include "tests/helper_component_1.h"

using namespace std;


/**
 * @brief Löscht alle Elemente aus componentList, die mit alive=false markiert sind.
 *
 * Dabei wird von zwei Seiten durch das Array iteriert und Elemente werden vertauscht,
 * falls eines davon gelöscht werden soll, sodass am sich Ende alle zu löschenden Elemente
 * am Ende des Arrays befinden und zusammen gelöscht werden können.
 *
 * Achtung: Falls @var itemsDead = true, wird immer mindestens das letzte Element gelöscht.
 * @var itemsDead sollte also nur über @fn eraseComponent verändert werden.
 */
template <typename T, typename S>
void GameSystem<T, S>::clean() {

    if (itemsDead && !doNotClean) {
        editLock.lock();
        // initialisieren
        typename vector<T>::iterator leftIterator = componentList.begin();
        typename vector<T>::iterator rightIterator = componentList.end();
        rightIterator--;
        unsigned int leftIndex = 0;
        unsigned int rightIndex = componentList.size() - 1;

        while (itemsDead) {

            // Zu löschende Komponente links finden
            while(leftIterator->alive && leftIterator != rightIterator) {
                leftIterator++;
                leftIndex++;
            }

            // "Lebende" Komponenten rechts finden
            while(!rightIterator->alive && leftIterator != rightIterator) {
                // Index der zu löschenden Komponente entfernen
                //indices.erase(leftIterator->getId());

                rightIterator--;
                rightIndex--;
            }

            // Elemente vertauschen
            if (leftIterator != rightIterator) {
                // Index der "lebenden" Komponente aktualisieren
                indices[rightIterator->getId()] = leftIndex;
                // Id der zu löschenden Komponente wieder verfügbar machen
                indices.erase(leftIterator->getId());
                //
                manager.eraseComponentRegistrations(leftIterator->getId());
                iter_swap(leftIterator, rightIterator);
            } else {
                itemsDead = false;
            }
        }

        // Tote Elemente löschen
        componentList.erase(rightIterator, componentList.end());
        editLock.unlock();
    }
}


/**
 * @brief Gibt Komponente der ID zurück
 *
 * @param id Die ID der Komponente.
 * @return Die entsprechende Komponente
 */
template <typename T, typename S>
T * GameSystem<T, S>::getComponent(unsigned int id) {
    if (id < 0 || id > indices.getCapacity() - 1) {
        return nullptr;
    } else {
        return &(componentList[indices.get(id)]);
    }
}


/**
 * @brief Update-Routine.
 *
 * Kann in Unterklassen dazu benutzt werden, durch alle Komponenten zu iterieren.
 * Verteilt Messages und führt clean() aus
 */
template <typename T, typename S>
void GameSystem<T, S>::update(float dt) {
    clean();
    manager.deployMessages();
}

/**
 * @brief Erstellt eine Komponente und fügt sie in das Array ein.
 *
 * @param settings Die zur Komponente entsprechenden Settings
 * @return Ein Handle mit der ID der neuen Komponente
 */
template <typename T, typename S>
Handle* GameSystem<T, S>::createComponent(S settings) {
    editLock.lock();
    // Index und Id festlegen
    unsigned int index = componentList.size();
    unsigned int id = indices.add(index);
    Handle* handle = new Handle(id, this);

    // Hinzufügen
    //componentList.emplace_back(T(settings, handle->id));
    componentList.emplace_back(T(settings, handle));
    componentList.back().setGameSystem(this);
    componentList.back().setHandle(handle);
    editLock.unlock();

    return handle;
}


/**
 * @brief Löscht eine Komponente anhand ihrere ID
 *
 * @param id Die ID der zu löschenden Komponente
 */
template <typename T, typename S>
void GameSystem<T, S>::eraseComponent(unsigned int id) {
    editLock.lock();
    getComponent(id)->getHandle()->alive = false;
    std::map<Event, std::vector<Listener>>* eventListenerMap =
                                            componentList[indices.get(id)].getEventListenerMap();

    /*
     * Eigenen EventManager Löschung mitteilen.
     * Dieser deregistiert dabei die Komponente bei den anderen EventManagern.
     */
    doNotClean = true;
    editLock.unlock();
    manager.eraseComponentRegistrations(id);
    editLock.lock();
    doNotClean = false;

    /*
     * EventManager aller Listener die Löschung mitteilen
     */
    for(auto& vectorEventPair : *eventListenerMap) {
        //Event event = vectorEventPair.first;
        std::vector<Listener> vectorElement = vectorEventPair.second;

        for (Listener element : vectorElement) {
            element.destinationManager->signalDeletion(id, &(this->manager));
        }
    }

    componentList[indices.get(id)].alive = false;
    itemsDead = true;
    editLock.unlock();
}

/**
 * @brief Gibt Anzahl der gespeicherten Komponenten zurück
 * @return Anzahl der gespeicherten Komponenten
 */
template <typename T, typename S>
unsigned int GameSystem<T, S>::getCount() {
    return componentList.size();
}


/**
 * @brief Registriert einen Listener (andere Komponente) bei einer Komponente
 * @param componentId Die Id der Komponente, wo der Listener registriert werden soll
 * @param event Das Event, unter dem der Listener benachricht werden soll
 * @param listenerId Die Id des Listeners
 * @param manager Der EventManager des Listeners
 *
 * Diese Methode leitet den Aufruf lediglich an die Komponente weiter.
 */
template <typename T, typename S>
void GameSystem<T, S>::registerComponentAsListener(unsigned int componentId, Event event,
        unsigned int listenerId, EventManager* listenerManager) {
    editLock.lock();
    componentList[indices.get(componentId)].registerComponentAsListener(event, listenerId, listenerManager);
    // Achtung: Wird nicht beim eigenen EventManager aufgerufen!
    listenerManager->storeComponentRegistration(componentId, event, listenerId, &(this->manager));
    editLock.unlock();
}

/**
 * @brief Registriert einen Listener (ein GameSystem) bei einer Komponente
 * @param componentId Die Id der Komponente, wo der Listener registriert werden soll
 * @param event Das Event, unter dem der Listener benachricht werden soll
 * @param gameSystem Das Listener-GameSystem
 * @param manager Der EventManager des Listeners
 *
 * Diese Methode leitet den Aufruf lediglich an die Komponente weiter.
 */
template <typename T, typename S>
void GameSystem<T, S>::registerSystemAsListener(unsigned int componentId, Event event,
        EventManager* listenerManager) {
    editLock.lock();
    componentList[indices.get(componentId)].registerSystemAsListener(event, listenerManager);
    // Achtung: Wird nicht beim eigenen EventManager aufgerufen!
    listenerManager->storeSystemRegistration(componentId, event, &(this->manager));
    editLock.unlock();
}

/**
 * @brief Löscht die Registrierung des Listeners (Komponente) bei einer Komponente
 * @param componentId Die Id der Komponente, wo der Listener entfernt werden soll
 * @param event Das Event, unter dem der Listener registriert ist
 * @param listenerId Die Id des Listeners
 * @param manager der EventManager des Listeners
 * @warning Diese Methode nicht direkt aufrufen, da die Registrierung beim EventManager
 *          des Listeners (d.h. nicht hier) noch zusätzlich gespeichert ist.
 *          Eine solche veraltete bzw. fehlerhafte Registrierung kann zu einem
 *          Segmentation Fault führen.
 *          Stattdessen sollte GameSystem::eraseComponentRegistration()
 *          oder EventManager::eraseComponentRegistration() benutzt werden.
 *
 * Diese Methode leitet den Aufruf lediglich an die Komponente weiter.
 */
template <typename T, typename S>
void GameSystem<T, S>::deregisterComponentAsListener(unsigned int componentId, Event event,
        unsigned int listenerId, EventManager* listenerManager) {
    editLock.lock();
    componentList[indices.get(componentId)].deregisterComponentAsListener(event, listenerId, listenerManager);
    editLock.unlock();
}


/**
 * @brief Löscht die Registrierung des Listeners (GameSystem) bei einer Komponente
 * @param componentId Die Id der Komponente, wo der Listener entfernt werden soll
 * @param event Das Event, unter dem der Listener registriert ist
 * @param listenerId Die Id des Listeners
 * @param manager der EventManager des Listeners
 * @warning Diese Methode nicht direkt aufrufen, da die Registrierung beim EventManager
 *          des Listeners (d.h. nicht hier) noch zusätzlich gespeichert ist.
 *          Eine solche veraltete bzw. fehlerhafte Registrierung kann zu einem
 *          Segmentation Fault führen.
 *          Stattdessen sollte GameSystem::eraseSystemRegistration() oder
 *          EventManager::eraseSystemRegistration() benutzt werden.
 *
 * Diese Methode leitet den Aufruf lediglich an die Komponente weiter.
 */
template <typename T, typename S>
void GameSystem<T, S>::deregisterSystemAsListener(unsigned int componentId, Event event,
        EventManager* listenerManager) {
    editLock.lock();
    componentList[indices.get(componentId)].deregisterSystemAsListener(event, listenerManager);
    editLock.unlock();
}


/**
 * @brief Löscht eine gespeicherte Listener-Registrierung (Komponente).
 *        Meldet die eigene Komponente beim fremden EventManager ab.
 * @param componentId Die Id der Komponente beim fremden GameSystem
 * @param event Das Event, unter der der Listener registriert wurde
 * @param listenerId Die Id der eigenen Komponente, die als Listener registriert wurde
 * @param manager Der fremde EventManager, der für die Komponente mit
 *                componentId zuständig ist.
 *
 * Diese Methode sollte benutzt werden, um manuell eine Komponente abzumelden.
 * Leitet den Aufruf an den eigenen EventManager weiter. Löscht nur eine einzelne Registrierung.
 */
template <typename T, typename S>
void GameSystem<T, S>::eraseComponentRegistration(unsigned int componentId, Event event,
        unsigned int listenerId, EventManager* manager) {
    this->manager.eraseComponentRegistration(componentId, event, listenerId, manager);
}


/**
 * @brief Löscht eine gespeicherte Listener-Registrierung (GameSystem).
 *        Meldet das eigene GameSystem beim fremden EventManager ab.
 * @param componentId Die Id der Komponente beim fremden GameSystem
 * @param event Das Event, unter der der Listener registriert wurde
 * @param manager Der fremde EventManager, der für die Komponente mit
 *                componentId zuständig ist.
 *
 * Diese Methode sollte benutzt werden, um manuell das GameSystem abzumelden.
 * Leitet den Aufruf an den eigenen EventManager weiter. Löscht nur eine einzelne Registrierung.
 */
template <typename T, typename S>
void GameSystem<T, S>::eraseSystemRegistration(unsigned int componentId, Event event, EventManager* manager) {
    this->manager.eraseSystemRegistration(componentId, event, manager);
}


/**
 * @brief Benachrichtigt eine Komponente über das Eintreten eines Event
 * @param message Die EventMessage, die der Komponente geschickt werden soll
 *
 * Diese Methode leitet den Aufruf lediglich an die Komponente weiter.
 */
template <typename T, typename S>
void GameSystem<T, S>::notifyComponent(EventMessage * message) {
    if (indices.isUsed(message->receiverId)) {
        componentList[indices.get(message->receiverId)].notify(message);
    }

    //editLock.unlock();
}


/**
 * @brief Benachrichtigt das GameSystem über ein Event
 * @param message Die EventMessage von dem Event
 */
template <typename T, typename S>
void GameSystem<T, S>::notify(EventMessage *message) {
    delete message;
}


/**
 * @brief Gibt den gespeicherten EventManager zurück.
 * @return Der EventManager
 */
template <typename T, typename S>
EventManager* GameSystem<T, S>::getEventManager() {
    return &manager;
}

template <typename T, typename S>
void GameSystem<T, S>::discardMessages() {
    manager.discardMessages();
}

template <typename T, typename S>
GameSystem<T, S>::GameSystem() : manager(this) {

}

/**
 * @brief Destruktor. Löscht auch alle Komponenten.
 */
template <typename T, typename S>
GameSystem<T, S>::~GameSystem() {
    manager.eraseSystemRegistrations();
    editLock.lock();

    for (typename std::vector<T>::iterator it = componentList.begin();
            it != componentList.end(); it++) {

        unsigned int id = (*it).getId();
        (*it).alive = false;

        /*
         * Eigenen EventManager Löschung mitteilen.
         * Dieser deregistiert dabei die Komponente/ das GameSystem bei
         * den anderen EventManagern.
         */
        doNotClean = true;
        editLock.unlock();
        manager.eraseComponentRegistrations(id);
        editLock.lock();
        doNotClean = false;

        /*
         * EventManager aller Listener die Löschung mitteilen
         */
        std::map<Event, std::vector<Listener>>* eventListenerMap =
                                                (*it).getEventListenerMap();

        for(auto& vectorEventPair : *eventListenerMap) {
            //Event event = vectorEventPair.first;
            std::vector<Listener> vectorElement = vectorEventPair.second;

            for (Listener element : vectorElement) {
                element.destinationManager->signalDeletion(id, &(this->manager));
            }
        }

    }

    itemsDead = true;
    editLock.unlock();


    /* Methode 2

    editLock.lock();
    std::list<unsigned int> usedPositions = indices.getUsedPositions();
    editLock.unlock();

    for(std::list<unsigned int>::iterator it = usedPositions.begin();
        it != usedPositions.end(); it++) {

        eraseComponent(*it);
    }*/
}

template class GameSystem<Component, Settings>;
template class GameSystem<GraphicsComponent, GraphicsSettings>;
template class GameSystem<BackgroundComponent, BackgroundSettings>;
template class GameSystem<LightComponent, LightSettings>;
template class GameSystem<PhysicsComponent, PhysicsSettings>;
template class GameSystem<ShipComponent, ShipSettings>;
template class GameSystem<InputComponent, Settings>;
template class GameSystem<ModelComponent, ModelSettings>;
template class GameSystem<CameraComponent, Settings>;
template class GameSystem<CameraShakeComponent, CameraShakeSettings>;
template class GameSystem<WeaponComponent, WeaponSettings>;
template class GameSystem<AmmoComponent, AmmoSettings>;
template class GameSystem<ShipInputComponent, ShipInputSettings>;
template class GameSystem<TagComponent, TagSettings>;
template class GameSystem<MainMenuComponent, Settings>;
template class GameSystem<ShieldComponent, ShieldSettings>;
template class GameSystem<EnergyComponent, EnergySettings>;
template class GameSystem<ExplosionComponent, ExplosionSettings>;
template class GameSystem<EngineEffectComponent, EngineEffectSettings>;
template class GameSystem<SoundComponent, SoundSettings>;
template class GameSystem<AIComponent, AISettings>;
template class GameSystem<RewardComponent, RewardSettings>;
template class GameSystem<ShopComponent, ShopSettings>;
template class GameSystem<AreaComponent, Settings>;
template class GameSystem<TeleportComponent, Settings>;

// Tests
template class GameSystem<Helper_Component_1, Helper_Settings_1>;
