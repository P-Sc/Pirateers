/**
 * @file inputcomponent.h
 */

#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "events/messages.h"
#include "base/component.h"


/**
 * @class InputComponent
 * @brief Dummy-Komponente zum versenden von Messages.
 */
class InputComponent : public Component
{
/*
protected:
    virtual EventMessage* cloneMessage(EventMessage* message); */
public:
    InputComponent(Settings settings, Handle* handle);
};

#endif // INPUTCOMPONENT_H
