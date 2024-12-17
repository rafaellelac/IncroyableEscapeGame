// EinsteinPuzzle.cpp
#include "einstein.hh"
#include <iostream>

EinsteinPuzzle::EinsteinPuzzle()
    : window(sf::VideoMode(400, 400), "Einstein Puzzle Game"),
      isDragging(false),
      currentDraggable(nullptr) {
    loadResources();
    reset();
}

void EinsteinPuzzle::loadResources() {
    // Load maison textures
    maisonTextures[0].loadFromFile("resources/maison_bleu.png");
    maisonTextures[1].loadFromFile("resources/maison_rouge.png");
    maisonTextures[2].loadFromFile("resources/maison_verte.png");

    // Load boisson textures
    boissonTextures[0].loadFromFile("resources/cafe.png");
    boissonTextures[1].loadFromFile("resources/lait.png");
    boissonTextures[2].loadFromFile("resources/tea.png");

    // Load animal textures
    animalTextures[0].loadFromFile("resources/poisson.png");
    animalTextures[1].loadFromFile("resources/chien.png");
    animalTextures[2].loadFromFile("resources/chat.png");

    femmeTextures[0].loadFromFile("resources/josephine_backer.png");
    femmeTextures[1].loadFromFile("resources/marie_curie.png");
    femmeTextures[2].loadFromFile("resources/simone_veil.png");
}
void EinsteinPuzzle::reset() {
    // Initialize the grid with unique values
    for (int i = 0; i < 3; ++i) {
        grid[i].maison.setTexture(maisonTextures[i]);
        grid[i].femme.setTexture(femmeTextures[i]);
        grid[i].boisson.setTexture(boissonTextures[i]);
        grid[i].animal.setTexture(animalTextures[i]);

        grid[i].maison.setPosition(i * 160.0f, 0);
        grid[i].femme.setPosition(i * 160.0f, 100.0f);
        grid[i].boisson.setPosition(i * 160.0f, 200.0f);
        grid[i].animal.setPosition(i * 160.0f, 300.0f);

        // Set the scale to control the size of the images
        grid[i].maison.setScale(0.5f, 0.5f);
        grid[i].femme.setScale(0.25f, 0.25f);
        grid[i].boisson.setScale(0.1f, 0.1f);
        grid[i].animal.setScale(0.1f, 0.1f);
    }

    // Shuffle the grid to randomize the initial positions
    std::random_shuffle(grid.begin(), grid.end());
}

void EinsteinPuzzle::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            for (int i = 0; i < 3; ++i) {
                if (grid[i].maison.getGlobalBounds().contains(window.mapPixelToCoords(mousePos))) {
                    isDragging = true;
                    currentDraggable = &grid[i].maison;
                    dragOffset = mousePos - sf::Vector2i(currentDraggable->getPosition());
                    break;
                }
                if (grid[i].femme.getGlobalBounds().contains(window.mapPixelToCoords(mousePos))) {
                    isDragging = true;
                    currentDraggable = &grid[i].femme;
                    dragOffset = mousePos - sf::Vector2i(currentDraggable->getPosition());
                    break;
                }
                if (grid[i].boisson.getGlobalBounds().contains(window.mapPixelToCoords(mousePos))) {
                    isDragging = true;
                    currentDraggable = &grid[i].boisson;
                    dragOffset = mousePos - sf::Vector2i(currentDraggable->getPosition());
                    break;
                }
                if (grid[i].animal.getGlobalBounds().contains(window.mapPixelToCoords(mousePos))) {
                    isDragging = true;
                    currentDraggable = &grid[i].animal;
                    dragOffset = mousePos - sf::Vector2i(currentDraggable->getPosition());
                    break;
                }
            }
        } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            if (isDragging && currentDraggable) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                int x = mousePos.x / 160;
                if (x >= 0 && x < 5) {
                    currentDraggable->setPosition(x * 160.0f, currentDraggable->getPosition().y);
                }
                isDragging = false;
                currentDraggable = nullptr;
            }
        }
        if (checkSolution()) {
            std::cout << "Solution found! Closing the window." << std::endl;
            window.close();
        }
    }
}

void EinsteinPuzzle::update() {
    if (isDragging && currentDraggable) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        currentDraggable->setPosition(mousePos.x - dragOffset.x, currentDraggable->getPosition().y);
    }
}

void EinsteinPuzzle::draw() {
    window.clear(sf::Color::White);
    for (int i = 0; i < 3; ++i) {
        window.draw(grid[i].maison);
        window.draw(grid[i].femme);
        window.draw(grid[i].boisson);
        window.draw(grid[i].animal);
    }
    window.display();
}

bool EinsteinPuzzle::checkSolution() {
    // Check the solution conditions
    // JB(0) maison verte (2) lait(1) et chien(1)
    if (grid[0].maison.getTexture() != &maisonTextures[2]) return false;
    if (grid[0].femme.getTexture() != &femmeTextures[0]) return false;
    if (grid[0].boisson.getTexture() != &boissonTextures[1]) return false;
    if (grid[0].animal.getTexture() != &animalTextures[2]) return false;
    // MC(1) maison bleue(2) thé(2) et poisson(0)
    if (grid[1].femme.getTexture() != &femmeTextures[1]) return false;
    if (grid[1].maison.getTexture() != &maisonTextures[0]) return false;
    if (grid[1].boisson.getTexture() != &boissonTextures[2]) return false;
    if (grid[1].animal.getTexture() != &animalTextures[1]) return false;
    // SV(2) maison rouge(0) café(0) et chat(2)
    if (grid[2].femme.getTexture() != &femmeTextures[2]) return false;
    if (grid[2].boisson.getTexture() != &boissonTextures[0]) return false;
    if (grid[2].maison.getTexture() != &maisonTextures[0]) return false;
    if (grid[2].animal.getTexture() != &animalTextures[2]) return false;

    return true;
}

void EinsteinPuzzle::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        draw();
        if (checkSolution()) {
            std::cout << "Solution found! Closing the window." << std::endl;
            window.close();
        }
    }
}