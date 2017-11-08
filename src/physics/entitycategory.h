/**
 * @file entitycatergory.h
 */
#ifndef ENTITYCATEGORY_H
#define ENTITYCATEGORY_H

/**
 * @enum EntityCategory
 * @brief Physik-Kategorien für Box2D, um Kollision (von Projektilen) zu unterscheiden.
 */
enum EntityCategory {
    ENTITY_DEFAULT =    0x0001,
    ENTITY_WEAPON =     0x0002,
};

#endif // ENTITYCATEGORY_H
