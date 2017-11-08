#include "backgroundsystem.h"
#include <SFML/Graphics.hpp>
#include "graphics/textures.h"


/**
 * @brief Setzt den Hintergrund und die passende Lichtintensität
 */
void BackgroundSystem::setBackground() {
    switch(area) {
    case Area::StartArea:
        background = startBackground;
        lightShader.setParameter("intensity", 80.f);
        break;
    case Area::ShopArea:
        background = shopBackground;
        lightShader.setParameter("intensity", 20.f);
        break;
    case Area::BretoniaArea:
        background = bretoniaBackground;
        lightShader.setParameter("intensity", 50.f);
        break;
    case Area::BanditArea:
        background = banditBackground;
        lightShader.setParameter("intensity", 80.f);
        break;
    case Area::TaulanArea:
        background = taulanBackground;
        lightShader.setParameter("intensity", 20.f);
        break;
    case Area::AlienArea:
        background = alienBackground;
        lightShader.setParameter("intensity", 80.f);
        break;
    case Area::XuruArea:
        background = xuruBackground;
        lightShader.setParameter("intensity", 40.f);
        break;
    }
}

/**
 * @brief Passt Hintergrund der Kamera an
 */
void BackgroundSystem::resize() {
    sf::Vector2u initSize = background.getTexture()->getSize();
    float scale = std::max(cameraView.getSize().x / initSize.x,
                           cameraView.getSize().y / initSize.y);
    background.setScale(scale, scale);
    //background.setOrigin(background.getGlobalBounds().width * 0.5f,
    //                     background.getGlobalBounds().height * 0.5f);
}

/**
 * @brief Zoomt heran/heraus
 * @param scroll Zoom-Faktor. Relativ zum derzeitigen Zoom-Faktor.
 */
void BackgroundSystem::zoom(float scroll) {
    if (scroll < 0) {
        background.scale(1.05f, 1.05f);
    } else {
        background.scale(0.95f, 0.95f);
    }
}

/**
 * @copydoc GameSystem::update
 *
 * Zeichnet Hintergrund mit Shader
 */
void BackgroundSystem::update(float dt) {
    GameSystem::update(dt);

    lightShader.setParameter("u_texture", sf::Shader::CurrentTexture);
    lightShader.setParameter("u_lightmap", lightMap.getTexture());
    lightShader.setParameter("resolution", sf::Vector2f(window->getSize().x,
                             window->getSize().y));
    //lightShader.setParameter("intensity", 80.f);
    sf::Vector2f uShift(1.f / window->getSize().x, 1.f / window->getSize().y);
    uShift *= blurFactor / scrollFactor;
    lightShader.setParameter("uShift", uShift);
    window->draw(background, &lightShader);
}


/**
 * @copydoc GameSystem::notify
 * - ::evCameraChanged Hintergrund der Kamera anpassen
 * - ::evWindowResized Nötig für Anpassung
 * - ::evAreaChanged Wechselt hintergrund
 */
void BackgroundSystem::notify(EventMessage * message) {
    switch(message->event) {
    case evCameraChanged: {
        EventCameraMessage* cameraMessage = (EventCameraMessage*) message;
        cameraView.setSize(cameraMessage->size.x, cameraMessage->size.y);
        cameraView.setCenter(cameraMessage->center.x, cameraMessage->center.y);

        if (needsResize || scrollFactor != cameraMessage->scale) {
            scrollFactor = cameraMessage->scale;
            resize();;
        }

        sf::Vector2f cameraPos(cameraMessage->center.x, cameraMessage->center.y);
        background.setPosition(cameraPos);
        break;
    }

    case evWindowResized: {
        needsResize = true;
        break;
    }

    case evAreaChanged: {
        EventAreaMessage* areaMessage = (EventAreaMessage*) message;
        area = areaMessage->area;
        setBackground();
        break;
    }
    }

    delete message;;
}


BackgroundSystem::BackgroundSystem(sf::RenderWindow * window, sf::RenderTexture& lightMap)
    : lightMap(lightMap) {

    this->window = window;
    window->setVerticalSyncEnabled(false);
    //background.setTexture(Textures::get("Backgrounds/taulan.jpg"));
    //background.setColor(sf::Color(50, 30, 20, 255));

    startBackground.setTexture(Textures::get("Backgrounds/startarea.jpg"));
    startBackground.setColor(sf::Color(50, 50, 50, 255));
    shopBackground.setTexture(Textures::get("Backgrounds/shop.jpg"));
    shopBackground.setColor(sf::Color(150, 150, 150, 255));
    alienBackground.setTexture(Textures::get("Backgrounds/alien.jpg"));
    alienBackground.setColor(sf::Color(50, 50, 50, 255));
    banditBackground.setTexture(Textures::get("Backgrounds/bandits.jpg"));
    banditBackground.setColor(sf::Color(50, 30, 30, 255));
    bretoniaBackground.setTexture(Textures::get("Backgrounds/bretonia.jpg"));
    bretoniaBackground.setColor(sf::Color(70, 70, 70, 255));
    taulanBackground.setTexture(Textures::get("Backgrounds/taulan.jpg"));
    taulanBackground.setColor(sf::Color(100, 80, 80, 255));
    xuruBackground.setTexture(Textures::get("Backgrounds/xuru.jpg"));
    xuruBackground.setColor(sf::Color(100, 100, 100, 255));


    //background.setOrigin(background.getTexture()->getSize().x * 0.5f,
    //                     background.getTexture()->getSize().y * 0.5f);
    startBackground.setOrigin(startBackground.getTexture()->getSize().x * 0.5f,
                              startBackground.getTexture()->getSize().y * 0.5f);
    shopBackground.setOrigin(shopBackground.getTexture()->getSize().x * 0.5f,
                              shopBackground.getTexture()->getSize().y * 0.5f);
    alienBackground.setOrigin(alienBackground.getTexture()->getSize().x * 0.5f,
                              alienBackground.getTexture()->getSize().y * 0.5f);
    banditBackground.setOrigin(banditBackground.getTexture()->getSize().x * 0.5f,
                               banditBackground.getTexture()->getSize().y * 0.5f);
    bretoniaBackground.setOrigin(bretoniaBackground.getTexture()->getSize().x * 0.5f,
                                 bretoniaBackground.getTexture()->getSize().y * 0.5f);
    taulanBackground.setOrigin(taulanBackground.getTexture()->getSize().x * 0.5f,
                               taulanBackground.getTexture()->getSize().y * 0.5f);
    xuruBackground.setOrigin(xuruBackground.getTexture()->getSize().x * 0.5f,
                             xuruBackground.getTexture()->getSize().y * 0.5f);

    lightShader.loadFromFile("../resources/light_low_res.frag", sf::Shader::Fragment);
    setBackground();

}
