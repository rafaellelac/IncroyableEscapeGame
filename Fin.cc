#include "Fin.hh"
#include "Classroom.hh"
#include "MainMenu.hh"
#include <memory>
#include "Scores.hh"
#include "game.hh"
#include <fstream>


int Fin::m_score = 0;

Fin::Fin(std::shared_ptr<Context> &context) : m_context(context) {}


void Fin::Init(){

    m_context->m_assets->AddFont(FONT2, "ASSETS/newseptember.otf" );
    m_context->m_assets->AddTexture(HALLWAY, "ASSETS/hallway.jpg" );

    //Background
    m_backgroundSprite.setTexture(m_context->m_assets->GetTexture(HALLWAY));
    m_backgroundSprite.setScale(
        m_context->m_window->getSize().x / m_backgroundSprite.getLocalBounds().width,
        m_context->m_window->getSize().y / m_backgroundSprite.getLocalBounds().height
    );

    //Congrats Text
    m_congrats.setFont(m_context->m_assets->GetFont(FONT2));
    m_congrats.setFillColor(sf::Color::Black);
    m_congrats.setOutlineColor(sf::Color::White);
    m_congrats.setOutlineThickness(1);
    m_congrats.setCharacterSize(50);
    m_congrats.setString("Felicitations! Vous etes sortis en 'TEMPS' minutes!");
    m_congrats.setOrigin(
        m_congrats.getLocalBounds().width / 2, 
        m_congrats.getLocalBounds().height / 2
    );
    m_congrats.setPosition(
        m_context->m_window->getSize().x/2,
        m_context->m_window->getSize().y/2 - 200
    );

    //Time and Score Text
    m_time.setFont(m_context->m_assets->GetFont(FONT2));
    m_time.setFillColor(sf::Color::Black);
    m_time.setCharacterSize(30);
    m_time.setString("Entrez voter prenom sur votre clavier pour rajouter votre score a la liste\n du menu principal!");
    m_time.setOrigin(
        m_time.getLocalBounds().width/2, 
        m_time.getLocalBounds().height/2
    );
    m_time.setPosition(
        m_context->m_window->getSize().x/2,
        m_context->m_window->getSize().y/2 
    );

    //Main Menu Text
    m_mainmenu.setFont(m_context->m_assets->GetFont(FONT2));
    m_mainmenu.setFillColor(sf::Color::Black);
    m_mainmenu.setCharacterSize(30);
    m_mainmenu.setString("Appuyer sur la fleche droite pour retourner au menu principal");
    m_mainmenu.setOrigin(
        m_mainmenu.getLocalBounds().width, 
        m_mainmenu.getLocalBounds().height
    );
    m_mainmenu.setPosition(
        m_context->m_window->getSize().x - 50,
        m_context->m_window->getSize().y - 50
    );

    // Player Input Text
    m_playerText.setFont(m_context->m_assets->GetFont(FONT2));
    m_playerText.setFillColor(sf::Color::Black);
    m_playerText.setCharacterSize(30);
    m_playerText.setPosition(20, 20);

}


void Fin::ProcessInput(){
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_context->m_window->close();
        else if (event.type == sf::Event::KeyPressed){
            switch (event.key.code){
                case sf::Keyboard::Right:
                    {
                    m_context->m_states->Add(std::make_unique<MainMenu>(m_context));
                    }
                    break;
                case sf::Keyboard::Return:
                    {
                    AddHighScore();
                    m_playerInput.clear();
                    m_playerText.setString(m_playerInput);
                    //methode show high score de Scores
                    }
                    break;
                default:
                    break;
            }
        }
        else if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode < 128) {  // Ignore non-ASCII characters
                if (event.text.unicode == 8 && !m_playerInput.empty()) { // Backspace
                    m_playerInput.pop_back();
                } else if (event.text.unicode != 8) {  // Regular character
                    m_playerInput += static_cast<char>(event.text.unicode);
                }
            }
        }
    }
}

void Fin::AddHighScore(){
    std::ofstream highscoreFile("highscores.txt", std::ios_base::app);
    highscoreFile << m_playerInput << "," << m_score << "|";
    highscoreFile.close();
}

void Fin::SetScore(int newScore){
    m_score=newScore;
}

int Fin::GetScore(){
    return m_score;
}
void Fin::Update(sf::Time deltaTime) {}
        
        
void Fin::Draw() {
    m_context->m_window->clear();
    m_context->m_window->draw(m_backgroundSprite);
    m_context->m_window->draw(m_congrats);
    m_context->m_window->draw(m_time);
    m_context->m_window->draw(m_mainmenu);
    m_context->m_window->draw(m_playerText);
    m_context->m_window->display();
}
