#include "Gameplay.h"
#include <iostream>

Gameplay::Gameplay(sf::RenderWindow& win, SoundManager& soundManager)
    : window(win),

      soundManager(soundManager),
      chunkManager(32, 64),
      pauseMenu(window, soundManager),
      entityManager()
{
    std::cout << ">> Iniciando constructor de Gameplay\n";
    window.setFramerateLimit(60);
    //view.setSize(1000, 650);
    view.setSize(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
    view.setCenter(0, 0);


    /*if (!mapTexture.loadFromFile("Assets/Mapa/Mapa.png"))
        throw std::runtime_error("No se pudo cargar la imagen del mapa.");*/

    if (!playerTexture.loadFromFile("Assets/Character/Walk3.png"))
        throw std::runtime_error("No se pudo cargar la textura del personaje.");

    if (!deathTexture.loadFromFile("Assets/Character/Death3.png"))
        throw std::runtime_error("No se pudo cargar la textura de muerte del personaje.");

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

    if (!bossTexture.loadFromFile("Assets/Enemies/3/RunSD.png"))
        throw std::runtime_error("No se pudo cargar textura del boss");

    if (!pocionTexture.loadFromFile("Assets/Drops/pocion.png"))
        throw std::runtime_error("No se pudo cargar textura de pocion");

    if (!xpTexture.loadFromFile("Assets/Drops/gema.png"))
        throw std::runtime_error("No se pudo cargar textura de la gema");

    if (!hudFont.loadFromFile("Assets/Fonts/font1.ttf"))
        throw std::runtime_error("No se pudo cargar la fuente del HUD.");

    if (!tilesetTexture.loadFromFile("Assets/Mapa/1 Tiles/TileSet2.png")) {
        throw std::runtime_error("No se pudo cargar el tileset.");
    }



    // Spawn inicial de entidades
    personaje = new Personaje(playerTexture, deathTexture);
    collisionManager = new CollisionManager(personaje, &entityManager);

    chunkManager.setTileTexture(tilesetTexture);
    chunkManager.updateChunksAround(personaje->getPosition());
    std::vector<sf::Texture*> enemyTextures = {
        &enemigoTexture1, &enemigoTexture2, &enemigoTexture3,
        &enemigoTexture4, &enemigoTexture5, &enemigoTexture6
        };

    entityManager.setEnemyTextures(enemyTextures);
    entityManager.spawnEnemyWave(1, personaje->getPosition(), 1000.f);
    entityManager.spawnBoss(bossTexture,{ 700.f, 0.f});
    entityManager.spawnPotion(pocionTexture, { 200.f, 0.f });
    entityManager.spawnGema(xpTexture, { -200.f, 0.f} );

    hud = new HUD(personaje);


    gameOverText.setFont(hudFont);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(80);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setOutlineColor(sf::Color::Black);
    gameOverText.setOutlineThickness(4.f);
    sf::FloatRect boundsGO = gameOverText.getLocalBounds();
    gameOverText.setOrigin(boundsGO.width / 2.f, boundsGO.height / 2.f);
    gameOverText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f - 40.f);

    salirText.setFont(hudFont);
    salirText.setString("ESC para salir");
    salirText.setCharacterSize(24);
    salirText.setFillColor(sf::Color::White);
    sf::FloatRect boundsSalir = salirText.getLocalBounds();
    salirText.setOrigin(boundsSalir.width / 2.f, boundsSalir.height / 2.f);
    salirText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f + 40.f);


    hud = new HUD(personaje);

}

Gameplay::~Gameplay()
{
    delete personaje;
    delete collisionManager;
    delete hud;


}
int Gameplay::run() {
    sf::Clock clock;
    pauseMenu.resetReturnToMainMenu();

    soundManager.setMenuMusicEnabled(false);
    soundManager.setGameplayMusicEnabled(true);
    window.setView(view);  // Aseguramos que se use la vista del juego
    while (window.isOpen()) {
        if (pauseMenu.shouldReturnToMainMenu()) {
            soundManager.setGameplayMusicEnabled(false);
            soundManager.setMenuMusicEnabled(true);
            return 0;
        }

        float deltaTime = clock.restart().asSeconds();
        handleEvents();

        if (!pauseMenu.isPaused()) {
            update(deltaTime);
        }

        render();
    }

    return -1;
}

void Gameplay::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            if (personaje->estaMuerto() && animacionMuerteTerminada)
                window.close();

        }
         pauseMenu.processEvent(event);
    }
}


void Gameplay::update(float deltaTime) {

    if (!personaje->estaMuerto()) {
        chunkManager.updateChunksAround(personaje->getPosition());
        personaje->update(deltaTime, view);
        entityManager.update(deltaTime, view);
        collisionManager->checkCollisions();
        hud->update(deltaTime, tiempoPartida.getElapsedTime());
        chunkManager.updateChunksAround(personaje->getPosition());


    } else if (!animacionMuerteTerminada) {
        personaje->update(deltaTime, view);


        if (personaje->getCurrentFrame() >= personaje->getFrameInicioMuerte() + 4) {
            animacionMuerteTerminada = true;
        }
    }

}

void Gameplay::render() {
    window.clear();

    window.setView(view);
    window.draw(chunkManager);
    window.draw(backgroundMap);
    window.draw(*personaje);
    entityManager.render(window);

    window.setView(window.getDefaultView());
    hud->render(window);
    pauseMenu.render(); //NUEVO

    if (personaje->estaMuerto() && animacionMuerteTerminada) {

        window.draw(gameOverText);
        window.draw(salirText);
}

    window.display();

}
