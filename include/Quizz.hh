#pragma once
#include "Minigame.hh"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "game.hh"

struct Question {
    std::string questionText;
    std::vector<std::string> options;
    int correctOption; // Index de la bonne réponse (0, 1, 2, ...)
};


class Quizz : public MiniGame {

    private:
        std::shared_ptr<Context> m_context;
        sf::Text m_questionText;
        std::vector<sf::Text> m_optionsText;
        sf::Text m_timerText;
        std::vector<Question> m_questions;
        int m_currentQuestionIndex;
        sf::Clock m_clock;
        int m_timeLimit;
        bool m_completed;


    public:
        Quizz(std::shared_ptr<Context> &context);
        void Init() override;
        void ProcessInput() override;
        void Update(sf::Time deltaTime) override;
        void Draw() override;
        bool isCompleted() const override;
        void ResetGame();
        void AddQuestions();
        // Surcharge de l'opérateur += pour ajouter une nouvelle question
        Quizz& operator+=(const Question& question) {
            m_questions.push_back(question);
            return *this;
        }
};