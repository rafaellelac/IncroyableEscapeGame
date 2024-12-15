
#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Player {
public:
    Player();
    void move(float deltaTime);
    void collectCode(const std::string& code);
    const std::string& getCode() const;
    const sf::Vector2f& getPosition() const;

private:
    sf::Vector2f position;
    std::string code;
};
