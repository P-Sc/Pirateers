/**
 * @file shipinputsystem.h
 */
#ifndef SHIPINPUTSYSTEM_H
#define SHIPINPUTSYSTEM_H

#include "input/shipinputcomponent.h"
#include "input/shipinputsettings.h"
#include "base/gamesystem.h"
#include <set>

class InputSystem;
class CameraSystem;


/**
 * @class ShipInputSystem
 * @brief Klasse zur Verarbeitung der Spielereingaben für die Schiffssteuerung.
 *
 * Interpretiert Eingaben und sendet daraufhin Messages an ein ShipComponent.
 * Dies ist nötig, da jedes ShipComponent nur generischere Events empfängt,
 * um diese auch für KI nutzbar zu machen.
 */
class ShipInputSystem : public GameSystem<ShipInputComponent, ShipInputSettings>
{
private:
    InputSystem& inputSystem;
    CameraSystem& cameraSystem;
    Handle* singleton = nullptr;
    std::set<Keyboard::Key> pressedKeys;
    bool rotating;
    void registerAsListener();
    void powerEngines();
    virtual Handle* createComponent(ShipInputSettings settings);
public:
    void registerShipAsListener(Handle* shipHandle);
    virtual void update(float dt);
    virtual void notify(EventMessage *message);
    ShipInputSystem(ShipInputSettings settings, InputSystem& inputSystem,
                    CameraSystem& cameraSystem);
};

#endif // SHIPINPUTSYSTEM_H
