#include "Gameplay.h"
#include <iostream>


Gameplay::Gameplay()
    : window(sf::VideoMode(1000, 650), "SurvivorPrueba"),
      chunkManager(32, 64),
      entityManager()
{
    window.setFramerateLimit(60);
    view.setSize(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
    view.setCenter(0.f, 0.f);


    if (!playerTexture.loadFromFile("Assets/Character/Walk3.png"))
        throw std::runtime_error("No se pudo cargar la textura del personaje.");

    if (!enemigoTexture1.loadFromFile("Assets/Enemies/1/RunSD.png"))
        throw std::runtime_error("No se pudo cargar textura de enemigo 1");

    if (!enemigoTexture2.loadFromFile("Assets/Enemies/2/RunSD.png"))
        throw std::runtime_error("No se pudo cargar textura del enemigo 2");

    if (!enemigoTexture3.loadFromFile("Assets/Enemies/3/RunSD.png"))
        throw std::runtime_error("No se pudo cargar textura del enemigo 3");

    if (!enemigoTexture4.loadFromFile("Assets/Enemies/4/RunSD.png"))
        throw std::runtime_error("No se pudo cargar textura del enemigo 4");

    if (!enemigoTexture5.loadFromFile("Assets/Enemies/5/RunSD.png"))
        throw std::runtime_error("No se pudo cargar textura del enemigo 5");

    if (!enemigoTexture6.loadFromFile("Assets/Enemies/6/RunSD.png"))
        throw std::runtime_error("No se pudo cargar textura del enemigo 6");

    if (!bossTexture.loadFromFile("Assets/Enemies/Bosses/green-monster.png"))
        throw std::runtime_error("No se pudo cargar textura del boss");

    if (!pocionTexture.loadFromFile("Assets/Drops/pocion.png"))
        throw std::runtime_error("No se pudo cargar textura de pocion");

    if (!xpTexture.loadFromFile("Assets/Drops/gema.png"))
        throw std::runtime_error("No se pudo cargar textura de la gema");

        // Cargar tileset y pasarlo al chunk manager
    if (!tilesetTexture.loadFromFile("Assets/Mapa/1 Tiles/TileSet2.png")) {
        throw std::runtime_error("No se pudo cargar el tileset.");
    }

    chunkManager.setTileTexture(tilesetTexture);


    // Spawn inicial de entidades
    personaje = new Personaje(playerTexture);
    view.setCenter(0.f, 0.f);
    chunkManager.updateChunksAround(personaje->getPosition());

    std::vector<sf::Texture*> enemyTextures = {
        &enemigoTexture1, &enemigoTexture2, &enemigoTexture3,
        &enemigoTexture4, &enemigoTexture5, &enemigoTexture6
        };

    entityManager.setEnemyTextures(enemyTextures);
    //entityManager.setPocionTexture(pocionTexture);
    //entityManager.setXpTexture(xpTexture);

    entityManager.spawnEnemyWave(24, personaje->getPosition(), 1000.f);
    entityManager.spawnBoss(bossTexture,{ 700.f, 0.f});
    entityManager.spawnPotion(pocionTexture, { 200.f, 0.f });
    entityManager.spawnGema(xpTexture, { -200.f, 0.f} );


}
Gameplay::~Gameplay()
{
    delete personaje;
}


void Gameplay::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        handleEvents();
        update(deltaTime);
        render();
    }
}

void Gameplay::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Gameplay::update(float deltaTime) {


    chunkManager.updateChunksAround(personaje->getPosition());  //Esto es nuevo
    personaje->update(deltaTime, view);
    entityManager.update(deltaTime, view);
    view.setCenter(personaje->getPosition()); // esto es nuevo
}

void Gameplay::render() {
    window.clear();
    window.setView(view);
    window.draw(chunkManager);
    window.draw(*personaje);
    entityManager.render(window);

    window.display();
}

