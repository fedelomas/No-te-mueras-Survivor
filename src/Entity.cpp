#include "Entity.h"

Entity::Entity(sf::Texture& texture)
    : texture(texture), alive(true)
{
    sprite.setTexture(texture);
}

Entity::~Entity() = default;

void Entity::update(float deltaTime, sf::View& view) {

}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

bool Entity::isAlive() const {
    return alive;
}

void Entity::kill() {
    alive = false;
}

sf::Vector2f Entity::getPosition() const {
    return sprite.getPosition();
}

void Entity::setPosition(const sf::Vector2f& pos) {
    sprite.setPosition(pos);
}

sf::FloatRect Entity::getBounds() const {
    return sprite.getGlobalBounds();
}
sf::FloatRect Entity::getHitbox() const {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    float offsetX = bounds.width * 0.1f;
    float offsetY = bounds.height * 0.15f;
    float width = bounds.width * 0.8f;
    float height = bounds.height * 0.7f;
    return {bounds.left + offsetX, bounds.top + offsetY, width, height};
}
