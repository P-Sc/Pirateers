#include "component.h"
#include "events/eventmanager.h"
#include "base/settings.h"


class Settings;


void Component::initializeEvents(Event possibleEvents[], unsigned int count) {
    //listeners = new std::vector<Listener>[count];
    for (unsigned int i = 0; i < count; i++) {
        eventListenerMap.insert(std::pair<Event, std::vector<Listener>>
                                (possibleEvents[i], std::vector<Listener>()));
    }
}

Handle* Component::getHandle() {
    return handle;
}


/* Deprecated
 *
EventMessage* Component::cloneMessage(EventMessage* message) {
    EventMessage* clone = new EventMessage();
    *clone = *message;
    return clone;
}
*/

int Component::getId() {
    return id;
}

std::map<Event, std::vector<Listener>>* Component::getEventListenerMap() {
    return &eventListenerMap;
}


void Component::setGameSystem(ISystem* gameSystem) {
    this->gameSystem = gameSystem;
}

void Component::setHandle(Handle* handle) {
    this->handle = handle;
}

/**
 * @brief Benachrichtigt diese Komponente über ein Event.
 * @param message Die EventMessage von dem Event
 */
void Component::notify(EventMessage* message) {
    delete message;;
}


/**
 * @brief Schickt EventMessages an die Listener. Löscht nicht die übergebene EventMessage.
 * @param message Die EventMessage, die dem Listener geschickt werden soll.
 *
 * Es werden nur Kopien der übergebenen EventMessage verschickt. D.h.,
 * Schickt message nur an Listener, die auch für das Event registriert sind.
 */
void Component::notifyListeners(EventMessage* message) {
    mapEditLock.lock();

    try {
        std::vector<Listener>& listeners = eventListenerMap.at(message->event);
        message->senderId = this->getId();

        for(Listener element : listeners) {
            EventMessage* customMessage = MessageCloner::cloneMessage(message);

            if (element.gameSystemListener) {
                customMessage->gameSystemListener = true;
            } else {
                customMessage->receiverId = element.id;
            }

            element.destinationManager->sendMessage(customMessage);
        }
    } catch (std::out_of_range e) {
        // TODO: Notify Logger (and create logger)
    }

    mapEditLock.unlock();
}


/**
 * @brief Fügt einen Listener (Komponente) hinzu.
 * @param event Das Event, unter dem der Listener benachrichtigt werden soll
 * @param listenerId Die Id des Listeners
 * @param manager Der EventManager, an dem die EventMessage geschickt werden soll
 *
 * Sobald ein Listener hinzugefügt wurde, wird eine EventMessage an den entsprechenden
 * EventManager geschickt, sobald die Komponente Event auslöst.
 */
void Component::registerComponentAsListener(Event event, unsigned int listenerId, EventManager* manager) {
    Listener listener;
    listener.id = listenerId;
    listener.destinationManager = manager;
    mapEditLock.lock();
    eventListenerMap.at(event).push_back(listener);
    mapEditLock.unlock();
}

/**
 * @brief Fügt einen Listener (GameSystem) hinzu.
 * @param event Das Event, unter dem der Listener benachrichtigt werden soll
 * @param manager Der EventManager, an dem die EventMessage geschickt werden soll
 *
 * Sobald ein Listener hinzugefügt wurde, wird eine EventMessage an den entsprechenden
 * EventManager geschickt, sobald die Komponente Event auslöst.
 */
void Component::registerSystemAsListener(Event event, EventManager* manager) {
    Listener listener;
    listener.gameSystemListener = true;
    listener.destinationManager = manager;
    mapEditLock.lock();
    eventListenerMap.at(event).push_back(listener);
    mapEditLock.unlock();
}


/**
 * @brief Entfernt einen Listener (Komponente).
 * @param event Das Event, unter dem der Listener gespeichert wurde
 * @param listenerId Die Komponenten-ID des Listeners.
 * @param manager Der EventManager des GameSystem des Listeners
 *
 * Dieser Listener wird danach nicht mehr benachrichtigt, falls diese Komponente
 * ein Event aussendet.
 */
void Component::deregisterComponentAsListener(Event event, unsigned int listenerId,
        EventManager* manager) {
    mapEditLock.lock();
    std::vector<Listener>& listeners = eventListenerMap.at(event);

    for(std::vector<Listener>::iterator element = listeners.begin();
            element != listeners.end(); element++) {
        if (element->id == listenerId && element->destinationManager == manager) {
            listeners.erase(element);
            break;
        }
    }

    mapEditLock.unlock();
}


/**
 * @brief Entfernt einen Listener (GameSystem).
 * @param event Das Event, unter dem der Listener gespeichert wurde
 * @param manager Der EventManager des GameSystems
 *
 * Dieser Listener wird danach nicht mehr benachrichtigt, falls diese Komponente
 * ein Event aussendet.
 */
void Component::deregisterSystemAsListener(Event event, EventManager* manager) {
    mapEditLock.lock();
    std::vector<Listener>& listeners = eventListenerMap.at(event);

    for(std::vector<Listener>::iterator element = listeners.begin();
            element != listeners.end(); element++) {
        if (element->gameSystemListener && element->destinationManager == manager) {
            listeners.erase(element);
            break;
        }
    }

    mapEditLock.unlock();
}


Component::Component(Component&& other) noexcept {
    eventListenerMap = std::move(other.eventListenerMap);
    alive = std::move(other.alive);
    id = std::move(other.id);
    gameSystem = std::move(other.gameSystem);
    handle = std::move(other.handle);
    other.eventListenerMap.clear();
}


Component::Component(const Component& other) {
    eventListenerMap = std::move(other.eventListenerMap);
    alive = std::move(other.alive);
    id = std::move(other.id);
    gameSystem = std::move(other.gameSystem);
    handle = std::move(other.handle);

}

Component& Component::operator = (Component&& other) noexcept {
    eventListenerMap = std::move(other.eventListenerMap);
    alive = std::move(other.alive);
    id = std::move(other.id);
    gameSystem = std::move(other.gameSystem);
    handle = std::move(other.handle);
    other.eventListenerMap.clear();
    return *this;
}


Component & Component::operator =(const Component& other) {
    eventListenerMap = std::move(other.eventListenerMap);
    alive = std::move(other.alive);
    id = std::move(other.id);
    gameSystem = std::move(other.gameSystem);
    handle = std::move(other.handle);
    return *this;
}


/**
 * @brief Konstruktor.
 * @param settings Die Settings mit den Einstellungen
 * @param handle Das eigene Handle
 */
Component::Component(Settings settings, Handle* handle) {
    this->id = handle->id;
}

