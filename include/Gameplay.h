#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/View.hpp>
#include "Personaje.h"

class Gameplay
{
public:
    Gameplay();
    void run();


private:
    sf::RenderWindow window;
    sf::Texture playerTexture;
    sf::Texture mapTexture;      // Textura del fondo
    sf::Sprite backgroundMap;     // Sprite del fondo
    sf::View view;
    std::vector<sf::Sprite> enemigos;
    std::vector<sf::Sprite> mapTiles;

    Personaje player;

    void processEvents();
    void update();
    void render();
};



