#include "stardustsystem.h"
#include <SFML/Graphics/RenderWindow.hpp>

/**
 * @brief Spalte rechts auf die linke Seite verschieben
 */
void StarDustSystem::moveColumnLeft() {
    sf::VertexArray* temp;

    for (int row = 0; row < 3; row++) {
        temp = particles[row][2];
        sf::VertexArray* test0 = particles[row][0];
        sf::VertexArray* test1 = particles[row][1];
        sf::VertexArray* test2 = particles[row][2];

        for (int col = 2; col != 0; col--) {
            particles[row][col] = particles[row][col - 1];
        }

        particles[row][0] = temp;
        assert(test0 == particles[row][1]);
        assert(test1 == particles[row][2]);
        assert(test2 == particles[row][0]);
    }

}


/**
 * @brief Spalte links auf die rechte Seite verschieben
 */
void StarDustSystem::moveColumnRight() {
    sf::VertexArray* temp;

    for (int row = 0; row < 3; row++) {
        temp = particles[row][0];
        sf::VertexArray* test0 = particles[row][0];
        sf::VertexArray* test1 = particles[row][1];
        sf::VertexArray* test2 = particles[row][2];

        for (int col = 0; col < 2; col++) {
            particles[row][col] = particles[row][col + 1];
        }

        particles[row][2] = temp;
        assert(test0 == particles[row][2]);
        assert(test1 == particles[row][0]);
        assert(test2 == particles[row][1]);
    }

}

/**
 * @brief Zeile unten auf die obere Seite verschieben
 */
void StarDustSystem::moveRowUp() {
    sf::VertexArray* temp;

    for (int col = 0; col < 3; col++) {
        temp = particles[2][col];
        sf::VertexArray* test0 = particles[0][col];
        sf::VertexArray* test1 = particles[1][col];
        sf::VertexArray* test2 = particles[2][col];
        for (int row = 2; row != 0; row--) {
            particles[row][col] = particles[row - 1][col];
        }

        particles[0][col] = temp;

        assert(test0 == particles[1][col]);
        assert(test1 == particles[2][col]);
        assert(test2 == particles[0][col]);
    }

}

/**
 * @brief Zeile oben auf die untere Seite verschieben
 */
void StarDustSystem::moveRowDown() {
    sf::VertexArray* temp;

    for (int col = 0; col < 3; col++) {
        temp = particles[0][col];
        sf::VertexArray* test0 = particles[0][col];
        sf::VertexArray* test1 = particles[1][col];
        sf::VertexArray* test2 = particles[2][col];

        for (int row = 0; row < 2; row++) {
            particles[row][col] = particles[row + 1][col];
        }

        particles[2][col] = temp;
        assert(test0 == particles[2][col]);
        assert(test1 == particles[0][col]);
        assert(test2 == particles[1][col]);
    }
}

/**
 * @brief Allen Koordinaten der Partikel eines Blocks einen Vektor addieren
 * @param row Zeile
 * @param col Spalte
 * @param offset Zu addierender Vektor
 */
void StarDustSystem::addOffset(int row, int col, sf::Vector2f offset) {
    for (int k = 0; k < particles[row][col]->getVertexCount(); k++) {
        (*particles[row][col])[k].position += offset;
    }
}

/**
 * @brief Alle Blöcke neu ausrichten
 */
void StarDustSystem::rearrangeParticles() {
    area.left = cameraView.getCenter().x - cameraView.getSize().x * 1.5f;
    area.top = cameraView.getCenter().y - cameraView.getSize().y * 1.5f;
    area.width = cameraView.getSize().x * 3;
    area.height = cameraView.getSize().y * 3;
    int offsetX = area.left;
    int offsetY = area.top;

    for (int i = 0; i < 3; i++) {
        offsetY = area.top + cameraView.getSize().y * i;
        for (int j = 0; j < 3; j++) {
            offsetX = area.left + cameraView.getSize().x * j;
            for (int k = 0; k < particles[i][j]->getVertexCount(); k++) {
                sf::Vector2f pos(rand() % ((int) cameraView.getSize().x) + offsetX,
                                 rand() % ((int) cameraView.getSize().y) + offsetY);
                (*particles[i][j])[k].position = pos;
                (*particles[i][j])[k].color = sf::Color(255, 255, 255, 255);
            }
        }
    }
}

/**
 * @brief Blöcke erstellen
 */
void StarDustSystem::createParticles() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            size_t newSize = window->getSize().x * window->getSize().y * density;
            particles[i][j]->resize(newSize);
        }
    }

    rearrangeParticles();
}

/**
 * @brief Alle Partikel zeichnen
 */
void StarDustSystem::draw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            size_t count = particles[i][j]->getVertexCount();
            sf::Vector2f test[count];
            for (int k = 0; k < count; k++) {
                test[k] = (*particles[i][j])[k].position;
            }
            window->draw(*particles[i][j]);
        }
    }
}

/**
 * @copydoc GameSystem::update
 * Positionen der Blöcke ggf. anpassen und alle Partikel zeichnen
 */
void StarDustSystem::update(float dt) {
    GameSystem::update(dt);

    sf::FloatRect viewport;
    viewport.left = cameraView.getCenter().x - cameraView.getSize().x/2.f;
    viewport.top = cameraView.getCenter().y - cameraView.getSize().y/2.f;
    viewport.width = cameraView.getSize().x;
    viewport.height = cameraView.getSize().y;

    if (viewport.left < area.left) {
        moveColumnLeft();
        sf::Vector2f offset;
        offset.x = -cameraView.getSize().x * 3;
        offset.y = 0;

        for (int row = 0; row < 3; row++) {
            addOffset(row, 0, offset);
        }
        area.left -= cameraView.getSize().x;
    } else if (viewport.left + viewport.width > area.left + area.width) {
        moveColumnRight();
        sf::Vector2f offset;
        offset.x = cameraView.getSize().x * 3;
        offset.y = 0;

        for (int row = 0; row < 3; row++) {
            addOffset(row, 2, offset);
        }
        area.left += cameraView.getSize().x;
    } else if (viewport.top < area.top) {
        moveRowUp();
        sf::Vector2f offset;
        offset.x = 0;
        offset.y = -cameraView.getSize().y * 3;

        for (int col = 0; col < 3; col++) {
            addOffset(0, col, offset);
        }
        area.top -= cameraView.getSize().y;
    } else if (viewport.top + viewport.height > area.top + area.height) {
        moveRowDown();
        sf::Vector2f offset;
        offset.x = 0;
        offset.y = cameraView.getSize().y * 3;

        for (int col = 0; col < 3; col++) {
            addOffset(2, col, offset);
        }
        area.top += cameraView.getSize().y;
    }
    draw();

}

/**
 * @copydoc GameSystem::notify
 * - ::evCameraChanged Kameraposition aktualisieren und ggf. Partikel neu ausrichten
 * - ::evWindowResized Partikel neu erstellen
 */
void StarDustSystem::notify(EventMessage* message) {
    switch (message->event) {
    case evCameraChanged: {
        EventCameraMessage* cameraMessage = (EventCameraMessage*) message;
        cameraView.setSize(cameraMessage->size.x, cameraMessage->size.y);
        cameraView.setCenter(cameraMessage->center.x, cameraMessage->center.y);

        if (scale != cameraMessage->scale || windowResized) {
            rearrangeParticles();
            scale = cameraMessage->scale;
            windowResized = false;
        }

        break;
    }

    case evWindowResized: {
        createParticles();
        windowResized = true;
        break;
    }
    }

    delete message;;
}

StarDustSystem::StarDustSystem(sf::RenderWindow* window) : window(window) {

    cameraView.setSize(1200, 800);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            particles[i][j] = new sf::VertexArray(sf::Points, density * 1200 * 800);
        }
    }

    createParticles();
}
