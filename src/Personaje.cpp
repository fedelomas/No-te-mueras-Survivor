#include "Personaje.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

Personaje::Personaje(sf::Texture& playerTexture, sf::Texture& deathTexture)
    : Entity(playerTexture), deathTexture(&deathTexture)
{
    totalFrames = 4;
    totalFramesMuerte = 4;

    frameWidth = texture.getSize().x / totalFrames;
    frameHeight = texture.getSize().y;

    frameInicioMuerte = 0;
    sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
    sprite.setOrigin(frameWidth / 2.f, frameHeight * 0.7f);
    sprite.setScale(1.5f, 1.5f);
    sprite.setPosition(0.f, 0.f);
}

void Personaje::update(float deltaTime, sf::View& view) {

    if (estaRecibiendoDanio && flashClock.getElapsedTime().asMilliseconds() > 150) {
    sprite.setColor(sf::Color::White);
    estaRecibiendoDanio = false;
}
    if (muerto) {
        reproducirAnimacionMuerte(deltaTime);
        return;
    }

    mover(deltaTime, view);
    actualizarAnimacion();
}

void Personaje::mover(float deltaTime, sf::View& view) {
    sf::Vector2f direction(0.f, 0.f);
    sf::Vector2f pos = sprite.getPosition();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        direction.y = -speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        direction.y = speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        direction.x = speed;
        sprite.setScale(1.5f, 1.5f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        direction.x = -speed;
        sprite.setScale(-1.5f, 1.5f);
    }

    if (direction != sf::Vector2f(0.f, 0.f)) {
        sprite.move(direction * deltaTime * 60.f);
        view.move(direction * deltaTime * 60.f);
        estaMoviendo = true;
    } else {
        estaMoviendo = false;
    }
}

void Personaje::actualizarAnimacion() {
    if (estaMoviendo && clock.getElapsedTime() >= frameTime) {
        currentFrame = (currentFrame + 1) % totalFrames;
        sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
        clock.restart();
    }
}

void Personaje::reproducirAnimacionMuerte(float deltaTime) {
    if (clock.getElapsedTime() >= frameTime && currentFrame < frameInicioMuerte + totalFramesMuerte) {
        sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
        currentFrame++;
        clock.restart();
    }
}

sf::Vector2f Personaje::getPosition() const {
    return sprite.getPosition();
}

void Personaje::recibirDanio(int cantidad) {
    vida -= cantidad;
    if (vida < 0) vida = 0;

    //std::cout << "El personaje recibió " << cantidad << " de daño. Vida actual: " << vida << "\n";

    if (vida == 0 && !muerto) {
        //std::cout << "¡El personaje ha muerto!\n";
        kill();
    }
    sprite.setColor(sf::Color::Red);
    estaRecibiendoDanio = true;
    flashClock.restart();

}

void Personaje::curar(int cantidad) {
    vida += cantidad;
    if (vida > 100) vida = 100;

    //std::cout << "El personaje se ha curado " << cantidad << " puntos. Vida actual: " << vida << "\n";
}

void Personaje::ganarXP(int cantidad) {
    xp += cantidad;
    std::cout << "XP: " << xp << " / " << xpParaSubir << " (Nivel " << nivel << ")\n";

    while (xp >= xpParaSubir) {
        xp -= xpParaSubir;
        nivel++;
        xpParaSubir += 50;
        std::cout << "¡Subiste al nivel " << nivel << "!\n";
        vida = 100;
    }
}

int Personaje::getVida() const {
    return vida;
}
int Personaje::getNivel() const {
     return nivel;
}
int Personaje::getXP() const {
     return xp;
}
int Personaje::getXPParaSubir() const {
     return xpParaSubir;
}

bool Personaje::estaMuerto() const {
     return muerto;
}

void Personaje::kill() {
    alive = false;
    muerto = true;
    currentFrame = 0;

    if (deathTexture)
        sprite.setTexture(*deathTexture);

    int anchoTextura = deathTexture->getSize().x;
    frameWidth = anchoTextura / totalFramesMuerte;
    frameHeight = deathTexture->getSize().y;

    sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
    sprite.setOrigin(frameWidth / 2.f, frameHeight * 0.7f);

    clock.restart();
}

int Personaje::getCurrentFrame() const {
    return currentFrame;
}

int Personaje::getFrameInicioMuerte() const {
    return frameInicioMuerte;
}

/*sf::FloatRect Personaje::getHitbox() const {
    sf::Vector2f pos = sprite.getPosition();
    sf::Vector2f scale = sprite.getScale();

    float ancho = frameWidth * 0.4f * std::abs(scale.x);  // Ajustá proporción según cuerpo
    float alto = frameHeight * 0.6f * scale.y;

    return sf::FloatRect(
        pos.x - ancho / 2.f,
        pos.y - alto / 2.f,
        ancho,
        alto
    );*/


