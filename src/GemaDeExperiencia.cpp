
#include "GemaDeExperiencia.h"
#include <cmath>

GemaDeExperiencia::GemaDeExperiencia(sf::Texture& texture, sf::Vector2f posicion)
    : Entity(texture)
{
    sprite.setPosition(posicion);
    sprite.setScale(2.5f, 2.5f);
    frameWidth = texture.getSize().x;
    frameHeight = texture.getSize().y;
    sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
    //sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
}

void GemaDeExperiencia::update(float deltaTime, sf::View& view) {

    float offset = std::sin(clock.getElapsedTime().asSeconds() * 2.f) * 0.5f;
    sprite.move(0.f, offset);
}
