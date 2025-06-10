#include "Menu.h"

Menu::Menu(sf::RenderWindow& window) : window(window), selectedIndex(0) {
    if (!backgroundTexture.loadFromFile("Assets/Menus/MainMenu/MenuBackground.png") ||
        !buttonTexture.loadFromFile("Assets/Menus/MainMenu/MenuButtons.png")) {
        throw std::runtime_error("No se pudieron cargar las imágenes.");
    }

    //  Configurar imagen de fondo centrada y ajustada al tamaño de la ventana
    background.setTexture(backgroundTexture);
    background.setOrigin(backgroundTexture.getSize().x / 2, backgroundTexture.getSize().y / 2);
    background.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    background.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    //  Dimensiones calculadas para spritesheet (5 columnas x 2 filas)
    int buttonWidth = 1318 / 5;  // 263 px
    int buttonHeight = 189 / 2;  // 94.5 px

    //  Asignar botones con sus posiciones exactas en la spritesheet
    buttons[0].setTexture(buttonTexture);
    buttons[0].setTextureRect(sf::IntRect(0, 0, buttonWidth, buttonHeight)); // "Play" (Col 1, Fila 1)
    buttons[1].setTexture(buttonTexture);
    buttons[1].setTextureRect(sf::IntRect(buttonWidth * 3, 0, buttonWidth, buttonHeight)); // "Options" (Col 4, Fila 1)
    buttons[2].setTexture(buttonTexture);
    buttons[2].setTextureRect(sf::IntRect(buttonWidth * 4, 0, buttonWidth, buttonHeight)); // "Exit" (Col 5, Fila 1)

    //  Posicionar botones en el centro
    for (int i = 0; i < 3; i++) {
        buttons[i].setOrigin(buttonWidth / 2, buttonHeight / 2);
        buttons[i].setPosition(window.getSize().x / 2, window.getSize().y / 2 - 100 + i * 100);
    }
}

int Menu::run() {
    while (window.isOpen()) {
        processEvents();
        updateSelection();
        render();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            if (selectedIndex == 2) { //  Si selecciona "Exit", cerrar el juego
                window.close();
            }
            return selectedIndex;
        }
    }
    return -1;
}

void Menu::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::W && selectedIndex > 0) selectedIndex--;
            if (event.key.code == sf::Keyboard::S && selectedIndex < 2) selectedIndex++;
        }
    }
}

void Menu::updateSelection() {
    for (int i = 0; i < 3; i++) {
        float scaleFactor = (i == selectedIndex) ? 1.2f : 1.0f;  //  Definir el tamaño resaltado
        buttons[i].setScale(scaleFactor, scaleFactor);  //  Aplicar en X e Y
    }
}
void Menu::render() {
    window.clear();
    window.draw(background);
    for (auto& button : buttons) window.draw(button);
    window.display();
}
