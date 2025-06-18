#pragma once
#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable, public sf::Transformable {
protected:
    sf::Sprite sprite;
    sf::Texture& texture;
    sf::Clock clock;
    sf::Time frameTime = sf::seconds(0.1f);

    bool alive;
    float speed = 5.0f;
    int frameWidth = 0;
    int frameHeight = 0;
    int currentFrame = 0;
    int totalFrames = 1;

public:
    Entity(sf::Texture& texture);
    virtual ~Entity();

    virtual void update(float deltaTime, sf::View& view) = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    virtual bool isAlive() const;
    virtual void kill();

    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& pos);

    sf::FloatRect getBounds() const;
};
