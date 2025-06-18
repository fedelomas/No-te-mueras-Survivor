#pragma once
#include "Entity.h"

class PocionDeVida : public Entity {
public:
    PocionDeVida(sf::Texture& texture, sf::Vector2f posicion);

    void update(float deltaTime, sf::View& view) override;
};
