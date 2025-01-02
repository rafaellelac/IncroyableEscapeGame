#include "Fin.hh"
#include "Classroom.hh"
#include "MainMenu.hh"
#include <memory>


Fin::Fin(std::shared_ptr<Context> &context) : m_context(context) {}


void Fin::Init(){

    m_context->m_assets->AddFont(FONT2, "ASSETS/newseptember.otf" );
    m_context->m_assets->AddFont(COMPUTER_FONT, "ASSETS/computer.ttf" );
    m_context->m_assets->AddTexture(CLASSROOM, "ASSETS/classroom.jpg" );

    //Background
    m_backgroundSprite.setTexture(m_context->m_assets->GetTexture(CLASSROOM));
    m_backgroundSprite.setScale(
        m_context->m_window->getSize().x / m_backgroundSprite.getLocalBounds().width,
        m_context->m_window->getSize().y / m_backgroundSprite.getLocalBounds().height
    );

    //Congrats Text
    m_congrats.setFont(m_context->m_assets->GetFont(FONT2));
    m_congrats.setFillColor(sf::Color::Black);
    m_congrats.setOutlineColor(sf::Color::White);
    m_congrats.setOutlineThickness(1);
    m_congrats.setCharacterSize(40);
    m_congrats.setString("Felicitations! Vous etes sortis en 'TEMPS' minutes!");
    m_congrats.setOrigin(
        m_congrats.getLocalBounds().width / 2, 
        m_congrats.getLocalBounds().height / 2
    );
    m_congrats.setPosition(
        m_context->m_window->getSize().x/2,
        m_context->m_window->getSize().y/2
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
        m_context->m_window->getSize().y/2 + 100
    );

    //Main Menu Text
    m_mainmenu.setFont(m_context->m_assets->GetFont(FONT2));
    m_mainmenu.setFillColor(sf::Color::Black);
    m_mainmenu.setCharacterSize(30);
    m_mainmenu.setString("Appuyer sur ENTRER pour retourner au menu principal");
    m_mainmenu.setOrigin(
        m_mainmenu.getLocalBounds().width/2, 
        m_mainmenu.getLocalBounds().height/2
    );
    m_mainmenu.setPosition(
        m_context->m_window->getSize().x/2,
        m_context->m_window->getSize().y/2 + 150
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
                   m_context->m_states->Add(std::make_unique<MainMenu>(m_context));
                    }
                    break;
                default:
                    break;
            }
        }
    }
}


void Fin::Update(sf::Time deltaTime) {}
        
        
void Fin::Draw() {
    m_context->m_window->clear();
    m_context->m_window->draw(m_backgroundSprite);
    m_context->m_window->draw(m_congrats);
    m_context->m_window->draw(m_time);
    m_context->m_window->draw(m_mainmenu);
    m_context->m_window->display();
}
