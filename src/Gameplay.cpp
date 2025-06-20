#include "Gameplay.h"
#include <iostream>

Gameplay::Gameplay(SoundManager& soundManager): window(sf::VideoMode(1000, 650), "SurvivorPrueba"),soundManager(soundManager),pauseMenu(window, soundManager)
{


    window.setFramerateLimit(60);
    view.setSize(1000, 650);
    view.setCenter(0, 0);


    if (!mapTexture.loadFromFile("Assets/Mapa/Mapa.png"))
        throw std::runtime_error("No se pudo cargar la imagen del mapa.");

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

    if (!pocionTexture.loadFromFile("Assets/Drops/pocion.png"))
        throw std::runtime_error("No se pudo cargar textura de pocion");

    if (!xpTexture.loadFromFile("Assets/Drops/gema.png"))
        throw std::runtime_error("No se pudo cargar textura de la gema");


    // Spawn inicial de entidades
    personaje = new Personaje(playerTexture);
    std::vector<sf::Texture*> enemyTextures =
    {
        &enemigoTexture1, &enemigoTexture2, &enemigoTexture3,
        &enemigoTexture4, &enemigoTexture5, &enemigoTexture6
    };

    entityManager.setEnemyTextures(enemyTextures);
    //entityManager.setPocionTexture(pocionTexture);
    //entityManager.setXpTexture(xpTexture);

    entityManager.spawnEnemyWave(24, personaje->getPosition(), 500.f);
    entityManager.spawnPotion(pocionTexture, { 200.f, 0.f });
    entityManager.spawnGema(xpTexture, { -200.f, 0.f} );

    backgroundMap.setTexture(mapTexture);
    backgroundMap.setOrigin(mapTexture.getSize().x / 2.f, mapTexture.getSize().y / 2.f);
    backgroundMap.setPosition(0.f, 0.f);
}

Gameplay::~Gameplay()
{
    delete personaje;
}

int Gameplay::run()
{
    sf::Clock clock;

    // Evitar que el flag esté en true si venís desde "Continuar"
    pauseMenu.resetReturnToMainMenu();

    soundManager.setMenuMusicEnabled(false);     // Apagar música del menú
    soundManager.setGameplayMusicEnabled(true);  // Encender música del juego

    while (window.isOpen())
    {
        if (pauseMenu.shouldReturnToMainMenu())
        {
            soundManager.setGameplayMusicEnabled(false);  // Detener música del juego
            soundManager.setMenuMusicEnabled(true);       // Reproducir música del menú

            // No eliminar ni cerrar recursos aquí
            return 0;  // Volver al menú pero mantener la instancia viva
        }

        float deltaTime = clock.restart().asSeconds();

        handleEvents();
        update(deltaTime);
        render();
    }

    return -1;  // Salida por cierre normal de ventana
}

void Gameplay::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        pauseMenu.processEvent(event);  //Delegar eventos al menú de pausa
    }
}

void Gameplay::update(float deltaTime)
{
    if (!pauseMenu.isPaused())
    {
        personaje->update(deltaTime, view);
        entityManager.update(deltaTime, view);
    }
}

void Gameplay::render()
{
    window.clear();

    window.setView(view);
    window.draw(backgroundMap);
    window.draw(*personaje);
    entityManager.render(window);

    pauseMenu.render();  // Dibuja HUD + menú/carte

    window.display();
}


