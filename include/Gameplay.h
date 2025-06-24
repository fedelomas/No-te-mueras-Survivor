#pragma once
#include <SFML/Graphics.hpp>
#include "Personaje.h"
#include "EntityManager.h"
#include "ChunkManager.h"

class Gameplay {
public:
    Gameplay();
    ~Gameplay();
    void run();


private:

    sf::RenderWindow window;
    ChunkManager chunkManager;
    EntityManager entityManager;
    sf::View view;

    sf::Texture tilesetTexture;
    sf::Texture playerTexture;
    sf::Texture enemigoTexture1, enemigoTexture2, enemigoTexture3, enemigoTexture4, enemigoTexture5, enemigoTexture6;
    sf::Texture bossTexture;
    sf::Texture pocionTexture;
    sf::Texture xpTexture;
    Personaje* personaje;

    void handleEvents();
    void update(float deltaTime);
    void render();
};






