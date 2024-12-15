// Puzzle.cpp
#include "Puzzle.hh"
#include <iostream>


Puzzle::Puzzle(const std::vector<int>& nums) {
    window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode(512, 512),
        "Puzzle::Remix",
        sf::Style::Titlebar | sf::Style::Close
    );
    window->setPosition(sf::Vector2i(50, 50));
    window->setFramerateLimit(60);
    event = std::make_shared<sf::Event>();

    if (!texture.loadFromFile("puzzle.png")) {
        std::cerr << "Failed to load puzzle texture" << std::endl;
        exit(1);
    }

    w = 128;
    n = 0;
    x = 0;
    y = 0;
    dx = 0;
    dy = 0;

    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            ++n;
            sprite[n].setTexture(texture);
            sprite[n].setTextureRect(sf::IntRect(i * w, j * w, w, w));
            grid[i + 1][j + 1] = nums[n - 1];
        }
    }
}

void Puzzle::events() {
    while (window->pollEvent(*event)) {
        if (event->type == sf::Event::Closed) {
            window->close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            this->logic();
        }
    }
}

void Puzzle::draw() {
    window->clear(sf::Color::Black);
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            n = grid[i + 1][j + 1];
            sprite[n].setPosition(i * w, j * w);
            window->draw(sprite[n]);
        }
    }
    window->display();
}

void Puzzle::logic() {
    sf::Vector2i pos = sf::Mouse::getPosition(*window);
    x = pos.x / w + 1;
    y = pos.y / w + 1;

    if (grid[x + 1][y] == 16) {
        dx = 1;
    }

    if (grid[x - 1][y] == 16) {
        dx = -1;
    }

    if (grid[x][y + 1] == 16) {
        dy = 1;
    }

    if (grid[x][y - 1] == 16) {
        dy = -1;
    }

    n = grid[x][y];
    grid[x][y] = 16;
    grid[x + dx][y + dy] = n;
    dx = 0;
    dy = 0;
}

void Puzzle::init() {
    // Initialize the game (if needed)
}

void Puzzle::update(float deltaTime) {
    events(); // Call the events method to handle input
}

void Puzzle::render(sf::RenderWindow& window) {
    draw(); // Call the draw method to render the game
}

bool Puzzle::isCompleted() const {
    // Check if the puzzle is completed
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            if (grid[i + 1][j + 1] != (i * 4 + j + 1)) {
                return false;
            }
        }
    }
    return true;
}