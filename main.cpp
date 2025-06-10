#include "Menu.h"
#include "Gameplay.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 650), "Survivor - Menú");

    Menu menu(window);
    int selection = menu.run();  /// Espera la opción del menú

    if (selection == 0) {  /// Si el usuario presiona "Play"
        Gameplay game;
        game.run();  /// Inicia el juego solo si se selecciona "Play"
    }

    return 0;
}
