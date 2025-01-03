#include "Quizz.hh"
#include "MECEnigme.hh"
#include <SFML/Graphics.hpp>
#include <iostream>


Quizz::Quizz(std::shared_ptr<Context> &context) : 
    m_context(context), 
    m_currentQuestionIndex(0), 
    m_timeLimit(15), 
    m_completed(false)
{}

void Quizz::Init(){

    //Load Timer Font
    m_context->m_assets->AddFont(TIMER, "ASSETS/arial.ttf");


    //Question Text
    m_questionText.setFont(m_context->m_assets->GetFont(FONT2));
    m_questionText.setFillColor(sf::Color::White);
    m_questionText.setCharacterSize(40);
    m_questionText.setPosition(50, 50);

    //Timer Text
    m_timerText.setFont(m_context->m_assets->GetFont(TIMER));
    m_timerText.setFillColor(sf::Color::Red);
    m_timerText.setCharacterSize(25);
    m_timerText.setPosition(900, 50);

    AddQuestions();

}

void Quizz::ProcessInput() {
    sf::Event event;
    while (m_context->m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_context->m_window->close();
        }

        if (event.type == sf::Event::KeyPressed) {
            int selectedOption = -1;
            
            // Associer les touches A, B, C aux options 0, 1, 2
            if (event.key.code == sf::Keyboard::A) {
                selectedOption = 0;
            } else if (event.key.code == sf::Keyboard::B) {
                selectedOption = 1;
            } else if (event.key.code == sf::Keyboard::C) {
                selectedOption = 2;
            }
            // Vérifier si l'option sélectionnée est correcte
            if (selectedOption >= 0 && selectedOption < static_cast<int>(m_questions[m_currentQuestionIndex].options.size())) {
                if (selectedOption == m_questions[m_currentQuestionIndex].correctOption) {
                    m_currentQuestionIndex++;
                    if (m_currentQuestionIndex >= static_cast<int>(m_questions.size())) {
                        m_completed = true;
                    }
                    m_clock.restart();
                } else {
                    ResetGame();
                }
            }
        }
    }

    // Vérifier si le temps est écoulé
    int timeLeft = m_timeLimit - m_clock.getElapsedTime().asSeconds();
    m_timerText.setString("Temps restant: " + std::to_string(timeLeft) + "s");

    if (timeLeft <= 0) {
        ResetGame();
    }

    // Mettre à jour la question et les options
    m_questionText.setString(m_questions[m_currentQuestionIndex].questionText);
    m_optionsText.clear();
    for (size_t i = 0; i < m_questions[m_currentQuestionIndex].options.size(); ++i) {
        sf::Text optionText;
        optionText.setFont(m_context->m_assets->GetFont(FONT2));
        optionText.setCharacterSize(30);
        optionText.setFillColor(sf::Color::White);
        optionText.setPosition(50, 150 + i * 50);
        char optionLetter = 'A' + i; // Convertir l'indice (0, 1, 2) en lettre (A, B, C)
        optionText.setString(optionLetter + std::string(". ") + m_questions[m_currentQuestionIndex].options[i]);
        m_optionsText.push_back(optionText);
    }
}


void Quizz::Update(sf::Time deltaTime){
}


void Quizz::Draw() {

    while (m_context->m_window->isOpen()) {
        ProcessInput();
        m_context->m_window->clear();
        m_context->m_window->draw(m_questionText);
        for (const auto& option : m_optionsText) {
            m_context->m_window->draw(option);
        }
        m_context->m_window->draw(m_timerText);
        m_context->m_window->display();

        if (isCompleted()) {
            m_context->m_states->PopCurrent();
            m_context->m_states->Add(std::make_unique<MECEnigme>(m_context));
            break;
        }
    }
}


bool Quizz::isCompleted() const {
    return m_completed;
}


void Quizz::ResetGame(){
    m_currentQuestionIndex = 0;
    m_clock.restart();
}


void Quizz::AddQuestions(){
    m_questions.push_back({"Quelle est la capitale de l'Allemagne ?", {"Munich", "Berlin"}, 1});
    m_questions.push_back({"Quelle est la couleur de la case 1 du puzzle", {"Bleu", "Rouge", "Vert"}, 0});
    m_questions.push_back({"Si dans une course tu doubles le deuxieme, tu es?", {"Premier", "Deuxieme", "Dernier"}, 1});
    m_questions.push_back({"Quel est le chiffre en haut a droite du labyrinthe ?", {"1","5","9"}, 2});
    m_questions.push_back({"Combien y a-t-il d'arondissements a Paris?",{"21","18","20"}, 2});
    m_questions.push_back({"Les micro-ondes de la tour 66 sont a quel etage?", {"-1", "5","6"}, 1});
    m_questions.push_back({"Est-ce que ce jeu est incroyable?", {"oui","OUI!!"}, 1});
}