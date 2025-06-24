/*#pragma once

#include <SFML/Graphics.hpp>
#include "TileMap.h" // Usamos TileMap internamente

class Chunk : public sf::Drawable, public sf::Transformable {
public:
    Chunk();
    Chunk(int chunkX, int chunkY, unsigned int tileSize, unsigned int chunkSize);

    bool generate(const sf::Texture& tileset); // genera los tiles (puede ser aleatorio)
    sf::Vector2i getChunkCoords() const;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    TileMap tileMap;
    sf::Vector2i chunkCoords; // posición del chunk en coordenadas de chunk
    unsigned int tileSize;
    unsigned int chunkSize;
};

*/
