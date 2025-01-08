#include "LastScreen.hh"
#include "Classroom.hh"


LastScreen::LastScreen(std::shared_ptr<Context> &context) : MEC(context) {}


void LastScreen::Init(){


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
    m_gamecontext.setString("Felicitations! il ne vous reste plus qu'a \nremettre ce code dans l'ordre\n et l'utiliser pour ouvrir la porte!");
    m_gamecontext.setOrigin(
        m_gamecontext.getLocalBounds().width / 2, 
        m_gamecontext.getLocalBounds().height / 2
    );
    m_gamecontext.setPosition(
        m_context->m_window->getSize().x/2,
        m_context->m_window->getSize().y/2 - 150
    );

    //code 1 
    m_code1.setFont(m_context->m_assets->GetFont(FONT2));
    m_code1.setFillColor(sf::Color::Red);
    m_code1.setCharacterSize(50);
    m_code1.setString("IN");
    m_code1.setPosition(400,450);

    //code 2
    m_code2.setFont(m_context->m_assets->GetFont(FONT2));
    m_code2.setFillColor(sf::Color::Red);
    m_code2.setCharacterSize(50);
    m_code2.setString("PP");
    m_code2.setPosition(500,450);

    //code 3
    m_code3.setFont(m_context->m_assets->GetFont(FONT2));
    m_code3.setFillColor(sf::Color::Red);
    m_code3.setCharacterSize(50);
    m_code3.setString("4C");
    m_code3.setPosition(600,450);

    //code 4
    m_code4.setFont(m_context->m_assets->GetFont(FONT2));
    m_code4.setFillColor(sf::Color::Red);
    m_code4.setCharacterSize(50);
    m_code4.setString("MA");
    m_code4.setPosition(700,450);



    //Next Text
    m_next.setFont(m_context->m_assets->GetFont(COMPUTER_FONT));
    m_next.setFillColor(sf::Color::Blue);
    m_next.setCharacterSize(20);
    m_next.setString("Appuyer sur ENTRER pour revenir dans la salle");
    m_next.setOrigin(
        m_next.getLocalBounds().width, 
        m_next.getLocalBounds().height
    );
    m_next.setPosition(
        m_context->m_window->getSize().x-20,
        m_context->m_window->getSize().y-50
    );

}


void LastScreen::ProcessInput(){
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_context->m_window->close();
        else if (event.type == sf::Event::KeyPressed){
            switch (event.key.code){
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


void LastScreen::Update(sf::Time deltaTime) {}
        
        
void LastScreen::Draw() {
    m_context->m_window->clear();
    m_context->m_window->draw(m_backgroundSprite);
    m_context->m_window->draw(m_gamecontext);
    m_context->m_window->draw(m_code1);
    m_context->m_window->draw(m_code2);
    m_context->m_window->draw(m_code3);
    m_context->m_window->draw(m_code4);
    m_context->m_window->draw(m_next);
    m_context->m_window->display();
}