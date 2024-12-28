#include "MECMaze.hh"
#include "Classroom.hh"
#include <memory>


MECMaze::MECMaze(std::shared_ptr<Context> &context) : m_context(context) {}


void MECMaze::Init(){


    m_context->m_assets->AddTexture(COMPUTER_SCREEN, "ASSETS/computerscreen.jpg" );

    //Background
    m_backgroundSprite.setTexture(m_context->m_assets->GetTexture(COMPUTER_SCREEN));
    m_backgroundSprite.setScale(
        m_context->m_window->getSize().x / m_backgroundSprite.getLocalBounds().width,
        m_context->m_window->getSize().y / m_backgroundSprite.getLocalBounds().height
    );

    //Context Text
    m_mazecontext.setFont(m_context->m_assets->GetFont(COMPUTER_FONT));
    m_mazecontext.setFillColor(sf::Color::Black);
    m_mazecontext.setOutlineColor(sf::Color::White);
    m_mazecontext.setOutlineThickness(2);
    m_mazecontext.setCharacterSize(35);
    m_mazecontext.setString("Vous vous etes endormi en TP de C++.\nLorsque vous vous reveillez, la salle est vide \net la porte est fermee a cle. \nVous devez trouver un moyen de sortir de la salle \navant que le professeur ne revienne. \nPour cela, vous devez reussir a ouvrir la porte \nen resolvant des enigmes.\nBonne chance !");
    m_mazecontext.setOrigin(
        m_mazecontext.getLocalBounds().width / 2, 
        m_mazecontext.getLocalBounds().height / 2
    );
    m_mazecontext.setPosition(
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

}


void MECMaze::ProcessInput(){
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
                   m_context->m_states->Add(std::make_unique<Classroom>(m_context));
                    }
                    break;
                default:
                    break;
            }
        }
    }
}


void MECMaze::Update(sf::Time deltaTime) {}
        
        
void MECMaze::Draw() {
    m_context->m_window->clear();
    m_context->m_window->draw(m_backgroundSprite);
    m_context->m_window->draw(m_mazecontext);
    m_context->m_window->draw(m_next);
    m_context->m_window->display();
}
