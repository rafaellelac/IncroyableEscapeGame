#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class MiniGame {
public:
    virtual ~MiniGame() = default;
    virtual void init() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual bool isCompleted() const = 0;
};
