#include "Menu.h"
#include "SoundManager.h"

Menu::Menu(sf::RenderWindow& window) : window(window), selectedIndex(0) {
    if (!backgroundTexture.loadFromFile("Assets/Menus/MainMenu/MenuBackground.png") ||
        !buttonTexture1.loadFromFile("Assets/Menus/MainMenu/MenuButtons.png")) {
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
    soundManager.playMenuMusic();

    // Dimensiones exactas de cada botón según la imagen
    int buttonWidth = 1007 / 5;  // 201 px
    int buttonHeight = 248 / 2;  // 124 px

    // Asignar textura a los botones
    for (int i = 0; i < 5; i++) {
        buttons[i].setTexture(buttonTexture1);
    }

    // Aplicar recortes precisos
    buttons[0].setTextureRect(sf::IntRect(buttonWidth * 1 + 17, buttonHeight * 1, buttonWidth - 13, buttonHeight)); // "Play"
    buttons[1].setTextureRect(sf::IntRect(buttonWidth * 3 - 1, buttonHeight * 0, buttonWidth - 10, buttonHeight));  // "Continue"
    buttons[2].setTextureRect(sf::IntRect(buttonWidth * 4 - 13, buttonHeight * 0, buttonWidth - 10, buttonHeight)); // "Load Game"
    buttons[3].setTextureRect(sf::IntRect(buttonWidth * 3, buttonHeight * 1, buttonWidth - 11, buttonHeight));      // "Options"
    buttons[4].setTextureRect(sf::IntRect(buttonWidth * 1 + 15, buttonHeight * 0, buttonWidth - 7, buttonHeight));  // "Exit"

    // Reducir tamaño de los botones
    scaleButtons(0.8f);

    // Centrar cada botón correctamente en la pantalla
    float spacing = buttonHeight * 0.8;
    for (int i = 0; i < 5; i++) {
        buttons[i].setOrigin(buttonWidth / 2, buttonHeight / 2);
        buttons[i].setPosition(window.getSize().x / 2, window.getSize().y / 2 - (spacing * 2) + i * spacing);
    }
}

void Menu::scaleButtons(float scaleFactor) {
    for (int i = 0; i < 5; i++) {
        buttons[i].setScale(scaleFactor, scaleFactor);  // Aplica la escala a todos los botones
    }
}

void Menu::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::W && selectedIndex > 0) {
                selectedIndex--;
                soundManager.playSoundEffect("navigate");
            }
            if (event.key.code == sf::Keyboard::S && selectedIndex < 4) {
                selectedIndex++;
                soundManager.playSoundEffect("navigate");
            }
        }
    }
}

int Menu::run() {
    while (window.isOpen()) {
        processEvents();
        updateSelection();
        render();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            soundManager.playSoundEffect("select");
            soundManager.stopMenuMusic();

            sf::sleep(sf::milliseconds(150));

            if (selectedIndex == 4) {
                window.close();
            }

            return selectedIndex;
        }
    }
    return -1;
}

void Menu::updateSelection() {
    for (int i = 0; i < 5; i++) {
        float scaleFactor = (i == selectedIndex) ? 1.2f : 0.8f;
        buttons[i].setScale(scaleFactor, scaleFactor);
    }
}

void Menu::render() {
    window.clear();
    window.draw(background);
    for (auto& button : buttons) window.draw(button);
    window.display();
}
