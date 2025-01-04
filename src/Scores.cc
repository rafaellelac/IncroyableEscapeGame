#include "Scores.hh"
#include "Classroom.hh"
#include <memory>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
Scores::Scores(std::shared_ptr<Context> &context) : m_context(context) {}


void Scores::Init(){

    m_context->m_assets->AddFont(BOARD_FONT, "ASSETS/Chalk.ttf" );
    m_context->m_assets->AddTexture(BOARD, "ASSETS/blackboard.jpg" );

    //Background
    m_backgroundSprite.setTexture(m_context->m_assets->GetTexture(BOARD));
    m_backgroundSprite.setScale(
        m_context->m_window->getSize().x / m_backgroundSprite.getLocalBounds().width,
        m_context->m_window->getSize().y / m_backgroundSprite.getLocalBounds().height
    );


    //Back Text
    m_back.setFont(m_context->m_assets->GetFont(BOARD_FONT));
    m_back.setFillColor(sf::Color::White);
    m_back.setCharacterSize(30);
    m_back.setPosition(20,20);
    m_back.setString("Appuyer sur RETOUR pour retourner au Menu Principal");

    LoadHighScores();
}


void Scores::LoadHighScores() {
    std::ifstream highscoreFile("ASSETS/highscore.txt");
    if (highscoreFile.is_open()) {
        std::string line;
        m_scores.clear();  // Clear previous scores if reloading
        while (std::getline(highscoreFile, line)) {
            std::istringstream lineStream(line);
            std::string name, time;
            lineStream >> name;
            std::getline(lineStream, time);  // Get the rest of the line as the time
            m_scores.emplace_back(name + " " + time);
        }
        highscoreFile.close();
    } else {
        std::cerr << "Unable to open highscores.txt" << std::endl;
    }

    // Combine the scores into a single string for display
    std::string scoresStr;
    for (const auto &score : m_scores) {
        scoresStr += score + "\n";
    }
    m_scoresText.setString(scoresStr);

    // Set text properties
    m_scoresText.setFont(m_context->m_assets->GetFont(BOARD_FONT));
    m_scoresText.setFillColor(sf::Color::White);
    m_scoresText.setCharacterSize(50);
    m_scoresText.setPosition(50, 100);
}



void Scores::ProcessInput(){
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
                default:
                    break;
            }
        }
    }
}


void Scores::Update(sf::Time deltaTime) {}
        
        
void Scores::Draw() {
    m_context->m_window->clear();
    m_context->m_window->draw(m_backgroundSprite);
    m_context->m_window->draw(m_back);
    m_context->m_window->draw(m_scoresText);
    m_context->m_window->display();
}
