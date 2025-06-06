#include "Gameplay.h"
#include <SFML/Graphics.hpp>
#include "Personaje.h"


Gameplay::Gameplay() : window(sf::VideoMode(1000, 650), "SurvivorPrueba"), player(playerTexture)
{
    window.setFramerateLimit(60);

    view.setSize(1000,650);
    view.setCenter(0,0);



    if (!mapTexture.loadFromFile("Assets/Mapa/Mapa.png")) {
        throw std::runtime_error("No se pudo cargar la imagen de fondo.");
    }
    if (!playerTexture.loadFromFile("Assets/Player/Soldier/_Run.png")) {
        throw std::runtime_error("No se pudo cargar la imagen de fondo.");
    }

    backgroundMap.setTexture(mapTexture);
    backgroundMap.setOrigin(mapTexture.getSize().x/2, mapTexture.getSize().y/2 );
    backgroundMap.setPosition(0,0);




}

void Gameplay::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Gameplay::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Gameplay::update() {
   player.update(window, view);
}

void Gameplay::render() {
    window.clear(sf::Color::White);
    window.setView(view);
    window.draw(backgroundMap);
    window.draw(player);
    window.display();
}



