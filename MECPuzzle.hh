#pragma once
#include "MEC.hh"
#include "game.hh"
#include <memory>
#include <SFML/Graphics.hpp>  

class MECPuzzle : public MEC {

    private:
        sf::Text m_congrats;
        sf::Text m_mazehint;
 
    
    public:
        MECPuzzle(std::shared_ptr<Context> &context);
        void Init() override;
        void ProcessInput() override;
        void Update(sf::Time deltaTime) override;
        void Draw() override;
};