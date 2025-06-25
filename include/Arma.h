#pragma once
#include <vector>
#include "Proyectil.h"
#include "Personaje.h"
#include "EntityManager.h"

class Arma
{
public:
    Arma(sf::Texture& texturaProyectil, sf::Texture& texturaArma, Personaje* duenio, EntityManager* entityManager);

    void update(float deltaTime, sf::View& view);
    void render(sf::RenderWindow& window);
    std::vector<Proyectil*>& getProyectiles();

private:
    Personaje* duenio;
    EntityManager* entityManager;

    sf::Texture& texturaProyectil;
    sf::Texture& texturaSpriteSheetArma;
    sf::Sprite spriteArma;

    int totalFrames = 10;
    int frameWidth ;
    int frameHeight ;

    std::vector<Proyectil*> proyectiles;
    sf::Clock relojDisparo;
    float intervaloDisparo = 1.f;
};
