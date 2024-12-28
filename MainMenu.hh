#pragma once

#include <memory>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>

#include "state.hh"
#include "game.hh"

class MainMenu : public Engine::State{
    private:
        std::shared_ptr<Context> m_context;
        sf::Sprite m_backgroundSprite;
        sf::Text m_gameTitle;
        sf::Text m_playButton;
        sf::Text m_scoresButton;
        sf::Text m_exitButton;

        bool isPlayButtonSelected;
        bool isPlayButtonPressed;
        bool isScoresButtonSelected;
        bool isScoresButtonPressed;
        bool isExitButtonSelected;
        bool isExitButtonPressed;


    public:
        MainMenu(std::shared_ptr<Context> &context);
        void Init() override ; 
        void ProcessInput() override;
        void Update(sf::Time deltaTime) override;
        void Draw() override;


};
