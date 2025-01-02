#pragma once
#include "state.hh"
#include "game.hh"
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>  

class Scores : public Engine::State {

    protected:
    std::shared_ptr<Context> m_context;
    sf::Sprite m_backgroundSprite;
    std::vector<sf::Text> m_highscoreTexts;
    std::vector<std::pair<std::string,int>> m_highscoreList;
    sf::Text m_time;
    sf::Text m_back;

 
    
    public:
        Scores(std::shared_ptr<Context> &context);
        void Init() override;
        void ProcessInput() override;
        void Update(sf::Time deltaTime) override;
        void Draw() override;
        void ShowHighScore();
};