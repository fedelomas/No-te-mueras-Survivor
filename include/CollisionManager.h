<<<<<<< Updated upstream
#pragma once
#include "EntityManager.h"
#include "Personaje.h"
#include "Enemigo.h"
#include "PocionDeVida.h"
#include "GemaDeExperiencia.h"
#include "Boss.h"

class CollisionManager {
private:
    Personaje* personaje;
    EntityManager* entityManager;

public:
    CollisionManager(Personaje* personaje, EntityManager* entityManager)
        : personaje(personaje), entityManager(entityManager) {}

    void checkCollisions();
};
=======
#pragma once
#include "EntityManager.h"
#include "Personaje.h"
#include "Enemigo.h"
#include "PocionDeVida.h"
#include "GemaDeExperiencia.h"
#include "Boss.h"

class CollisionManager {
private:
    Personaje* personaje;
    EntityManager* entityManager;

public:
    CollisionManager(Personaje* personaje, EntityManager* entityManager)
        : personaje(personaje), entityManager(entityManager) {}

    void checkCollisions();
};
>>>>>>> Stashed changes
