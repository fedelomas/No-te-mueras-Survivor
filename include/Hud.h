#pragma once
#include <SFML/Graphics.hpp>
#include "Personaje.h"

class HUD {
public:
    HUD(Personaje* personaje);
    void update(float deltaTime, sf::Time tiempoTotal);
    void render(sf::RenderWindow& window);

private:
    Personaje* personaje;

    sf::Font font;
    sf::Text textoVida;
    sf::Text textoXP;
    sf::Text textoNivel;
    sf::Text textoTiempo;

    sf::RectangleShape fondoVida;
    sf::RectangleShape barraVida;

    sf::RectangleShape fondoXP;
    sf::RectangleShape barraXP;
};
