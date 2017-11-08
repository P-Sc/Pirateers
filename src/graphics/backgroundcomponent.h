/**
 * @file backgroundcomponent.h
 */
#ifndef BACKGROUNDCOMPONENT_H
#define BACKGROUNDCOMPONENT_H

#include "base/component.h"
#include "graphics/backgroundsettings.h"

/**
 * @class BackgroundComponent
 * @brief Dummy-Component zum Versenden von Nachrichten
 */
class BackgroundComponent : public Component {
private:
    BackgroundSettings settings;
public:
    virtual void notify(EventMessage *message);
    BackgroundComponent(BackgroundSettings settings, Handle* handle);
};

#endif // BACKGROUNDCOMPONENT_H
