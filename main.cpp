<<<<<<< Updated upstream
#include "Gameplay.h"
#include "Menu.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 650), "Survivor - Men˙");
    SoundManager soundManager;


    while (window.isOpen()) {
        Menu menu(window, soundManager);
        int selection = menu.run();  //  Espera la opciÛn del men˙

        if (selection == 0) {  // "Play"
            Gameplay game(window, soundManager);
            game.run(); // Inicia el juego
            soundManager.setGameplayMusicEnabled(false);
            soundManager.setMenuMusicEnabled(true);

            continue;
        } else if (selection == 4) {  // "Options"
            Menu optionsMenu(window, soundManager);  // Cargar men˙ de opciones
            int optionsSelection = optionsMenu.run();  // Ejecutar men˙ de opciones

            if (optionsSelection == 2) {  // "Back" en opciones
                continue;  // Volver al men˙ principal
            }
        } else if (selection == -1) {  // "Exit"
            window.close();  // Cierra la aplicaciÛn
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
=======
#include <SFML/Graphics.hpp>
#include <memory>
#include "Menu.h"
#include "Gameplay.h"
#include "SoundManager.h"
#include "iostream"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 650), "Survivor - Men√∫");
    SoundManager soundManager;

    std::unique_ptr<Gameplay> partidaGuardada;
    bool hayPartidaEnPausa = false;
    int estado = 0;

    while (window.isOpen() && estado != -1)
    {
        switch (estado)
        {
        case 0:
        {
            Menu menu(window, soundManager, hayPartidaEnPausa);
            estado = menu.run();  // espera Play / Continue / Exit
            break;
        }

        case 1:
        {
            try
            {
                partidaGuardada = std::make_unique<Gameplay>(window, soundManager);
                estado = partidaGuardada->run();
                hayPartidaEnPausa = true;
            }
            catch (const std::exception& e)
            {
                std::cerr << "Error al iniciar Gameplay: " << e.what() << "\n";
                std::cin.get();  // ‚Üê Espera input y evita qaue cierre la consola
                estado = 0;
            }
            break;
        }


        case 2:    // Continuar
        {
            if (partidaGuardada)
                estado = partidaGuardada->run();
            else
                estado = 0;  // fallback al men√∫ si no hay partida
            break;
        }

        case 3:
        {
            // futuro: cargar partida
            estado = 0;
            break;
        }

        default:
            estado = -1;
            break;
        }
    }

    return 0;
}
>>>>>>> Stashed changes
