#include "MECPuzzle.hh"
#include "Puzzle.hh"
#include "Quizz.hh"

MECPuzzle::MECPuzzle(std::shared_ptr<Context> &context) : MEC(context) {}


void MECPuzzle::Init(){


    m_context->m_assets->AddTexture(COMPUTER_SCREEN, "ASSETS/computerscreen.jpg" );

    //Background
    m_backgroundSprite.setTexture(m_context->m_assets->GetTexture(COMPUTER_SCREEN));
    m_backgroundSprite.setScale(
        m_context->m_window->getSize().x / m_backgroundSprite.getLocalBounds().width,
        m_context->m_window->getSize().y / m_backgroundSprite.getLocalBounds().height
    );

    //Context Text
    m_gamecontext.setFont(m_context->m_assets->GetFont(COMPUTER_FONT));
    m_gamecontext.setFillColor(sf::Color::Black);
    m_gamecontext.setCharacterSize(30);
    m_gamecontext.setString("Maintenant, faites coulisser les nombres pour les \nremettre dans l'ordre croissant.\nde gauche a droite, le 1 en haut a gauche!");
    m_gamecontext.setOrigin(
        m_gamecontext.getLocalBounds().width / 2, 
        m_gamecontext.getLocalBounds().height / 2
    );
    m_gamecontext.setPosition(
        m_context->m_window->getSize().x/2,
        m_context->m_window->getSize().y/2 + 150
    );

    //Hint text
    m_mazehint.setFont(m_context->m_assets->GetFont(COMPUTER_FONT));
    m_mazehint.setFillColor(sf::Color::Red);
    m_mazehint.setCharacterSize(35);
    m_mazehint.setString("Indice: Josephine Baker n'aime pas le cafe \net habite en dessous de celle qui a un poisson");
    m_mazehint.setOrigin(
        m_mazehint.getLocalBounds().width / 2, 
        m_mazehint.getLocalBounds().height / 2 
    );
    m_mazehint.setPosition(
        m_context->m_window->getSize().x/2,
        m_context->m_window->getSize().y/2 - 50
    );

    //Congrats Text
    m_congrats.setFont(m_context->m_assets->GetFont(COMPUTER_FONT));
    m_congrats.setFillColor(sf::Color::Black);
    m_congrats.setCharacterSize(35);
    m_congrats.setString("Bravo! Vous avez reussi!");
    m_congrats.setOrigin(
        m_congrats.getLocalBounds().width / 2, 
        m_congrats.getLocalBounds().height / 2 
    );
    m_congrats.setPosition(
        m_context->m_window->getSize().x/2,
        m_context->m_window->getSize().y/2 -250
    );



    //Next Text
    m_next.setFont(m_context->m_assets->GetFont(COMPUTER_FONT));
    m_next.setFillColor(sf::Color::Blue);
    m_next.setCharacterSize(20);
    m_next.setString("Appuyer sur ENTRER pour acceder au puzzle");
    m_next.setOrigin(
        m_next.getLocalBounds().width, 
        m_next.getLocalBounds().height
    );
    m_next.setPosition(
        m_context->m_window->getSize().x-20,
        m_context->m_window->getSize().y-50
    );

}


void MECPuzzle::ProcessInput(){
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
                   m_context->m_states->Add(std::make_unique<Quizz>(m_context));
                    }
                    break;
                default:
                    break;
            }
        }
    }
}


void MECPuzzle::Update(sf::Time deltaTime) {}
        
        
void MECPuzzle::Draw() {
    m_context->m_window->clear();
    m_context->m_window->draw(m_backgroundSprite);
    m_context->m_window->draw(m_gamecontext);
    m_context->m_window->draw(m_mazehint);
    m_context->m_window->draw(m_congrats);   
    m_context->m_window->draw(m_next);
    m_context->m_window->display();
}
