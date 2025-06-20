#include <SFML/Graphics.hpp>
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
            sf::RenderWindow window(sf::VideoMode(1000, 650), "Survivor - Menú");
            Menu menu(window, soundManager, hayPartidaEnPausa);
            estado = menu.run();  // 1 = nueva partida, 2 = continuar, -1 = salir
        }

        if (estado == 1)
        {
            partidaGuardada = std::make_unique<Gameplay>(soundManager);
            estado = partidaGuardada->run();
            hayPartidaEnPausa = true;
        }

        if (estado == 2 && partidaGuardada)
        {
            estado = partidaGuardada->run();
        }
    }

    return 0;
}
