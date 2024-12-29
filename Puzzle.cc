#include "Puzzle.hh"
#include <SFML/Graphics.hpp>
#include "asset.hh"
#include "MECPuzzle.hh"
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
    for (int i = 1; i <= 16; ++i) {
        m_nums.push_back(i);
    }

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
    m_window.reset(); // Ensure the window is closed and released
}

void Puzzle::Init() {

    // Load the puzzle texture
    if (!m_texture.loadFromFile("ASSETS/puzzle.png")) {
        std::cerr << "Failed to load texture" << std::endl;
        return;
    }
    
    //Seed the random number generator
    std::srand(std::time(nullptr));

    // Shuffle the vector to randomize the puzzle
    std::random_shuffle(m_nums.begin(), m_nums.end());

    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
                ++n;
                m_sprite[n].setTexture(m_texture);
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
    while (m_window->pollEvent(*m_event)) {
            if (m_event->type == sf::Event::Closed) {
                m_window->close();
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i pos = sf::Mouse::getPosition(*m_window);
                x = pos.x / w + 1;
                y = pos.y / w + 1;

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
}

void Puzzle::Draw() {
    while (m_window->isOpen()){
        
        ProcessInput();

        m_window->clear(sf::Color::Black);
            for (size_t i = 0; i < 4; ++i) {
                for (size_t j = 0; j < 4; ++j) {
                    n = m_grid[i + 1][j + 1];
                    m_sprite[n].setPosition(i * w, j * w);
                    m_window->draw(m_sprite[n]);
                }
            }
    
        m_window->display();

        if (isCompleted()){
            m_window->close();
            m_context->m_states->PopCurrent(); 
            m_context->m_states->Add(std::make_unique<MECPuzzle>(m_context));
        }
    }
}

bool Puzzle::isCompleted() const {
    // Check if the puzzle is completed
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            if (m_grid[i + 1][j + 1] != static_cast<int>(i * 4 + j + 1)) {
                return false;
            }
        }
    }
    return true;
}
