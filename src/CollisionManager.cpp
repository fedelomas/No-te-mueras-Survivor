#include "CollisionManager.h"
#include "Proyectil.h"
#include <iostream>

void CollisionManager::checkCollisions() {
    auto& entities = entityManager->getEntities();

    for (Entity* entidad : entities) {
        if (!entidad->isAlive())
            continue;

        // Colisión con el personaje
        if (entidad->getBounds().intersects(personaje->getBounds())) {
            if (auto pocion = dynamic_cast<PocionDeVida*>(entidad)) {
                entidad->kill();
                personaje->curar(20);
            } else if (auto gema = dynamic_cast<GemaDeExperiencia*>(entidad)) {
                entidad->kill();
                personaje->ganarXP(10);
            } else if (auto enemigo = dynamic_cast<Enemigo*>(entidad)) {
                if (enemigo->clockAtaque.getElapsedTime().asSeconds() >= enemigo->intervaloAtaque) {
                    personaje->recibirDanio(10);
                    enemigo->clockAtaque.restart();
                }
            }
        }

        // Colisión con proyectiles
        for (Entity* otra : entities) {
            if (!otra->isAlive() || entidad == otra)
                continue;

            // Proyectil golpea a Enemigo
            if (auto proyectil = dynamic_cast<Proyectil*>(entidad)) {
                if (auto enemigo = dynamic_cast<Enemigo*>(otra)) {
                    if (proyectil->getBounds().intersects(enemigo->getBounds())) {
                        enemigo->recibirDanio(15);   // ← daño ajustable
                        proyectil->kill();
                    }
                }
            }
        }
    }
}
