#include "PocionDeVida.h"
#include <cmath>

PocionDeVida::PocionDeVida(sf::Texture& texture, sf::Vector2f posicion)
    : Entity(texture)
{
    sprite.setPosition(posicion);
    sprite.setScale(2.1f, 2.1f);
    frameWidth = texture.getSize().x;
    frameHeight = texture.getSize().y;
    sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
}

void PocionDeVida::update(float deltaTime, sf::View& view)
{

    float offset = std::sin(clock.getElapsedTime().asSeconds() * 2.f) * 0.5f;
    sprite.move(0.f, offset);
}
