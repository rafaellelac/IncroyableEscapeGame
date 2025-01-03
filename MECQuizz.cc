#include "MECQuizz.hh"
#include "Quizz.hh"


MECQuizz::MECQuizz(std::shared_ptr<Context> &context) : MEC(context) {}


void MECQuizz::Init(){


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
    m_gamecontext.setCharacterSize(27);
    m_gamecontext.setString("C'est l'heure de verifier si vous etes attentifs! \nRepondez aux questions suivantes \ndans le temps imparti. \n\nAttention, a la moindre erreur il faudra \nrecommencer!\nLe chrono tourne... Bonne chance!\n\nP.S:Utilisez les touches A/B/C pour repondre");
    m_gamecontext.setOrigin(
        m_gamecontext.getLocalBounds().width / 2, 
        m_gamecontext.getLocalBounds().height / 2
    );
    m_gamecontext.setPosition(
        m_context->m_window->getSize().x/2,
        m_context->m_window->getSize().y/2 + 150
    );

    //Hint text
    m_puzzlehint.setFont(m_context->m_assets->GetFont(COMPUTER_FONT));
    m_puzzlehint.setFillColor(sf::Color::Red);
    m_puzzlehint.setCharacterSize(35);
    m_puzzlehint.setString("Indice 2: Marie Curie habite au dessus de la \nmaison verte et boit du the");
    m_puzzlehint.setOrigin(
        m_puzzlehint.getLocalBounds().width / 2, 
        m_puzzlehint.getLocalBounds().height / 2 
    );
    m_puzzlehint.setPosition(
        m_context->m_window->getSize().x/2,
        m_context->m_window->getSize().y/2 - 100
    );

    //Congrats Text
    m_congrats.setFont(m_context->m_assets->GetFont(COMPUTER_FONT));
    m_congrats.setFillColor(sf::Color::Black);
    m_congrats.setCharacterSize(30);
    m_congrats.setString("Pas mal! Mais vous n'etes qu'a mi-chemin \net le temps presse");
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
    m_next.setString("Appuyer sur ENTRER pour acceder au quizz");
    m_next.setOrigin(
        m_next.getLocalBounds().width, 
        m_next.getLocalBounds().height
    );
    m_next.setPosition(
        m_context->m_window->getSize().x-20,
        m_context->m_window->getSize().y-50
    );

}


void MECQuizz::ProcessInput(){
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

void MECQuizz::Update(sf::Time deltaTime) {}
      
void MECQuizz::Draw() {
    m_context->m_window->clear();
    m_context->m_window->draw(m_backgroundSprite);
    m_context->m_window->draw(m_gamecontext);
    m_context->m_window->draw(m_puzzlehint);
    m_context->m_window->draw(m_congrats);   
    m_context->m_window->draw(m_next);
    m_context->m_window->display();
}
