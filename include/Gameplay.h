 #pragma once
#include <SFML/Graphics.hpp>
#include "Personaje.h"
#include "EntityManager.h"
#include "ChunkManager.h"

class Gameplay {
public:
    Gameplay();
    ~Gameplay();

    int run();

private:
    void handleEvents();
    void update(float deltaTime);
    void render();

    sf::RenderWindow window;
    ChunkManager chunkManager;
    EntityManager entityManager;
    sf::View view;

    sf::Texture tilesetTexture;
    sf::Texture mapTexture;
    sf::Texture playerTexture;
    sf::Texture enemigoTexture1, enemigoTexture2, enemigoTexture3, enemigoTexture4, enemigoTexture5, enemigoTexture6;
    sf::Texture bossTexture;
    sf::Texture enemigoTexture4, enemigoTexture5, enemigoTexture6;
    sf::Texture pocionTexture;
    sf::Texture xpTexture;
    Personaje* personaje;
    sf::Texture armaTexture;
    sf::Texture proyectilTexture;

    void handleEvents();
    void update(float deltaTime);
    void render();
};



};
    sf::Sprite backgroundMap;

    Personaje* personaje;
    Arma* arma;


    EntityManager entityManager;
    PauseMenu pauseMenu;
    SoundManager& soundManager;
};
