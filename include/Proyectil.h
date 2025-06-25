#pragma once
#include "Entity.h"

class Proyectil : public Entity {
public:
    Proyectil(sf::Texture& texture, sf::Vector2f posicion, sf::Vector2f direccion, float velocidad = 600.f);

    void update(float deltaTime, sf::View& view) override;
    bool fueraDePantalla(const sf::View& view) const;

private:
    sf::Vector2f direccion;
    float velocidad;
};
