#include "HS.hh"
#include "Classroom.hh"


HS::HS(std::shared_ptr<Context> &context) : m_context(context) {}


void HS::Init(){

    m_context->m_assets->AddTexture(COMPUTER_SCREEN, "ASSETS/computerscreen.jpg" );
    
    //Background
    m_backgroundSprite.setTexture(m_context->m_assets->GetTexture(COMPUTER_SCREEN));
    m_backgroundSprite.setScale(
        m_context->m_window->getSize().x / m_backgroundSprite.getLocalBounds().width,
        m_context->m_window->getSize().y / m_backgroundSprite.getLocalBounds().height
    );

    //HS Text
    m_hs.setFont(m_context->m_assets->GetFont(COMPUTER_FONT));
    m_hs.setFillColor(sf::Color::Black);
    m_hs.setCharacterSize(35);
    m_hs.setString("HORS SERVICE");
    m_hs.setOrigin(
        m_hs.getLocalBounds().width / 2, 
        m_hs.getLocalBounds().height / 2
    );
    m_hs.setPosition(
        m_context->m_window->getSize().x/2,
        m_context->m_window->getSize().y/2
    );

    //Back Text
    m_back.setFont(m_context->m_assets->GetFont(COMPUTER_FONT));
    m_back.setFillColor(sf::Color::Blue);
    m_back.setCharacterSize(20);
    m_back.setPosition(20,20);
    m_back.setString("<- Appuyer sur RETOUR ");
}


void HS::ProcessInput(){
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_context->m_window->close();
        else if (event.type == sf::Event::KeyPressed){
            switch (event.key.code){
                case sf::Keyboard::BackSpace:
                    {
                    m_context->m_states->PopCurrent();                       
                    }
                    break;
                default:
                    break;
            }
        }
    }
}


void HS::Update(sf::Time deltaTime) {}
        
        
void HS::Draw() {
    m_context->m_window->clear();
    m_context->m_window->draw(m_backgroundSprite);
    m_context->m_window->draw(m_hs);
    m_context->m_window->draw(m_back);
    m_context->m_window->display();
}