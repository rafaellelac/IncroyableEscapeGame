#pragma once

#include <memory>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>

#include "state.hh"
#include "game.hh"

class Classroom : public Engine::State{
    private:
        std::shared_ptr<Context> m_context;
        sf::Sprite m_backgroundSprite;
        sf::Text m_computerButton;
        sf::Text m_doorButton;
        
        bool isComputerSelected;
        bool isDoorSelected;
        bool isComputerPressed;
        bool isDoorPressed;

    public:
        Classroom(std::shared_ptr<Context> &context);
        void Init() override ; 
        void ProcessInput() override;
        void Update(sf::Time deltaTime) override;
        void Draw() override;


};