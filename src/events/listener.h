/**
 * @file listener.h
 */

#ifndef LISTENER_H
#define LISTENER_H

class EventManager;
class EventMessage;

/**
 * @struct Listener
 * @brief Struct zum Speichern von Listenern.
 *
 * Wird in Component benutzt.
 */
struct Listener {
    bool gameSystemListener = false;
    unsigned int id = 0;
    EventManager* destinationManager = nullptr;
    EventMessage* message;
};

#endif // LISTENER_H
