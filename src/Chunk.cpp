/* #include "Chunk.h"
#include <cstdlib>  // para rand()

// Constructor por defecto (no hace nada especial)
Chunk::Chunk()
    : chunkCoords(0, 0), tileSize(0), chunkSize(0) {}

// Constructor con coordenadas de chunk y tamaños
Chunk::Chunk(int chunkX, int chunkY, unsigned int tileSize, unsigned int chunkSize)
    : chunkCoords(chunkX, chunkY), tileSize(tileSize), chunkSize(chunkSize) {

    // Posicionamos el chunk en el mundo
    float worldX = static_cast<float>(chunkX * chunkSize * tileSize);
    float worldY = static_cast<float>(chunkY * chunkSize * tileSize);
    setPosition(worldX, worldY);
}

    // generate(): crea tiles aleatorios
    bool Chunk::generate(const sf::Texture& tileset) {
    std::vector<int> tileIndices;
    int totalTiles = (tileset.getSize().x / tileSize) * (tileset.getSize().y / tileSize);

    if (tileSize == 0 || chunkSize == 0 || totalTiles == 0)
        return false;

    tileIndices.reserve(chunkSize * chunkSize);
    for (unsigned int i = 0; i < chunkSize * chunkSize; ++i) {
        tileIndices.push_back(rand() % totalTiles);  // tile aleatorio
    }

    return tileMap.load(
        "",  // ya no usamos ruta, pasamos la textura directamente
        sf::Vector2u(tileSize, tileSize),
        tileIndices,
        chunkSize,
        chunkSize,
        tileset
    );
}


// Genera el contenido del chunk usando una textura ya cargada
bool Chunk::generate(const sf::Texture& tileset) {
    // Calculamos cuántos tiles hay disponibles en la textura
    int tilesX = tileset.getSize().x / tileSize;
    int tilesY = tileset.getSize().y / tileSize;
    int totalTiles = tilesX * tilesY;

    // Validaciones básicas
    if (tileSize == 0 || chunkSize == 0 || totalTiles == 0)
        return false;

    // Creamos el vector con índices de tiles aleatorios
    std::vector<int> tileIndices;
    tileIndices.reserve(chunkSize * chunkSize);
    for (unsigned int i = 0; i < chunkSize * chunkSize; ++i) {
        tileIndices.push_back(rand() % totalTiles);
    }

    // Usamos la versión de load que NO carga desde archivo
    return tileMap.load(
        sf::Vector2u(tileSize, tileSize),  // tamaño de cada tile
        tileIndices,                       // índices de tiles
        chunkSize,                         // ancho en tiles
        chunkSize,                         // alto en tiles
        tileset                            // textura ya cargada
     );
}


void Chunk::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();  // posicionar el chunk
    target.draw(tileMap, states);       // dibujar el TileMap del chunk
}

*/
