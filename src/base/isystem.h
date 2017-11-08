/**
 * @file isystem.h
 */

#ifndef ISYSTEM_H
#define ISYSTEM_H

/**
 * @class ISystem
 * @brief Ein Interface für GameSystem, um in anderen Klassen die Templates
 *        nicht spezifizieren zu müssen.
 *
 * Zum Beispiel in Handle benutzt, da Handle einen Pointer zum jeweiligen GameSystem
 * abspeichert.
 */

#include "events/messages.h"

class EventManager;
class EventMessage;

class ISystem {
public:
    virtual void update(float dt) = 0;

    //virtual void init (void) = 0;

    //virtual void SendMessage(Message *msg) = 0;

    //virtual typedef Handle* createComponent(S settings) = 0;

    //virtual T* getComponent(unsigned int id) = 0;

    virtual void eraseComponent(unsigned int id) = 0;

    virtual unsigned int getCount() = 0;

    virtual void registerComponentAsListener(unsigned int componentId, Event event,
                                  unsigned int listenerId,EventManager* manager) = 0;
    virtual void registerSystemAsListener(unsigned int componentId, Event event,
                                  EventManager* manager) = 0;
    virtual void deregisterComponentAsListener(unsigned int componentId, Event event,
                                    unsigned int listenerId, EventManager* manager) = 0;
    virtual void deregisterSystemAsListener(unsigned int componentId, Event event,
                                    EventManager* manager) = 0;
    virtual void eraseComponentRegistration(unsigned int componentId, Event event,
                                    unsigned int listenerId, EventManager* manager) = 0;

    virtual void eraseSystemRegistration(unsigned int componentId, Event event, EventManager* manager) = 0;
    virtual void notifyComponent(EventMessage* message) = 0;
    virtual void notify(EventMessage* message) = 0;
    virtual EventManager* getEventManager() = 0;

    virtual ~ISystem() {}
};

#endif // ISYSTEM_H
