#include "TileMap.h"
#include <iostream> // Para los mensajes de depuración opcionales

bool TileMap::load(sf::Vector2u tileSize, const std::vector<int>& tiles,
                   unsigned int width, unsigned int height, const sf::Texture& texture)
{
    // Guarda la dirección de la textura que ya está cargada en Gameplay
    m_tilesetPtr = &texture;

    // Redimensiona el VertexArray para todos los cuadriláteros
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    // Rellena el VertexArray con las posiciones y coordenadas de textura
    for (unsigned int i = 0; i < width; ++i)
    {
        for (unsigned int j = 0; j < height; ++j)
        {
            int tileNumber = tiles[i + j * width];


            int tileCountX = m_tilesetPtr->getSize().x / tileSize.x;
            int tileCountY = m_tilesetPtr->getSize().y / tileSize.y;
            int totalAvailableTiles = tileCountX * tileCountY;

            if (tileNumber < 0 || tileNumber >= totalAvailableTiles) {
                 std::cerr << "Advertencia: Indice de tile fuera de rango! Usando tile 0." << std::endl;
                tileNumber = 0; // Asigna un tile por defecto si el índice es inválido
            }
            // ********************************************************************************

            int tu = tileNumber % tileCountX; // Coordenada U (horizontal) en el tileset
            int tv = tileNumber / tileCountX; // Coordenada V (vertical) en el tileset

            sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

            // Establece las posiciones de los 4 vértices del cuadrilátero
            // Estas son las coordenadas *locales* dentro de este TileMap
            quad[0].position = sf::Vector2f(static_cast<float>(i * tileSize.x), static_cast<float>(j * tileSize.y));
            quad[1].position = sf::Vector2f(static_cast<float>((i + 1) * tileSize.x), static_cast<float>(j * tileSize.y));
            quad[2].position = sf::Vector2f(static_cast<float>((i + 1) * tileSize.x), static_cast<float>((j + 1) * tileSize.y));
            quad[3].position = sf::Vector2f(static_cast<float>(i * tileSize.x), static_cast<float>((j + 1) * tileSize.y));

            // Establece las coordenadas de textura de los 4 vértices del cuadrilátero
            // Estas apuntan a la parte correcta del tileset para el tile actual
            quad[0].texCoords = sf::Vector2f(static_cast<float>(tu * tileSize.x), static_cast<float>(tv * tileSize.y));
            quad[1].texCoords = sf::Vector2f(static_cast<float>((tu + 1) * tileSize.x), static_cast<float>(tv * tileSize.y));
            quad[2].texCoords = sf::Vector2f(static_cast<float>((tu + 1) * tileSize.x), static_cast<float>((tv + 1) * tileSize.y));
            quad[3].texCoords = sf::Vector2f(static_cast<float>(tu * tileSize.x), static_cast<float>((tv + 1) * tileSize.y));
        }
    }

    return true;
}



void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Aplica la transformación (posición) de este TileMap
    states.transform *= getTransform();
    if (m_tilesetPtr) {
        states.texture = m_tilesetPtr; // Usa el puntero a la textura
    } else {
         std::cerr << "Error: TileMap intentando dibujar sin tileset (puntero es nullptr)!" << std::endl;
        return;
    }

    // Dibuja los vértices usando la textura
    target.draw(m_vertices, states);
}

