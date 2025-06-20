#pragma once
#include <SFML/Graphics.hpp>
#include "SoundManager.h"

class PauseMenu {
public:
    PauseMenu(sf::RenderWindow& win, SoundManager& sm);
    void processEvent(const sf::Event& event);
    void render();
    void resetReturnToMainMenu();

    bool isPaused() const;
    bool isMusicEnabled() const;
    bool isSoundEnabled() const;
    bool shouldReturnToMainMenu() const;

private:
    sf::RenderWindow& window;
    sf::Texture hudTexture;
    sf::Texture menuPrincipalTexture;

    SoundManager& soundManager;

    sf::Sprite btnMainMenu;
    sf::Sprite btnMenu;
    sf::Sprite btnSound;
    sf::Sprite btnMusic;
    sf::Sprite btnPause;

    int iconW, iconH;

    bool menuOpen;
    bool soundOn;
    bool musicOn;
    bool returnToMainMenu = false;

    sf::IntRect sonidoOnRect, sonidoOffRect;
    sf::IntRect musicaOnRect, musicaOffRect;
    sf::IntRect menuClosedRect, menuOpenRect;
    sf::IntRect playRect, pauseRect;

    void updateIcons();
};
