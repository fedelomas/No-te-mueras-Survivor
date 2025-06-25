<<<<<<< Updated upstream
#pragma once
#include "Entity.h"

class Boss : public Entity {
public:
    Boss(sf::Texture& texture, const sf::Vector2f& posicionInicial, float velocidad = 10.f, float escala = 3.0f );

    void update(float deltaTime, sf::View& view) override;

    sf::Clock clockAtaque;
    float intervaloAtaque = 2.5f;

private:
    void actualizarAnimacion();
    float escalaBase = 1.5f;
};

=======
#pragma once
#include "Entity.h"

class Boss : public Entity {
public:
    Boss(sf::Texture& texture, const sf::Vector2f& posicionInicial, float velocidad = 10.f, float escala = 3.0f );

    void update(float deltaTime, sf::View& view) override;

    sf::Clock clockAtaque;
    float intervaloAtaque = 2.5f;

private:
    void actualizarAnimacion();
    float escalaBase = 1.5f;
};

>>>>>>> Stashed changes
