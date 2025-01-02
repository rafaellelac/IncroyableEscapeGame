#include "Enigme.hh"
#include <iostream>
#include <algorithm>
#include "game.hh"

Enigme::Enigme(std::shared_ptr<Context> &context) : 
    m_context(context), 
    m_window(sf::VideoMode(550, 500), "Einstein Puzzle Game"),
    isDragging(false),
    currentDraggable(nullptr),
    iscompleted(false) {
}


void Enigme::Init() {

    //Chargement du font 
    m_context->m_assets->AddFont(ENIGME, "ASSETS/Enigme/font.ttf");

    //Chargement des textures pour les maisons
    if (maisonTextures[0].loadFromFile("ASSETS/Enigme/maison_bleu.png")) {
        textureIDs[&maisonTextures[0]] = 0; // ID 0 pour maison bleue
    }
    if (maisonTextures[1].loadFromFile("ASSETS/Enigme/maison_rouge.png")) {
        textureIDs[&maisonTextures[1]] = 1; // ID 1 pour maison rouge
    }
    if (maisonTextures[2].loadFromFile("ASSETS/Enigme/maison_verte.png")) {
        textureIDs[&maisonTextures[2]] = 2; // ID 2 pour maison verte
    }

    // Chargement des textures pour les boissons
    if (boissonTextures[0].loadFromFile("ASSETS/Enigme/cafe.png")) {
        textureIDs[&boissonTextures[0]] = 0; // ID 0 pour café
    }
    if (boissonTextures[1].loadFromFile("ASSETS/Enigme/lait.png")) {
        textureIDs[&boissonTextures[1]] = 1; // ID 1 pour lait
    }
    if (boissonTextures[2].loadFromFile("ASSETS/Enigme/tea.png")) {
        textureIDs[&boissonTextures[2]] = 2; // ID 2 pour thé
    }

    // Chargement des textures pour les animaux
    if (animalTextures[0].loadFromFile("ASSETS/Enigme/poisson.png")) {
        textureIDs[&animalTextures[0]] = 0; // ID 0 pour poisson
    }
    if (animalTextures[1].loadFromFile("ASSETS/Enigme/chien.png")) {
        textureIDs[&animalTextures[1]] = 1; // ID 1 pour chien
    }
    if (animalTextures[2].loadFromFile("ASSETS/Enigme/chat.png")) {
        textureIDs[&animalTextures[2]] = 2; // ID 2 pour chat
    }

    // Chargement des textures pour les femmes
    if (femmeTextures[0].loadFromFile("ASSETS/Enigme/josephine_backer.png")) {
        textureIDs[&femmeTextures[0]] = 0; // ID 0 pour Joséphine Baker
    }
    if (femmeTextures[1].loadFromFile("ASSETS/Enigme/marie_curie.png")) {
        textureIDs[&femmeTextures[1]] = 1; // ID 1 pour Marie Curie
    }
    if (femmeTextures[2].loadFromFile("ASSETS/Enigme/simone_veil.png")) {
        textureIDs[&femmeTextures[2]] = 2; // ID 2 pour Simone Veil
    }

    // Mélanger les textures pour les cellules
    iscompleted = false;
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


    //Answer Box
    m_answerBox.setSize(sf::Vector2f(120, 30));
    m_answerBox.setFillColor(sf::Color::Green);
    m_answerBox.setPosition(300, 430);

    m_answerText.setFont(m_context->m_assets->GetFont(ENIGME));
    m_answerText.setString("Check Answer");
    m_answerText.setCharacterSize(20);
    m_answerText.setPosition(300, 430);
    m_answerText.setFillColor(sf::Color::White);

    m_inputBox.setSize(sf::Vector2f(130, 30));
    m_inputBox.setFillColor(sf::Color::White);
    m_inputBox.setOutlineColor(sf::Color::Black);
    m_inputBox.setOutlineThickness(2);
    m_inputBox.setPosition(140, 430);

    m_inputText.setFont(m_context->m_assets->GetFont(ENIGME));
    m_inputText.setCharacterSize(24);
    m_inputText.setPosition(150, 430);
    m_inputText.setFillColor(sf::Color::Black);

    m_phraseText.setFont(m_context->m_assets->GetFont(ENIGME));
    m_phraseText.setString("Ces femmes sont :");
    m_phraseText.setCharacterSize(20);
    m_phraseText.setPosition(160, 400); // Position above the answer box
    m_phraseText.setFillColor(sf::Color::Black);


}


void Enigme::ProcessInput() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
        } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
            
            // Check if the "Check Answer" button was clicked
            if (m_answerBox.getGlobalBounds().contains(m_window.mapPixelToCoords(mousePos))) {
                if (m_playerInput == "incroyables") {
                    std::cout << "Solution found!" << std::endl;
                    iscompleted = true;
                } else {
                    std::cout << "Incorrect answer, try again!" << std::endl;
                    m_playerInput.clear();  // Clear the input for the next attempt
                }
            }
            
            // Dragging logic
            for (int i = 0; i < 3; ++i) {
                if (grid[i].maison.getGlobalBounds().contains(m_window.mapPixelToCoords(mousePos))) {
                    isDragging = true;
                    currentDraggable = &grid[i].maison;
                    dragOffset = mousePos - sf::Vector2i(currentDraggable->getPosition());
                    break;
                }
                if (grid[i].femme.getGlobalBounds().contains(m_window.mapPixelToCoords(mousePos))) {
                    isDragging = true;
                    currentDraggable = &grid[i].femme;
                    dragOffset = mousePos - sf::Vector2i(currentDraggable->getPosition());
                    break;
                }
                if (grid[i].boisson.getGlobalBounds().contains(m_window.mapPixelToCoords(mousePos))) {
                    isDragging = true;
                    currentDraggable = &grid[i].boisson;
                    dragOffset = mousePos - sf::Vector2i(currentDraggable->getPosition());
                    break;
                }
                if (grid[i].animal.getGlobalBounds().contains(m_window.mapPixelToCoords(mousePos))) {
                    isDragging = true;
                    currentDraggable = &grid[i].animal;
                    dragOffset = mousePos - sf::Vector2i(currentDraggable->getPosition());
                    break;
                }
            }
        } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            if (isDragging && currentDraggable) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
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
                if (event.text.unicode == 8 && !m_playerInput.empty()) { // Backspace
                    m_playerInput.pop_back();
                } else if (event.text.unicode != 8) {  // Regular character
                    m_playerInput += static_cast<char>(event.text.unicode);
                }
            }
        }
        m_inputText.setString(m_playerInput); // Update the input text
    }
}


void Enigme::Update(sf::Time deltaTime) {
    if (isDragging && currentDraggable) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
        currentDraggable->setPosition(currentDraggable->getPosition().x, mousePos.y - dragOffset.y);
    }
}


void Enigme::Draw() {
    while (m_window.isOpen()) {
        ProcessInput();
        if (iscompleted) {
            m_window.close();
            m_context->m_states->PopCurrent(); 
            //add next state
        } 

        m_window.clear(sf::Color::White); // Default white background
        for (int i = 0; i < 3; ++i) {
            m_window.draw(grid[i].maison);
            m_window.draw(grid[i].femme);
            m_window.draw(grid[i].boisson);
            m_window.draw(grid[i].animal);
        }

        // Draw the answer box
        m_window.draw(m_answerBox);
        m_window.draw(m_answerText); // Display the answer text
        m_window.draw(m_inputBox); // Draw the input box
        m_window.draw(m_inputText); // Display the player's input
        m_window.draw(m_phraseText);
        m_window.display();

        if (!iscompleted){
            Update(sf::seconds(0.1f));
        }
    }
}

bool Enigme::isCompleted() const {
    return iscompleted;
}



/*void EinsteinPuzzle::run() {

        if (!solutionFound) {
            update();
        }
        draw();
    }
}*/


