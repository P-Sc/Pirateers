/**
 *@file shipparser.h
 */

#ifndef SHIPPARSER_H
#define SHIPPARSER_H

#include <string>
#include <map>
#include "physics/physicssettings.h"
#include "graphics/graphicssettings.h"
#include "ship/shipsettings.h"
#include "rapidxml/rapidxml.hpp"

class b2Shape;
class b2PolygonShape;
class b2CircleShape;
class b2EdgeShape;
class b2ChainShape;


/**
 * @class ShipParser
 * @brief Liest Schiffe ein.
 *
 * Liest .xml-Dateien aus dem "resources/Ships/"-Ordner ein. Nimmt relative Bildpfade.
 */
class ShipParser {
private:
    bool validatePolygonShapes;
    float scale = 1.f;
    void convertShapeCoordinates(PhysicsSettings &physicsSettings,
                                 GraphicsSettings &graphicsSettings);
    void convertShape(GraphicsSettings & graphicsSettings, b2PolygonShape* shape);
    void convertShape(GraphicsSettings & graphicsSettings, b2CircleShape* shape);
    void convertShape(GraphicsSettings & graphicsSettings, b2EdgeShape* shape);
    void convertShape(GraphicsSettings & graphicsSettings, b2ChainShape* shape);

    b2Shape* parseShape(rapidxml::xml_node<> * shapeNode);
    b2PolygonShape* parsePolygonShape(rapidxml::xml_node<> * shapeNode, bool validate);
    b2CircleShape* parseCircleShape(rapidxml::xml_node<> * shapeNode);
    b2EdgeShape* parseEdgeShape(rapidxml::xml_node<> * shapeNode);
    b2ChainShape* parseChainShape(rapidxml::xml_node<> * shapeNode);

    std::string openFile(std::string filename);
    bool parseText(std::string text);
public:
    std::map<std::string, ShipSettings> ships;
    std::map<std::string, PhysicsSettings> shipPhysics;
    std::map<std::string, GraphicsSettings> shipGraphics;
    void parseDirectory(std::string path);
    bool isShipStored(std::string shipName);
    ShipParser(bool validatePolygonShapes);
};

#endif // SHIPPARSER_H
