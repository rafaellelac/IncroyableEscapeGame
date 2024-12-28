#pragma once
#include "state.hh"
#include "game.hh"
#include <memory>
#include <SFML/Graphics.hpp>  

class MECMaze : public Engine::State {

    private:
    std::shared_ptr<Context> m_context;
    sf::Sprite m_backgroundSprite;
    sf::Text m_mazecontext;
    sf::Text m_next;
 
    
    public:
        MECMaze(std::shared_ptr<Context> &context);
        void Init() override;
        void ProcessInput() override;
        void Update(sf::Time deltaTime) override;
        void Draw() override;
};