#include "Puzzle.hh"
#include "MECQuizz.hh"
#include <SFML/Graphics.hpp>
#include <iostream>


Puzzle::Puzzle(std::shared_ptr<Context> &context): 
    m_context(context),
    w(128),
    n(0),
    x(0),
    y(0),
    dx(0),
    dy(0)
    {
    // Initialisation des numéros du puzzle
    for (int i = 1; i <= 16; ++i) {
        m_nums.push_back(i);
    }

    // Création de la fenêtre du puzzle
    m_window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode(512, 512),
        "Puzzle",
        sf::Style::Titlebar | sf::Style::Close
    );
    m_window->setPosition(sf::Vector2i(50, 50));
    m_window->setFramerateLimit(60);
    m_event = std::make_shared<sf::Event>();
    }

Puzzle::~Puzzle() {
    m_window.reset(); // Assurer que la fenêtre est fermée et libérée
}

void Puzzle::Init() {

    // Charger la texture du puzzle
   m_context->m_assets->AddTexture(PUZZLE, "ASSETS/puzzle.png" );
    
    // Initialiser le générateur de nombres aléatoires
    std::srand(std::time(nullptr));

    // Mélanger le vecteur pour randomiser le puzzle
    std::random_shuffle(m_nums.begin(), m_nums.end());

    // Initialiser les sprites du puzzle
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
                ++n;
                m_sprite[n].setTexture(m_context->m_assets->GetTexture(PUZZLE));
                m_sprite[n].setTextureRect(sf::IntRect(i * w, j * w, w, w));
                m_grid[i + 1][j + 1] = m_nums[n - 1];
        }
    }
}


void Puzzle::ProcessInput() {
    dx=0;
    dy=0;
    x=0;
    y=0;
    // Gérer les événements de la fenêtre
    while (m_window->pollEvent(*m_event)) { 
            if (m_event->type == sf::Event::Closed) { 
                m_window->close();
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { // Vérifier si le bouton gauche de la souris est enfoncé
                sf::Vector2i pos = sf::Mouse::getPosition(*m_window); // Obtenir la position de la souris
                x = pos.x / w + 1; // Calculer la position x
                y = pos.y / w + 1; // Calculer la position y

            // Vérifier les mouvements possibles
            if (x+1<5 && m_grid[x + 1][y] == 16) {
                dx = 1;
            }

            if (x-1>0 && m_grid[x - 1][y] == 16) {
                dx = -1;
            }

            if (y+1<5 && m_grid[x][y + 1] == 16) {
                dy = 1;
            }

            if (y-1>0 && m_grid[x][y - 1] == 16) {
                dy = -1;
            }

            // Effectuer le mouvement
            if (dx != 0 || dy != 0) {
                n = m_grid[x][y];
                m_grid[x][y] = 16;
                m_grid[x + dx][y + dy] = n;
                dx = 0;
                dy = 0;
            }
        }
    }
}
void Puzzle::Update(sf::Time deltaTime) {
    // Mise à jour du puzzle (actuellement vide)
}

void Puzzle::Draw() {
    while (m_window->isOpen()){
        
        ProcessInput();

        m_window->clear(sf::Color::Black); 
            for (size_t i = 0; i < 4; ++i) {
                for (size_t j = 0; j < 4; ++j) {
                    n = m_grid[i + 1][j + 1]; // Obtenir le numéro du puzzle
                    m_sprite[n].setPosition(i * w, j * w); // Définir la position du puzzle
                    m_window->draw(m_sprite[n]); // Dessiner le puzzle
                }
            }
    
        m_window->display();

        // Vérifier si le puzzle est complété
        if (isCompleted()){
            m_window->close();
            m_context->m_states->PopCurrent(); 
            m_context->m_states->Add(std::make_unique<MECQuizz>(m_context));
        }
    }
}

bool Puzzle::isCompleted() const { // fonction qui retourne si le puzzle est terminé
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) { 
            if (m_grid[i + 1][j + 1] != static_cast<int>(i * 4 + j + 1)) { // Vérifier si le puzzle est dans l'ordre
                return false;
            }
        }
    }
    return true;
}
