#include "MECEnigme.hh"
#include "Enigme.hh"
#include <memory>


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
    m_gamecontext.setFont(m_context->m_assets->GetFont(COMPUTER_FONT));
    m_gamecontext.setFillColor(sf::Color::Black);
    m_gamecontext.setCharacterSize(24);
    m_gamecontext.setString("J'espere que tu connais l'enigme d'einstein \nparce qu'il faut maintenant en resoudre une variante \nsur des femmes incroyables!\n\nTu peux bouger les images pour trouver \nles bonnes combinaisons.Une fois sur(e) des combinaisons,\nreponds a la question en dessous et valide la reponse\n\nBonne chance!");
    m_gamecontext.setOrigin(
        m_gamecontext.getLocalBounds().width / 2, 
        m_gamecontext.getLocalBounds().height / 2
    );
    m_gamecontext.setPosition(
        m_context->m_window->getSize().x/2,
        m_context->m_window->getSize().y/2 + 150
    );

    //Hint text
    m_quizzhint.setFont(m_context->m_assets->GetFont(COMPUTER_FONT));
    m_quizzhint.setFillColor(sf::Color::Red);
    m_quizzhint.setCharacterSize(35);
    m_quizzhint.setString("Indice 3: Le chat habite la maison rouge\n en haut de la rue");
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
    m_congrats.setString("Voici le dernier indice!");
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
    m_next.setString("Appuyer sur ENTRER pour acceder a l'enigme");
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
                    m_context->m_states->Add(std::make_unique<Enigme>(m_context));
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
    m_context->m_window->draw(m_gamecontext);
    m_context->m_window->draw(m_quizzhint);
    m_context->m_window->draw(m_congrats);   
    m_context->m_window->draw(m_next);
    m_context->m_window->display();
}
