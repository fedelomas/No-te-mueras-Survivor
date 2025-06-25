#pragma once
#include <SFML/Graphics.hpp>
#include "Personaje.h"
#include "EntityManager.h"
#include "CollisionManager.h"
#include "HUD.h"
#include "PauseMenu.h"
#include "SoundManager.h"
#include "ChunkManager.h"

class Gameplay {
public:
    //Gameplay();
    Gameplay(sf::RenderWindow& window, SoundManager& soundManager);
    ~Gameplay();
    int run();



private:
    sf::RenderWindow window;
    sf::View view;

    sf::Clock tiempoPartida;
    HUD* hud = nullptr;
    sf::Text gameOverText;
    sf::Text salirText;
    sf::Font hudFont;


    sf::Texture tilesetTexture;
    //sf::Texture mapTexture;
    sf::Texture playerTexture;
    sf::Texture deathTexture;
    sf::Texture enemigoTexture1, enemigoTexture2, enemigoTexture3, enemigoTexture4, enemigoTexture5, enemigoTexture6;
    sf::Texture bossTexture;
    sf::Texture pocionTexture;
    sf::Texture xpTexture;

    sf::Sprite backgroundMap;
    bool animacionMuerteTerminada = false;
    bool volverAlMenu = false;

    PauseMenu pauseMenu;
    SoundManager& soundManager;

    Personaje* personaje;
    EntityManager entityManager;
    CollisionManager* collisionManager;

    ChunkManager chunkManager;

    void handleEvents();
    void update(float deltaTime);
    void render();
};
