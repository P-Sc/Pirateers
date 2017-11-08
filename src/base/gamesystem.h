/**
 * @file gamesystem.h
 */

#ifndef SYSTEM_H
#define SYSTEM_H

#include "base/isystem.h"
#include "handle.h"
#include "utils/fixedindexarray.h"
#include "events/messages.h"
#include "events/eventmanager.h"

#include <string>
#include <vector>
#include <memory>
#include <mutex>


class Component;
class Settings;
class EventMessage;

/**
 * @class GameSystem
 * @brief Die Grundklasse aller Spielsysteme.
 *
 * GameSystem implementiert mehrere wichtige, grundlegende Elemente für davon
 * abgeleitete Spielsysteme. Dabei kümmert sich GameSystem vorallem um die
 * Verwaltung von Components, samt dem Erstellen, Löschen und Durchiterieren.
 *
 * GameSystem hat dabei zwei Arrays zum Verwalten der Komponenten:
 *   - Ein Array, das IDs Indizes zuordnet,
 *   - und ein Array, welches die Komponenten unter diesen Indizes beinhaltet.
 * Die gesamte Interaktion mit Komponenten aus einem GameSystem erfolgt dabei über
 * die einzigartigen IDs.
 *
 * @param T Das zu speichernde Component
 * @param S Die entsprechenden Settings
 */
template <typename T, typename S>
class GameSystem : public ISystem {
private:
    bool itemsDead = false; ///< Gibt an, ob Komponenten gelöscht werden müssen

    /**
     * @brief Gibt an, ob Elemente aus dem Komponenten-Array entfernt werden drüfen
     */
    bool doNotClean = false;
    EventManager manager;
    void clean();
protected:
    std::mutex editLock;
    FixedIndexArray indices;
    std::vector<T> componentList;
    virtual T* getComponent(unsigned int id);
public:
    virtual void update(float dt);

    virtual Handle* createComponent(S settings);

    virtual void eraseComponent(unsigned int id);

    unsigned int getCount();

    // Messaging Abstraktionen für Components
    virtual void registerComponentAsListener(unsigned int componentId, Event event,
                                  unsigned int listenerId,EventManager* listenerManager);

    virtual void registerSystemAsListener(unsigned int componentId, Event event,
                                  EventManager* listenerManager);

    virtual void deregisterComponentAsListener(unsigned int componentId, Event event,
                                    unsigned int listenerId, EventManager* listenerManager);

    virtual void deregisterSystemAsListener(unsigned int componentId, Event event,
                                    EventManager* listenerManager);

    virtual void eraseComponentRegistration(unsigned int componentId, Event event,
                                    unsigned int listenerId, EventManager* manager);

    virtual void eraseSystemRegistration(unsigned int componentId, Event event, EventManager* manager);

    virtual void notifyComponent(EventMessage* message);

    virtual void notify(EventMessage* message);

    virtual EventManager* getEventManager();

    virtual void discardMessages();

    GameSystem();
    virtual ~GameSystem();
};

#endif // SYSTEM_H
