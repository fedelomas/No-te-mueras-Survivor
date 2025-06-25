#pragma once
#include <SFML/Graphics.hpp>
#include "SoundManager.h"
#include "PauseMenu.h"
#include "Personaje.h"
#include "EntityManager.h"
#include "CollisionManager.h"
#include "HUD.h"
#include "PauseMenu.h"
#include "SoundManager.h"
#include "ChunkManager.h"

class Gameplay {
public:
    Gameplay(sf::RenderWindow& window, SoundManager& soundManager);
    ~Gameplay();
    int run();

private:
    void handleEvents();
    void update(float deltaTime);
    void render();

    sf::RenderWindow& window;
    sf::View view;

    SoundManager& soundManager;
    PauseMenu pauseMenu;

    Personaje* personaje = nullptr;
    HUD* hud = nullptr;
    CollisionManager* collisionManager = nullptr;
    EntityManager entityManager;
    ChunkManager chunkManager;

    sf::Texture tilesetTexture;
    sf::Texture playerTexture;
    sf::Texture deathTexture;
    sf::Texture enemigoTexture1;
    sf::Texture enemigoTexture2;
    sf::Texture enemigoTexture3;
    sf::Texture enemigoTexture4;
    sf::Texture enemigoTexture5;
    sf::Texture enemigoTexture6;
    sf::Texture bossTexture;
    sf::Texture pocionTexture;
    sf::Texture xpTexture;
    sf::Texture backgroundMapTexture;
    sf::Sprite backgroundMap;
    bool animacionMuerteTerminada = false;
    bool volverAlMenu = false;

    sf::Font hudFont;
    sf::Text gameOverText;
    sf::Text salirText;

    sf::Clock tiempoPartida;
};
