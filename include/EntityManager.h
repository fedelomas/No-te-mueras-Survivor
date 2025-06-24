#pragma once
#include <vector>
#include "Entity.h"
#include <SFML/Graphics.hpp>

class EntityManager {
private:
    std::vector<Entity*> entities;

    sf::Clock xpSpawnClock;
    sf::Clock pocionSpawnClock;
    float xpSpawnInterval = 5.f;
    float pocionSpawnInterval = 10.f;

    int cantidadXP = 5;
    int cantidadPociones = 3;

    std::vector<sf::Texture*> enemyTextures;
    sf::Texture* xpTexture = nullptr;
    sf::Texture* pocionTexture = nullptr;
    sf::Texture* bossTexture = nullptr;

public:
    EntityManager(){};
    ~EntityManager();

    void update(float deltaTime, sf::View& view);
    void render(sf::RenderWindow& window);
    void add(Entity* entity);
    void removeDead();

    void spawnBoss(sf::Texture& texture, sf::Vector2f posicion);
    void spawnEnemyWave(int cantidadTotal, sf::Vector2f zonaCentro, float radio);

    void spawnPotion(sf::Texture& texture, sf::Vector2f posicion);
    void spawnGema(sf::Texture& texture, sf::Vector2f posicion);

    void setEnemyTextures(const std::vector<sf::Texture*>& textures);
    void setBossTexture(sf::Texture& texture);
    void setPocionTexture(sf::Texture& texture);
    void setXpTexture(sf::Texture& texture);
};
