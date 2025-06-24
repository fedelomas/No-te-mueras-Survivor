#include "Gameplay.h"
#include "Menu.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 650), "Survivor - Menú");

    while (window.isOpen()) {
        Menu menu(window);
        int selection = menu.run();  //  Espera la opción del menú

        if (selection == 0) {  // "Play"
            Gameplay game;
            game.run();  // Inicia el juego
            break;
        } else if (selection == 4) {  // "Options"
            Menu optionsMenu(window);  // Cargar menú de opciones
            int optionsSelection = optionsMenu.run();  // Ejecutar menú de opciones

            if (optionsSelection == 2) {  // "Back" en opciones
                continue;  // Volver al menú principal
            }
        } else if (selection == -1) {  // "Exit"
            window.close();  // Cierra la aplicación
        }
    }

    return 0;
}
