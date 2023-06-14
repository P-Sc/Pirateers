#include "shipparser.h"
#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>
//#include <string>

#include <box2d/b2_shape.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_edge_shape.h>
#include <box2d/b2_chain_shape.h>



using namespace rapidxml;
using namespace boost::filesystem;


/**
 * @brief Konvertiert alle Shape-Koordinaten aus physicsSettings in Box2D-Koordinaten
 * @param physicsSettings Die PhysicsSettings mit den unkonvertierten b2Shapes
 * @param graphicsSettings Die GraphicsSettings mit der nötigen Texturbreite/ -höhe
 *                         und der Skalierung
 *
 */
void ShipParser::convertShapeCoordinates(PhysicsSettings &physicsSettings,
                                         GraphicsSettings &graphicsSettings) {

    std::vector<b2Shape*>::iterator it = physicsSettings.shapes.begin();
    for (it; it != physicsSettings.shapes.end(); it++) {
        switch ((*it)->GetType()) {

        case b2Shape::e_polygon: {
            b2PolygonShape* shape = (b2PolygonShape*) (*it);
            convertShape(graphicsSettings, shape);
            break;
        }
        case b2Shape::e_circle: {
            b2CircleShape* shape = (b2CircleShape*) (*it);
            convertShape(graphicsSettings, shape);
            break;
        }
        case b2Shape::e_edge: {
            b2EdgeShape* shape = (b2EdgeShape*) (*it);
            convertShape(graphicsSettings, shape);
            break;
        }
        case b2Shape::e_chain: {
            b2ChainShape* shape = (b2ChainShape*) (*it);
            convertShape(graphicsSettings, shape);
            break;
        }

        }
    }
}


/**
 * @brief Konvertiert die Koordinaten eines PolygonShape in Box2D-Koordinaten um
 * @param graphicsSettings Entsprechende GraphicsSettings
 * @param shape Das anzupasende Shape
 *
 * Die GraphicsSettings sind für Die zentrierung und die Skalierung wichtig.
 * Das Shape wird direkt verändert und nicht kopiert.
 */
void ShipParser::convertShape(GraphicsSettings & graphicsSettings, b2PolygonShape* shape) {
    // Mitte auf Ursprung setzen
    shape->m_centroid = b2Vec2(0,0);

    //b2Vec2* vertices = shape->m_vertices;
    b2Vec2 *vertices;
    vertices = shape->m_vertices;
    for (int i = 0; i < shape->m_count; i++) {

        // An X-Achse spiegeln
        vertices[i].y = graphicsSettings.rectHeight - vertices[i].y;

        // An Y-Achse spiegeln
        vertices[i].x = graphicsSettings.rectWidth - vertices[i].x;

        // Zentrieren
        vertices[i] -= b2Vec2(graphicsSettings.rectWidth/2.f, graphicsSettings.rectHeight/2.f);

        // Auf Box2D-Maßstab anpassen und (falls nötig) skalieren
        vertices[i] *= 1/30.f * graphicsSettings.scale;
        //test[i] = vertices[i];
    }
    shape->Set(vertices, shape->m_count);
    shape->m_centroid = b2Vec2(0,0);


    if (validatePolygonShapes && !shape->Validate()) {
        int j = shape->m_count - 1;
        for (int i = 0; i < shape->m_count/2; i++) {
            std::swap(vertices[i], vertices[j]);
            j--;
        }
    }
}


/**
 * @brief Konvertiert die Koordinaten eines CircleShape in Box2D-Koordinaten um
 * @param graphicsSettings Entsprechende GraphicsSettings
 * @param shape Das anzupasende Shape
 *
 * Die GraphicsSettings sind für Die zentrierung und die Skalierung wichtig.
 * Das Shape wird direkt verändert und nicht kopiert.
 */
void ShipParser::convertShape(GraphicsSettings & graphicsSettings, b2CircleShape* shape) {

    // An X-Achse spiegeln
    //shape->m_p.y = graphicsSettings.rectHeight - shape->m_p.y;

    // An Y-Achse spiegeln
    //shape->m_p.x = graphicsSettings.rectWidth - shape->m_p.x;

    // Zentrieren
    shape->m_p -= b2Vec2(graphicsSettings.rectWidth/2.f, graphicsSettings.rectHeight/2.f);
    shape->m_p *= -1;

    // Auf Box2D-Maßstab anpassen und (falls nötig) skalieren
    shape->m_p *= 1/30.f * graphicsSettings.scale;
    shape->m_radius *= 1/30.f * graphicsSettings.scale;
}


/**
 * @brief Konvertiert die Koordinaten eines EdgeShape in Box2D-Koordinaten um
 * @param graphicsSettings Entsprechende GraphicsSettings
 * @param shape Das anzupasende Shape
 *
 * Die GraphicsSettings sind für Die zentrierung und die Skalierung wichtig.
 * Das Shape wird direkt verändert und nicht kopiert.
 */
void ShipParser::convertShape(GraphicsSettings & graphicsSettings, b2EdgeShape* shape) {

    // An X-Achse spiegeln
    shape->m_vertex1.y = graphicsSettings.rectHeight - shape->m_vertex1.y;
    shape->m_vertex2.y = graphicsSettings.rectHeight - shape->m_vertex2.y;

    // An Y-Achse spiegeln
    shape->m_vertex1.x = graphicsSettings.rectWidth - shape->m_vertex1.x;
    shape->m_vertex2.x = graphicsSettings.rectWidth - shape->m_vertex2.x;

    // Zentrieren
    shape->m_vertex1 -= b2Vec2(graphicsSettings.rectWidth/2.f, graphicsSettings.rectHeight/2.f);
    shape->m_vertex2 -= b2Vec2(graphicsSettings.rectWidth/2.f, graphicsSettings.rectHeight/2.f);

    // Auf Box2D-Maßstab anpassen und (falls nötig) skalieren
    shape->m_vertex1 *= 1/30.f * graphicsSettings.scale;
    shape->m_vertex2 *= 1/30.f * graphicsSettings.scale;
}


/**
 * @brief Konvertiert die Koordinaten eines ChainShape in Box2D-Koordinaten um
 * @param graphicsSettings Entsprechende GraphicsSettings
 * @param shape Das anzupasende Shape
 *
 * Die GraphicsSettings sind für Die zentrierung und die Skalierung wichtig.
 * Das Shape wird direkt verändert und nicht kopiert.
 */
void ShipParser::convertShape(GraphicsSettings & graphicsSettings, b2ChainShape* shape) {
    int32 count = shape->m_count;
    b2Vec2 vertices[8];
    for (int i = 0; i < count; i++) {
        vertices[i] = shape->m_vertices[i];

        // An X-Achse spiegeln
        vertices[i].y = graphicsSettings.rectHeight - vertices[i].y;

        // An Y-Achse spiegeln
        vertices[i].x = graphicsSettings.rectWidth - vertices[i].x;

        // Zentrieren
        vertices[i] -= b2Vec2(graphicsSettings.rectWidth/2.f, graphicsSettings.rectHeight/2.f);

        // Auf Box2D-Maßstab anpassen und (falls nötig) skalieren
        vertices[i] *= 1/30.f * graphicsSettings.scale;
    }
    if (vertices[0] == vertices[count-1]) {
        b2Vec2 tmp[count-1];
        for (int i = 0; i < count - 1; i++)
            tmp[i] = vertices[i];
        shape->Clear();
        shape->CreateLoop(tmp, count-1);
    } else {
        shape->Clear();
        shape->CreateLoop(vertices, count);
    }
}



/**
 * @brief Erstellt das passende Shape aus einem XML-Knoten
 * @param shapeNode Der spezifische Shape-Knoten
 * @return Bei Erfolg das erstellte, spezifische Shape. Bei Fehlern wird nullptr zurückgegeben.
 *
 * Der XML-Knoten muss entweder vom Typ Polygon, Circle, Edge oder Chain sein.
 * Es wird automatisch ermittelt, um welchen Typ es sich handelt.
 */
b2Shape* ShipParser::parseShape(xml_node<> * shapeNode) {
    if (!std::strcmp(shapeNode->name(), "Polygon")) {
        return parsePolygonShape(shapeNode, validatePolygonShapes);

    } else if (!std::strcmp(shapeNode->name(), "Circle")) {
        return parseCircleShape(shapeNode);

    } else if (!std::strcmp(shapeNode->name(), "Edge")) {
        return parseEdgeShape(shapeNode);

    } else if (!std::strcmp(shapeNode->name(), "Chain")) {
        return parseChainShape(shapeNode);
    } else {
        std::cout << "Error: Unknown shape name: " << shapeNode->name() << std::endl;
        return nullptr;
    }
}


/**
 * @brief Erstellt ein PolygonShape aus einem XML-Knoten
 * @param shapeNode Der Polygon-Knoten
 * @param validate Gibt an, ob das Polygon überprüft werden soll. Sehr zeitaufwendig.
 * @return Bei Erfolg das erstellte PolygonShape. Bei Fehlern wird nullptr zurückgegeben.
 *
 * @warning Polygone mit mehr als 8 Ecken werden "abgeschnitten".
 *          D.h. restliche Knoten werden ignoriert.
 */
b2PolygonShape* ShipParser::parsePolygonShape(xml_node<> * shapeNode, bool validate) {
    int i = 0;
    b2Vec2 vertices[8];

    xml_node<> * vertexNode = shapeNode->first_node("Vertex", 0, false);
    std::cout << "Polygon shape:" << std::endl;

    /*
     * Durch alle Vertex-Knoten iterieren
     */
    while (true) {

        // Zu viele Knoten
        if (vertexNode != 0 && i == 8) {
            std::cout << "Warning: Too many vertices (>8). Ignoring remaining vertices."
                      << std::endl;
            break;

        // Noch nicht zu viele Knoten
        } else if (vertexNode != 0) {
            xml_attribute<> * xAttribute = vertexNode->first_attribute("x", 0, false);
            xml_attribute<> * yAttribute = vertexNode->first_attribute("y", 0, false);

            if (xAttribute != 0 && yAttribute != 0) {
                vertices[i].Set(atof(xAttribute->value()), atof(yAttribute->value()));
                std::cout << "  Vertex " << i << " - x: " << vertices[i].x
                          << "  y: " << vertices[i].y << std::endl;
                i++;
            } else {
                std::cout << "Error: Corrupt vertex. Skipping to next vertex." << std::endl;
            }

            vertexNode = vertexNode->next_sibling("Vertex", 0, false);

        // Kein Knoten mehr über
        } else
            break;
    }

    /*
     * Überprüfen und Rückgabe
     */
    if (i < 3) {
        std::cout << "Error: Not enough vertices" << std::endl;
        return nullptr;
    } else {
        b2PolygonShape* shape = new b2PolygonShape();

        // Vertices in passendes Array kopieren
        b2Vec2 tmp_vertices[i];
        for (int j = 0; j < i; j++)
            tmp_vertices[j] = vertices[j];

        shape->Set(tmp_vertices, i);
        if (validate && !shape->Validate()) {
            std::cout << "Error: PolygonShape not convex." << std::endl;
            delete shape;
            return nullptr;
        } else
            return shape;
    }
}


/**
 * @brief Erstellt ein CircleShape aus einem XML-Knoten
 * @param shapeNode Der Circle-Knoten
 * @return Bei Erfolg das erstellte CircleShape. Bei Fehlern wird nullptr zurückgegeben.
 */
b2CircleShape* ShipParser::parseCircleShape(xml_node<> * shapeNode) {
    std::cout << "Circle shape:" << std::endl;
    xml_attribute<> * xAttribute = shapeNode->first_attribute("x", 0, false);
    xml_attribute<> * yAttribute = shapeNode->first_attribute("y", 0, false);
    xml_attribute<> * radiusAttribute = shapeNode->first_attribute("radius", 0, false);

    if (xAttribute != 0 && yAttribute != 0 && radiusAttribute != 0) {
        b2CircleShape* shape = new b2CircleShape;
        shape->m_p.Set(atof(xAttribute->value()), atof(yAttribute->value()));
        shape->m_radius = atof(radiusAttribute->value());
        std::cout << "  Position - x: " << atof(xAttribute->value())
                  << "  y: " << atof(yAttribute->value()) << std::endl;
        std::cout << "  Radius: " << atof(radiusAttribute->value()) << std::endl;
        return shape;
    } else {
        std::cout << "Error: Corrupt circle shape." << std::endl;
        return nullptr;
    }
}


/**
 * @brief Erstellt ein EdgeShape (Kante) aus einem XML-Knoten
 * @param shapeNode Der Edge-Knoten
 * @return Bei Erfolg das erstellte EdgeShape. Bei Fehlern wird nullptr zurückgegeben.
 *
 * @warning Mindestlänge von 5mm, also 0,15 Pixeln
 */
b2EdgeShape* ShipParser::parseEdgeShape(xml_node<> * shapeNode) {
    std::cout << "Edge shape:" << std::endl;
    xml_attribute<> * vxAttribute = shapeNode->first_attribute("v_x", 0, false);
    xml_attribute<> * vyAttribute = shapeNode->first_attribute("v_y", 0, false);
    xml_attribute<> * wxAttribute = shapeNode->first_attribute("w_x", 0, false);
    xml_attribute<> * wyAttribute = shapeNode->first_attribute("w_y", 0, false);

    if (vxAttribute != 0 && vyAttribute != 0 && wxAttribute != 0 && wyAttribute != 0) {
        b2EdgeShape* shape = new b2EdgeShape;
        b2Vec2 v;
        b2Vec2 w;
        v.Set(atof(vxAttribute->value()), atof(vyAttribute->value()));
        w.Set(atof(wxAttribute->value()), atof(wyAttribute->value()));

        shape->SetTwoSided(v, w);
        std::cout << "  Point 1 - x: " << v.x << "  y: " << v.y << std::endl;
        std::cout << "  Point 2 - x: " << w.x << "  y: " << w.y << std::endl;
        return shape;
    } else {
        std::cout << "Error: Corrupt circle shape." << std::endl;
        return nullptr;
    }
}


/**
 * @brief Erstellt ein ChainShape (Kette von Kanten) aus einem XML-Knoten
 * @param shapeNode Der Chain-Knoten
 * @return Bei Erfolg das erstellte ChainShape. Bei Fehlern wird nullptr zurückgegeben.
 *
 * @warning Mindestlänge von 5mm (pro Kante), also 0,15 Pixeln
 */
b2ChainShape* ShipParser::parseChainShape(xml_node<> * shapeNode) {
    std::cout << "Chain shape:" << std::endl;

    /*
     * Überprüfen, ob ein Kreis gebildet werden soll
     */
    xml_attribute<> * loopAttribute = shapeNode->first_attribute("loop", 0, false);
    bool loop = false;
    if (loopAttribute != 0 && std::strcmp(loopAttribute->value(), "true") == 0)
        loop = true;

    std::vector<b2Vec2> points;
    xml_node<> * pointNode = shapeNode->first_node("Point", 0, false);

    /*
     * Durch alle Point-Knoten iterieren
     */
    int i = 0;
    while (true) {
        if (pointNode != 0) {
            xml_attribute<> * xAttribute = pointNode->first_attribute("x", 0, false);
            xml_attribute<> * yAttribute = pointNode->first_attribute("y", 0, false);

            if (xAttribute != 0 && yAttribute != 0) {
                b2Vec2 point;
                point.Set(atof(xAttribute->value()), atof(yAttribute->value()));
                points.push_back(point);
                std::cout << "  Point " << i << " - x: " << point.x
                          << "  y: " << point.y << std::endl;
                i++;
            } else {
                std::cout << "Error: Corrupt point. Skipping to next point." << std::endl;
            }

            pointNode = pointNode->next_sibling("Point", 0, false);

        // Kein Knoten mehr über
        } else
            break;
    }

    /*
     * Überprüfen und Rückgabe
     */
    if (i < 2) {
        std::cout << "Error: Not enough points" << std::endl;
        return nullptr;
    } else {
        b2ChainShape* shape = new b2ChainShape();

        // Punkte in passendes Array kopieren
        b2Vec2* tmp_points = points.data();
        //for (int j = 0; j <= i; j++)
        //    tmp_vertices[j] = vertices[j];

        if (loop)
            shape->CreateLoop(tmp_points, points.size());
        else
            shape->CreateLoop(tmp_points, points.size());

        return shape;
    }
}


/**
 * \cond HIDDEN_SYMBOLS
 * @class recursive_directory_range
 * @brief Wird für das parsen von Dateien benutzt
 *
 */
// Credit: https://stackoverflow.com/questions/67273
struct recursive_directory_range
{
    typedef recursive_directory_iterator dirIterator;
    recursive_directory_range(path p) : p_(p) {}

    dirIterator begin() { return recursive_directory_iterator(p_); }
    dirIterator end() { return recursive_directory_iterator(); }

    path p_;
};

/**
 * \endcond
 */

/**
 * @brief Öffnet eine Datei
 * @param filename Der Dateiname inkl. Pfad
 * @return Ein String mit dem gesamten Inhalt der Datei
 */
std::string ShipParser::openFile(std::string filename) {
    std::fstream ifs(filename);
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                          (std::istreambuf_iterator<char>()) );
    return content;
}


/**
 * @brief Verarbeitet einen XML-Text für Schiffe und speichert die entsprechenden Settings
 * @param text Der komplette Inhalt der XML-Datei
 * @return False, falls Fehler aufgetreten sind, sonst True.
 */
bool ShipParser::parseText(std::string text) {
    /*
     * Text parsen mit RapidXML
     */
    xml_document<> doc;
    char buffer[text.size()];
    text.copy(buffer, sizeof buffer);
    buffer[sizeof buffer - 1] = '\0';
    doc.parse<0>(buffer);

    xml_node<> *node = doc.first_node("Ship", 0, false);
    while (true) {
        if (node != 0) {

            std::cout << "Parsing ship..." << std::endl;

            PhysicsSettings physicsSettings;
            ShipSettings shipSettings;
            GraphicsSettings graphicsSettings;
            xml_attribute<> * nameAttribute;
            xml_attribute<> * densityAttribute;
            xml_attribute<> * frictionAttribute;
            xml_attribute<> * propulsionAttribute;
            xml_attribute<> * maxTorqueAttribute;
            xml_attribute<> * scaleAttribute;
            xml_attribute<> * fileAttribute;
            xml_attribute<> * widthAttribute;
            xml_attribute<> * heightAttribute;

            /*
             * Direkte Attribute auslesen
             */
            nameAttribute = node->first_attribute("name", 0, false);
            densityAttribute = node->first_attribute("density", 0, false);
            frictionAttribute = node->first_attribute("friction", 0, false);
            propulsionAttribute = node->first_attribute("propulsion", 0, false);
            maxTorqueAttribute = node->first_attribute("maxTorque", 0, false);
            scaleAttribute = node->first_attribute("scale", 0, false);


            /*
             * Shape-Daten auslesen
             */
            xml_node<> *shapeNode = node->first_node("Shape", 0, false);
            if (shapeNode != 0) {
                shapeNode =  shapeNode->first_node();
                while (true) {
                    if (shapeNode != 0) {
                        b2Shape * parsedShape = parseShape(shapeNode);
                        if (parsedShape != nullptr)
                            physicsSettings.shapes.push_back(parsedShape);
                        shapeNode = shapeNode->next_sibling();
                    } else {
                        break;
                    }
                }
            } else {
                std::cout << "Error: No shapes found!";
                return false;
            }

            /*
             * Textur-Daten auslesen
             */
            xml_node<> *textureNode = node->first_node("Texture", 0, false);
            if (textureNode != 0) {
                fileAttribute = textureNode->first_attribute("file", 0, false);
                widthAttribute = textureNode->first_attribute("width", 0, false);
                heightAttribute = textureNode->first_attribute("height", 0, false);
            } else {
                std::cout << "Error: No texture node found!";
                return false;
            }

            /*
             * Auf Vollständigkeit prüfen
             */
            if (nameAttribute == 0 || densityAttribute == 0 || propulsionAttribute == 0
                    || maxTorqueAttribute == 0 || fileAttribute == 0 || widthAttribute == 0
                    || heightAttribute == 0 ) {
                std::cout << "Error: Not enough or corrupt attributes" << std::endl;
                return false;
            }

            /*
             * Ausgabe
             */
            std::cout << "Shipname: " << nameAttribute->value() << std::endl;
            std::cout << "Density: " << densityAttribute->value() << std::endl;
            std::cout << "Propulsion: " << propulsionAttribute->value() << std::endl;
            std::cout << "Maximum torque: " << maxTorqueAttribute->value() << std::endl;
            // (optionale Parameter)
            if (frictionAttribute != 0)
                std::cout << "Friction: " << frictionAttribute->value() << std::endl;
            if (scaleAttribute != 0)
                std::cout << "Scale: " << scaleAttribute->value() << std::endl;
            std::cout << "Texture: " << fileAttribute->value() << std::endl;
            std::cout << "Texture width: " << widthAttribute->value() << std::endl;
            std::cout << "Texture height: " << heightAttribute->value() << std::endl;


            /*
             * Zuweisen
             */
            if (frictionAttribute != 0)
                physicsSettings.friction = atof(frictionAttribute->value());
            physicsSettings.density = atof(densityAttribute->value());
            shipSettings.propulsion = atof(propulsionAttribute->value());
            shipSettings.maxTorque = atof(maxTorqueAttribute->value());
            graphicsSettings.texture = fileAttribute->value();
            graphicsSettings.rectWidth = atof(widthAttribute->value());
            graphicsSettings.rectHeight = atof(heightAttribute->value());
            if (scaleAttribute != 0)
                graphicsSettings.scale = atof(scaleAttribute->value());


            /*
             * Einfügen
             */
            std::string shipName = nameAttribute->value();
            if (!isShipStored(shipName)) {
                convertShapeCoordinates(physicsSettings, graphicsSettings);
                ships.insert(std::make_pair(shipName, shipSettings));
                shipGraphics.insert(std::make_pair(shipName, graphicsSettings));
                shipPhysics.insert(std::make_pair(shipName, physicsSettings));
            }

            node = node->next_sibling();
            std::cout << std::endl;
        } else
            break;
    }
    return true;
}


/**
 * @brief Verarbeitet alle Dateien in einem Ordner (rekursiv)
 * @param path Der Pfad des Ordners
 */
void ShipParser::parseDirectory(std::string path) {
    std::cout << std::endl;
    for (directory_entry it : recursive_directory_range(path))
    {
        std::string relativePath = it.path().string();

        if(it.status().type() == directory_file
                || !parseText(openFile(relativePath))) {
            continue;
        }

        relativePath.erase(0, path.size());
        std::cout << "Shipfile added: " << relativePath << std::endl;
    }
}


/**
 * @brief Überprüft, ob die nötigen Settings für ein Schiff gespeichert sind
 * @param shipName Der Name des Schiffes
 * @return True, falls Schiff vorhanden ist, False sonst.
 *
 * Überprüft werden ships (für ShipSettings), shipGraphics (für GraphicsSettings)
 * und shipPhysics(für PhysicsSettings)
 */
bool ShipParser::isShipStored(std::string shipName) {
    return (ships.find(shipName) != ships.end()
            && shipGraphics.find(shipName) != shipGraphics.end()
            && shipPhysics.find(shipName) != shipPhysics.end());
}


ShipParser::ShipParser(bool validatePolygonShapes) {
    this->validatePolygonShapes = validatePolygonShapes;
}
