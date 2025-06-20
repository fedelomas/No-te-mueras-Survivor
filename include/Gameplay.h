#pragma once
#include <SFML/Graphics.hpp>
#include "Personaje.h"
#include "EntityManager.h"
#include "PauseMenu.h"
#include "SoundManager.h"


class Gameplay {
public:
    Gameplay(SoundManager& soundManager);
    ~Gameplay();
    int run();

private:
    sf::RenderWindow window;
    sf::View view;

    sf::Texture mapTexture;
    sf::Texture playerTexture;
    sf::Texture enemigoTexture1, enemigoTexture2, enemigoTexture3, enemigoTexture4, enemigoTexture5, enemigoTexture6;
    sf::Texture pocionTexture;
    sf::Texture xpTexture;

    sf::Sprite backgroundMap;

    Personaje* personaje;
    EntityManager entityManager;
    PauseMenu pauseMenu;
    SoundManager& soundManager;

    void handleEvents();
    void update(float deltaTime);
    void render();
};

