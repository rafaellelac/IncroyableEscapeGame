#include "Fin.hh"
#include "Classroom.hh"
#include "MainMenu.hh"
#include "game.hh"
#include <fstream>
#include <sstream>


Fin::Fin(std::shared_ptr<Context> &context) : m_context(context) {}


void Fin::Init(){

    m_context->m_assets->AddFont(FONT2, "ASSETS/newseptember.otf" );
    m_context->m_assets->AddTexture(HALLWAY, "ASSETS/hallway.jpg" );

    //on arrete le timer et on recupere le temps du joueur
    sf::Time time = m_context->m_timer->getElapsedTime();
    int minutes = static_cast<int>(time.asSeconds()) / 60;
    int seconds = static_cast<int>(time.asSeconds()) % 60;
    
    std::ostringstream timeStream;
    timeStream << "Vous avez reussi en " << minutes << " minutes et " << seconds << " secondes!";

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
    m_congrats.setString(timeStream.str());

    m_congrats.setOrigin(
        m_congrats.getLocalBounds().width / 2, 
        m_congrats.getLocalBounds().height / 2
    );
    m_congrats.setPosition(
        m_context->m_window->getSize().x/2,
        m_context->m_window->getSize().y/2 - 200
    );

    
    //Player Text and Input
    m_playerText.setFont(m_context->m_assets->GetFont(FONT2));
    m_playerText.setFillColor(sf::Color::Black);
    m_playerText.setCharacterSize(45);
    m_playerText.setString("Entrez voter nom et appuyez sur ENTRER :");
    m_playerText.setOrigin(
        m_playerText.getLocalBounds().width/2, 
        m_playerText.getLocalBounds().height/2
    );
    m_playerText.setPosition(
        m_context->m_window->getSize().x/2,
        m_context->m_window->getSize().y/2 
    );
}


void Fin::ProcessInput(){
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_context->m_window->close();
        else if (event.type == sf::Event::KeyPressed){
            switch (event.key.code){
                case sf::Keyboard::Return: 
                    { 
                    AddHighScore();
                    m_playerInput.clear();
                    m_context->m_states->Add(std::make_unique<MainMenu>(m_context)); // si le nom est valide par le joueur, on rajoute son score a la liste et on retourne au menu principal
                    }
                    break;
                default:
                    break;
            }
        }
        else if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode < 128) {  // on ignore les caracteres non ASCII 
                if (event.text.unicode == 8 && !m_playerInput.empty()) { // si RETOUR est appuye, on efface le dernier caractere
                    m_playerInput.pop_back();
                } else if (event.text.unicode != 8) {  // sinon, on rajoute le caractere
                    m_playerInput += static_cast<char>(event.text.unicode);
                    m_playerText.setString("Entrez voter nom et appuyez sur ENTRER :" + m_playerInput);
                }
            }
        }
    }
}

void Fin::AddHighScore() {
    std::ofstream highscoreFile("ASSETS/highscore.txt", std::ios_base::app);
    if (highscoreFile.is_open()) {
       sf::Time time = m_context->m_timer->getElapsedTime();
       int minutes = static_cast<int>(time.asSeconds()) / 60;
    int seconds = static_cast<int>(time.asSeconds()) % 60;
        highscoreFile << m_playerInput << " " << minutes << ":" << seconds << "\n"; // on rajoute le nom et le temps du joueur a la liste des scores 
    }
    highscoreFile.close();
}

void Fin::Update(sf::Time deltaTime) {}
        
        
void Fin::Draw() {
    m_context->m_window->clear();
    m_context->m_window->draw(m_backgroundSprite);
    m_context->m_window->draw(m_congrats);
    m_context->m_window->draw(m_playerText);
    m_context->m_window->display();
}
