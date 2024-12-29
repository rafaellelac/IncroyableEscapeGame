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
        sf::Text m_computerButton2;
        sf::Text m_computerButton3;
        sf::Text m_computerButton4;

        bool isComputerSelected;
        bool isDoorSelected;
        bool isComputer2Selected;
        bool isComputer3Selected;
        bool isComputer4Selected;
        bool isComputerPressed;
        bool isDoorPressed;
        bool isComputer2Pressed;
        bool isComputer3Pressed;
        bool isComputer4Pressed;


    public:
        Classroom(std::shared_ptr<Context> &context);
        void Init() override ; 
        void ProcessInput() override;
        void Update(sf::Time deltaTime) override;
        void Draw() override;


};