#pragma once
#include "Entity.h"

class GemaDeExperiencia : public Entity {
public:
    GemaDeExperiencia(sf::Texture& texture, sf::Vector2f posicion);

    void update(float deltaTime, sf::View& view) override;
};
