#include "Door.hh"
#include "Classroom.hh"
#include "Fin.hh"
#include "game.hh"


Door::Door(std::shared_ptr<Context> &context) : m_context(context) {}


void Door::Init(){
    m_context->m_assets->AddFont(FONT2, "ASSETS/newseptember.otf" );
    m_context->m_assets->AddTexture(DOOR, "ASSETS/closeddoor.jpg" );
    
    //Background
    m_backgroundSprite.setTexture(m_context->m_assets->GetTexture(DOOR));
    m_backgroundSprite.setScale(
        m_context->m_window->getSize().x / m_backgroundSprite.getLocalBounds().width,
        m_context->m_window->getSize().y / m_backgroundSprite.getLocalBounds().height
    );

    // Text
    m_text.setFont(m_context->m_assets->GetFont(FONT2));
    m_text.setFillColor(sf::Color::Black);
    m_text.setOutlineColor(sf::Color::White);
    m_text.setOutlineThickness(1);
    m_text.setCharacterSize(50);
    m_text.setString("Entrez le code sur votre clavier");
    m_text.setOrigin(
        m_text.getLocalBounds().width / 2, 
        m_text.getLocalBounds().height / 2
    );
    m_text.setPosition(
        m_context->m_window->getSize().x/2,
        m_context->m_window->getSize().y/2 - 100
    );

    // Input box
    m_inputBox.setSize(sf::Vector2f(260, 60));
    m_inputBox.setFillColor(sf::Color::White);
    m_inputBox.setOutlineColor(sf::Color::Black);
    m_inputBox.setPosition(
        m_context->m_window->getSize().x / 2 - 130,
        m_context->m_window->getSize().y / 2
    );

    // Input Text
    m_inputText.setFont(m_context->m_assets->GetFont(FONT2));
    m_inputText.setFillColor(sf::Color::Black);
    m_inputText.setCharacterSize(48);
    m_inputText.setPosition(
        m_context->m_window->getSize().x / 2 - 130,
        m_context->m_window->getSize().y / 2 
    );

    // Check Text
    m_check.setFont(m_context->m_assets->GetFont(FONT2));
    m_check.setFillColor(sf::Color::Black);
    m_check.setOutlineColor(sf::Color::White);
    m_check.setOutlineThickness(1);
    m_check.setString("Appuyer Entrer pour valider");
    m_check.setCharacterSize(40);
    m_check.setOrigin(
        m_check.getLocalBounds().width / 2 , 
        m_check.getLocalBounds().height / 2
    );
    m_check.setPosition(
        m_context->m_window->getSize().x/2 + 300,
        m_context->m_window->getSize().y/2 + 100
    ); 

    // Wrong X
    m_wrong.setFont(m_context->m_assets->GetFont(FONT2));
    m_wrong.setFillColor(sf::Color::Transparent); //Pour l'instant le X est transparent, il sera rouge seulement si le code entre est faux
    m_wrong.setString("X");
    m_wrong.setCharacterSize(40);
    m_wrong.setOrigin(
        m_wrong.getLocalBounds().width / 2 , 
        m_wrong.getLocalBounds().height / 2
    );
    m_wrong.setPosition(
        m_context->m_window->getSize().x/2 + 300,
        m_context->m_window->getSize().y/2 
    );
  

    //Back Text
    m_back.setFont(m_context->m_assets->GetFont(FONT2));
    m_back.setFillColor(sf::Color::Blue);
    m_back.setCharacterSize(30);
    m_back.setPosition(20,20);
    m_back.setString("<- Appuyer sur la FLECHE ARRIERE ");
}


void Door::ProcessInput(){
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_context->m_window->close();
        else if (event.type == sf::Event::KeyPressed){
            switch (event.key.code){
                case sf::Keyboard::Left:
                    {
                    m_context->m_states->PopCurrent();                       
                    }
                    break;
                case sf::Keyboard::Return:
                    {
                    if (m_playerInput == "MAIN4CPP") {
                        m_context->m_states->Add(std::make_unique<Fin>(m_context)); // si le code entre est le bon, on passe a la fenetre de fin
                    } 
                    else {
                        m_playerInput.clear();  // A chaque fois qu'un code est faux, on efface le champ pour le prochain essai
                        m_wrong.setFillColor(sf::Color::Red); // le X est visible tres brievement
                    }
                }
                default:
                    break;
            }
        }
        else if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode < 128) {  // on ignore les caracteres non ASCII
                if (event.text.unicode == 8 && !m_playerInput.empty()) { // si RETOUR est appuye, on efface le dernier caractere
                    m_playerInput.pop_back();
                } else if (event.text.unicode != 8) {  // sinon, on rajoute le caractere et on efface le X si il est rouge
                    m_wrong.setFillColor(sf::Color::Transparent);
                    m_playerInput += static_cast<char>(event.text.unicode);
                }
            }
        }
        m_inputText.setString(m_playerInput); // on update le champ d'entree a chaque fois qu'un caractere est entre
            break;
    }
}

void Door::Update(sf::Time deltaTime) {
}
        
        
void Door::Draw() {
    m_context->m_window->clear();
    m_context->m_window->draw(m_backgroundSprite);
    m_context->m_window->draw(m_text);
    m_context->m_window->draw(m_inputBox);
    m_context->m_window->draw(m_inputText);
    m_context->m_window->draw(m_check);
    m_context->m_window->draw(m_wrong);
    m_context->m_window->draw(m_back);
    m_context->m_window->display();
}