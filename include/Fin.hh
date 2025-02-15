#pragma once
#include "state.hh"
#include "game.hh"
#include <memory>
#include <SFML/Graphics.hpp>  

class Fin : public Engine::State {

    private:
    std::shared_ptr<Context> m_context;
    sf::Sprite m_backgroundSprite;
    sf::Text m_congrats;
    std::string m_playerInput;
    sf::Text m_playerText;
    sf::Clock m_clock;


    public:
        Fin(std::shared_ptr<Context> &context);
        void Init() override;
        void ProcessInput() override;
        void Update(sf::Time deltaTime) override;
        void Draw() override;
        void AddHighScore();
};
