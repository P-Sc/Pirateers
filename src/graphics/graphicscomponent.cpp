#include "graphicscomponent.h"
#include <iostream>
//#include "settings/graphicssettings.h"
//#include <SFML/Graphics.hpp>

#include "exceptions/fileopenerror.h"


/**
 * @copydoc Component::notify
 *
 * Erkannte Events:
 * - ::evMove Position des Sprites. Konvertiert von Box2D-Koordinaten
 * - ::cmActivate Macht Sprite sichtbar.
 * - ::cmDeactivate Macht Sprite unsichtbar.
 */
void GraphicsComponent::notify(EventMessage* message) {
    switch (message->event) {
    case evMove: {
        EventPosMessage* posMessage = (EventPosMessage*) message;
        sprite.setPosition(posMessage->pos.x * scale,
                           posMessage->pos.y * scale);
        double r = posMessage->rotation + M_PI;
        sprite.setRotation(r * 180 / M_PI);
        break;
    }

    case cmActivate: {
        visible = true;
        break;
    }

    case cmDeactivate: {
        visible = false;
        break;
    }
    }

    delete message;;
}


/**
 * @brief Gibt an, ob Komponente sichtbar ist
 * @return True, falls sichtbar
 */
bool GraphicsComponent::isVisible(unsigned int layer) {
    return (visible && settings.layer == layer);
}


/**
 * @brief Gibt an, ob Sprite mit Shadern gemalt werden soll
 */
bool GraphicsComponent::usesShader() {
    return settings.useShader;
}


/**
 * @brief Setzt die Sichtbarkeit der Komponente
 * @param visible Die Sichtbarkeit
 */
void GraphicsComponent::setVisible(bool visible) {
    this->visible = visible;
}


/**
 * @brief Gibt den Namen/Pfad der Textur zurück
 * @return Name/Pfad der Textur
 */
std::string GraphicsComponent::getTextureName() {
    return settings.texture;
}


GraphicsComponent::GraphicsComponent(GraphicsSettings settings, Handle* handle)
    : Component(settings, handle) {

    this->settings = settings;
    sprite.setColor(settings.color);
    sprite.setPosition(settings.pos * scale);
    sprite.setRotation(settings.rotation);
    //sprite.setTextureRect(sf::IntRect(settings.rectX, settings.rectY,
    //                                 settings.rectWidth, settings.rectHeight));
    //sprite.setOrigin(settings.rectWidth/2.f, settings.rectHeight/2.f);
    //sprite.scale(settings.scale, settings.scale);

}
