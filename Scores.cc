#include "Scores.hh"
#include "Classroom.hh"
#include <memory>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
Scores::Scores(std::shared_ptr<Context> &context) : m_context(context) {}


void Scores::Init(){

    m_context->m_assets->AddFont(BOARD_FONT, "ASSETS/Chalk.otf" );
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

    ifstream highscoreFile("ASSETS/highscore.txt");
    if(!highscoreFile) {
        cerr << "Failed to open highscore file." << std::endl;
        return;
    }

    string line;
    getline(highscoreFile, line);
    istringstream iss(line);
    string entry;

    while (getline(iss, entry, '|')) {
        istringstream entryStream(entry);
        string name;
        string score;

        getline(entryStream, name, ',');
        getline(entryStream, score);

        // Remove any leading/trailing whitespace
        name.erase(name.find_last_not_of(" \n\r\t") + 1);
        score.erase(score.find_last_not_of(" \n\r\t") + 1);

        int points = stoi(score);
        m_highscoreList.push_back(make_pair(name, points));
    }
    highscoreFile.close();

    // Sort the highscores in descending order
    sort(m_highscoreList.begin(), m_highscoreList.end(), []
            (const auto& a, const auto& b) {
        return a.second > b.second;
    });

    // Only keep the top 10 highscores
    if (m_highscoreList.size() > 10) {
        m_highscoreList.resize(10);
    }

    ShowHighScore();
}

void Scores::ShowHighScore(){
    m_highscoreTexts.clear();

    float y = 105.0f; // Starting position
    int rank = 1;
    for (const auto& highscore : m_highscoreList) {
        sf::Text text;
        text.setFont(m_context->m_assets->GetFont(BOARD_FONT));
        text.setCharacterSize(50);
        text.setStyle(sf::Text::Bold);
        text.setFillColor(sf::Color::White);
        text.setPosition(455.f, y);
        text.setString(std::to_string(rank) + ". " + highscore.first + "  " + std::to_string(highscore.second));
        m_highscoreTexts.push_back(text);

        rank++;
        y += 40.f;
    }
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
    for (const auto& text : m_highscoreTexts) {
        m_context->m_window->draw(text);
    }
    m_context->m_window->display();
}
