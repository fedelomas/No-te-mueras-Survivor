#include "Boss.h"
#include <cmath>

Boss::Boss(sf::Texture& texture, const sf::Vector2f& posicionInicial, float velocidad, float escala)
    : Entity(texture)
{
    sprite.setPosition(posicionInicial);
    speed = velocidad;
    frameWidth = texture.getSize().x / 4;
    frameHeight = texture.getSize().y;
    sprite.setScale(escala, escala);
    totalFrames = 4;
    sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
    sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
}

void Boss::update(float deltaTime, sf::View& view) {
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
void Boss::actualizarAnimacion()
{
    if (clock.getElapsedTime() >= frameTime)
    {
        currentFrame = (currentFrame + 1) % totalFrames;
        sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
        clock.restart();
    }
}
