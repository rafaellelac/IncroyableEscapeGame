#include "game.hh"
#include "MainMenu.hh"
#include "SFML/Graphics.hpp"

Game::Game() : m_context(std::make_shared<Context>()){
    // on cree principale du jeu, il commencera avec le 'state' MainMenu
    m_context->m_window->create(sf::VideoMode(1250, 780), "Incroyable Escape Game", sf::Style::Close);
    m_context->m_states->Add(std::make_unique<MainMenu>(m_context));

}


void Game::Run(){

    // on commence l'horloge, et pour chaque frame, on va utiliser les fonctions du state actuel pour mettre a jour ce qu'on voit et ce que le jeu fait
    sf::Clock clock;
    sf::Time timeSinceLastFrame = sf::Time::Zero;

    while (m_context->m_window->isOpen())
    {
        timeSinceLastFrame += clock.restart();   
        while (timeSinceLastFrame > TIME_PER_FRAME)
        {
            timeSinceLastFrame -= TIME_PER_FRAME; 
            m_context->m_states->ProcessStateChange(); 
            m_context->m_states->GetCurrent()->ProcessInput();
            m_context->m_states->GetCurrent()->Update(TIME_PER_FRAME);
            m_context->m_states->GetCurrent()->Draw();
        }
    }
}

Game::~Game(){
}