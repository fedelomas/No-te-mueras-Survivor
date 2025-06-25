#pragma once
#include <SFML/Graphics.hpp>
#include "SoundManager.h"

class Menu {
public:
    Menu(sf::RenderWindow& window, SoundManager& soundManager);
    int run();
    void processEvents();
    void render();
    void loadOptionsMenu();
    void loadMainMenu();
    void updateSelection();
    void scaleButtons(float scaleFactor);
    void setSoundEffectsEnabled(bool enabled);

private:
    sf::RenderWindow& window;
    sf::Texture backgroundTexture;
    sf::Texture buttonTexture1;
    sf::Sprite background;
    sf::Sprite buttons[5];  // Botones del menú principal
    sf::Sprite optionButtons[3];  // Botones del menú de opciones

    bool musicEnabled = true;  // Estado de la música (activada por defecto)
    bool soundEnabled = true;  // Estado de los efectos de sonido (activados por defecto)

    int selectedIndex;
    enum MenuState { MAIN_MENU, OPTIONS_MENU };
    MenuState menuState = MAIN_MENU;


    SoundManager& soundManager;  // Manejo de sonidos
};

/*
#pragma once
#include <SFML/Graphics.hpp>
#include "SoundManager.h"

class Menu {
public:
    Menu(sf::RenderWindow& window, SoundManager& soundManager, bool hayPartidaEnPausa);
    int run();
    void processEvents();
    void render();
    void loadOptionsMenu();
    void loadMainMenu();
    void updateSelection();
    void scaleButtons(float scaleFactor);
    void setSoundEffectsEnabled(bool enabled);

private:
    sf::RenderWindow& window;
    sf::Texture backgroundTexture;
    sf::Texture buttonTexture1;
    sf::Sprite background;
    sf::Sprite buttons[5];  // Botones del menú principal
    sf::Sprite optionButtons[3];  // Botones del menú de opciones

    bool musicEnabled = true;  // Estado de la música (activada por defecto)
    bool soundEnabled = true;  // Estado de los efectos de sonido (activados por defecto)
    bool hayPartidaEnPausa;

    int selectedIndex;
    int estadoFinal = 0;
    enum MenuState { MAIN_MENU, OPTIONS_MENU };
    MenuState menuState = MAIN_MENU;


    SoundManager& soundManager;
};*/
