// Puzzle.h
#pragma once
#include "Minigame.hh"
#include <memory>
#include <array>
#include <vector>

class Puzzle : public MiniGame {
private:
    std::shared_ptr<sf::Event> event;

    sf::Texture texture;
    int w, n, x, y, dx, dy;
    std::array<std::array<int, 6>, 6> grid;
    std::array<sf::Sprite, 17> sprite;

protected:
    void events();
    void draw();
    void logic();

public:
    std::shared_ptr<sf::RenderWindow> window;
    Puzzle(const std::vector<int>& nums);
    void init() override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    bool isCompleted() const override;
};