#include "QCMGame.hh"
#include <iostream>

QCMGame::QCMGame(sf::RenderWindow* window)
    : window(window), currentQuestionIndex(0), timeLimit(60), completed(false) {
}

void QCMGame::init() {
    // Charger la police
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Erreur lors du chargement de la police !" << std::endl;
    }

    // Initialiser le texte
    questionText.setFont(font);
    questionText.setCharacterSize(24);
    questionText.setFillColor(sf::Color::White);
    questionText.setPosition(50, 50);

    timerText.setFont(font);
    timerText.setCharacterSize(20);
    timerText.setFillColor(sf::Color::Red);
    timerText.setPosition(500, 500);

    addQuestions();
}

void QCMGame::addQuestions() {
    questions.push_back({"Quelle est la capitale de l'Allemagne ?", {"Munich", "Berlin"}, 1});
    questions.push_back({"Quelle est la couleur de la case 1 du puzzle", {"Bleu", "Rouge", "Vert"}, 0});
    questions.push_back({"Quel est le chiffre en haut à droite du labyrinthe ?", {"1","5","9"}, 2});
    questions.push_back({"Les micro-ondes de la tour 66 sont à quel étage?", {"-1", "5","6"}, 1});
    questions.push_back({"Est-ce que ce jeu est incroyable?", {"oui","OUI!!"}, 1});
}

void QCMGame::update(float deltaTime) {
    // Gérer les événements
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
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
            if (selectedOption >= 0 && selectedOption < questions[currentQuestionIndex].options.size()) {
                if (selectedOption == questions[currentQuestionIndex].correctOption) {
                    currentQuestionIndex++;
                    if (currentQuestionIndex >= questions.size()) {
                        completed = true;
                    }
                    clock.restart();
                } else {
                    resetGame("Mauvaise réponse ! Recommencez.");
                }
            }
        }
    }

    // Vérifier si le temps est écoulé
    int timeLeft = timeLimit - clock.getElapsedTime().asSeconds();
    timerText.setString("Temps restant: " + std::to_string(timeLeft) + "s");

    if (timeLeft <= 0) {
        resetGame("Temps écoulé ! Recommencez.");
    }

    // Mettre à jour la question et les options
    questionText.setString(questions[currentQuestionIndex].questionText);
    optionsText.clear();
    for (size_t i = 0; i < questions[currentQuestionIndex].options.size(); ++i) {
        sf::Text optionText;
        optionText.setFont(font);
        optionText.setCharacterSize(20);
        optionText.setFillColor(sf::Color::White);
        optionText.setPosition(50, 150 + i * 50);
        char optionLetter = 'A' + i; // Convertir l'indice (0, 1, 2) en lettre (A, B, C)
        optionText.setString(optionLetter + std::string(". ") + questions[currentQuestionIndex].options[i]);
        optionsText.push_back(optionText);
    }
}


void QCMGame::render(sf::RenderWindow& window) {
    window.clear();

    window.draw(questionText);
    for (const auto& option : optionsText) {
        window.draw(option);
    }
    window.draw(timerText);

    window.display();
}

bool QCMGame::isCompleted() const {
    return completed;
}

void QCMGame::resetGame(const std::string& message) {
    std::cout << message << std::endl;
    currentQuestionIndex = 0;
    clock.restart();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "QCM Game");
    QCMGame game(&window);

    game.init();

    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        game.update(deltaTime);

        if (game.isCompleted()) {
            std::cout << "Félicitations ! Vous avez terminé toutes les questions." << std::endl;
            window.close();
        }

        game.render(window);
    }

    return 0;
}
