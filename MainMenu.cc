#include "MainMenu.hh"
#include "MEC.hh"
#include "Scores.hh"
#include "asset.hh"
#include "game.hh"
#include <SFML/Window/Event.hpp>


MainMenu::MainMenu(std::shared_ptr<Context> &context):
m_context(context),
isPlayButtonSelected(true),isPlayButtonPressed(false),
isScoresButtonSelected(false),isScoresButtonPressed(false),isExitButtonSelected(false),isExitButtonPressed(false){   
    };

void MainMenu::Init() {

    m_context->m_assets->AddFont(MAIN_FONT, "ASSETS/BrightAlmond.ttf" );
    m_context->m_assets->AddTexture(BACKGROUND1, "ASSETS/salle.jpg" );

    //Background
    m_backgroundSprite.setTexture(m_context->m_assets->GetTexture(BACKGROUND1));
    m_backgroundSprite.setScale(
        m_context->m_window->getSize().x / m_backgroundSprite.getLocalBounds().width,
        m_context->m_window->getSize().y / m_backgroundSprite.getLocalBounds().height
    );

    //Title
    m_gameTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameTitle.setFillColor(sf::Color::White);
    m_gameTitle.setOutlineColor(sf::Color::Black);
    m_gameTitle.setOutlineThickness(2);
    m_gameTitle.setCharacterSize(70);
    m_gameTitle.setString("Incroyable Escape Game");
    m_gameTitle.setOrigin(
        m_gameTitle.getLocalBounds().width / 2, 
        m_gameTitle.getLocalBounds().height / 2
    );
    m_gameTitle.setPosition(
        m_context->m_window->getSize().x/2,
        m_context->m_window->getSize().y/3
    );
    
    //Play Button
    m_playButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_playButton.setFillColor(sf::Color::White);
    m_playButton.setOutlineColor(sf::Color::Black);
    m_playButton.setOutlineThickness(2);
    m_playButton.setCharacterSize(50);
    m_playButton.setString("Start");
    m_playButton.setOrigin(
        m_playButton.getLocalBounds().width / 2,
        m_playButton.getLocalBounds().height / 2
    );
    m_playButton.setPosition(
        m_context->m_window->getSize().x/2,
        m_context->m_window->getSize().y/2
    );

    //Scores Button
    m_scoresButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_scoresButton.setFillColor(sf::Color::White);
    m_scoresButton.setOutlineColor(sf::Color::Black);
    m_scoresButton.setOutlineThickness(2);
    m_scoresButton.setCharacterSize(40);
    m_scoresButton.setString("Best Scores");
    m_scoresButton.setOrigin(
        m_scoresButton.getLocalBounds().width / 2,
        m_scoresButton.getLocalBounds().height / 2
    );
    m_scoresButton.setPosition(
        m_context->m_window->getSize().x/2,
        m_context->m_window->getSize().y/1.6
    );


    //Exit Button
    m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_exitButton.setFillColor(sf::Color::White);
    m_exitButton.setOutlineColor(sf::Color::Black);
    m_exitButton.setOutlineThickness(2);
    m_exitButton.setCharacterSize(40);
    m_exitButton.setString("Exit");
    m_exitButton.setOrigin(
        m_exitButton.getLocalBounds().width / 2,
        m_exitButton.getLocalBounds().height / 2
    );
    m_exitButton.setPosition(
        m_context->m_window->getSize().x/2,
        m_context->m_window->getSize().y/1.35
    );
}
        
        
void MainMenu::ProcessInput() {
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_context->m_window->close();
        else if (event.type == sf::Event::KeyPressed){
            switch (event.key.code){
                case sf::Keyboard::Up:
                    {
                    if (isPlayButtonSelected){
                        isPlayButtonSelected = true;
                        isScoresButtonSelected = false;
                        isExitButtonSelected = false;                       
                    }
                    if (isScoresButtonSelected){
                        isPlayButtonSelected = true;
                        isScoresButtonSelected = false;
                        isExitButtonSelected = false;
                    }
                    if (isExitButtonSelected){
                        isPlayButtonSelected = false;
                        isScoresButtonSelected = true;
                        isExitButtonSelected = false;
                    }
                }
                    break;
                case sf::Keyboard::Down:
                    {
                    if (isExitButtonSelected){
                        isPlayButtonSelected = false;
                        isScoresButtonSelected = false;
                        isExitButtonSelected = true;
                    }
                    if (isScoresButtonSelected){
                        isPlayButtonSelected = false;
                        isScoresButtonSelected = false;
                        isExitButtonSelected = true;
                    }
                    if (isPlayButtonSelected){
                        isPlayButtonSelected = false;
                        isScoresButtonSelected = true;
                        isExitButtonSelected = false;                       
                    }
                }
                    break;
                case sf::Keyboard::Return:
                {
                    if(isPlayButtonSelected)
                        isPlayButtonPressed=true;
                    if (isScoresButtonSelected)
                        isScoresButtonPressed=true;
                    if (isExitButtonSelected)
                        isExitButtonPressed=true;
                }
                    break;
                default:
                    break;
            }
        }
    }
}
        
        
void MainMenu::Update(sf::Time deltaTime) {
    if(isPlayButtonSelected){
        m_playButton.setFillColor(sf::Color::Red);
        m_scoresButton.setFillColor(sf::Color::White);
        m_exitButton.setFillColor(sf::Color::White);
    }
    if(isScoresButtonSelected){
        m_playButton.setFillColor(sf::Color::White);
        m_scoresButton.setFillColor(sf::Color::Red);
        m_exitButton.setFillColor(sf::Color::White);
    }
    else if (isExitButtonSelected){
        m_playButton.setFillColor(sf::Color::White);
        m_scoresButton.setFillColor(sf::Color::White);
        m_exitButton.setFillColor(sf::Color::Red);
    }
    if(isPlayButtonPressed) {
        m_context->m_timer->restart();
        m_context->m_states->Add(std::make_unique<MEC>(m_context));
        isPlayButtonPressed = false;
    }
    if(isScoresButtonPressed) {
        m_context->m_states->Add(std::make_unique<Scores>(m_context));
        isScoresButtonPressed = false;
    }
    if(isExitButtonPressed){
        m_context->m_window->close();
    }
}
        
        
void MainMenu::Draw() {
   
    m_context->m_window->clear();
    m_context->m_window->draw(m_backgroundSprite);
    m_context->m_window->draw(m_gameTitle);
    m_context->m_window->draw(m_playButton);
    m_context->m_window->draw(m_scoresButton);
    m_context->m_window->draw(m_exitButton);  
    m_context->m_window->display();
}
