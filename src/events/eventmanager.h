/**
 * @file eventmanager.h
 */

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "messages.h"
#include "base/isystem.h"
//#include "systems/gamesystem.h"
#include <vector>
#include <list>
#include <mutex>
//#include <list>


/**
 * @struct RegistrationRecord
 * @brief Zum Speichern von "eigenen", d.h. vom eigenen GameSystem ausgehenden,
 *        Registrierungen als Listener
 *
 * Registriert sich also das eigene GameSystem oder eine Komponente des eigenen
 * GaneSystems bei einer fremden Komponente, wird dafür RegistrationRecord benutzt.
 */
struct RegistrationRecord {
    unsigned int componentId = 0, listenerId = 0;
    bool gameSystemListener = false;
    Event event;
    EventManager* manager;

    bool isEqual(unsigned int componentId, Event event, unsigned int listenerId,
                 EventManager* manager) {
        return (manager == this->manager && componentId == this->componentId &&
                listenerId == this->listenerId && event == this->event
                && this->gameSystemListener == false);
    }

    bool isEqual(unsigned int componentId, EventManager* manager, bool gameSystemListener) {
        return (manager == this->manager && componentId == this->componentId
                && gameSystemListener == this->gameSystemListener);
    }

    bool isEqual(unsigned int listenerId) {
        return (listenerId == this->listenerId && this->gameSystemListener == false);
    }

    bool isEqual(RegistrationRecord& record) {
        return (record.manager == this->manager && record.componentId == this->componentId &&
                record.listenerId == this->listenerId && record.event == this->event
                && record.gameSystemListener == this->gameSystemListener);
    }

    /**
     * @brief Speichern einer Komponenten-Registrierung
     * @param componentId Die Id der Komponente beim fremden GameSystem
     * @param event Das Event, unter der der Listener registriert wurde
     * @param listenerId Die Id der eigenen Komponente, die als Listener registriert wurde
     * @param manager Der fremde EventManager, der für die Komponente mit
     *                componentId zuständig ist.
     */
    RegistrationRecord(unsigned int componentId, Event event, unsigned int listenerId,
                       EventManager* manager) {
        this->componentId = componentId;
        this->event = event;
        this->listenerId = listenerId;
        this->manager = manager;
    }

    /**
     * @brief Speicherung GameSystem-Registrierung
     * @param componentId Die Id der Komponente beim fremden GameSystem
     * @param event Das Event, unter der der Listener registriert wurde
     * @param manager Der fremde EventManager, der für die Komponente mit
     *                componentId zuständig ist.
     */
    RegistrationRecord(unsigned int componentId, Event event, EventManager *manager) {
        this->componentId = componentId;
        this->event = event;
        this->gameSystemListener = true;
        this->manager = manager;
    }
};

/**
 * @class EventManager
 * @brief Zuständig für das verteilen und Löschen von Nachrichten.
 *        Kann Listener abmelden.
 *
 * Der EventManager arbeitet mit dem GameSystem, den er bei Konstruktion erhält.
 * Nachrichten, die dem EventManager geschickt werden, kommen in eine Message-Queue
 * und werden durch deployMessages() an das GameSystem bzw. dessen Komponenten weitergeleitet.
 */
class EventManager {
private:
    ISystem* receivingSystem;
    std::vector<EventMessage*> messagesA;
    std::vector<EventMessage*> messagesB;

    std::vector<EventMessage*>* receivingMessages;
    std::vector<EventMessage*>* workingMessages;

    std::list<RegistrationRecord> registrations;

    std::mutex editLock;
public:
    /*
    virtual void registerListener(unsigned int componentId, Event event, unsigned int listenerId,
                             EventManager* manager);*/
    void deregisterComponentAsListener(unsigned int componentId, Event event, unsigned int listenerId,
                            EventManager* manager);

    void deregisterSystemAsListener(unsigned int componentId, Event event, EventManager* manager);

    void storeComponentRegistration(unsigned int componentId, Event event,
                           unsigned int listenerId, EventManager* manager);

    void storeSystemRegistration(unsigned int componentId, Event event,
                           EventManager* manager);

    void eraseComponentRegistration(unsigned int componentId, Event event,
                                    unsigned int listenerId, EventManager* manager);

    void eraseComponentRegistrations(unsigned int listenerId);

    void eraseSystemRegistration(unsigned int componentId, Event event, EventManager* manager);

    void eraseSystemRegistrations();

    void signalDeletion(unsigned int componentId, EventManager* manager);

    void sendMessage(EventMessage* message);
    void deployMessages();
    void discardMessages();
    EventManager(ISystem * receivingSystem);
    virtual ~EventManager();
};



#endif // EVENTMANAGER_H
