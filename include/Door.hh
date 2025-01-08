#pragma once

#include <memory>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>

#include "state.hh"
#include "game.hh"

class Door : public Engine::State{

    private:
        std::shared_ptr<Context> m_context;
        sf::Sprite m_backgroundSprite;
        sf::Text m_text;
        sf::Text m_back;
        sf::RectangleShape m_inputBox;
        sf::Text m_inputText;
        std::string m_playerInput;
        sf::Text m_check;
        sf::Text m_wrong;


    public:
        Door(std::shared_ptr<Context> &context);
        void Init() override ; 
        void ProcessInput() override;
        void Update(sf::Time deltaTime) override;
        void Draw() override;
};