#include "Personaje.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

Personaje::Personaje(sf::Texture& texture)
    : Entity(texture)
{
    totalFrames = 4;
    frameWidth = texture.getSize().x / totalFrames;
    frameHeight = texture.getSize().y;

    sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
    sprite.setOrigin(frameWidth / 2.f, frameHeight * 0.7f);

    sprite.setScale(1.5f, 1.5f);
    sprite.setPosition(0.f, 0.f);
}


void Personaje::update(float deltaTime, sf::View& view)
{
    mover(deltaTime, view);
    actualizarAnimacion();
}

/*void Personaje::mover(float deltaTime, sf::View& view)
{
    sf::Vector2f direction(0.f, 0.f);
    sf::Vector2f pos = sprite.getPosition();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && pos.y > -470)
        direction.y = -speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && pos.y < 480)
        direction.y = speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && pos.x < 730) {
        direction.x = speed;
        sprite.setScale(1.5f, 1.5f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && pos.x > -730) {
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
} */


void Personaje::mover(float deltaTime, sf::View& view)
{
    sf::Vector2f direction(0.f, 0.f);

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

void Personaje::actualizarAnimacion()
{
    if (estaMoviendo && clock.getElapsedTime() >= frameTime) {
        currentFrame = (currentFrame + 1) % totalFrames;
        sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
        clock.restart();
    }
}

sf::Vector2f Personaje::getPosition() const
{
    return sprite.getPosition();
}
