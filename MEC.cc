#include "MEC.hh"
#include "Maze.hh"
#include <memory>

MEC::MEC(std::shared_ptr<Context> &context) : m_context(context) {}


void MEC::Init(){

    m_context->m_assets->AddFont(COMPUTER_FONT, "ASSETS/computer.ttf" );

    //Context Text
    m_gamecontext.setFont(m_context->m_assets->GetFont(COMPUTER_FONT));
    m_gamecontext.setFillColor(sf::Color::White);
    m_gamecontext.setCharacterSize(30);
    m_gamecontext.setString("Vous vous etes endormi en TP de C++.\nLorsque vous vous reveillez, la salle est vide \net la porte est fermee a cle. \nVous devez trouver un moyen de sortir de la salle \navant que le professeur ne revienne. \nPour cela, vous devez reussir a ouvrir la porte \nen resolvant des enigmes.\nBonne chance !");
    m_gamecontext.setOrigin(
        m_gamecontext.getLocalBounds().width / 2, 
        m_gamecontext.getLocalBounds().height / 2
    );
    m_gamecontext.setPosition(
        m_context->m_window->getSize().x/2,
        m_context->m_window->getSize().y/2
    );

    //Next Text
    m_next.setFont(m_context->m_assets->GetFont(COMPUTER_FONT));
    m_next.setFillColor(sf::Color::Blue);
    m_next.setCharacterSize(20);
    m_next.setString("Appuyer sur ENTRER pour jouer");
    m_next.setOrigin(
        m_next.getLocalBounds().width, 
        m_next.getLocalBounds().height
    );
    m_next.setPosition(
        m_context->m_window->getSize().x-20,
        m_context->m_window->getSize().y-50
    );

    //Back Text
    m_back.setFont(m_context->m_assets->GetFont(COMPUTER_FONT));
    m_back.setFillColor(sf::Color::Blue);
    m_back.setCharacterSize(20);
    m_back.setPosition(20,20);
    m_back.setString("<- Appuyer sur RETOUR ");
}


void MEC::ProcessInput(){
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
                case sf::Keyboard::Return:
                    {
                   m_context->m_states->Add(std::make_unique<MazeGame>(m_context));
                    }
                    break;
                default:
                    break;
            }
        }
    }
}


void MEC::Update(sf::Time deltaTime) {}
        
        
void MEC::Draw() {
    m_context->m_window->clear(sf::Color::Black);
    m_context->m_window->draw(m_gamecontext);
    m_context->m_window->draw(m_next);
    m_context->m_window->draw(m_back);
    m_context->m_window->display();
}


void MEC::Pause() {}
        
        
void MEC::Start() {}