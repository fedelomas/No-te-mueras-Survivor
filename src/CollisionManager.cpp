#include "CollisionManager.h"
#include <iostream>

void CollisionManager::checkCollisions() {
    auto& entities = entityManager->getEntities();

    for (std::size_t i = 0; i < entities.size(); ++i) {
        Entity* entidad = entities[i];

        //if (entidad->getBounds().intersects(personaje->getBounds())){
        if (entidad->getHitbox().intersects(personaje->getHitbox())){

            // Pocion de vida
            if (dynamic_cast<PocionDeVida*>(entidad)) {
                std::cout << "[Collision] Pocion de Vida recogida!" << std::endl;
                entidad->kill();
                personaje->curar(50);
            }
            // Gema de experiencia
            else if (dynamic_cast<GemaDeExperiencia*>(entidad)) {
                std::cout << "[Collision] Gema de experiencia recogida!" << std::endl;
                entidad->kill();
                personaje->ganarXP(10);
            }
            // Enemigo
             else if (dynamic_cast<Enemigo*>(entidad)) {
                Enemigo* enemigo = dynamic_cast<Enemigo*>(entidad);
                if (enemigo) {
                    if (enemigo->clockAtaque.getElapsedTime().asSeconds() >= enemigo->intervaloAtaque) {
                        std::cout << "[Collision] Enemigo tocado!" << std::endl;
                        personaje->recibirDanio(10);
                        enemigo->clockAtaque.restart();
            }
                }
                    }

            // Boss
             else if (dynamic_cast<Boss*>(entidad)) {
                Boss* boss = dynamic_cast<Boss*>(entidad);
                if (boss) {
                    if (boss->clockAtaque.getElapsedTime().asSeconds() >= boss->intervaloAtaque) {
                        std::cout << "[Collision] Enemigo tocado!" << std::endl;
                        personaje->recibirDanio(50);
                        boss->clockAtaque.restart();
            }
                }
                    }
        }
    }
}
