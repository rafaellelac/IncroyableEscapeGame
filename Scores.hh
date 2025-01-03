#pragma once
#include "state.hh"
#include "game.hh"
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>  

class Scores : public Engine::State {

    private:
        std::shared_ptr<Context> m_context;
        sf::Sprite m_backgroundSprite;
        sf::Text m_scoresText;
        std::vector<std::string> m_scores;
        sf::Text m_back;


    public:
        Scores(std::shared_ptr<Context> &context);
        void Init() override;
        void ProcessInput() override;
        void Update(sf::Time deltaTime) override;
        void Draw() override;
        void LoadHighScores();
};