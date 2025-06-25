#include "Menu.h"
#include "SoundManager.h"
#include <SFML/System.hpp>

Menu::Menu(sf::RenderWindow& window, SoundManager& soundManager, bool hayPartidaEnPausa)
    : window(window), soundManager(soundManager), hayPartidaEnPausa(hayPartidaEnPausa),
      selectedIndex(0), menuState(MAIN_MENU), estadoFinal(0), musicEnabled(true), soundEnabled(true)
{
    if (!backgroundTexture.loadFromFile("Assets/Menus/MainMenu/MenuBackground.png") ||
        !buttonTexture1.loadFromFile("Assets/Menus/MainMenu/MenuButtons.png"))
        throw std::runtime_error("No se pudieron cargar los archivos del menú.");

    background.setTexture(backgroundTexture);
    background.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
    background.setOrigin(backgroundTexture.getSize().x / 2.f, backgroundTexture.getSize().y / 2.f);
    background.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    buttonTexture1.setSmooth(true);
    soundManager.setGameplayMusicEnabled(false);
    soundManager.setMenuMusicEnabled(true);

    loadMainMenu();
}

void Menu::loadMainMenu()
{
    menuState = MAIN_MENU;
    int buttonWidth = 1007 / 5;
    int buttonHeight = 248 / 2;
    float spacing = buttonHeight * 0.8f;

    for (int i = 0; i < 5; ++i)
    {
        buttons[i].setTexture(buttonTexture1);
        buttons[i].setOrigin(buttonWidth / 2.f, buttonHeight / 2.f);
        buttons[i].setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f - spacing * 2 + i * spacing);
        buttons[i].setScale(1.f, 1.f);
        buttons[i].setColor(sf::Color::White);
    }

    buttons[0].setTextureRect(sf::IntRect(buttonWidth * 1 + 17, buttonHeight * 1, buttonWidth - 13, buttonHeight)); // Play
    buttons[1].setTextureRect(sf::IntRect(buttonWidth * 3 - 1, 0, buttonWidth - 10, buttonHeight));                // Continue
    buttons[2].setTextureRect(sf::IntRect(buttonWidth * 4 - 13, 0, buttonWidth - 10, buttonHeight));               // Load Game
    buttons[3].setTextureRect(sf::IntRect(buttonWidth * 3, buttonHeight, buttonWidth - 11, buttonHeight));         // Options
    buttons[4].setTextureRect(sf::IntRect(buttonWidth * 1 + 15, 0, buttonWidth - 7, buttonHeight));                // Exit

    if (!hayPartidaEnPausa)
        buttons[1].setColor(sf::Color(255, 255, 255, 100)); // Desactivado visual

    selectedIndex = 0;
    updateSelection();
}

void Menu::loadOptionsMenu()
{
    menuState = OPTIONS_MENU;

    int buttonWidth = 1007 / 5;
    int buttonHeight = 248 / 2;
    float spacing = buttonHeight * 1.0f;

    for (int i = 0; i < 3; ++i)
    {
        optionButtons[i].setTexture(buttonTexture1);
        optionButtons[i].setOrigin(buttonWidth / 2.f, buttonHeight / 2.f);
        optionButtons[i].setScale(1.f, 1.f);
        optionButtons[i].setColor(sf::Color::White);
        float offsetX = (i == 0) ? -30.f : 0.f;
        optionButtons[i].setPosition(window.getSize().x / 2.f + offsetX, window.getSize().y / 2.f - spacing + i * spacing);
    }

    optionButtons[0].setTextureRect(sf::IntRect(buttonWidth * 0 + 5, buttonHeight, buttonWidth + 12, buttonHeight));  // Music
    optionButtons[1].setTextureRect(sf::IntRect(buttonWidth * 2 + 8, 0, buttonWidth - 10, buttonHeight));             // Sound
    optionButtons[2].setTextureRect(sf::IntRect(buttonWidth * 2 + 9, buttonHeight, buttonWidth - 15, buttonHeight));  // Back

    selectedIndex = 0;
    updateSelection();
    sf::sleep(sf::milliseconds(150));
}

int Menu::run()
{
    while (estadoFinal == 0 && window.isOpen())
    {
        processEvents();
        updateSelection();
        render();
    }
    return estadoFinal;
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
                    if (selectedIndex == 0) // Play
                        estadoFinal = 1;
                    else if (selectedIndex == 1 && hayPartidaEnPausa) // Continue
                        estadoFinal = 2;
                    else if (selectedIndex == 2) // Load Game
                        estadoFinal = 3;
                    else if (selectedIndex == 3) // Options
                        loadOptionsMenu();
                    else if (selectedIndex == 4) // Exit
                    {
                        estadoFinal = -1;
                        window.close();
                    }
                }
                else if (menuState == OPTIONS_MENU)
                {
                    if (selectedIndex == 0) {
                        musicEnabled = !musicEnabled;
                        soundManager.setMenuMusicEnabled(musicEnabled);
                    }
                    else if (selectedIndex == 1) {
                        soundEnabled = !soundEnabled;
                        soundManager.setSoundEffectsEnabled(soundEnabled);
                    }
                    else if (selectedIndex == 2) {
                        loadMainMenu();
                    }
                }
            }
        }
    }
}

void Menu::updateSelection()
{
    if (menuState == MAIN_MENU)
    {
        for (int i = 0; i < 5; ++i)
        {
            if (buttons[i].getScale().x == 0.f || buttons[i].getColor().a == 0)
                continue;

            float scaleFactor = (i == selectedIndex) ? 1.2f : 0.8f;
            buttons[i].setScale(scaleFactor, scaleFactor);
        }
    }
    else if (menuState == OPTIONS_MENU)
    {
        for (int i = 0; i < 3; ++i)
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
        for (int i = 0; i < 5; i++) window.draw(buttons[i]);
    else if (menuState == OPTIONS_MENU)
        for (int i = 0; i < 3; i++) window.draw(optionButtons[i]);

    window.display();
}
