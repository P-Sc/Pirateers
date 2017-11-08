/**
 * @file component.h
 */

#ifndef COMPONENT_H
#define COMPONENT_H

#include "handle.h"
#include "events/listener.h"
#include "events/messages.h"
#include "base/isystem.h"
#include <memory>
#include <map>
#include <vector>
#include <mutex>

class Settings;
class EventManager;

/**
 * @class Component
 * @brief Die Basisklasse aller Spielkomponenten. Beinhaltet kaum Spiellogik.
 *
 */
class Component
{
private:
    unsigned int id;
    /* Array von Vectors, z.b.
     *
     * evHasMoved : Listener5, Listener3, ...
     * evImpact   : Listener3, Listener7, ...
     * ...
     */
protected:
    Handle* handle = nullptr;
    ISystem* gameSystem = nullptr;
    std::mutex mapEditLock;
    std::map<Event, std::vector<Listener>> eventListenerMap;
    virtual void initializeEvents(Event possibleEvents[], unsigned int count);
    //virtual EventMessage* cloneMessage(EventMessage* message);
public:
    bool alive = true;
    Handle* getHandle();
    virtual int getId();
    virtual std::map<Event, std::vector<Listener>>* getEventListenerMap();
    virtual void setGameSystem(ISystem* gameSystem);
    virtual void setHandle(Handle* handle);
    /*
     * Messaging
     */
    virtual void notify(EventMessage* message);
    virtual void notifyListeners(EventMessage * message);
    virtual void registerComponentAsListener(Event event, unsigned int listenerId, EventManager* manager);
    virtual void registerSystemAsListener(Event event, EventManager* manager);
    virtual void deregisterComponentAsListener(Event event, unsigned int listenerId, EventManager* manager);
    virtual void deregisterSystemAsListener(Event event, EventManager* manager);

    /*
     * Component muss wegen der std::mutex mapEditLock wieder "copy-/moveable" gemacht werden
     * Credits: http://stackoverflow.com/a/24273106
     */
    Component(Component&& other) noexcept;
    Component(const Component& other);
    Component& operator = (Component&& other) noexcept;
    Component& operator = (const Component& other);

    Component(Settings settings, Handle* handle);
    virtual ~Component() noexcept {}
};

#endif
