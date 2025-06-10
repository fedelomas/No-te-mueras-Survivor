#pragma once
#include <SFML/Graphics.hpp>

class Menu {
public:
    Menu(sf::RenderWindow& window);
    int run();  /// Ejecuta el menú y devuelve la opción seleccionada

private:
    void processEvents();  ///  Maneja eventos del teclado
    void updateSelection();  ///  Resalta el botón seleccionado
    void render();  /// Dibuja el menú en pantalla

    sf::RenderWindow& window;
    sf::Texture backgroundTexture;
    sf::Texture buttonTexture;
    sf::Sprite background;
    sf::Sprite buttons[3];  // Tres botones: Play, Options, Exit
    int selectedIndex = 0;  /// Índice del botón seleccionado
};
