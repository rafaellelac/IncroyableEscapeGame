#include "MainMenu.hh"
#include <SFML/Window/Event.hpp>
#include "asset.hh"
#include "game.hh"
#include "Classroom.hh"

Classroom::Classroom(std::shared_ptr<Context> &context): m_context(context), isComputerSelected(false),isDoorSelected(false),isComputerPressed(false),isDoorPressed(false){   
    };


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
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (isComputerSelected) {
                    isComputerPressed = true;
                }
                if (isDoorSelected) {
                    isDoorPressed = true;
                }
            }
        }
    }
}


void Classroom::Update(sf::Time deltaTime) {}


void Classroom::Draw() {
    m_context->m_window->clear();
    m_context->m_window->draw(m_backgroundSprite);
    m_context->m_window->draw(m_computerButton);
    m_context->m_window->draw(m_doorButton);
    m_context->m_window->display();
}