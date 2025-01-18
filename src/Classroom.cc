#include "Classroom.hh"
#include "MainMenu.hh"
#include "asset.hh"
#include "game.hh"
#include "MECMaze.hh"
#include "HS.hh"
#include "Door.hh"
#include <SFML/Window/Event.hpp>

Classroom::Classroom(std::shared_ptr<Context> &context): 
        m_context(context), 
        isComputerSelected(false),
        isDoorSelected(false),
        isComputer2Selected(false),
        isComputer3Selected(false),
        isComputer4Selected(false),
        isComputerPressed(false),
        isDoorPressed(false),
        isComputer2Pressed(false),
        isComputer3Pressed(false),
        isComputer4Pressed(false)
        {};


void Classroom::Init(){


    //Background
    m_backgroundSprite.setTexture(m_context->m_assets->GetTexture(CLASSROOM));
    m_backgroundSprite.setScale(
        m_context->m_window->getSize().x / m_backgroundSprite.getLocalBounds().width,
        m_context->m_window->getSize().y / m_backgroundSprite.getLocalBounds().height
    );

    //Computer Button
    m_computerButton.setFont(m_context->m_assets->GetFont(COMPUTER_FONT));
    m_computerButton.setFillColor(sf::Color::Transparent);
    m_computerButton.setString("Click me");
    m_computerButton.setCharacterSize(12);
    m_computerButton.setOrigin(
        m_computerButton.getLocalBounds().width / 2,
        m_computerButton.getLocalBounds().height / 2
    );
    m_computerButton.setPosition(
        m_context->m_window->getSize().x/1.37,
        m_context->m_window->getSize().y/1.75
    );

    //Computer Button2
    m_computerButton2.setFont(m_context->m_assets->GetFont(COMPUTER_FONT));
    m_computerButton2.setFillColor(sf::Color::Transparent);
    m_computerButton2.setString("Click me");
    m_computerButton2.setCharacterSize(12);
    m_computerButton2.setOrigin(
        m_computerButton2.getLocalBounds().width / 2,
        m_computerButton2.getLocalBounds().height / 2
    );
    m_computerButton2.setPosition(
        m_context->m_window->getSize().x / 1.17,
        m_context->m_window->getSize().y / 1.75
    );

    //Computer Button3
    m_computerButton3.setFont(m_context->m_assets->GetFont(COMPUTER_FONT));
    m_computerButton3.setFillColor(sf::Color::Transparent);
    m_computerButton3.setString("Click me");
    m_computerButton3.setCharacterSize(12);
    m_computerButton3.setOrigin(
        m_computerButton3.getLocalBounds().width / 2,
        m_computerButton3.getLocalBounds().height / 2
    );
    m_computerButton3.setPosition(
        m_context->m_window->getSize().x / 4.1,
        m_context->m_window->getSize().y / 1.75
    );

    //Computer Button4
    m_computerButton4.setFont(m_context->m_assets->GetFont(COMPUTER_FONT));
    m_computerButton4.setFillColor(sf::Color::Transparent);
    m_computerButton4.setString("Click me");
    m_computerButton4.setCharacterSize(12);
    m_computerButton4.setOrigin(
        m_computerButton4.getLocalBounds().width / 2,
        m_computerButton4.getLocalBounds().height / 2
    );
    m_computerButton4.setPosition(
        m_context->m_window->getSize().x/ 9,
        m_context->m_window->getSize().y/ 1.75
    );

    //Door Button
    m_doorButton.setFont(m_context->m_assets->GetFont(COMPUTER_FONT));
    m_doorButton.setFillColor(sf::Color::Transparent);
    m_doorButton.setString("Click me");
    m_doorButton.setCharacterSize(15);
    m_doorButton.setOrigin(
        m_doorButton.getLocalBounds().width / 2,
        m_doorButton.getLocalBounds().height / 2
    );
    m_doorButton.setPosition(
        m_context->m_window->getSize().x / 1.15,
        m_context->m_window->getSize().y / 2.2
    );
} 


void Classroom::ProcessInput(){
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_context->m_window->close();
        else if (event.type == sf::Event::MouseMoved) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*m_context->m_window);
        //Les boutons ne se voient que si la souris est positionee dessus, sinon ils restent transparents
            if (m_computerButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                m_computerButton.setFillColor(sf::Color::Red);
                isComputerSelected = true;
            } else {
                m_computerButton.setFillColor(sf::Color::Transparent);
                isComputerSelected = false;
            }
            if (m_doorButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                m_doorButton.setFillColor(sf::Color::Red);
                isDoorSelected = true;
            } else {
                m_doorButton.setFillColor(sf::Color::Transparent);
                isDoorSelected = false;
            }
            if (m_computerButton2.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                m_computerButton2.setFillColor(sf::Color::Red);
                isComputer2Selected = true;
            } else {
                m_computerButton2.setFillColor(sf::Color::Transparent);
                isComputer2Selected = false;
            }
            if (m_computerButton3.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                m_computerButton3.setFillColor(sf::Color::Red);
                isComputer3Selected = true;
            } else {
                m_computerButton3.setFillColor(sf::Color::Transparent);
                isComputer3Selected = false;
            }
            if (m_computerButton4.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                m_computerButton4.setFillColor(sf::Color::Red);
                isComputer4Selected = true;
            } else {
                m_computerButton4.setFillColor(sf::Color::Transparent);
                isComputer4Selected = false;
            }
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (isComputerSelected) {
                    isComputerPressed = true;
                }
                if (isComputer2Selected){
                    isComputer2Pressed = true;
                }
                if (isComputer3Selected){
                    isComputer3Pressed = true;
                }
                if (isComputer4Selected){
                    isComputer4Pressed = true;
                }
                if (isDoorSelected) {
                    isDoorPressed = true;
                }
            }
        }
    }
}


void Classroom::Update(sf::Time deltaTime) {
    // on va au 'state' precise dans le cas ou un bouton est appuye
    if (isComputerPressed) {
        m_context->m_states->Add(std::make_unique<MECMaze>(m_context));
        isComputerPressed = false;
    }
    if (isDoorPressed) {
        m_context->m_states->Add(std::make_unique<Door>(m_context));
        isDoorPressed = false;
    }
   if (isComputer2Pressed){
        m_context->m_states->Add(std::make_unique<HS>(m_context));
        isComputer2Pressed = false;
   }
   if (isComputer3Pressed){
        m_context->m_states->Add(std::make_unique<HS>(m_context));
        isComputer3Pressed = false;
   }
   if (isComputer4Pressed){
        m_context->m_states->Add(std::make_unique<HS>(m_context));
        isComputer4Pressed = false;
   }


}


void Classroom::Draw() {
    m_context->m_window->clear();
    m_context->m_window->draw(m_backgroundSprite);
    m_context->m_window->draw(m_computerButton);
    m_context->m_window->draw(m_computerButton2);
    m_context->m_window->draw(m_computerButton3);
    m_context->m_window->draw(m_computerButton4);
    m_context->m_window->draw(m_doorButton);
    m_context->m_window->display();
}