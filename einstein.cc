// EinsteinPuzzle.cpp
#include "einstein.hh"
#include <iostream>

EinsteinPuzzle::EinsteinPuzzle()
    : window(sf::VideoMode(800, 800), "Einstein Puzzle Game"),
      isDragging(false),
      currentDraggable(nullptr) {
    loadResources();
    reset();
}

void EinsteinPuzzle::loadResources() {
    // Load maison textures
    maisonTextures[0].loadFromFile("resources/maison_blanche.png");
    maisonTextures[1].loadFromFile("resources/maison_bleue.png");
    maisonTextures[2].loadFromFile("resources/maison_jaune.png");
    maisonTextures[3].loadFromFile("resources/maison_rouge.png");
    maisonTextures[4].loadFromFile("resources/maison_verte.png");

    // Load nationalite textures
    nationaliteTextures[0].loadFromFile("resources/norvege.png");
    nationaliteTextures[1].loadFromFile("resources/uk.png");
    nationaliteTextures[2].loadFromFile("resources/danemark.png");
    nationaliteTextures[3].loadFromFile("resources/allemand.png");
    nationaliteTextures[4].loadFromFile("resources/suede.png");

    // Load boisson textures
    boissonTextures[0].loadFromFile("resources/beer.png");
    boissonTextures[1].loadFromFile("resources/cafe.png");
    boissonTextures[2].loadFromFile("resources/eau.png");
    boissonTextures[3].loadFromFile("resources/lait.png");
    boissonTextures[4].loadFromFile("resources/tea.png");

    // Load cigare textures
    cigareTextures[0].loadFromFile("resources/blend.png");
    cigareTextures[1].loadFromFile("resources/bluemaster.png");
    cigareTextures[2].loadFromFile("resources/dunhill.png");
    cigareTextures[3].loadFromFile("resources/pullman.png");
    cigareTextures[4].loadFromFile("resources/prince.png");

    // Load animal textures
    animalTextures[0].loadFromFile("resources/poisson.png");
    animalTextures[1].loadFromFile("resources/cheval.png");
    animalTextures[2].loadFromFile("resources/chien.png");
    animalTextures[3].loadFromFile("resources/oiseau.png");
    animalTextures[4].loadFromFile("resources/chat.png");
}
void EinsteinPuzzle::reset() {
    // Initialize the grid with unique values
    for (int i = 0; i < 5; ++i) {
        grid[i].maison.setTexture(maisonTextures[i]);
        grid[i].nationalite.setTexture(nationaliteTextures[i]);
        grid[i].boisson.setTexture(boissonTextures[i]);
        grid[i].cigare.setTexture(cigareTextures[i]);
        grid[i].animal.setTexture(animalTextures[i]);

        grid[i].maison.setPosition(i * 160.0f, 0);
        grid[i].nationalite.setPosition(i * 160.0f, 100.0f);
        grid[i].boisson.setPosition(i * 160.0f, 200.0f);
        grid[i].cigare.setPosition(i * 160.0f, 300.0f);
        grid[i].animal.setPosition(i * 160.0f, 400.0f);

        // Set the scale to control the size of the images
        grid[i].maison.setScale(0.5f, 0.5f);
        grid[i].nationalite.setScale(0.2f, 0.2f);
        grid[i].boisson.setScale(0.1f, 0.1f);
        grid[i].cigare.setScale(0.3f, 0.3f);
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
            for (int i = 0; i < 5; ++i) {
                if (grid[i].maison.getGlobalBounds().contains(window.mapPixelToCoords(mousePos))) {
                    isDragging = true;
                    currentDraggable = &grid[i].maison;
                    dragOffset = mousePos - sf::Vector2i(currentDraggable->getPosition());
                    break;
                }
                if (grid[i].nationalite.getGlobalBounds().contains(window.mapPixelToCoords(mousePos))) {
                    isDragging = true;
                    currentDraggable = &grid[i].nationalite;
                    dragOffset = mousePos - sf::Vector2i(currentDraggable->getPosition());
                    break;
                }
                if (grid[i].boisson.getGlobalBounds().contains(window.mapPixelToCoords(mousePos))) {
                    isDragging = true;
                    currentDraggable = &grid[i].boisson;
                    dragOffset = mousePos - sf::Vector2i(currentDraggable->getPosition());
                    break;
                }
                if (grid[i].cigare.getGlobalBounds().contains(window.mapPixelToCoords(mousePos))) {
                    isDragging = true;
                    currentDraggable = &grid[i].cigare;
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
    for (int i = 0; i < 5; ++i) {
        window.draw(grid[i].maison);
        window.draw(grid[i].nationalite);
        window.draw(grid[i].boisson);
        window.draw(grid[i].cigare);
        window.draw(grid[i].animal);
    }
    window.display();
}

bool EinsteinPuzzle::checkSolution() {
    // Check the solution conditions
    // 1. The Norwegian lives in the first house.
    if (grid[0].nationalite.getTexture() != &nationaliteTextures[0]) return false;
    // 2. The Norwegian drinks water.
    if (grid[0].boisson.getTexture() != &boissonTextures[2]) return false;
    // 3. The Norwegian has cats.
    if (grid[0].animal.getTexture() != &animalTextures[4]) return false;
    // 4. The Norwegian smokes Dunhill.
    if (grid[0].cigare.getTexture() != &cigareTextures[2]) return false;
    // 5. The Norwegian lives next to the blue house.
    if (grid[1].maison.getTexture() != &maisonTextures[1]) return false;
    // 6. The British live in the red house.
    if (grid[3].maison.getTexture() != &maisonTextures[3]) return false;
    // 7. The British drink milk.
    if (grid[3].boisson.getTexture() != &boissonTextures[3]) return false;
    // 8. The British have a bird.
    if (grid[3].animal.getTexture() != &animalTextures[3]) return false;
    // 9. The British smoke Pall Mall.
    if (grid[3].cigare.getTexture() != &cigareTextures[3]) return false;
    // 10. The Dane lives in the second house.
    if (grid[1].nationalite.getTexture() != &nationaliteTextures[2]) return false;
    // 11. The Dane drinks tea.
    if (grid[1].boisson.getTexture() != &boissonTextures[4]) return false;
    // 12. The Dane has horses.
    if (grid[1].animal.getTexture() != &animalTextures[1]) return false;
    // 13. The Dane smokes Blend.
    if (grid[1].cigare.getTexture() != &cigareTextures[0]) return false;
    // 14. The German lives in the third house.
    if (grid[2].nationalite.getTexture() != &nationaliteTextures[3]) return false;
    // 15. The German smokes Prince.
    if (grid[2].cigare.getTexture() != &cigareTextures[4]) return false;
    // 16. The German drinks coffee.
    if (grid[2].boisson.getTexture() != &boissonTextures[1]) return false;
    // 17. The German has a fish.
    if (grid[2].animal.getTexture() != &animalTextures[0]) return false;
    // 18. The Swede lives in the fourth house.
    if (grid[4].nationalite.getTexture() != &nationaliteTextures[4]) return false;
    // 19. The Swede drinks beer.
    if (grid[4].boisson.getTexture() != &boissonTextures[0]) return false;
    // 20. The Swede smokes Bluemaster.
    if (grid[4].cigare.getTexture() != &cigareTextures[1]) return false;
    // 21. The Swede has dogs.
    if (grid[4].animal.getTexture() != &animalTextures[2]) return false;
    // 22. The house on the left of the white house is green.
    if (grid[3].maison.getTexture() != &maisonTextures[4]) return false;
    // 23. The person in the green house drinks coffee.
    if (grid[3].boisson.getTexture() != &boissonTextures[1]) return false;
    // 24. The person in the green house smokes Pall Mall.
    //if (grid[3].cigare.getTexture() != &cigareTextures[3]) return false;

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