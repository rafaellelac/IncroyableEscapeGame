
// cette classe maze hérite de la classe Minigame, elle est donc une classe fille. Cela signifie qu'elle doit implémenter la fonction play() de la classe mère
//on veut implémenter un labyrinthe

#pragma once
#include <SFML/Graphics.hpp>
#include "Minigame.hh"

class MazeGame : public MiniGame {
public:
    MazeGame();
    ~MazeGame() override = default;

    void init() override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    bool isCompleted() const override;

private:
    sf::Texture mazeTexture;
    sf::Sprite mazeSprite;
    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    sf::Vector2f playerPosition;
    bool completed;
    sf::Image mazeImage; // To check pixel colors

    bool isPixelBlack(const sf::Vector2f& position);
};
// Overload the division operator for sf::Vector2f
sf::Vector2f operator/(const sf::Vector2f& vec, const sf::Vector2f& divisor);