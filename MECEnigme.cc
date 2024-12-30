#include "MECEnigme.hh"
#include <memory>
#include "MazeGame.hh"
//#include "Enigme.hh"


MECEnigme::MECEnigme(std::shared_ptr<Context> &context) : MEC(context) {}


void MECEnigme::Init(){

    m_context->m_assets->AddTexture(COMPUTER_SCREEN, "ASSETS/computerscreen.jpg" );

    //Background
    m_backgroundSprite.setTexture(m_context->m_assets->GetTexture(COMPUTER_SCREEN));
    m_backgroundSprite.setScale(
        m_context->m_window->getSize().x / m_backgroundSprite.getLocalBounds().width,
        m_context->m_window->getSize().y / m_backgroundSprite.getLocalBounds().height
    );

    //Context Text
    m_enigmecontext.setFont(m_context->m_assets->GetFont(COMPUTER_FONT));
    m_enigmecontext.setFillColor(sf::Color::Black);
    m_enigmecontext.setCharacterSize(30);
    m_enigmecontext.setString("C'est l'heure de verifier si vous etes attentifs! \nRepondez aux questions suivantes \ndans le temps imparti. \n\nAttention, a la moindre erreur il faudra \nrecommencer!\nLe chrono tourne... Bonne chance!");
    m_enigmecontext.setOrigin(
        m_enigmecontext.getLocalBounds().width / 2, 
        m_enigmecontext.getLocalBounds().height / 2
    );
    m_enigmecontext.setPosition(
        m_context->m_window->getSize().x/2,
        m_context->m_window->getSize().y/2 + 150
    );

    //Hint text
    m_quizzhint.setFont(m_context->m_assets->GetFont(COMPUTER_FONT));
    m_quizzhint.setFillColor(sf::Color::Red);
    m_quizzhint.setCharacterSize(35);
    m_quizzhint.setString("Indice 2: blablabla");
    m_quizzhint.setOrigin(
        m_quizzhint.getLocalBounds().width / 2, 
        m_quizzhint.getLocalBounds().height / 2 
    );
    m_quizzhint.setPosition(
        m_context->m_window->getSize().x/2,
        m_context->m_window->getSize().y/2 - 100
    );

    //Congrats Text
    m_congrats.setFont(m_context->m_assets->GetFont(COMPUTER_FONT));
    m_congrats.setFillColor(sf::Color::Black);
    m_congrats.setCharacterSize(35);
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


void MECEnigme::ProcessInput(){
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
                  // add enigme state here
                    }
                    break;
                default:
                    break;
            }
        }
    }
}
        
void MECEnigme::Draw() {
    m_context->m_window->clear();
    m_context->m_window->draw(m_backgroundSprite);
    m_context->m_window->draw(m_enigmecontext);
    m_context->m_window->draw(m_quizzhint);
    m_context->m_window->draw(m_congrats);   
    m_context->m_window->draw(m_next);
    m_context->m_window->display();
}
