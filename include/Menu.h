#pragma once
#include <SFML/Graphics.hpp>
#include "SoundManager.h"

class Menu {
public:
    Menu(sf::RenderWindow& window);
    int run();  // Ejecuta el menú y devuelve la opción seleccionada

private:
    void processEvents();  //  Maneja eventos del teclado
    void updateSelection();  //  Resalta el botón seleccionado
    void render();  // Dibuja el menú en pantalla
    void scaleButtons(float scaleFactor);

    sf::RenderWindow& window;
    sf::Texture backgroundTexture;
    sf::Texture buttonTexture1;
    sf::Sprite background;
    sf::Sprite buttons[5];
    int selectedIndex = 0;

    SoundManager soundManager;  // Manejo de sonidos
};

