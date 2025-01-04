#include "Enigme.hh"
#include "LastScreen.hh"
#include "game.hh"
#include <iostream>
#include <algorithm>


Enigme::Enigme(std::shared_ptr<Context> &context) :  
    m_context(context), 
    m_window(sf::VideoMode(550, 500), "Einstein Puzzle Game"),
    isDragging(false),
    currentDraggable(nullptr), 
    iscompleted(false) {
}


void Enigme::Init() {

    // Chargement de la police
    m_context->m_assets->AddFont(ENIGME, "ASSETS/Enigme/font.ttf");

    // Chargement des textures pour les maisons
    maisonTextures[0].loadFromFile("ASSETS/Enigme/maison_bleu.png");
    maisonTextures[1].loadFromFile("ASSETS/Enigme/maison_rouge.png");
    maisonTextures[2].loadFromFile("ASSETS/Enigme/maison_verte.png");

    // Chargement des textures pour les boissons
    boissonTextures[0].loadFromFile("ASSETS/Enigme/cafe.png");
    boissonTextures[1].loadFromFile("ASSETS/Enigme/lait.png");
    boissonTextures[2].loadFromFile("ASSETS/Enigme/tea.png");

    // Chargement des textures pour les animaux
    animalTextures[0].loadFromFile("ASSETS/Enigme/poisson.png");
    animalTextures[1].loadFromFile("ASSETS/Enigme/chien.png");
    animalTextures[2].loadFromFile("ASSETS/Enigme/chat.png");

    // Chargement des textures pour les femmes
    femmeTextures[0].loadFromFile("ASSETS/Enigme/josephine_backer.png");
    femmeTextures[1].loadFromFile("ASSETS/Enigme/marie_curie.png");
    femmeTextures[2].loadFromFile("ASSETS/Enigme/simone_veil.png");

    // Mélanger les textures pour les cellules
    iscompleted = false;
    for (int i = 0; i < 3; ++i) {
        grid[i].maison.setTexture(maisonTextures[i]);
        grid[i].femme.setTexture(femmeTextures[i]);
        grid[i].boisson.setTexture(boissonTextures[i]);
        grid[i].animal.setTexture(animalTextures[i]);

        grid[i].maison.setPosition(0, i * 150.0f);
        grid[i].femme.setPosition(160, i * 150.0f);
        grid[i].boisson.setPosition(320, i * 150.0f);
        grid[i].animal.setPosition(480, i * 150.0f);

        grid[i].maison.setScale(0.5f, 0.5f);
        grid[i].femme.setScale(0.25f, 0.25f);
        grid[i].boisson.setScale(0.1f, 0.1f);
        grid[i].animal.setScale(0.1f, 0.1f);
    }
    std::random_shuffle(grid.begin(), grid.end()); // Mélanger les cellules


    // Boîte de réponse
    m_answerBox.setSize(sf::Vector2f(120, 30));
    m_answerBox.setFillColor(sf::Color::Green);
    m_answerBox.setPosition(300, 430);
    // Texte de réponse
    m_answerText.setFont(m_context->m_assets->GetFont(ENIGME));
    m_answerText.setString("Check Answer");
    m_answerText.setCharacterSize(20);
    m_answerText.setPosition(300, 430);
    m_answerText.setFillColor(sf::Color::White);
    // Boîte de saisie
    m_inputBox.setSize(sf::Vector2f(130, 30));
    m_inputBox.setFillColor(sf::Color::White);
    m_inputBox.setOutlineColor(sf::Color::Black);
    m_inputBox.setOutlineThickness(2);
    m_inputBox.setPosition(140, 430);
    // Texte de saisie
    m_inputText.setFont(m_context->m_assets->GetFont(ENIGME));
    m_inputText.setCharacterSize(24);
    m_inputText.setPosition(150, 430);
    m_inputText.setFillColor(sf::Color::Black);
    // Texte de l'énigme
    m_phraseText.setFont(m_context->m_assets->GetFont(ENIGME));
    m_phraseText.setString("Quelle est la couleur de la maison de Marie Curie?");
    m_phraseText.setCharacterSize(20);
    m_phraseText.setPosition(80, 400); // Position au-dessus de la boîte de réponse
    m_phraseText.setFillColor(sf::Color::Black);


}


void Enigme::ProcessInput() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
        } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
            
            // Vérifier si le bouton "Check Answer" a été cliqué
            if (m_answerBox.getGlobalBounds().contains(m_window.mapPixelToCoords(mousePos))) {
                if (m_playerInput == "bleue") {
                    iscompleted = true;
                } else {
                    m_playerInput.clear();  // Effacer la saisie pour la prochaine tentative
                }
            }
            
            // Logique de glisser-déposer
            for (int i = 0; i < 3; ++i) {
                if (grid[i].maison.getGlobalBounds().contains(m_window.mapPixelToCoords(mousePos))) { // Vérifier si la souris est sur la maison
                    isDragging = true; // Activer le glisser-déposer
                    currentDraggable = &grid[i].maison; // Définir l'élément actuel
                    dragOffset = mousePos - sf::Vector2i(currentDraggable->getPosition()); // Calculer le décalage
                    break;
                }
                if (grid[i].femme.getGlobalBounds().contains(m_window.mapPixelToCoords(mousePos))) { // Vérifier si la souris est sur la femme
                    isDragging = true; // Activer le glisser-déposer
                    currentDraggable = &grid[i].femme; // Définir l'élément actuel
                    dragOffset = mousePos - sf::Vector2i(currentDraggable->getPosition()); // Calculer le décalage
                    break;
                }
                if (grid[i].boisson.getGlobalBounds().contains(m_window.mapPixelToCoords(mousePos))) { // Vérifier si la souris est sur la boisson
                    isDragging = true; // Activer le glisser-déposer
                    currentDraggable = &grid[i].boisson; // Définir l'élément actuel
                    dragOffset = mousePos - sf::Vector2i(currentDraggable->getPosition()); // Calculer le décalage
                    break;
                }
                if (grid[i].animal.getGlobalBounds().contains(m_window.mapPixelToCoords(mousePos))) { // Vérifier si la souris est sur l'animal
                    isDragging = true; // Activer le glisser-déposer
                    currentDraggable = &grid[i].animal; // Définir l'élément actuel
                    dragOffset = mousePos - sf::Vector2i(currentDraggable->getPosition()); // Calculer le décalage
                    break;
                }
            }
        } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) { // Relâcher le bouton gauche de la souris
            if (isDragging && currentDraggable) { // Vérifier si un élément est en cours de glisser-déposer
                sf::Vector2i mousePos = sf::Mouse::getPosition(m_window); // Obtenir la position de la souris
                int y = mousePos.y / 150; // Calculer la ligne de la grille
                if (y >= 0 && y < 3) { // Vérifier si la ligne est valide
                    currentDraggable->setPosition(currentDraggable->getPosition().x, y * 150.0f); // Définir la position de l'élément
                }
                isDragging = false; // Désactiver le glisser-déposer
                currentDraggable = nullptr; // Réinitialiser l'élément actuel
            }
        } else if (event.type == sf::Event::TextEntered) { 
            // Gérer la saisie de texte (taper la solution)
            if (event.text.unicode < 128) {  // Ignorer les caractères non-ASCII
                if (event.text.unicode == 8 && !m_playerInput.empty()) { // Retour arrière
                    m_playerInput.pop_back();
                } else if (event.text.unicode != 8) {  // Caractère régulier
                    m_playerInput += static_cast<char>(event.text.unicode);
                }
            }
        }
        m_inputText.setString(m_playerInput); // Mettre à jour le texte de saisie
    }
}


void Enigme::Update(sf::Time deltaTime) { 
    if (isDragging && currentDraggable) { 
        sf::Vector2i mousePos = sf::Mouse::getPosition(m_window); // Obtenir la position de la souris
        currentDraggable->setPosition(currentDraggable->getPosition().x, mousePos.y - dragOffset.y); // Définir la position de l'élément
    }
}


void Enigme::Draw() { 
    while (m_window.isOpen()) {
        ProcessInput();
        Update(sf::seconds(0.1f));
        
        m_window.clear(sf::Color::White); // Fond blanc par défaut
        for (int i = 0; i < 3; ++i) { // Dessiner les cellules
            m_window.draw(grid[i].maison); 
            m_window.draw(grid[i].femme);
            m_window.draw(grid[i].boisson); 
            m_window.draw(grid[i].animal);
        }

        // Dessiner la boîte de réponse
        m_window.draw(m_answerBox);
        m_window.draw(m_answerText); // Afficher le texte de réponse
        m_window.draw(m_inputBox); // Dessiner la boîte de saisie
        m_window.draw(m_inputText); // Afficher la saisie du joueur
        m_window.draw(m_phraseText);
        m_window.display();

        if (iscompleted) {
            m_window.close();
            m_context->m_states->PopCurrent(); 
            m_context->m_states->Add(std::make_unique<LastScreen>(m_context));
        } 
 
        if (!iscompleted){
            Update(sf::seconds(0.1f)); 
        }
    }
}

bool Enigme::isCompleted() const {
    return iscompleted;
}