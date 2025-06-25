#include <SFML/Graphics.hpp>
#include <memory>
#include "Menu.h"
#include "Gameplay.h"
#include "SoundManager.h"
#include "iostream"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 650), "Survivor - Menú");
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
                std::cin.get();  // ← Espera input y evita qaue cierre la consola
                estado = 0;
            }
            break;
        }


        case 2:    // Continuar
        {
            if (partidaGuardada)
                estado = partidaGuardada->run();
            else
                estado = 0;  // fallback al menú si no hay partida
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
