#include "tagcomponent.h"
#include "SFML/System/Vector2.hpp"

/**
 * @copydoc Component::notify
 * - ::evMove Positionen aktualisieren
 * - ::evShield Schildstatus aktualisieren
 * - ::evEnergyStatus Energiestatus aktualisieren
 * - ::cmActivate Komponente sichtbar machen
 * - ::cmDeactivate Komponente unsichtbar machen
 */
void TagComponent::notify(EventMessage *message) {
    switch (message->event) {
    case evMove: {
        EventPosMessage* posMessage = (EventPosMessage*) message;
        borderLeft.setPosition(posMessage->pos.x * 30.f,
                               posMessage->pos.y * 30.f);
        borderTopLeft.setPosition(posMessage->pos.x * 30.f,
                               posMessage->pos.y * 30.f);
        borderBottomLeft.setPosition(posMessage->pos.x * 30.f,
                               posMessage->pos.y * 30.f);
        borderRight.setPosition(posMessage->pos.x * 30.f,
                               posMessage->pos.y * 30.f);
        borderTopRight.setPosition(posMessage->pos.x * 30.f,
                               posMessage->pos.y * 30.f);
        borderBottomRight.setPosition(posMessage->pos.x * 30.f,
                               posMessage->pos.y * 30.f);
        hullBar.setPosition(posMessage->pos.x * 30.f,
                              posMessage->pos.y * 30.f + settings.gap * 30.f);
        hullBackgroundBar.setPosition(posMessage->pos.x * 30.f,
                              posMessage->pos.y * 30.f + settings.gap * 30.f);
        hullBorderBar.setPosition(posMessage->pos.x * 30.f,
                              posMessage->pos.y * 30.f + settings.gap * 30.f);
        shieldBar.setPosition(posMessage->pos.x * 30.f,
                              posMessage->pos.y * 30.f + settings.gap * 30.f + 2* barHeight);
        shieldBackgroundBar.setPosition(posMessage->pos.x * 30.f,
                              posMessage->pos.y * 30.f + settings.gap * 30.f + 2* barHeight);
        shieldBorderBar.setPosition(posMessage->pos.x * 30.f,
                              posMessage->pos.y * 30.f + settings.gap * 30.f + 2* barHeight);
        energyBar.setPosition(posMessage->pos.x * 30.f,
                              posMessage->pos.y * 30.f + settings.gap * 30.f + 4* barHeight);
        energyBackgroundBar.setPosition(posMessage->pos.x * 30.f,
                              posMessage->pos.y * 30.f + settings.gap * 30.f + 4* barHeight);
        energyBorderBar.setPosition(posMessage->pos.x * 30.f,
                              posMessage->pos.y * 30.f + settings.gap * 30.f + 4* barHeight);
        break;
    }

    case evShield: {
        EventShieldMessage* shieldMessage = (EventShieldMessage*) message;
        hullBar.setSize(sf::Vector2f(settings.gap * 30.f
                                     * shieldMessage->hull / shieldMessage->maxHull,
                                     barHeight));
        shieldBar.setSize(sf::Vector2f(settings.gap * 30.f
                                       * shieldMessage->shield / shieldMessage->maxShield,
                                       barHeight));
        break;
    }

    case evEnergyStatus: {
        energyBar.setSize(sf::Vector2f(settings.gap * 30.f
                                     * message->value / message->value2,
                                     barHeight));
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

    default:
    {}
    }

    delete message;;
}

TagComponent::TagComponent(TagSettings settings, Handle* handle)
    : settings(settings), Component(settings, handle) {


    hullBar.setSize(sf::Vector2f(settings.gap * 30.f, barHeight));
    hullBar.setOrigin(settings.gap * 30.f / 2.f, barHeight / 2.f);
    hullBar.setFillColor(hullColor);
    hullBackgroundBar.setSize(sf::Vector2f(settings.gap * 30.f, barHeight));
    hullBackgroundBar.setOrigin(settings.gap * 30.f / 2.f, barHeight / 2.f);
    hullBackgroundBar.setFillColor(hullBackgroundColor);
    hullBorderBar.setSize(sf::Vector2f(settings.gap * 30.f, barHeight));
    hullBorderBar.setOrigin(settings.gap * 30.f / 2.f, barHeight / 2.f);
    hullBorderBar.setFillColor(sf::Color(0,0,0,0));
    hullBorderBar.setOutlineColor(hullColor);
    hullBorderBar.setOutlineThickness(2);
    shieldBar.setSize(sf::Vector2f(settings.gap * 30.f, barHeight));
    shieldBar.setOrigin(settings.gap * 30.f / 2.f, barHeight / 2.f);
    shieldBar.setFillColor(shieldColor);
    shieldBackgroundBar.setSize(sf::Vector2f(settings.gap * 30.f, barHeight));
    shieldBackgroundBar.setOrigin(settings.gap * 30.f / 2.f, barHeight / 2.f);
    shieldBackgroundBar.setFillColor(shieldBackgroundColor);
    shieldBorderBar.setSize(sf::Vector2f(settings.gap * 30.f, barHeight));
    shieldBorderBar.setOrigin(settings.gap * 30.f / 2.f, barHeight / 2.f);
    shieldBorderBar.setFillColor(sf::Color(0,0,0,0));
    shieldBorderBar.setOutlineColor(shieldColor);
    shieldBorderBar.setOutlineThickness(2);
    energyBar.setSize(sf::Vector2f(settings.gap * 30.f, barHeight));
    energyBar.setOrigin(settings.gap * 30.f / 2.f, barHeight / 2.f);
    energyBar.setFillColor(energyColor);
    energyBackgroundBar.setSize(sf::Vector2f(settings.gap * 30.f, barHeight));
    energyBackgroundBar.setOrigin(settings.gap * 30.f / 2.f, barHeight / 2.f);
    energyBackgroundBar.setFillColor(energyBackgroundColor);
    energyBorderBar.setSize(sf::Vector2f(settings.gap * 30.f, barHeight));
    energyBorderBar.setOrigin(settings.gap * 30.f / 2.f, barHeight / 2.f);
    energyBorderBar.setFillColor(sf::Color(0,0,0,0));
    energyBorderBar.setOutlineColor(energyColor);
    energyBorderBar.setOutlineThickness(2);


    borderRight.setFillColor(settings.color);
    borderBottomRight.setFillColor(settings.color);
    borderTopRight.setFillColor(settings.color);
    borderLeft.setFillColor(settings.color);
    borderBottomLeft.setFillColor(settings.color);
    borderTopLeft.setFillColor(settings.color);

    int borderHeight = settings.height * 30.f * 0.5f;
    int borderWidth = settings.height * 30.f * 0.05f;
    int offset = settings.height * 30.f * offsetFactor;
    borderRight.setPointCount(4);
    borderTopRight.setPointCount(4);
    borderBottomRight.setPointCount(4);
    borderLeft.setPointCount(4);
    borderTopLeft.setPointCount(4);
    borderBottomLeft.setPointCount(4);

    // Rechtes Mittelteil
    borderRight.setPoint(0, sf::Vector2f(settings.gap * 30.f,
                                         borderHeight * -1));
    borderRight.setPoint(1, sf::Vector2f(settings.gap * 30.f,
                                         borderHeight));
    borderRight.setPoint(2, sf::Vector2f(settings.gap * 30.f + borderWidth,
                                         borderHeight));
    borderRight.setPoint(3, sf::Vector2f(settings.gap * 30.f + borderWidth,
                                         borderHeight * -1));

    // Rechter unterer Teil
    borderBottomRight.setPoint(0, sf::Vector2f(settings.gap * 30.f + borderWidth,
                                               borderHeight));
    borderBottomRight.setPoint(1, sf::Vector2f(settings.gap * 30.f,
                                               borderHeight));
    borderBottomRight.setPoint(2, sf::Vector2f(settings.gap * 30.f - offset,
                                               borderHeight + offset));
    borderBottomRight.setPoint(3, sf::Vector2f(settings.gap * 30.f - offset + borderWidth,
                                               borderHeight + offset));

    // Rechter oberer Teil
    borderTopRight.setPoint(0, sf::Vector2f(settings.gap * 30.f,
                                            borderHeight * -1));
    borderTopRight.setPoint(1, sf::Vector2f(settings.gap * 30.f + borderWidth,
                                            borderHeight * -1));
    borderTopRight.setPoint(2, sf::Vector2f(settings.gap * 30.f - offset + borderWidth,
                                            borderHeight * -1 - offset));
    borderTopRight.setPoint(3, sf::Vector2f(settings.gap * 30.f - offset,
                                            borderHeight * -1 - offset));

    // Linkes Mittelteil
    borderLeft.setPoint(0, sf::Vector2f(settings.gap * 30.f * -1,
                                         borderHeight * -1));
    borderLeft.setPoint(1, sf::Vector2f(settings.gap * 30.f * -1,
                                         borderHeight));
    borderLeft.setPoint(2, sf::Vector2f(settings.gap * 30.f * -1 - borderWidth,
                                         borderHeight));
    borderLeft.setPoint(3, sf::Vector2f(settings.gap * 30.f * -1 - borderWidth,
                                         borderHeight * -1));

    // Linker unterer Teil
    borderBottomLeft.setPoint(0, sf::Vector2f(settings.gap * 30.f * -1 - borderWidth,
                                               borderHeight));
    borderBottomLeft.setPoint(1, sf::Vector2f(settings.gap * 30.f * -1,
                                               borderHeight));
    borderBottomLeft.setPoint(2, sf::Vector2f(settings.gap * 30.f * -1 + offset,
                                               borderHeight + offset));
    borderBottomLeft.setPoint(3, sf::Vector2f(settings.gap * 30.f * -1 + offset - borderWidth,
                                               borderHeight + offset));

    // Linker oberer Teil
    borderTopLeft.setPoint(0, sf::Vector2f(settings.gap * 30.f * -1,
                                            borderHeight * -1));
    borderTopLeft.setPoint(1, sf::Vector2f(settings.gap * 30.f * -1 - borderWidth,
                                            borderHeight * -1));
    borderTopLeft.setPoint(2, sf::Vector2f(settings.gap * 30.f * -1 + offset - borderWidth,
                                            borderHeight * -1 - offset));
    borderTopLeft.setPoint(3, sf::Vector2f(settings.gap * 30.f * -1 + offset,
                                            borderHeight * -1 - offset));

}
