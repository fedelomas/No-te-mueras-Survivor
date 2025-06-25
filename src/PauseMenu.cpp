#include "PauseMenu.h"
#include <stdexcept>
#include "iostream"

using namespace std;

PauseMenu::PauseMenu(sf::RenderWindow& win, SoundManager& sm): window(win), soundManager(sm), menuOpen(false), soundOn(true), musicOn(true)
{
    if (!hudTexture.loadFromFile("Assets/Menus/MenuIcons/IconsButtons.png"))
        throw std::runtime_error("No se pudo cargar IconsButtons.png");
    if (!menuPrincipalTexture.loadFromFile("Assets/Menus/MenuIcons/IconsButtons2.png"))
        throw std::runtime_error("No se pudo cargar IconsButtons2.png");

    btnMainMenu.setTexture(menuPrincipalTexture);
    btnMainMenu.setTextureRect(sf::IntRect(0, 0, 1920, 1920));
    btnMainMenu.setScale(0.07f, 0.07f); // Escalado a proporci�n similar a los otros �conos

    iconW = 631 / 4;
    iconH = 395 / 2;

// �conos por posici�n (columna x fila) � con ajustes personalizados
    sonidoOnRect    = {0 * iconW -10, 0 * iconH + 1, iconW -15, iconH - 2}; // margen ajustado
    sonidoOffRect   = {0 * iconW -10, 1 * iconH -10, iconW -15, iconH + 5};

    musicaOnRect    = {1 * iconW - 25, 0 * iconH, iconW +10, iconH - 1};
    musicaOffRect   = {1 * iconW - 25, 1 * iconH -15, iconW +10, iconH +7};

    menuClosedRect  = {2 * iconW, 0 * iconH, iconW, iconH};
    menuOpenRect    = {2 * iconW, 1 * iconH, iconW, iconH};

    playRect        = {3 * iconW + 1, 0 * iconH + 1, iconW - 2, iconH - 2};
    pauseRect       = {3 * iconW + 1, 1 * iconH + 1, iconW - 2, iconH - 2};

    // Sprites
    btnMenu.setTexture(hudTexture);
    btnSound.setTexture(hudTexture);
    btnMusic.setTexture(hudTexture);
    btnPause.setTexture(hudTexture);

    updateIcons();

    // Posicionar el bot�n hamburguesa arriba a la derecha
    btnMenu.setPosition(window.getSize().x - iconW - 20.f, 20.f);
}

void PauseMenu::updateIcons()
{
    btnSound.setTextureRect(soundOn ? sonidoOnRect : sonidoOffRect);
    btnMusic.setTextureRect(musicOn ? musicaOnRect : musicaOffRect);
    btnMenu.setTextureRect(menuOpen ? menuOpenRect : menuClosedRect);
    btnPause.setTextureRect(menuOpen ? pauseRect : playRect);

    // Escalado uniforme
    btnSound.setScale(0.7f, 0.7f);
    btnMusic.setScale(0.7f, 0.7f);
    btnPause.setScale(0.7f, 0.7f);
}

void PauseMenu::processEvent(const sf::Event& event)
{
    sf::View originalView = window.getView();
    window.setView(window.getDefaultView());
    sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    window.setView(originalView);

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        if (btnMenu.getGlobalBounds().contains(mouse))
        {
            menuOpen = !menuOpen;
            updateIcons();
        }
        else if (menuOpen && btnSound.getGlobalBounds().contains(mouse))
        {
            soundOn = !soundOn;
            soundManager.setSoundEffectsEnabled(soundOn);
            soundManager.playSoundEffect("select");
            updateIcons();
        }
        else if (menuOpen && btnMusic.getGlobalBounds().contains(mouse))
        {
            musicOn = !musicOn;
            std::cout << "Clic en bot�n de m�sica. Nuevo estado: " << musicOn << std::endl;
            soundManager.setGameplayMusicEnabled(musicOn);
            soundManager.playSoundEffect("select");
            updateIcons();
        }
        else if (menuOpen && btnMainMenu.getGlobalBounds().contains(mouse))
        {
            returnToMainMenu = true;
            soundManager.playSoundEffect("select");
            updateIcons();
        }
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
    {
        menuOpen = !menuOpen;
        updateIcons();
    }
}

void PauseMenu::render()
{
    // Vista fija de pantalla
    sf::View originalView = window.getView();
    window.setView(window.getDefaultView());

    // Dibujar men� hamburguesa (siempre visible)
    window.draw(btnMenu);

    if (menuOpen)
    {
        const float spacing = iconW * 0.6f;  // espacio horizontal entre �conos
        const float totalWidth = 3 * iconW * 0.7f + 2 * spacing;
        const float startX = (window.getSize().x - totalWidth) / 2.f;
        const float posY = window.getSize().y / 2.f - iconH * 0.35f;

        // Fondo com�n
        sf::RectangleShape bg;
        bg.setSize(sf::Vector2f(iconW * 0.7f, iconH * 0.7f));
        bg.setFillColor(sf::Color(0, 0, 0, 0));

        // Bot�n Sonido
        btnSound.setScale(0.7f, 0.7f);
        btnSound.setPosition(startX + 0 * (iconW * 0.7f + spacing), posY);
        bg.setPosition(btnSound.getPosition());
        window.draw(bg);
        window.draw(btnSound);

        // Bot�n M�sica
        btnMusic.setScale(0.7f, 0.7f);
        btnMusic.setPosition(startX + 1 * (iconW * 0.7f + spacing), posY);
        bg.setPosition(btnMusic.getPosition());
        window.draw(bg);
        window.draw(btnMusic);

        // Bot�n Pausa
        btnMainMenu.setPosition(startX + 2 * (iconW * 0.7f + spacing), posY);
        bg.setPosition(btnMainMenu.getPosition());
        window.draw(bg);
        window.draw(btnMainMenu);
    }

    // Restaurar vista del juego
    window.setView(originalView);
}

bool PauseMenu::isPaused() const
{
    return menuOpen;
}
bool PauseMenu::isMusicEnabled() const
{
    return musicOn;
}
bool PauseMenu::isSoundEnabled() const
{
    return soundOn;
}

bool PauseMenu::shouldReturnToMainMenu() const
{
    return returnToMainMenu;
}

void PauseMenu::resetReturnToMainMenu()
{
    returnToMainMenu = false;
}
