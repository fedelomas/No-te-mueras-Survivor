#include <iostream>
#include "ChunkManager.h"
#include <cmath>
#include <cstdlib>

ChunkManager::ChunkManager(unsigned int tileSize, unsigned int tilesPerChunk)
    : tileSize(tileSize), tilesPerChunk(tilesPerChunk) {}

void ChunkManager::setTileTexture(const sf::Texture& texture) {
    tileTexture = &texture;
}

void ChunkManager::updateChunksAround(const sf::Vector2f& playerPos) {
    if (!tileTexture) return;

    int currentChunkX = static_cast<int>(std::floor(playerPos.x / (tileSize * tilesPerChunk)));
    int currentChunkY = static_cast<int>(std::floor(playerPos.y / (tileSize * tilesPerChunk)));

    int radius = 1;
    for (int dy = -radius; dy <= radius; ++dy) {
        for (int dx = -radius; dx <= radius; ++dx) {
            int cx = currentChunkX + dx;
            int cy = currentChunkY + dy;

            std::pair<int, int> coords = {cx, cy};

            if (chunks.find(coords) == chunks.end()) {
                chunks[coords] = generateChunk(cx, cy);

            }
        }
    }


}

TileMap ChunkManager::generateChunk(int chunkX, int chunkY) {
//    std::cout << "Generando chunk en: (" << chunkX << ", " << chunkY << ")\n";

    TileMap map;

    std::vector<int> tiles;
    tiles.reserve(tilesPerChunk * tilesPerChunk);

    int tileCountX = tileTexture->getSize().x / tileSize;
    int tileCountY = tileTexture->getSize().y / tileSize;
    int totalTiles = tileCountX * tileCountY;

    for (unsigned int i = 0; i < tilesPerChunk * tilesPerChunk; ++i) {
        tiles.push_back(rand() % totalTiles);
    }

  map.setPosition(
    static_cast<int>(chunkX * tileSize * tilesPerChunk),
    static_cast<int>(chunkY * tileSize * tilesPerChunk)
);

    map.load(
    {tileSize, tileSize},   // sf::Vector2u tileSize
    tiles,                  // std::vector<int>
    tilesPerChunk,          // width
    tilesPerChunk,          // height
    *tileTexture            // const sf::Texture&
);

    return map;
}

void ChunkManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& pair : chunks) {
        target.draw(pair.second, states);
    }
}
