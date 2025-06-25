#include "Proyectil.h"
#include <cmath>

Proyectil::Proyectil(sf::Texture& texture, sf::Vector2f posicion, sf::Vector2f direccion, float velocidad)
    : Entity(texture), direccion(direccion), velocidad(velocidad)
{
    sprite.setPosition(posicion);
    sprite.setScale(1.f, 1.f);
    frameWidth = texture.getSize().x;
    frameHeight = texture.getSize().y;
    sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
}

void Proyectil::update(float deltaTime, sf::View& view)
{
    sprite.move(direccion * velocidad * deltaTime);
}

bool Proyectil::fueraDePantalla(const sf::View& view) const
{
    sf::FloatRect bounds = sprite.getGlobalBounds();
    sf::FloatRect vista(view.getCenter() - view.getSize() / 2.f, view.getSize());
    return !vista.intersects(bounds);
}
