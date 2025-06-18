#include "EntityManager.h"
#include "Enemigo.h"
#include "Boss.h"
#include "PocionDeVida.h"
#include "GemaDeExperiencia.h"
#include <cmath>

EntityManager::~EntityManager() {
    for (std::size_t i = 0; i < entities.size(); ++i) {
        delete entities[i];
    }
    entities.clear();
}

void EntityManager::update(float deltaTime, sf::View& view) {
    for (std::size_t i = 0; i < entities.size(); ++i) {
        entities[i]->update(deltaTime, view);
    }

    removeDead();
}

void EntityManager::render(sf::RenderWindow& window) {
    for (std::size_t i = 0; i < entities.size(); ++i) {
        window.draw(*entities[i]);
    }
}

void EntityManager::add(Entity* entity) {
    entities.push_back(entity);
}

void EntityManager::removeDead() {
    auto it = entities.begin();
    while (it != entities.end()) {
        if (!(*it)->isAlive()) {
            delete *it;
            it = entities.erase(it);
        } else {
            ++it;
        }
    }
}

void EntityManager::spawnBoss(sf::Texture& texture, sf::Vector2f posicion) {
    add(new Boss(texture, posicion));
}

void EntityManager::spawnPotion(sf::Texture& texture, sf::Vector2f posicion) {
    add(new PocionDeVida(texture, posicion));
}

void EntityManager::spawnGema(sf::Texture& texture, sf::Vector2f posicion) {
    add(new GemaDeExperiencia(texture, posicion));
}

void EntityManager::setEnemyTextures(const std::vector<sf::Texture*>& textures) {
    enemyTextures = textures;
}

void EntityManager::setBossTexture(sf::Texture& texture) {
    bossTexture = &texture;
}

void EntityManager::setPocionTexture(sf::Texture& texture) {
    pocionTexture = &texture;
}

void EntityManager::setXpTexture(sf::Texture& texture) {
    xpTexture = &texture;
}

void EntityManager::spawnEnemyWave(int cantidadTotal, sf::Vector2f zonaCentro, float radio) {
    if (enemyTextures.empty() || cantidadTotal <= 0)
        return;

    int tipos = enemyTextures.size();
    int porTipo = cantidadTotal / tipos;
    int resto = cantidadTotal % tipos;

    for (int tipo = 0; tipo < tipos; ++tipo) {
        int cantidad = porTipo + (tipo < resto ? 1 : 0);

        for (int i = 0; i < cantidad; ++i) {

            float angle = static_cast<float>(rand()) / RAND_MAX * 2 * 3.14159f;
            float distance = static_cast<float>(rand()) / RAND_MAX * radio;
            sf::Vector2f offset(std::cos(angle) * distance, std::sin(angle) * distance);
            sf::Vector2f posicion = zonaCentro + offset;

            sf::Texture* texture = enemyTextures[tipo];
            float velocidad = 0.f;
            float escala = 1.5f;

            switch (tipo){
                case 0:
                    velocidad = 50.f;
                    escala = 1.5f;
                break;
                case 1:
                    velocidad = 55.f;
                    escala = 1.5f;
                break;
                case 2:
                    velocidad = 30.f;
                    escala = 2.0f;
                break;
                case 3:
                    velocidad = 75.f;
                    escala = 1.1f;
                break;
                case 4:
                    velocidad = 80.f;
                    escala = 1.8f;
                break;
                case 5:
                    velocidad = 70.f;
                    escala = 1.1f;
                break;
            }

            add(new Enemigo(*texture, posicion, velocidad, escala));
        }
    }
}
