// EinsteinPuzzle.cpp
#include "einstein.hh"
#include <iostream>
#include <algorithm>

EinsteinPuzzle::EinsteinPuzzle(): 
    window(sf::VideoMode(550, 400), "Einstein Puzzle Game"),
    isDragging(false),
    currentDraggable(nullptr),
    solutionFound(false) {
    loadResources();
    reset();
}

/*void EinsteinPuzzle::loadResources() {
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

    // Load femme textures
    femmeTextures[0].loadFromFile("resources/josephine_backer.png");
    femmeTextures[1].loadFromFile("resources/marie_curie.png");
    femmeTextures[2].loadFromFile("resources/simone_veil.png");
}*/
void EinsteinPuzzle::loadResources() {
    // Chargement des textures pour les maisons
    if (maisonTextures[0].loadFromFile("resources/maison_bleu.png")) {
        textureIDs[&maisonTextures[0]] = 0; // ID 0 pour maison bleue
    }
    if (maisonTextures[1].loadFromFile("resources/maison_rouge.png")) {
        textureIDs[&maisonTextures[1]] = 1; // ID 1 pour maison rouge
    }
    if (maisonTextures[2].loadFromFile("resources/maison_verte.png")) {
        textureIDs[&maisonTextures[2]] = 2; // ID 2 pour maison verte
    }

    // Chargement des textures pour les boissons
    if (boissonTextures[0].loadFromFile("resources/cafe.png")) {
        textureIDs[&boissonTextures[0]] = 0; // ID 0 pour café
    }
    if (boissonTextures[1].loadFromFile("resources/lait.png")) {
        textureIDs[&boissonTextures[1]] = 1; // ID 1 pour lait
    }
    if (boissonTextures[2].loadFromFile("resources/tea.png")) {
        textureIDs[&boissonTextures[2]] = 2; // ID 2 pour thé
    }

    // Chargement des textures pour les animaux
    if (animalTextures[0].loadFromFile("resources/poisson.png")) {
        textureIDs[&animalTextures[0]] = 0; // ID 0 pour poisson
    }
    if (animalTextures[1].loadFromFile("resources/chien.png")) {
        textureIDs[&animalTextures[1]] = 1; // ID 1 pour chien
    }
    if (animalTextures[2].loadFromFile("resources/chat.png")) {
        textureIDs[&animalTextures[2]] = 2; // ID 2 pour chat
    }

    // Chargement des textures pour les femmes
    if (femmeTextures[0].loadFromFile("resources/josephine_backer.png")) {
        textureIDs[&femmeTextures[0]] = 0; // ID 0 pour Joséphine Baker
    }
    if (femmeTextures[1].loadFromFile("resources/marie_curie.png")) {
        textureIDs[&femmeTextures[1]] = 1; // ID 1 pour Marie Curie
    }
    if (femmeTextures[2].loadFromFile("resources/simone_veil.png")) {
        textureIDs[&femmeTextures[2]] = 2; // ID 2 pour Simone Veil
    }
}

void EinsteinPuzzle::reset() {
    solutionFound = false;
    for (int i = 0; i < 3; ++i) {
        grid[i].maison.setTexture(maisonTextures[i]);
        grid[i].femme.setTexture(femmeTextures[i]);
        grid[i].boisson.setTexture(boissonTextures[i]);
        grid[i].animal.setTexture(animalTextures[i]);

        grid[i].maisonID = i;
        grid[i].femmeID = i;
        grid[i].boissonID = i;
        grid[i].animalID = i;

        grid[i].maison.setPosition(0, i * 150.0f);
        grid[i].femme.setPosition(160, i * 150.0f);
        grid[i].boisson.setPosition(320, i * 150.0f);
        grid[i].animal.setPosition(480, i * 150.0f);

        grid[i].maison.setScale(0.5f, 0.5f);
        grid[i].femme.setScale(0.25f, 0.25f);
        grid[i].boisson.setScale(0.1f, 0.1f);
        grid[i].animal.setScale(0.1f, 0.1f);
    }
    std::random_shuffle(grid.begin(), grid.end());
    //create an answer box
    answerBox.setSize(sf::Vector2f(120, 30));
    answerBox.setFillColor(sf::Color::Green);
    answerBox.setPosition(250, 250);
    font.loadFromFile("resources/font.ttf");
    answerText.setFont(font);
    answerText.setString("Check Answer");
    answerText.setCharacterSize(20);
    answerText.setPosition(250, 250);
    answerText.setFillColor(sf::Color::White);
    inputBox.setSize(sf::Vector2f(80, 30));
    inputBox.setFillColor(sf::Color::White);
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setOutlineThickness(2);
    inputBox.setPosition(160, 250);
    inputText.setFont(font);
    inputText.setCharacterSize(24);
    inputText.setPosition(180, 250);
    inputText.setFillColor(sf::Color::Black);
}


/*void EinsteinPuzzle::handleEvents() {
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
                int y = mousePos.y / 150;
                if (y >= 0 && y < 3) {
                    currentDraggable->setPosition(currentDraggable->getPosition().x, y * 150.0f);
                }
                isDragging = false;
                currentDraggable = nullptr;
            }
        }
    }
}*/
void EinsteinPuzzle::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            
            // Check if the "Check Answer" button was clicked
            if (answerBox.getGlobalBounds().contains(window.mapPixelToCoords(mousePos))) {
                if (checkSolution()) {
                    std::cout << "Solution found!" << std::endl;
                    solutionFound = true;
                    sf::sleep(sf::seconds(3)); // Pause for 3 seconds before closing
                    window.close(); // Close window when solution is found
                } else {
                    std::cout << "Incorrect answer, try again!" << std::endl;
                }
            }
            
            // Dragging logic
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
                int y = mousePos.y / 150;
                if (y >= 0 && y < 3) {
                    currentDraggable->setPosition(currentDraggable->getPosition().x, y * 150.0f);
                }
                isDragging = false;
                currentDraggable = nullptr;
            }
        } else if (event.type == sf::Event::TextEntered) {
            // Handle text input (typing the solution)
            if (event.text.unicode < 128) {  // Ignore non-ASCII characters
                if (event.text.unicode == 8 && !playerInput.empty()) { // Backspace
                    playerInput.pop_back();
                } else if (event.text.unicode != 8) {  // Regular character
                    playerInput += static_cast<char>(event.text.unicode);
                }
            }
        }
        inputText.setString(playerInput); // Update the input text
    }
}






void EinsteinPuzzle::update() {
    if (isDragging && currentDraggable) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        currentDraggable->setPosition(currentDraggable->getPosition().x, mousePos.y - dragOffset.y);
    }
}

void EinsteinPuzzle::draw() {
    if (solutionFound) {
        window.clear(sf::Color::Green); // Green to indicate a correct solution
    } else {
        window.clear(sf::Color::White); // Default white background
    }
    for (int i = 0; i < 3; ++i) {
        window.draw(grid[i].maison);
        window.draw(grid[i].femme);
        window.draw(grid[i].boisson);
        window.draw(grid[i].animal);
    }

    // Draw the answer box
    window.draw(answerBox);
    window.draw(answerText); // Display the answer text
    window.draw(inputBox); // Draw the input box
    window.draw(inputText); // Display the player's input
    window.display();
}



/*void EinsteinPuzzle::draw() {
    if (solutionFound) {
        window.clear(sf::Color::Green); // Vert pour signaler une solution correcte
    } else {
        window.clear(sf::Color::White);
    }
    for (int i = 0; i < 3; ++i) {
        window.draw(grid[i].maison);
        window.draw(grid[i].femme);
        window.draw(grid[i].boisson);
        window.draw(grid[i].animal);
    }
    window.display();
}*/

/*bool EinsteinPuzzle::checkSolution() {
    for (int i = 0; i < 3; ++i) {
        std::cout << "Grid[" << i << "]: "
                  << "Maison ID=" << textureIDs[grid[i].maison.getTexture()] << ", "
                  << "Femme ID=" << textureIDs[grid[i].femme.getTexture()] << ", "
                  << "Boisson ID=" << textureIDs[grid[i].boisson.getTexture()] << ", "
                  << "Animal ID=" << textureIDs[grid[i].animal.getTexture()] << std::endl;
    }
    if (grid[0].maisonID != 2 || grid[0].femmeID != 0 || grid[0].boissonID != 1 || grid[0].animalID != 1) return false;
    if (grid[1].maisonID != 0 || grid[1].femmeID != 1 || grid[1].boissonID != 2 || grid[1].animalID != 0) return false;
    if (grid[2].maisonID != 1 || grid[2].femmeID != 2 || grid[2].boissonID != 0 || grid[2].animalID != 2) return false;

    return true; // If everything matches, the solution is correct
}*/
bool EinsteinPuzzle::checkSolution() {

    // Check the typed answer
    if (playerInput == "cat") {
        std::cout << "Solution found!" << std::endl;
        solutionFound = true;
        sf::sleep(sf::seconds(3)); // Wait for 3 seconds
        window.close();  // Close the window
    } else {
        std::cout << "Incorrect answer, try again!" << std::endl;
        playerInput.clear();  // Clear the input for the next attempt
    }
    return solutionFound;
}








void EinsteinPuzzle::run() {
    while (window.isOpen()) {
        handleEvents();
        if (!solutionFound) {
            update();
        }
        draw();
    }
}



int main() {
    EinsteinPuzzle puzzle;
    puzzle.run();
    return 0;
}


        