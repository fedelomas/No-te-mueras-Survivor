#pragma once
#include <SFML/Graphics.hpp>// Este ya incluye sf::Drawable y sf::Transformable.
#include <SFML/System/Vector2.hpp> // plantilla de clase para manipular vectores bidimensionales.


class Personaje : public sf::Drawable {
public:
    Personaje(sf::Texture& texture); // Constructor con referencia a la textura
    void Movimiento(sf::View& view); // Movimiento del personaje basado en la vista
    void update(sf::RenderWindow& window, sf::View& view); // Actualizar posición y lógica
    sf::Clock clock; // Reloj para medir el tiempo
    sf::Time frameTime = sf::seconds(0.1f); // Tiempo entre frames (0.1s = más lento)

    sf::Vector2f GetPosition(); // Obtener posición del personaje

private:
    sf::Sprite sprite; // Representación gráfica del personaje
    float speed = 5.0f;

    //  Dirección inicial del personaje (hacia la derecha)
    sf::Vector2f lastDirection = {1.f, 0.f};

    ///  Parámetros de la animación del soldado
    int frameWidth = 120;   // Ancho de cada frame
    int frameHeight = 80;   // Alto de cada frame
    int currentFrame = 0;   // Índice del frame actual (0 a 9)
    int totalFrames = 10;   // Número total de frames

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override; // Dibujar en pantalla
    void updateAnimation();
};

