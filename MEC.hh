#pragma once
#include "state.hh"
#include "game.hh"
#include <memory>
#include <SFML/Graphics.hpp>  

class MEC : public Engine::State {

    private:
    std::shared_ptr<Context> m_context;
    sf::Text m_gamecontext;
    sf::Text m_next;
    sf::Text m_back;
 
    
    public:
        MEC(std::shared_ptr<Context> &context);
        void Init() override;
        void ProcessInput() override;
        void Update(sf::Time deltaTime) override;
        void Draw() override;
        void Pause() override;
        void Start() override;
};