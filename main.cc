// main.cpp
/*#include <SFML/Graphics.hpp>
#include "Maze.hh"


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Maze Game");

    MazeGame mazeGame;
    mazeGame.init();

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float deltaTime = clock.restart().asSeconds();

        mazeGame.update(deltaTime);

        window.clear(sf::Color::White); // Set the background color to white
        mazeGame.render(window);
        window.display();

        if (mazeGame.isCompleted()) {
            // Move to the next game or end the game
            break;
        }
    }

    return 0;
}*/
/*#include <SFML/Graphics.hpp>
#include "Puzzle.hh"
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <iostream>


int main() {
    // Seed the random number generator
    std::srand(std::time(nullptr));

    // Generate a vector of numbers from 1 to 16
    std::vector<int> nums;
    for (int i = 1; i <= 16; ++i) {
        nums.push_back(i);
    }

    // Shuffle the vector to randomize the puzzle
    std::random_shuffle(nums.begin(), nums.end());

    // Create a unique pointer to the Puzzle object
    auto puzzle = std::make_unique<Puzzle>(nums);

    // Initialize the puzzle
    puzzle->init();

    sf::Clock clock;

    // Main game loop
    while (puzzle->window->isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        puzzle->update(deltaTime);

        // Check if the puzzle is completed
        if (puzzle->isCompleted()) {
            std::cout << "Puzzle completed! Closing the window." << std::endl;
            puzzle->window->close();
        }

        puzzle->render(*puzzle->window);
    }

    return 0;
}*/
#include "einstein.hh"

int main() {
    EinsteinPuzzle puzzle;
    puzzle.run();
    return 0;
}