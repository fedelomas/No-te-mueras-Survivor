#pragma once
#include <SFML/Graphics.hpp>
#include "Personaje.h"
#include "EntityManager.h"

class Gameplay {
public:
    Gameplay();
    ~Gameplay();
    void run();

private:
    sf::RenderWindow window;
    sf::View view;

    sf::Texture mapTexture;
    sf::Texture playerTexture;
    sf::Texture enemigoTexture1, enemigoTexture2, enemigoTexture3, enemigoTexture4, enemigoTexture5, enemigoTexture6;
    sf::Texture bossTexture;
    sf::Texture pocionTexture;
    sf::Texture xpTexture;

    sf::Sprite backgroundMap;

    Personaje* personaje;
    EntityManager entityManager;

    void handleEvents();
    void update(float deltaTime);
    void render();
};

