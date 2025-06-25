#pragma once
#include "Entity.h"

class Personaje : public Entity {
public:
    Personaje(sf::Texture& playerTexture, sf::Texture& deathTexture);
    void update(float deltaTime, sf::View& view) override;
    sf::Vector2f getPosition() const;
    bool estaMoviendo = false;

    sf::Clock flashClock;
    bool estaRecibiendoDanio = false;
    void recibirDanio(int cantidad);
    bool estaSiendoCurado = false;
    void curar(int cantidad);
    void ganarXP(int cantidad);
    void kill() override;

    int getVida() const;
    int getNivel() const;
    int getXP() const;
    int getXPParaSubir() const;

    bool estaMuerto() const;

    void reproducirAnimacionMuerte(float deltaTime);
    int getCurrentFrame() const;
    int getFrameInicioMuerte() const;

private:
    void mover(float deltaTime, sf::View& view);
    void actualizarAnimacion();

    int vida = 100;
    int xp = 0;
    int nivel = 1;
    int xpParaSubir = 100;

    sf::Texture* deathTexture = nullptr;

    bool muerto = false;
    int frameInicioMuerte = 0;
    int totalFramesMuerte = 4;
};
