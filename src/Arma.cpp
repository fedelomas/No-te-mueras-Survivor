#include "Arma.h"
#include "Enemigo.h"
#include <algorithm>
#include <cmath>
#include <limits>

const std::vector<int> posicionesX = {0, 43, 86, 129, 172, 215, 258, 301, 344, 387};
const std::vector<float> angulosPorFrame = {
    180.f, 160.f, 140.f, 120.f, 100.f, 80.f, 60.f, 40.f, 20.f, 0.f
};

Arma::Arma(sf::Texture& texturaProyectil, sf::Texture& texturaArma, Personaje* duenio, EntityManager* entityManager)
    : texturaProyectil(texturaProyectil),
      texturaSpriteSheetArma(texturaArma),
      duenio(duenio),
      entityManager(entityManager)
{
    totalFrames = 10;
    frameWidth = 43; // Cada frame ocupa ~43.2 px, redondeamos abajo
    frameHeight = texturaSpriteSheetArma.getSize().y;

    spriteArma.setTexture(texturaSpriteSheetArma);
    spriteArma.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
    spriteArma.setOrigin(frameWidth / 2.f, frameHeight);
    spriteArma.setScale(2.f, 2.f);

    relojDisparo.restart();
}

void Arma::update(float deltaTime, sf::View& view)
{
    sf::Vector2f posDuenio = duenio->getPosition();
    spriteArma.setPosition(posDuenio);

    // Buscar enemigo más cercano
    float distanciaMinima = std::numeric_limits<float>::max();
    Entity* objetivo = nullptr;

    for (Entity* e : entityManager->getEntities())
    {
        if (dynamic_cast<Enemigo*>(e) && e->isAlive())
        {
            float dx = posDuenio.x - e->getPosition().x;
            float dy = posDuenio.y - e->getPosition().y;
            float distancia = std::sqrt(dx * dx + dy * dy);

            if (distancia < distanciaMinima)
            {
                distanciaMinima = distancia;
                objetivo = e;
            }
        }
    }

    if (objetivo)
    {
        sf::Vector2f dir = objetivo->getPosition() - posDuenio;
        float angulo = std::atan2(dir.y, dir.x) * 180.f / 3.14159f;
        if (angulo < 0) angulo += 360.f;

        // Reinterpretar 180° como abajo y 90° como arriba (giro antihorario)
        bool reflejar = false;
        float anguloSimetrico = angulo;

        if (angulo > 180.f)
        {
            reflejar = true;
            anguloSimetrico = 360.f - angulo;
        }

        // Buscar el frame más cercano
        int frame = 0;
        float menorDiferencia = 999.f;

        for (int i = 0; i < angulosPorFrame.size(); ++i)
        {
            float diff = std::abs(angulosPorFrame[i] - anguloSimetrico);
            if (diff < menorDiferencia)
            {
                menorDiferencia = diff;
                frame = i;
            }
        }

        int x = posicionesX[frame];
        spriteArma.setTextureRect(sf::IntRect(x, 0, frameWidth, frameHeight));
        spriteArma.setScale(reflejar ? -2.f : 2.f, 2.f);

        // Disparo automático
        if (relojDisparo.getElapsedTime().asSeconds() >= intervaloDisparo)
        {
            float magnitud = std::sqrt(dir.x * dir.x + dir.y * dir.y);
            if (magnitud > 0) dir /= magnitud;

            proyectiles.push_back(new Proyectil(texturaProyectil, posDuenio, dir));
            relojDisparo.restart();
        }
    }

    for (auto* p : proyectiles)
        p->update(deltaTime, view);

    proyectiles.erase(std::remove_if(proyectiles.begin(), proyectiles.end(),
        [&](Proyectil* p)
    {
        if (p->fueraDePantalla(view))
        {
            delete p;
            return true;
        }
        return false;
    }), proyectiles.end());
}

void Arma::render(sf::RenderWindow& window)
{
    // Dibuja el arma en su posición actual
    window.draw(spriteArma);

    // Dibuja los proyectiles activos
    for (auto* proyectil : proyectiles)
        window.draw(*proyectil);

    // Diagnóstico visual: mostrar todos los frames alineados
    for (int i = 0; i < totalFrames; ++i)
    {
        sf::Sprite frameDebug;
        frameDebug.setTexture(texturaSpriteSheetArma);

        // Usá corte lineal o corregido según tu hoja (ver discusión sobre frameWidth real)
        int x = posicionesX[i];
        frameDebug.setTextureRect(sf::IntRect(x, 0, frameWidth, frameHeight));
        frameDebug.setScale(2.f, 2.f);
        frameDebug.setPosition(100.f + i * (frameWidth * 2.f + 5.f), 550.f);  // Alineados abajo

        window.draw(frameDebug);
    }
}

std::vector<Proyectil*>& Arma::getProyectiles()
{
    return proyectiles;
}
