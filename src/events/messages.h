/**
 * @file messages.h
 */

#ifndef MESSAGES_H
#define MESSAGES_H

#include <string>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Color.hpp>
#include <Box2D/Common/b2Math.h>

using sf::Keyboard;
using sf::Mouse;

/*
 * Anleitung für neue Events:
 * 1. Neues Event unter "enum Event" eintragen.
 * 2. Falls nötig passende Message-Klasse erstellen, welche von EventMessage erbt.
 * 3. Falls neue Message-Klasse: MessageCloner::clone() für neue Message-Klasse erstellen
 * 4. In MessageCloner::cloneMessage() eintragen.
 */


/**
 * @enum Event
 * @brief Die verschiedenen Typen an Ereignissen
 *
 * Kann auch eine spezifische EventMessage haben, welche in MessageCloner
 * korrekt aufgeführt werden muss.
 */
enum Event {
    /*
     * Allgemein
     */
    evNoEvent,              ///< Kein Event
    cmActivate,             ///< Komponente aktivieren
    cmDeactivate,           ///< Komponente deaktivieren
    evMove,                 ///< Komponente hat sich bewegt oder soll bewegt werden

    /*
     * Grafik
     */
    cmSpawnLight,           ///< Licht spawnen

    /*
     * Physik
     */
    cmApplyForce,           ///< Kraft anlegen
    cmRotateTo,             ///< Komponente soll sich zu einem Punkt drehen
    cmStopRotating,         ///< Komponente soll aufhören sich zu drehen

    /*
     * Input
     */
    evKeyPressed,           ///< Taste wurde gedrückt
    evKeyReleased,          ///< Taste wurde losgelassen
    evMouseMoved,           ///< Maus hat sich bewegt
    evMouseButtonPressed,   ///< Maustaste wurde gedrückt
    evMouseButtonReleased,  ///< Maustaste wurde losgelassen
    evMouseWheelScrolled,   ///< Mausrad wurde betätigt

    /*
     * Fenster & Kamera
     */
    evMainMenuOpened,       /// Hauptmenü wurde geöffnet
    evMainMenuClosed,       /// Hauptmenü wurde geschlossen
    cmShake,                ///< Kamera wackeln
    evWindowClosed,         ///< Fenster wurde geschlossen
    evWindowResized,        ///< Fenstergröße wurde verändert
    evCameraChanged,        ///< Kameraeinstellung hat sich verändert
    evZoomed,               ///< Zoom

    /*
     * Schiffe
     */
    cmOpenFire,             ///< Feuer eröffnen
    cmCeaseFire,            ///< Feuer einstellen
    cmAimAt,                ///< Komponente soll zu einem Punkt zielen
    cmPowerEngines,         ///< Antrieb aktivieren
    evHit,                  ///< Treffer
    evShield,               ///< Schild- /Rumpfwert verändert (z.B. durch Treffer)
    evDestroyed,            ///< (Schiff) wurde zerstört
    evEnergyStatus,         ///< Energiestand verändert
    evEnergyUsed,           ///< Energie benutzt

    /*
     * Spiellogik
     */
    evCreditStatus,         ///< Geld eingesammelt
    evPurchase,             ///< Gekauft
    cmUpgrade,              ///< Upgrade ausführen
    cmRepair,               ///< Reparieren
    evAreaChanged,          ///< Gebiet wurde gewechselt
    cmStartTeleport,        ///< Teleport starten
    evTeleported,           ///< Teleportiert
    evNoPlayerSet,          ///< Kein Spieler mehr für KI sichtbar
    evPlayerSet,            ///< Spieler (wieder) für KI sichtbar

    /*
     * Sound
     */
    cmPlaySound,
    cmPauseSound,
    cmStopSound,


    // Für Tests
    evTestEvent,            ///< Für Tests
};

enum Area {ShopArea, BretoniaArea, BanditArea, TaulanArea, AlienArea, XuruArea, StartArea};

/**
 * @struct EventMessage
 * @brief Basis-Speicherklasse für EventMessages.
 */
struct EventMessage {
    Event event = evNoEvent;
    bool gameSystemListener = false;
    unsigned int senderId = 0;
    unsigned int receiverId = 0;
    float value = 0, value2 = 0;
    EventMessage() {}
    EventMessage(Event event) : event(event) {}
    virtual ~EventMessage() {}
};

/**
 * @struct EventPosMessage
 * @brief EventMessage für Positionen
 */
struct EventPosMessage : public EventMessage {
    float rotation = 0, force = 0, torque = 0;
    b2Vec2 pos, center, velocity;
};


/**
 * @struct EventPosMessage
 * @brief EventMessage zum spawnen von Lichtern
 */
struct EventLightMessage : public EventMessage {
    sf::Color color = sf::Color(0,0,0);
    float duration = 0, delay = 0, fadeDelay = 0, size = 10;
    b2Vec2 pos = b2Vec2(0,0);

    EventLightMessage() {
        event = cmSpawnLight;
    }
};


/**
 * @struct EventKeyPressedMessage
 * @brief EventMessage für Benutzereingaben
 */
struct EventKeyMessage : public EventMessage {
    Keyboard::Key key;
};



/**
 * @struct EventMouseMessage
 * @brief EventMessage für Mauseingaben
 */
struct EventMouseMessage : public EventMessage {
    float scroll;
    b2Vec2 sfScreenPos;
    b2Vec2 sfRelScreenPos;
    b2Vec2 pos;
    Mouse::Button button;

    EventMouseMessage(Event event) : EventMessage(event) {}
    EventMouseMessage() {}
};


/**
 * @struct EventResizedMessage
 * @brief EventMessage für Fensteränderungen
 */
struct EventResizedMessage : public EventMessage {
    b2Vec2 size;
    EventResizedMessage() {
        event = evWindowResized;
    }
};


/**
 * @struct EventCameraMessage
 * @brief EventMessage für Kamera-Änderungen
 */
struct EventCameraMessage : public EventMessage {
    b2Vec2 center, relOffset, size;
    float scale;
    EventCameraMessage() {
        event = evCameraChanged;
    }
};


/**
 * @struct EventHitMessage
 * @brief EventMessage für Treffer
 */
struct EventHitMessage : public EventMessage {
    b2Vec2 pos, dir;
    int damage = 0;
    EventHitMessage() {
        event = evHit;
    }
};


/**
 * @struct EventShieldMessage
 * @brief EventMessage für Schilde und Rumpf
 */
struct EventShieldMessage : public EventMessage {
    int shield = 0, hull = 0, maxShield = 0, maxHull = 0;
    EventShieldMessage() {
        event = evShield;
    }
};


/**
 * @struct EventUpgradeMessage
 * @brief EventMessage für Upgrades
 */
struct EventUpgradeMessage : public EventMessage {
    std::string upgrade;
    int slot = -2;
    EventUpgradeMessage() {
        event = cmUpgrade;
    }
};


/**
 * @struct EventAreaMessage
 * @brief EventMessage für Areas
 */
struct EventAreaMessage : public EventMessage {
    Area area;
    EventAreaMessage() {
        event = evAreaChanged;
    }
};


/**
 * @struct EventSoundMessage
 * @brief EventMessage für Sounds
 */
struct EventSoundMessage : public EventMessage {
    b2Vec2 pos;
    std::string file;
    EventSoundMessage() {
        event = cmPlaySound;
    }
};



/**
 * @struct EventTestMessage
 * @brief Helfer-EventMessage für EventManager-UnitTest
 */
struct EventTestMessage : public EventMessage  {
    std::string text;
    EventTestMessage() {
        event = evTestEvent;
    }
};


/**
 * @class MessageCloner
 * @brief Statische Klasse zum Kopieren von Nachrichten
 *
 * Wird beim Versenden von Nachrichten (EventMessage) in Component dessen
 * Unterklassen verwendet
 */
class MessageCloner {
private:
    /**
     * @brief Kopiert die EventMessage
     * @param message Die EventMessage
     * @return Eine Duplikat
     */
    static EventMessage* clone(EventMessage* message) {
        EventMessage* clone = new EventMessage();
        *clone = *message;
        return clone;
    }


    /**
     * @brief Kopiert die EventKeyPressedMessage
     * @param message Die EventKeyPressedMessage
     * @return Eine Duplikat
     */
    static EventMessage* clone(EventKeyMessage* message) {
        EventKeyMessage* clone = new EventKeyMessage();
        *clone = *message;
        return clone;
    }


    /**
     * @brief Kopiert die EventPosMessage
     * @param message Die EventPosMessage
     * @return Eine Duplikat
     */
    static EventMessage* clone(EventPosMessage* message) {
        EventPosMessage* clone = new EventPosMessage();
        *clone = *message;
        return clone;
    }


    /**
     * @brief Kopiert die EventLightMessage
     * @param message Die EventLightMessage
     * @return Eine Duplikat
     */
    static EventMessage* clone(EventLightMessage* message) {
        EventLightMessage* clone = new EventLightMessage();
        *clone = *message;
        return clone;
    }


    /**
     * @brief Kopiert die EventMouseMessage
     * @param message Die EventMouseMessage
     * @return Eine Duplikat
     */
    static EventMessage* clone(EventMouseMessage* message) {
        EventMouseMessage* clone = new EventMouseMessage();
        *clone = *message;
        return clone;
    }


    /**
     * @brief Kopiert die EventResizedMessage
     * @param message Die EventResizedMessage
     * @return Eine Duplikat
     */
    static EventMessage* clone(EventResizedMessage* message) {
        EventResizedMessage* clone = new EventResizedMessage();
        *clone = *message;
        return clone;
    }

    /**
     * @brief Kopiert die EventCameraMessage
     * @param message Die EventCameraMessage
     * @return Eine Duplikat
     */
    static EventMessage* clone(EventCameraMessage* message) {
        EventCameraMessage* clone = new EventCameraMessage();
        *clone = *message;
        return clone;
    }

    /**
     * @brief Kopiert die EventHitMessage
     * @param message Die EventHitMessage
     * @return Eine Duplikat
     */
    static EventMessage* clone(EventHitMessage* message) {
        EventHitMessage* clone = new EventHitMessage();
        *clone = *message;
        return clone;
    }


    /**
     * @brief Kopiert die EventShieldMessage
     * @param message Die EventShieldMessage
     * @return Eine Duplikat
     */
    static EventMessage* clone(EventShieldMessage* message) {
        EventShieldMessage* clone = new EventShieldMessage();
        *clone = *message;
        return clone;
    }


    /**
     * @brief Kopiert die EventUpgradeMessage
     * @param message Die EventUpgradeMessage
     * @return Eine Duplikat
     */
    static EventMessage* clone(EventUpgradeMessage* message) {
        EventUpgradeMessage* clone = new EventUpgradeMessage();
        *clone = *message;
        return clone;
    }


    /**
     * @brief Kopiert die EventAreaMessage
     * @param message Die EventAreaMessage
     * @return Eine Duplikat
     */
    static EventMessage* clone(EventAreaMessage* message) {
        EventAreaMessage* clone = new EventAreaMessage();
        *clone = *message;
        return clone;
    }


    /**
     * @brief Kopiert die EventSoundMessage
     * @param message Die EventSoundMessage
     * @return Eine Duplikat
     */
    static EventMessage* clone(EventSoundMessage* message) {
        EventSoundMessage* clone = new EventSoundMessage();
        *clone = *message;
        return clone;
    }


    /**
     * @brief Kopiert die EventTestMessage
     * @param message Die EventTestMessage
     * @return Eine Duplikat
     */
    static EventMessage* clone(EventTestMessage* message) {
        EventTestMessage* clone = new EventTestMessage();
        *clone = *message;
        return clone;
    }


public:
    /**
     * @brief Kopiert die EventMessage anhand des Event-Typs.
     * @param message Eine EventMessage oder eine Unterklasse davon
     * @return Ein Duplikat
     * @warning Muss anschließend auf die korrekte Unterklasse von EventMessage
     *          gecastet werden (falls eine Unterklasse verwendet wird)
     */
    static EventMessage* cloneMessage(EventMessage* message) {
        switch (message->event) {
        case cmActivate:
            return clone ((EventMessage *) message);
        case cmDeactivate:
            return clone ((EventMessage *) message);
        case evMove:
            return clone((EventPosMessage*) message);
        case cmSpawnLight:
            return clone((EventLightMessage*) message);
        case cmApplyForce:
            return clone((EventPosMessage*) message);
        case cmRotateTo:
            return clone((EventPosMessage*) message);
        case cmStopRotating:
            return clone ((EventMessage *) message);
        case evKeyPressed:
            return clone((EventKeyMessage*) message);
        case evKeyReleased:
            return clone((EventKeyMessage*) message);
        case evTestEvent:
            return clone((EventTestMessage*) message);
        case evMouseMoved:
            return clone((EventMouseMessage*) message);
        case evMouseButtonPressed:
            return clone((EventMouseMessage*) message);
        case evMouseButtonReleased:
            return clone((EventMouseMessage*) message);
        case evMouseWheelScrolled:
            return clone((EventMouseMessage*) message);
        case evMainMenuOpened:
            return clone ((EventMessage *) message);
        case evMainMenuClosed:
            return clone ((EventMessage *) message);
        case cmShake:
            return clone ((EventMessage *) message);
        case evWindowResized:
            return clone((EventResizedMessage*) message);
        case evCameraChanged:
            return clone((EventCameraMessage*) message);
        case cmOpenFire:
            return clone ((EventMessage*) message);
        case cmCeaseFire:
            return clone ((EventMessage*) message);
        case cmAimAt:
            return clone((EventPosMessage*) message);
        case cmPowerEngines:
            return clone ((EventMessage *) message);
        case evHit:
            return clone ((EventHitMessage*) message);
        case evShield:
            return clone ((EventShieldMessage*) message);
        case evCreditStatus:
            return clone ((EventMessage*) message);
        case evPurchase:
            return clone ((EventMessage*) message);
        case cmUpgrade:
            return clone ((EventUpgradeMessage*) message);
        case evAreaChanged:
            return clone ((EventAreaMessage*) message);
        case cmStartTeleport:
            return clone ((EventMessage*) message);
        case evTeleported:
            return clone ((EventMessage*) message);
        case evNoPlayerSet:
            return clone ((EventMessage*) message);
        case evPlayerSet:
            return clone ((EventMessage*) message);
        case cmRepair:
            return clone ((EventMessage*) message);
        case evDestroyed:
            return clone ((EventShieldMessage*) message);
        case evEnergyStatus:
            return clone ((EventMessage*) message);
        case evEnergyUsed:
            return clone ((EventMessage*) message);
        case cmPlaySound:
            return clone ((EventSoundMessage*) message);
        case cmPauseSound:
            return clone ((EventSoundMessage*) message);
        case cmStopSound:
            return clone ((EventSoundMessage*) message);
        default:
            return clone(message);
        }
    }

    /**
     * @brief Löscht die EventMessage anhand ihres Typs.
     * @param message Eine EventMessage oder eine Unterklasse davon
     * @warning Der Pointer message wird danach auf NULL gesetzt
     */
    static void deleteMessage(EventMessage* message) {
        /*
        switch (message->event) {
        case cmActivate:
            delete ((EventMessage*) message);
            break;
        case cmDeactivate:
            delete ((EventMessage*) message);
            break;
        case evMove:
            delete ((EventPosMessage*) message);
            break;
        case cmSpawnLight:
            delete ((EventLightMessage*) message);
            break;
        case cmApplyForce:
            delete ((EventPosMessage*) message);
            break;
        case cmRotateTo:
            delete ((EventPosMessage*) message);
            break;
        case cmStopRotating:
            delete ((EventMessage*) message);
            break;
        case evKeyPressed:
            delete ((EventKeyMessage*) message);
            break;
        case evKeyReleased:
            delete ((EventKeyMessage*) message);
            break;
        case evTestEvent:
            delete ((EventTestMessage*) message);
            break;
        case evMouseMoved:
            delete ((EventMouseMessage*) message);
            break;
        case evMouseButtonPressed:
            delete ((EventMouseMessage*) message);
            break;
        case evMouseButtonReleased:
            delete ((EventMouseMessage*) message);
            break;
        case evMouseWheelScrolled:
            delete ((EventMouseMessage*) message);
            break;
        case cmShake:
            delete ((EventMessage*) message);
            break;
        case evWindowResized:
            delete ((EventResizedMessage*) message);
            break;
        case evCameraChanged:
            delete ((EventCameraMessage*) message);
            break;
        case cmOpenFire:
            delete ((EventMessage*) message);
            break;
        case cmCeaseFire:
            delete ((EventMessage*) message);
            break;
        case cmAimAt:
            delete ((EventPosMessage*) message);
            break;
        case cmPowerEngines:
            delete ((EventMessage*) message);
            break;
        case evHit:
            delete ((EventHitMessage*) message);
            break;
        case evShield:
            delete ((EventShieldMessage*) message);
            break;
        case evCreditStatus:
            delete ((EventMessage*) message);
            break;
        case evPurchase:
            delete ((EventMessage*) message);
            break;
        case cmUpgrade:
            delete ((EventUpgradeMessage*) message);
            break;
        case cmRepair:
            delete ((EventMessage*) message);
            break;
        case evDestroyed:
            delete ((EventShieldMessage*) message);
            break;
        case evEnergyStatus:
            delete ((EventMessage*) message);
            break;
        case evEnergyUsed:
            delete ((EventMessage*) message);
            break;
        case cmPlaySound:
            delete ((EventSoundMessage*) message);
            break;
        case cmPauseSound:
            delete ((EventSoundMessage*) message);
            break;
        case cmStopSound:
            delete ((EventSoundMessage*) message);
            break;
        default:
            // TODO: Logger!
            delete (message);
        }*/
        delete message;
        message = nullptr;
    }
};

//typedef std::shared_ptr<EventMessage> MessagePointer;

#endif // MESSAGES_H
