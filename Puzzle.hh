#pragma once
#include "Minigame.hh"
#include "game.hh"
#include <memory>
#include <array>
#include <vector>

class Puzzle : public MiniGame {

    private:
        std::shared_ptr<Context> m_context;
        int w, n, x, y, dx, dy;
        std::array<std::array<int, 6>, 6> m_grid;
        sf::Texture m_texture;
        std::array<sf::Sprite, 17> m_sprite;
        std::vector<int> m_nums;
        std::shared_ptr<sf::RenderWindow> m_window;
        std::shared_ptr<sf::Event> m_event;


    public:
        Puzzle(std::shared_ptr<Context> &context);
        ~Puzzle();
        void Init() override;
        void Update(sf::Time deltaTime) override;
        void ProcessInput() override;
        void Draw();
        bool isCompleted() const override;
};