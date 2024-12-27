#pragma once
#include "Minigame.hh"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

struct Question {
    std::string questionText;
    std::vector<std::string> options;
    int correctOption; // Index de la bonne réponse (0, 1, 2, ...)
};

class QCMGame : public MiniGame {
private:
    sf::RenderWindow* window;
    sf::Font font;
    sf::Text questionText;
    std::vector<sf::Text> optionsText;
    sf::Text timerText;
    std::vector<Question> questions;
    int currentQuestionIndex;
    sf::Clock clock;
    int timeLimit;
    bool completed;

public:
    QCMGame(sf::RenderWindow* window);
    virtual void init() override;
    virtual void update(float deltaTime) override;
    virtual void render(sf::RenderWindow& window) override;
    virtual bool isCompleted() const override;

private:
    void resetGame(const std::string& message);
    void addQuestions();
};
