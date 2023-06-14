#include "modelcomponent.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_circle_shape.h"
#include "box2d/b2_edge_shape.h"
#include "box2d/b2_chain_shape.h"


/**
 * @brief Konvertiert einen Vektor zu einem Winkel
 * @param v Der Vektor
 * @return Der Winkel im Bogenmaß
 */
float ModelComponent::vecToRad(b2Vec2 v)
{
    return atan2((double) v.y, (double) v.x);
}


/**
 * @brief Konvertiert einen Box2D-Winkel in einen SFML-Winkel
 * @param rad Box2D-Winkel im Bogenmaß
 * @return SFML-Winkel im Winkelmaß
 */
float ModelComponent::b2AngleToSfAngle(float rad) {
    return (rad + M_PI)*180/M_PI;
}


/**
 * @brief Erstellt ein sf::ConvexShape aus einem b2PolygonShape
 * @param shape Das b2PolygonShape
 */
void ModelComponent::addShape(b2PolygonShape *shape) {
    sf::ConvexShape polygon;
    polygon.setFillColor(fillColor);
    int count = shape->m_count;
    polygon.setPointCount(count);
    for (int i = 0; i < count; i++) {
        b2Vec2 vertex = shape->m_vertices[i];
        polygon.setPoint(i, sf::Vector2f(vertex.x*30*(-1), vertex.y*30 * (-1)));
    }
    polygons.push_back(polygon);
    sf::Vector2f offset(shape->m_centroid.x * 30, shape->m_centroid.y * 30);
    polygonOffsets.push_back(offset);
}


/**
 * @brief Erstellt ein sf::CircleShape aus einem b2CircleShape
 * @param shape Das b2CircleShape
 */
void ModelComponent::addShape(b2CircleShape *shape) {
    sf::CircleShape circle(shape->m_radius*30);
    circle.setFillColor(fillColor);
    circles.push_back(circle);
    sf::Vector2f offset(shape->m_p.x * 30 * (-1), shape->m_p.y * 30 * (-1));
    offset -= sf::Vector2f(shape->m_radius * 30, shape->m_radius * 30);
    circleOffsets.push_back(offset);
}


/**
 * @brief Erstellt ein sf::RectangleShape aus einem b2EdgeShape
 * @param shape Das b2EdgeShape
 */
void ModelComponent::addShape(b2EdgeShape *shape) {
    sf::Vector2f offset(shape->m_vertex1.x * 30*(-1), shape->m_vertex1.y * 30 *(-1));
    b2Vec2 delta = shape->m_vertex2 - shape->m_vertex1;
    float length = delta.Length() * 30;
    float b2Angle = vecToRad(delta);
    float rotationOffset = b2AngleToSfAngle(b2Angle);
    sf::RectangleShape rect(sf::Vector2f(length, 2));
    rect.setFillColor(fillColor);
    lines.push_back(rect);
    lineOffsets.push_back(offset);
    lineRotationOffsets.push_back(rotationOffset);
}


/**
 * @brief Erstellt mehrere sf::RectangleShapes aus einem b2ChainShape
 * @param shape Das b2PolygonShape
 */
void ModelComponent::addShape(b2ChainShape *shape) {
    int count = shape->GetChildCount();
    for (int i = 0; i < count; i++) {
        b2EdgeShape * edge = new b2EdgeShape;
        shape->GetChildEdge(edge, i);
        addShape(edge);
    }
}


/**
 * @copydoc Component::notify
 * - ::evMove Aktualisiert die Position
 * - ::cmActivate Macht die Shapes sichtbar
 * - ::cmDeactivate Macht die Shapes unsichtbar
 */
void ModelComponent::notify(EventMessage* message) {
    if (message->event == evMove) {
        EventPosMessage* posMessage = (EventPosMessage*) message;
        //sf::Vector2f newPos(posMessage->x * 30,
        //                    posMessage->y * 30);
        sf::Vector2f newPos(posMessage->pos.x * 30,
                            posMessage->pos.y * 30);
        float r = b2AngleToSfAngle(posMessage->rotation);
        sf::Transform t;
        t.rotate(r);

        for (unsigned int i = 0; i < circles.size(); i++) {
            circles[i].setPosition(newPos + t.transformPoint(circleOffsets[i]));
            circles[i].setRotation(r);
        }

        for (unsigned int i = 0; i < polygons.size(); i++) {
            polygons[i].setPosition(newPos + t.transformPoint(polygonOffsets[i]));
            polygons[i].setRotation(r);
        }

        for (unsigned int i = 0; i < lines.size(); i++) {
            lines[i].setPosition(newPos + t.transformPoint(lineOffsets[i]));
            lines[i].setRotation(r + lineRotationOffsets[i]);
        }
    } else if (message->event == cmActivate) {
        visible = true;
    } else if (message->event == cmDeactivate) {
        visible = false;
    }
    delete(message);
}


/**
 * @copydoc Component::Component
 *
 * Erstellt die Shapes
 */
ModelComponent::ModelComponent(ModelSettings settings, Handle* handle)
    : Component(settings, handle) {

    typename std::vector<b2Shape*>::iterator it = settings.shapes.begin();
    for (it; it != settings.shapes.end(); it++) {
        switch ((*it)->GetType()) {
        case b2Shape::e_circle : {
            b2CircleShape* shape = (b2CircleShape*) (*it);
            addShape(shape);
            break;
        } case b2Shape::e_polygon : {
            b2PolygonShape* shape = (b2PolygonShape*) (*it);
            addShape(shape);
            break;
        } case b2Shape::e_edge : {
            b2EdgeShape* shape = (b2EdgeShape*) (*it);
            addShape(shape);
            break;
        } case b2Shape::e_chain : {
            b2ChainShape* shape = (b2ChainShape*) (*it);
            addShape(shape);
            break;
        }
        }
    }

    Event events[1] = {evMove};
    initializeEvents(events, 1);
}
