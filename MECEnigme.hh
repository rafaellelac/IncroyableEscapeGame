#pragma once
#include "MEC.hh"
#include "game.hh"
#include <memory>
#include <SFML/Graphics.hpp>  

class MECEnigme : public MEC {

    private:
    sf::Text m_congrats;
    sf::Text m_quizzhint;
 
    
    public:
        MECEnigme(std::shared_ptr<Context> &context);
        void Init() override;
        void ProcessInput() override;
        void Draw() override;
};