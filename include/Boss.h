#pragma once
#include "Entity.h"

class Boss : public Entity {
public:
    Boss(sf::Texture& texture, const sf::Vector2f& posicionInicial, float velocidad = 20.f, float escala = 4.f );

    void update(float deltaTime, sf::View& view) override;

private:
    void actualizarAnimacion();
};

