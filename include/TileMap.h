#pragma once
#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable {
public:
    // Constructor para inicializar el puntero a nullptr
    TileMap() : m_tilesetPtr(nullptr) {}

    // Sobrecargo load para que cargue una textura ya cargada en memoria
    bool load(sf::Vector2u tileSize,
              const std::vector<int>& tiles,
              unsigned int width,
              unsigned int height,
              const sf::Texture& tileset); // Pasa la textura por referencia constante

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::VertexArray m_vertices;
    const sf::Texture* m_tilesetPtr;
};

