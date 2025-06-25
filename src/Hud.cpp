#include "HUD.h"
#include <sstream>

HUD::HUD(Personaje* personaje)
    : personaje(personaje)
{
    if (!font.loadFromFile("Assets/Fonts/font1.ttf"))
        throw std::runtime_error("No se pudo cargar la fuente del HUD.");

    // Vida
    fondoVida.setSize(sf::Vector2f(200.f, 20.f));
    fondoVida.setFillColor(sf::Color(50, 50, 50));
    fondoVida.setPosition(15.f, 15.f);



    barraVida.setSize(sf::Vector2f(200.f, 20.f));
    barraVida.setFillColor(sf::Color::Red);
    barraVida.setPosition(15.f, 15.f);

    // Experiencia
    fondoXP.setSize(sf::Vector2f(200.f, 12.f));
    fondoXP.setFillColor(sf::Color(50, 50, 50));
    fondoXP.setPosition(15.f, 45.f);


    barraXP.setSize(sf::Vector2f(200.f, 12.f));
    barraXP.setFillColor(sf::Color::Blue);
    barraXP.setPosition(15.f, 45.f);

    // Textos
    textoVida.setFont(font);
    textoVida.setCharacterSize(12);
    textoVida.setFillColor(sf::Color::White);
    textoVida.setPosition(225.f, 15.f);


    textoNivel.setFont(font);
    textoNivel.setCharacterSize(12);
    textoNivel.setFillColor(sf::Color::Yellow);
    textoNivel.setPosition(225.f, 45.f);

    textoTiempo.setFont(font);
    textoTiempo.setCharacterSize(14);
    textoTiempo.setFillColor(sf::Color::White);
    textoTiempo.setPosition(800.f, 10.f);
}

void HUD::update(float deltaTime, sf::Time tiempoTotal)
{
    // VIDA
    float vidaPorcentaje = static_cast<float>(personaje->getVida()) / 100.f;
    barraVida.setSize(sf::Vector2f(200.f * vidaPorcentaje, 20.f));

    std::stringstream ssVida;
    ssVida << "Vida: " << personaje->getVida() << " / 100";
    textoVida.setString(ssVida.str());

    // XP
    float xp = static_cast<float>(personaje->getXP());
    float xpMax = static_cast<float>(personaje->getXPParaSubir());
    float xpPorcentaje = xp / xpMax;
    barraXP.setSize(sf::Vector2f(200.f * xpPorcentaje, 12.f));

    std::stringstream ssNivel;
    ssNivel << "Nivel: " << personaje->getNivel();
    textoNivel.setString(ssNivel.str());

    // TIEMPO
    int segundos = static_cast<int>(tiempoTotal.asSeconds());
    int minutos = segundos / 60;
    segundos %= 60;

    std::stringstream ssTiempo;
    ssTiempo << "Tiempo: " << minutos << "m " << segundos << "s";
    textoTiempo.setString(ssTiempo.str());
}

void HUD::render(sf::RenderWindow& window)
{
    window.draw(fondoVida);
    window.draw(barraVida);
    window.draw(fondoXP);
    window.draw(barraXP);
    window.draw(textoVida);
    window.draw(textoNivel);
    window.draw(textoTiempo);
}
