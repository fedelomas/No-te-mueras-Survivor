#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include "TileMap.h" // Incluimos TileMap

class ChunkManager : public sf::Drawable {
public:
    // Constructor de ChunkManager
    ChunkManager(unsigned int tileSize, unsigned int tilesPerChunk);

    // Asigna la textura principal de los tiles.
    // Esta textura debe ser cargada y mantenida viva por la clase que usa ChunkManager (e.g., Gameplay).
    void setTileTexture(const sf::Texture& texture);

    // Actualiza y genera chunks alrededor de la posición del jugador.
    void updateChunksAround(const sf::Vector2f& playerPos);

private:
    // Método para dibujar los chunks. Heredado de sf::Drawable.
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // Mapa que almacena los chunks, indexados por sus coordenadas (chunkX, chunkY).
    std::map<std::pair<int, int>, TileMap> chunks;

    // Puntero a la textura principal de los tiles.
    // ChunkManager NO posee esta textura; solo mantiene una referencia a ella.
    const sf::Texture* tileTexture = nullptr;

    // Tamaño de cada tile en píxeles.
    unsigned int tileSize;
    // Número de tiles por lado en cada chunk (un chunk es tilesPerChunk x tilesPerChunk).
    unsigned int tilesPerChunk;

    // Función privada para generar un nuevo chunk en unas coordenadas dadas.
    // Devuelve un objeto TileMap por valor, el cual será copiado al mapa 'chunks'.
    TileMap generateChunk(int chunkX, int chunkY);
};
