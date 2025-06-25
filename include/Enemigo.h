#pragma once
#include "Entity.h"

class Enemigo : public Entity {
public:
    Enemigo(sf::Texture& texture, const sf::Vector2f& posicionInicial, float velocidad = 50.f, float escala = 1.5f );
    void update(float deltaTime, sf::View& view) override;
    //sf::FloatRect getHitbox() const override;


    sf::Clock clockAtaque;
    float intervaloAtaque = 2.0f;

private:
    void actualizarAnimacion();
};
