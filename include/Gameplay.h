#pragma once
#include <SFML/Graphics.hpp>
#include "SoundManager.h"
#include "PauseMenu.h"
#include "Personaje.h"
#include "EntityManager.h"
<<<<<<< Updated upstream
#include "CollisionManager.h"
#include "HUD.h"
#include "PauseMenu.h"
#include "SoundManager.h"
#include "ChunkManager.h"

class Gameplay {
public:
    //Gameplay();
=======
#include "ChunkManager.h"
#include "HUD.h"
#include "CollisionManager.h"

class Gameplay {
public:
>>>>>>> Stashed changes
    Gameplay(sf::RenderWindow& window, SoundManager& soundManager);
    ~Gameplay();
    int run();

<<<<<<< Updated upstream


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
=======
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
>>>>>>> Stashed changes
    sf::Texture bossTexture;
    sf::Texture pocionTexture;
    sf::Texture xpTexture;

<<<<<<< Updated upstream
=======
    sf::Texture backgroundMapTexture;
>>>>>>> Stashed changes
    sf::Sprite backgroundMap;
    bool animacionMuerteTerminada = false;
    bool volverAlMenu = false;

    PauseMenu pauseMenu;
    SoundManager& soundManager;

<<<<<<< Updated upstream
    Personaje* personaje;
    EntityManager entityManager;
    CollisionManager* collisionManager;

    ChunkManager chunkManager;

    void handleEvents();
    void update(float deltaTime);
    void render();
=======
    sf::Font hudFont;
    sf::Text gameOverText;
    sf::Text salirText;

    sf::Clock tiempoPartida;

    bool animacionMuerteTerminada = false;
>>>>>>> Stashed changes
};
