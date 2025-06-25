#include "Gameplay.h"
#include "Menu.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 650), "Survivor - Menú");
    SoundManager soundManager;


    while (window.isOpen()) {
        Menu menu(window, soundManager);
        int selection = menu.run();  //  Espera la opción del menú

        if (selection == 0) {  // "Play"
            Gameplay game(window, soundManager);
            game.run(); // Inicia el juego
            soundManager.setGameplayMusicEnabled(false);
            soundManager.setMenuMusicEnabled(true);

            continue;
        } else if (selection == 4) {  // "Options"
            Menu optionsMenu(window, soundManager);  // Cargar menú de opciones
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

/*
#include <memory>
#include "Menu.h"
#include "Gameplay.h"
#include "SoundManager.h"

int main()
{
    int estado = 0;
    bool hayPartidaEnPausa = false;
    std::unique_ptr<Gameplay> partidaGuardada;
    SoundManager soundManager;

    while (estado != -1)
    {
        if (estado == 0)
        {
    sf::RenderWindow window(sf::VideoMode(1000, 650), "Survivor - Menu");
            Menu menu(window, soundManager, hayPartidaEnPausa);
            estado = menu.run();  // 1 = nueva partida, 2 = continuar, -1 = salir
        }

        if (estado == 1)
        {
            sf::RenderWindow window;
            partidaGuardada = std::make_unique<Gameplay>(window, soundManager, hayPartidaEnPausa);
            estado = partidaGuardada->run();
            hayPartidaEnPausa = true;
        }






        if (estado == 2 && partidaGuardada)
        {
            estado = partidaGuardada->run();


        }
    }
}
*/
