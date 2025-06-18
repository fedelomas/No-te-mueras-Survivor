#pragma once
#include "Entity.h"

class Personaje : public Entity
{
public:
    Personaje(sf::Texture& texture);
    void update(float deltaTime, sf::View& view) override;
    sf::Vector2f getPosition() const;
    bool estaMoviendo = false;

private:
    void mover(float deltaTime, sf::View& view);
    void actualizarAnimacion();
};
