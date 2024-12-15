
#include "Player.h"
#include <iostream>

Player::Player() : position(400.0f, 400.0f), code("") {
}

void Player::move(float deltaTime) {
    sf::Vector2f movement(0.0f, 0.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        movement.y -= 100.0f * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        movement.y += 100.0f * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        movement.x -= 100.0f * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        movement.x += 100.0f * deltaTime;
    }
    position += movement;
}

void Player::collectCode(const std::string& code) {
    this->code += code;
    std::cout << "Collected code: " << code << std::endl;
}

const std::string& Player::getCode() const {
    return code;
}

const sf::Vector2f& Player::getPosition() const {
    return position;
}