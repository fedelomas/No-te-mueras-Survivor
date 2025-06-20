#include "Menu.h"
#include "SoundManager.h"

Menu::Menu(sf::RenderWindow& window, SoundManager& soundManager, bool hayPartidaEnPausa)
    : window(window), soundManager(soundManager), hayPartidaEnPausa(hayPartidaEnPausa),
      selectedIndex(0), menuState(MAIN_MENU)
{


    if (!backgroundTexture.loadFromFile("Assets/Menus/MainMenu/MenuBackground.png") ||
            !buttonTexture1.loadFromFile("Assets/Menus/MainMenu/MenuButtons.png"))
    {
        throw std::runtime_error("No se pudieron cargar las imágenes.");
    }

    // Activar suavizado en la textura
    buttonTexture1.setSmooth(true);

    // Configurar imagen de fondo centrada
    background.setTexture(backgroundTexture);
    background.setOrigin(backgroundTexture.getSize().x / 2, backgroundTexture.getSize().y / 2);
    background.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    background.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    // Iniciar música del menú
    soundManager.setGameplayMusicEnabled(false);   // Detener música del gameplay
    soundManager.setMenuMusicEnabled(true);        // Reproducir música del menú

    // Dimensiones exactas de cada botón según la imagen
    int buttonWidth = 1007 / 5;  // 201 px
    int buttonHeight = 248 / 2;  // 124 px

    // Inicializar botones del menú principal
    for (int i = 0; i < 5; i++)
    {
        buttons[i].setTexture(buttonTexture1);
    }

    // Aplicar recortes precisos para el menú principal
    buttons[0].setTextureRect(sf::IntRect(buttonWidth * 1 + 17, buttonHeight * 1, buttonWidth - 13, buttonHeight)); // "Play"
    buttons[1].setTextureRect(sf::IntRect(buttonWidth * 3 - 1, buttonHeight * 0, buttonWidth - 10, buttonHeight));  // "Continue"
    buttons[2].setTextureRect(sf::IntRect(buttonWidth * 4 - 13, buttonHeight * 0, buttonWidth - 10, buttonHeight)); // "Load Game"
    buttons[3].setTextureRect(sf::IntRect(buttonWidth * 3, buttonHeight * 1, buttonWidth - 11, buttonHeight));      // "Options"
    buttons[4].setTextureRect(sf::IntRect(buttonWidth * 1 + 15, buttonHeight * 0, buttonWidth - 7, buttonHeight));  // "Exit"

    // Inicializar botones del menú de opciones
    for (int i = 0; i < 3; i++)
    {
        optionButtons[i].setTexture(buttonTexture1);
    }

    // Aplicar recortes para el menú de opciones
    optionButtons[0].setTextureRect(sf::IntRect(buttonWidth * 0, buttonHeight * 1, buttonWidth, buttonHeight));  // "Audio"
    optionButtons[1].setTextureRect(sf::IntRect(buttonWidth * 1, buttonHeight * 1, buttonWidth, buttonHeight));  // "Video"
    optionButtons[2].setTextureRect(sf::IntRect(buttonWidth * 2, buttonHeight * 1, buttonWidth, buttonHeight));  // "Back"

    // Reducir tamaño de los botones
    scaleButtons(0.8f);

    // Centrar cada botón correctamente en la pantalla
    float spacing = buttonHeight * 0.8;
    for (int i = 0; i < 5; i++)
    {
        buttons[i].setOrigin(buttonWidth / 2, buttonHeight / 2);
        buttons[i].setPosition(window.getSize().x / 2, window.getSize().y / 2 - (spacing * 2) + i * spacing);
    }

    for (int i = 0; i < 3; i++)
    {
        optionButtons[i].setOrigin(buttonWidth / 2, buttonHeight / 2);
        optionButtons[i].setPosition(window.getSize().x / 2, window.getSize().y / 2 - spacing + i * spacing);
    }
    loadMainMenu();
}

void Menu::scaleButtons(float scaleFactor)
{
    for (int i = 0; i < 5; i++)
    {
        buttons[i].setScale(scaleFactor, scaleFactor);  // Aplica la escala a todos los botones
    }
}

void Menu::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            estadoFinal = -1;
            window.close();
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::W && selectedIndex > 0)
            {
                selectedIndex--;
                if (soundEnabled) soundManager.playSoundEffect("navigate");
            }

            if (event.key.code == sf::Keyboard::S && selectedIndex < (menuState == MAIN_MENU ? 4 : 2))
            {
                selectedIndex++;
                if (soundEnabled) soundManager.playSoundEffect("navigate");
            }

            if (event.key.code == sf::Keyboard::Enter)
            {
                if (soundEnabled) soundManager.playSoundEffect("select");

                if (menuState == MAIN_MENU)
                {
                    if (selectedIndex == 0)  // Play
                    {
                        soundManager.setMenuMusicEnabled(false);
                        estadoFinal = 1;
                        window.close();
                    }
                    else if (selectedIndex == 1)  // Continue
                    {
                        if (!hayPartidaEnPausa) return;

                        soundManager.setMenuMusicEnabled(false);
                        estadoFinal = 2;
                        window.close();
                    }
                    else if (selectedIndex == 3)  // Options
                    {
                        loadOptionsMenu();
                    }
                    else if (selectedIndex == 4)  // Exit
                    {
                        estadoFinal = -1;
                        window.close();
                    }
                }
                else if (menuState == OPTIONS_MENU)
                {
                    if (selectedIndex == 0)  // Music
                    {
                        musicEnabled = !musicEnabled;
                        soundManager.setMenuMusicEnabled(musicEnabled);
                    }
                    else if (selectedIndex == 1)  // Sound
                    {
                        soundEnabled = !soundEnabled;
                        soundManager.setSoundEffectsEnabled(soundEnabled);
                    }
                    else if (selectedIndex == 2)  // Back
                    {
                        loadMainMenu();
                        selectedIndex = 0;
                        updateSelection();
                    }
                }
            }
        }
    }
}

int Menu::run()
{
    while (window.isOpen())
    {
        processEvents();
        updateSelection();
        render();

    }

    return estadoFinal;
}

void Menu::updateSelection()
{
    if (menuState == MAIN_MENU)
    {
        for (int i = 0; i < 5; i++)
        {
            // Si el botón está oculto (escala en 0 o completamente transparente), no lo toques
            if (buttons[i].getScale().x == 0.f || buttons[i].getColor().a == 0)
                continue;

            float scaleFactor = (i == selectedIndex) ? 1.2f : 0.8f;
            buttons[i].setScale(scaleFactor, scaleFactor);
        }
    }
    else if (menuState == OPTIONS_MENU)
    {
        for (int i = 0; i < 3; i++)
        {
            float scaleFactor = (i == selectedIndex) ? 1.2f : 0.8f;
            optionButtons[i].setScale(scaleFactor, scaleFactor);
        }
    }
}

void Menu::render()
{
    window.clear();
    window.draw(background);

    if (menuState == MAIN_MENU)
    {
        for (int i = 0; i < 5; i++) window.draw(buttons[i]);  // Dibujar botones del menú principal
    }
    else if (menuState == OPTIONS_MENU)
    {
        for (int i = 0; i < 3; i++) window.draw(optionButtons[i]);  // Dibujar botones del menú de opciones
    }

    window.display();
}

void Menu::loadOptionsMenu()
{
    menuState = OPTIONS_MENU;

    int buttonWidth = 1007 / 5;
    int buttonHeight = 248 / 2;

    // Configurar botones de opciones
    optionButtons[0].setTexture(buttonTexture1);
    optionButtons[0].setTextureRect(sf::IntRect(buttonWidth * 0 + 5, buttonHeight * 1, buttonWidth + 12, buttonHeight));  // "Music"

    optionButtons[1].setTexture(buttonTexture1);
    optionButtons[1].setTextureRect(sf::IntRect(buttonWidth * 2 + 8, buttonHeight * 0, buttonWidth - 10, buttonHeight));  // "Sound"

    optionButtons[2].setTexture(buttonTexture1);
    optionButtons[2].setTextureRect(sf::IntRect(buttonWidth * 2 + 9, buttonHeight * 1, buttonWidth - 15, buttonHeight));  // "Back"

    float spacing = buttonHeight * 1.0f;
    for (int i = 0; i < 3; i++)
    {
        optionButtons[i].setOrigin(buttonWidth / 2, buttonHeight / 2);

        float offsetX = (i == 0) ? -30.f : 0.f;
        optionButtons[i].setPosition(window.getSize().x / 2 + offsetX, window.getSize().y / 2 - spacing + i * spacing);

        optionButtons[i].setScale(1.f, 1.f);  // Asegurar que estén visibles
        optionButtons[i].setColor(sf::Color::White);  // Restaurar color por si venís de otro menú
    }

    selectedIndex = 0;
    updateSelection();
    sf::sleep(sf::milliseconds(150));  // Evitar doble Enter al volver
}

void Menu::loadMainMenu()
{
    menuState = MAIN_MENU;

    int buttonWidth = 1007 / 5;
    int buttonHeight = 248 / 2;

    // Restaurar recortes de los botones del menú principal
    buttons[0].setTextureRect(sf::IntRect(buttonWidth * 1 + 17, buttonHeight * 1, buttonWidth - 13, buttonHeight)); // "Play"
    buttons[1].setTextureRect(sf::IntRect(buttonWidth * 3 - 1, buttonHeight * 0, buttonWidth - 10, buttonHeight));  // "Continue"
    buttons[2].setTextureRect(sf::IntRect(buttonWidth * 4 - 13, buttonHeight * 0, buttonWidth - 10, buttonHeight)); // "Load Game"
    buttons[3].setTextureRect(sf::IntRect(buttonWidth * 3, buttonHeight * 1, buttonWidth - 11, buttonHeight));      // "Options"
    buttons[4].setTextureRect(sf::IntRect(buttonWidth * 1 + 15, buttonHeight * 0, buttonWidth - 7, buttonHeight));  // "Exit"

    float spacing = buttonHeight * 0.8;
    for (int i = 0; i < 5; i++)
    {
        buttons[i].setOrigin(buttonWidth / 2, buttonHeight / 2);
        buttons[i].setPosition(window.getSize().x / 2, window.getSize().y / 2 - (spacing * 2) + i * spacing);
        buttons[i].setScale(1.f, 1.f);  // Restaurar escala por si venís de opciones
        buttons[i].setColor(sf::Color::White);  // Restaurar color
    }

    if (!hayPartidaEnPausa)
    {
        buttons[1].setColor(sf::Color(255, 255, 255, 100));  // Grisado
    }
    else
    {
        buttons[1].setColor(sf::Color::White);  // Color normal si hay partida
    }

    selectedIndex = 0;
    updateSelection();
}
