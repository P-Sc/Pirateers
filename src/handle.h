/**
 * @file handle.h
 */

#ifndef HANDLE_H
#define HANDLE_H

//#include <memory>
#include "base/isystem.h"


/**
 * @class Handle
 * @brief Ein Handle, welches primär zum Abspeichern der ID eines Components benutzt wird.
 */
struct Handle {
    unsigned int id = 0;
    ISystem* system = nullptr;
    bool alive = true;

    Handle(unsigned int id, ISystem* system) {
        this->id = id;
        this->system = system;
    }

    void destroy() {
        system->eraseComponent(id);
    }

    /**
     * @brief Destruktor. Zerstört auch die Komponente.
     */
    ~Handle() {
        if (alive) {
            system->eraseComponent(id);
        }
    }
};

//typedef std::shared_ptr<Handle> HandlePointer;

#endif // HANDLE_H
