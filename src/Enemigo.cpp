#include "Enemigo.h"
#include <cmath>

Enemigo::Enemigo(sf::Texture& texture, const sf::Vector2f& posicionInicial, float velocidad, float escala)
    : Entity(texture)
{
    sprite.setPosition(posicionInicial);
    speed = velocidad;
    frameWidth = texture.getSize().x / 6;
    frameHeight = texture.getSize().y;
    sprite.setScale(escala, escala);
    totalFrames = 6;
    sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
    sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
}

void Enemigo::update(float deltaTime, sf::View& view) {
    sf::Vector2f playerPos = view.getCenter();
    sf::Vector2f currentPos = sprite.getPosition();
    sf::Vector2f direction = playerPos - currentPos;

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0)
        direction /= length;

    if (direction.x < 0)
        sprite.setScale(-std::abs(sprite.getScale().x), sprite.getScale().y);
    else
        sprite.setScale(std::abs(sprite.getScale().x), sprite.getScale().y);

    sprite.move(direction * speed * deltaTime);


    actualizarAnimacion();
}

void Enemigo::actualizarAnimacion()
{
    if (clock.getElapsedTime() >= frameTime)
    {
        currentFrame = (currentFrame + 1) % totalFrames;
        sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
        clock.restart();
    }
}

/*sf::FloatRect Enemigo::getHitbox() const {
    sf::Vector2f pos = sprite.getPosition();
    sf::Vector2f scale = sprite.getScale();
    float w = frameWidth * 0.4f * std::abs(scale.x);
    float h = frameHeight * 0.5f * scale.y;
}*/
