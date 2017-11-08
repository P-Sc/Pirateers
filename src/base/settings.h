/**
 * @file settings.h
 */

#ifndef SETTINGS_H
#define SETTINGS_H


/**
 * @brief Eine leere Speicherklasse.
 *
 * Wird von GameSystem und den Unterklassen benutzt.
 */

struct Settings {
    bool active = true; // TODO: In jedem System verarbeiten
    virtual ~Settings() {}
};

#endif // SETTINGS_H
