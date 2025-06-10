#pragma once
#include <SFML/Graphics.hpp>

class Menu {
public:
    Menu(sf::RenderWindow& window);
    int run();  /// Ejecuta el men� y devuelve la opci�n seleccionada

private:
    void processEvents();  ///  Maneja eventos del teclado
    void updateSelection();  ///  Resalta el bot�n seleccionado
    void render();  /// Dibuja el men� en pantalla

    sf::RenderWindow& window;
    sf::Texture backgroundTexture;
    sf::Texture buttonTexture;
    sf::Sprite background;
    sf::Sprite buttons[3];  // Tres botones: Play, Options, Exit
    int selectedIndex = 0;  /// �ndice del bot�n seleccionado
};
