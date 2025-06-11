#include "Gameplay.h"
#include "Menu.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 650), "Survivor - Men�");

    Menu menu(window);
    int selection = menu.run();  /// Espera la opci�n del men�

    if (selection == 0) {  /// "Play"
        Gameplay game;
        game.run();  /// Inicia el juego
    } else if (selection == 4) {  /// "Exit"
        window.close();  /// Cierra la aplicaci�n
    }

    return 0;
}
