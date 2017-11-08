#include "eventmanager.h"
#include "base/gamesystem.h"
#include <utility>


/*
 * @brief Registriert einen Listener bei einer Komponente
 * @param componentId Die Id der Komponente, wo der Listener registriert werden soll
 * @param event Das Event, unter dem der Listener benachricht werden soll
 * @param listenerId Die Id des Listeners
 * @param manager Der EventManager des Listeners
 *
 * Diese Methode leitet den Aufruf lediglich an das GameSystem der Komponente weiter.
 */
/*
void EventManager::registerListener(unsigned int componentId, Event event,
                                    unsigned int listenerId, EventManager* manager) {
    receivingSystem->registerListener(componentId, event, listenerId, manager);
}
*/

/**
* @brief Leitet den Aufruf zum Abmelden des Listeners (Komponente) an das GameSystem weiter.
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
*/

void EventManager::deregisterComponentAsListener(unsigned int componentId, Event event,
        unsigned int listenerId, EventManager* manager) {
    receivingSystem->deregisterComponentAsListener(componentId, event, listenerId, manager);
}


/**
* @brief Leitet den Aufruf zum Abmelden des Listeners (GameSystem) an das GameSystem weiter.
* @param componentId Die Id der Komponente, wo der Listener entfernt werden soll
* @param event Das Event, unter dem der Listener registriert ist
* @param manager der EventManager des Listeners
* @warning Diese Methode nicht direkt aufrufen, da die Registrierung beim EventManager
 *          des Listeners (d.h. nicht hier) noch zusätzlich gespeichert ist.
 *          Eine solche veraltete bzw. fehlerhafte Registrierung kann zu einem
 *          Segmentation Fault führen.
 *          Stattdessen sollte GameSystem::eraseSystemRegistration() oder
 *          EventManager::eraseSystemRegistration() benutzt werden.
*/

void EventManager::deregisterSystemAsListener(unsigned int componentId, Event event,
        EventManager* manager) {
    receivingSystem->deregisterSystemAsListener(componentId, event, manager);
}



/**
 * @brief Speichert die Registrierung von einer eigenen Komponente
 * @param componentId Die Id der Komponente beim fremden GameSystem
 * @param event Das Event, unter der der Listener registriert wurde
 * @param listenerId Die Id der eigenen Komponente, die als Listener registriert wurde
 * @param manager Der fremde EventManager, der für die Komponente mit
 *                componentId zuständig ist.
 *
 * Die Speicherung der Registrierung erfolgt, damit beim Löschen der eigenen
 * Komponente, die bei einer fremden Komponente als Listener eingetragen ist,
 * auch dort abgemeldet werden kann und diese fremde Komponente keine unnötigen
 * Nachrichten mehr abschickt.
 */
void EventManager::storeComponentRegistration(unsigned int componentId, Event event,
        unsigned int listenerId, EventManager* manager) {
    RegistrationRecord record(componentId, event, listenerId, manager);

    editLock.lock();
    registrations.push_back(record);
    editLock.unlock();
}


/**
 * @brief Speichert die Registrierung vom eigenen GameSystem
 * @param componentId Die Id der Komponente beim fremden GameSystem
 * @param event Das Event, unter der der Listener registriert wurde
 * @param listenerId Die Id der eigenen Komponente, die als Listener registriert wurde
 * @param manager Der fremde EventManager, der für die Komponente mit
 *                componentId zuständig ist.
 *
 * Die Speicherung der Registrierung erfolgt, damit beim Löschen des eigenen
 * GameSystems, welches bei einer fremden Komponente als Listener eingetragen ist,
 * dort abgemeldet werden kann und diese fremde Komponente keine unnötigen
 * Nachrichten mehr abschickt.
 */
void EventManager::storeSystemRegistration(unsigned int componentId, Event event,
        EventManager* manager) {
    RegistrationRecord record(componentId, event, manager);

    editLock.lock();
    registrations.push_back(record);
    editLock.unlock();
}


/**
 * @brief Löscht eine gespeicherte Registrierung (Komponente). Meldet die eigene Komponente
 *        beim fremden EventManager ab.
 * @param componentId Die Id der Komponente beim fremden GameSystem
 * @param event Das Event, unter der der Listener registriert wurde
 * @param listenerId Die Id der eigenen Komponente, die als Listener registriert wurde
 * @param manager Der fremde EventManager, der für die Komponente mit
 *                componentId zuständig ist.
 *
 * Löscht nur eine einzelne Registrierung.
 */
void EventManager::eraseComponentRegistration(unsigned int componentId, Event event,
        unsigned int listenerId, EventManager* manager) {

    RegistrationRecord record(componentId, event, listenerId, manager);
    editLock.lock();

    /*
     * Registrierungen durchsuchen
     */
    for(std::list<RegistrationRecord>::iterator element = registrations.begin();
            element != registrations.end(); element++) {
        /*
         * Beim fremden Manager abmelden, falls Registrierung vorhanden
         */
        if (element->isEqual(record)) {
            element->manager->deregisterComponentAsListener(record.componentId, record.event,
                    record.listenerId, this);
            break;
        }
    }

    /*
     * Alle Registrierungen mit den passenden Werten entfernen
     */
    registrations.remove_if( [&](RegistrationRecord & element) {
        return element.isEqual(record);
    });

    editLock.unlock();
}


/**
 * @brief Löscht alle Registrierungen der eigenen Komponente. Meldet die eigene
 *        Komponente bei allen eingetragenen EventManagern ab.
 * @param listenerId Die Id der eigenen Komponente, die als Listener registriert wurde
 *
 * Nach Aufruf wird keine EventMessage mehr an diese Komponente geschickt.
 */
void EventManager::eraseComponentRegistrations(unsigned int listenerId) {
    editLock.lock();

    /*
     * Registrierungen durchsuchen
     */
    for(std::list<RegistrationRecord>::iterator element = registrations.begin();
            element != registrations.end(); element++) {
        /*
         * Beim fremden Manager abmelden, falls Registrierung vorhanden
         */
        if (element->isEqual(listenerId)) {
            element->manager->deregisterComponentAsListener(element->componentId, element->event,
                    listenerId, this);
        }
    }

    /*
     * Alle Registrierungen mit listenerId entfernen
     */
    registrations.remove_if( [&](RegistrationRecord & element) {
        return element.isEqual(listenerId);
    });
    editLock.unlock();
}


/**
 * @brief Löscht eine gespeicherte Registrierung (GameSystem). Meldet das eigene GameSystem
 *        beim fremden EventManager ab.
 * @param componentId Die Id der Komponente beim fremden GameSystem
 * @param event Das Event, unter der der Listener registriert wurde
 * @param manager Der fremde EventManager, der für die Komponente mit
 *                componentId zuständig ist.
 *
 * Löscht nur eine einzelne Registrierung.
 */
void EventManager::eraseSystemRegistration(unsigned int componentId, Event event, EventManager* manager) {
    RegistrationRecord record(componentId, event, manager);
    editLock.lock();

    /*
     * Registrierungen durchsuchen
     */
    for(std::list<RegistrationRecord>::iterator element = registrations.begin();
            element != registrations.end(); element++) {
        /*
         * Beim fremden Manager abmelden, falls Registrierung vorhanden
         */
        if (element->isEqual(record)) {
            element->manager->deregisterSystemAsListener(record.componentId, record.event, this);
            break;
        }
    }

    /*
     * Alle Registrierungen mit den passenden Werten entfernen
     */
    registrations.remove_if( [&](RegistrationRecord & element) {
        return element.isEqual(record);
    });

    editLock.unlock();
}


/**
 * @brief Löscht alle Registrierungen des eigenen GameSystems. Meldet das eigene
 *        GameSystem bei allen eingetragenen EventManagern ab.
 *
 * Nach Aufruf wird keine EventMessage mehr an dieses GameSystem geschickt.
 */
void EventManager::eraseSystemRegistrations() {
    editLock.lock();

    /*
     * Registrierungen durchsuchen
     */
    for(std::list<RegistrationRecord>::iterator element = registrations.begin();
            element != registrations.end(); element++) {
        /*
         * Beim fremden Manager abmelden, falls Registrierung vorhanden
         */
        if (element->gameSystemListener) {
            element->manager->deregisterSystemAsListener(element->componentId, element->event, this);
        }
    }

    /*
     * Alle Registrierungen mit listenerId entfernen
     */
    registrations.remove_if( [&](RegistrationRecord & element) {
        return element.gameSystemListener;
    });
    editLock.unlock();
}



/**
 * @brief Löscht eine gespeicherte Registrierung.
 * @param componentId Die Id der Komponente beim fremden GameSystem
 * @param manager Der fremde EventManager, der für die Komponente mit
 *                componentId zuständig ist.
 *
 * Wird von einer fremden Komponente aufgerufen, wenn sie gelöscht wird.
 * Die gespeicherten Registrierungen dieser fremden Komponente können
 * anschließend gelöscht werden, da sie keine EventMessage mehr aussenden
 * wird.
 */
void EventManager::signalDeletion(unsigned int componentId, EventManager* manager) {
    editLock.lock();
    /*
     * Alle Registrierungen mit den passenden Werten entfernen
     */
    registrations.remove_if( [&](RegistrationRecord & element) {
        return element.isEqual(componentId, manager, false)
               || element.isEqual(componentId, manager, true);
    });
    editLock.unlock();
}



/**
 * @brief Benachrichtigt eine Komponente über das Eintreten eines Event
 * @param message Die EventMessage, die der Komponente geschickt werden soll
 *
 * Diese Methode schickt den Aufruf lediglich in eine Queue, die möglicherweise nicht
 * unmittelbar verarbeitet wird.
 */
void EventManager::sendMessage(EventMessage * message) {
    receivingMessages->push_back(message);
}

/**
 * @brief Verteilt die Nachrichten an die Komponenten des GameSystem
 */
void EventManager::deployMessages() {
    std::swap(receivingMessages, workingMessages);

    for (unsigned int i = 0; i < workingMessages->size(); i++) {
        if (workingMessages->at(i)->gameSystemListener) {
            receivingSystem->notify(workingMessages->at(i));
        } else {
            receivingSystem->notifyComponent(workingMessages->at(i));
        }
    }

    workingMessages->clear();
}

void EventManager::discardMessages() {
    std::swap(receivingMessages, workingMessages);
    workingMessages->clear();
}


EventManager::EventManager(ISystem* receivingSystem) {
    this->receivingSystem = receivingSystem;
    this->receivingMessages = &messagesA;
    this->workingMessages = &messagesB;
}


EventManager::~EventManager() {
    for (unsigned int i = 0; i < messagesB.size(); i++) {
        delete(messagesB.at(i));
    }

    for (unsigned int i = 0; i < messagesA.size(); i++) {
        delete(messagesA.at(i));
    }
}
