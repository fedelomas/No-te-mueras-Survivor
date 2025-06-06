#include "Personaje.h"
#include <cmath>


Personaje::Personaje(sf::Texture& texture)
{
    sprite.setTexture(texture);
    sf::FloatRect bounds = sprite.getLocalBounds();

    sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));


    sprite.setOrigin(frameWidth / 2.f, frameHeight * 0.70f);
    sprite.setScale(1.5f, 1.5f);
    sprite.setPosition(0.f,0.f);
}


void Personaje::update(sf::RenderWindow& window, sf::View& view) {
    Movimiento(view);
    updateAnimation();
}

void Personaje::Movimiento(sf::View& view) {
    sf::Vector2f direction(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sprite.getPosition().y > -470) {
        direction.y = -speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sprite.getPosition().y < 460) {
        direction.y = speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sprite.getPosition().x < 730) {
        direction.x = speed;
        sprite.setScale(1.5f, 1.5f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sprite.getPosition().x > -730) {
        direction.x = -speed;
        sprite.setScale(-1.5f, 1.5f);
    }

    sprite.move(direction);
    view.move(direction);
}


void Personaje::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    target.draw(sprite,state);
}

void Personaje::updateAnimation()
{
    if (clock.getElapsedTime() >= frameTime)
    {
        currentFrame = (currentFrame + 1) % totalFrames;
        sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));

        sprite.setOrigin(frameWidth / 2.f, frameHeight * 0.70f);

        clock.restart();
    }
}


