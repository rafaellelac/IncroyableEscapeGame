#pragma once
#include "state.hh"
#include "game.hh"
#include <memory>
#include <SFML/Graphics.hpp>  
#include "MEC.hh"

class LastScreen : public MEC {

    private:
    sf::Text m_gamecontext;
    sf::Text m_next;
    sf::Text m_code1;
    sf::Text m_code2;
    sf::Text m_code3;
    sf::Text m_code4;
 
    
    public:
        LastScreen(std::shared_ptr<Context> &context);
        void Init() override;
        void ProcessInput() override;
        void Update(sf::Time deltaTime) override;
        void Draw() override;
};