#pragma once
#include <SFML/Graphics.hpp>
#include "Minigame.hh"
#include "game.hh"

class MazeGame : public MiniGame {
public:
    MazeGame(std::shared_ptr<Context> &context);
    void Init() override;
    void Update(sf::Time deltaTime) override;
    void ProcessInput() override;
    void Draw() override;
    bool isCompleted() const override;

private:

    std::shared_ptr<Context> m_context;
    sf::Sprite  mazeSprite;
    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    sf::Vector2f playerPosition;
    sf::Vector2f movement= sf::Vector2f(0.0f, 0.0f);
    bool completed;
    sf::Image mazeImage; // To check pixel colors

    bool isPixelBlack(const sf::Vector2f& position);
};
// Overload the division operator for sf::Vector2f
sf::Vector2f operator/(const sf::Vector2f& vec, const sf::Vector2f& divisor);