#pragma once
#include <SFML/Graphics.hpp>
#include "SoundManager.h"

class Menu {
public:
    Menu(sf::RenderWindow& window, SoundManager& soundManager, bool hayPartidaEnPausa);
    int run();

private:
    void loadMainMenu();
    void loadOptionsMenu();
    void updateSelection();
    void processEvents();
    void render();
    void scaleButtons(float scaleFactor);

    sf::RenderWindow& window;
    SoundManager& soundManager;

    sf::Texture backgroundTexture;
    sf::Texture buttonTexture1;
    sf::Sprite background;

    sf::Sprite buttons[5];        // Play, Continue, Load Game, Options, Exit
    sf::Sprite optionButtons[3];  // Music, Sound, Back

    int selectedIndex = 0;
    int estadoFinal = 0;

    bool hayPartidaEnPausa = false;
    bool musicEnabled = true;
    bool soundEnabled = true;

    enum MenuState { MAIN_MENU, OPTIONS_MENU };
    MenuState menuState = MAIN_MENU;
};
