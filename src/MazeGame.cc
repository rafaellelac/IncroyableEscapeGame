#include "MazeGame.hh"
#include "MECPuzzle.hh"
#include "asset.hh"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

// Surcharge de l'opérateur de division pour sf::Vector2f
sf::Vector2f operator/(const sf::Vector2f& vec, const sf::Vector2f& divisor) {
    return sf::Vector2f(vec.x / divisor.x, vec.y / divisor.y);
}

MazeGame::MazeGame(std::shared_ptr<Context> &context) : m_context(context), completed(false) {
}

void MazeGame::Init() {
    // Charger la texture du labyrinthe
    m_context->m_assets->AddTexture(MAZE, "ASSETS/maze.png");
    mazeSprite.setTexture(m_context->m_assets->GetTexture(MAZE));

    // Calculer le facteur d'échelle pour ajuster le labyrinthe à la fenêtre
    sf::Vector2u mazeSize = mazeSprite.getTexture()->getSize();
    float scaleX = static_cast<float>(1000) / static_cast<float>(mazeSize.x);
    float scaleY = static_cast<float>(1000) / static_cast<float>(mazeSize.y);
    float scale = std::min(scaleX, scaleY); // Utiliser l'échelle la plus petite pour ajuster le labyrinthe à la fenêtre

    // Appliquer le facteur d'échelle au sprite du labyrinthe
    mazeSprite.setScale(scale, scale);

    // Charger la texture du joueur
    m_context->m_assets->AddTexture(PLAYER, "ASSETS/naomi.png");
    playerSprite.setTexture(m_context->m_assets->GetTexture(PLAYER));

    // Définir l'échelle du sprite du joueur
    playerSprite.setScale(0.011f, 0.011f); // Ajuster l'échelle si nécessaire

    // Position de départ du joueur
    playerPosition = { 60.0f, 40.0f }; // Position de départ ajustée
    playerSprite.setPosition(playerPosition);

    // Convertir la texture du labyrinthe en image pour vérifier les pixels
    mazeImage = mazeSprite.getTexture()->copyToImage();
}

bool MazeGame::isPixelBlack(const sf::Vector2f& position) {
    // Convertir la position en coordonnées non mises à l'échelle
    sf::Vector2f unscaledPosition = position / mazeSprite.getScale();

    // Obtenir les limites du joueur
    sf::FloatRect playerBounds = playerSprite.getGlobalBounds();

    // Vérifier les pixels dans les limites du joueur
    for (int x = 0; x < playerBounds.width; ++x) {
        for (int y = 0; y < playerBounds.height; ++y) {
            int unscaledX = static_cast<int>(unscaledPosition.x + x / mazeSprite.getScale().x);
            int unscaledY = static_cast<int>(unscaledPosition.y + y / mazeSprite.getScale().y);

            // S'assurer que les coordonnées sont dans les limites de l'image
            if (unscaledX >= 0 && unscaledX < static_cast<int>(mazeImage.getSize().x) && unscaledY >= 0 && unscaledY < static_cast<int>(mazeImage.getSize().y)) {
                sf::Color pixelColor = mazeImage.getPixel(unscaledX, unscaledY);

                // Vérifier si le pixel est noir
                if (pixelColor == sf::Color::Black) {
                    return true;
                }
            }
        }
    }

    return false;
}

void MazeGame::ProcessInput() {
    // Gérer les entrées du clavier pour le mouvement du joueur
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        movement.y -= 10.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        movement.y += 10.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        movement.x -= 10.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        movement.x += 10.0f;
    }
}

void MazeGame::Update(sf::Time deltaTime) {
    // Mettre à l'échelle le mouvement par deltaTime
    sf::Vector2f scaledMovement = movement * deltaTime.asSeconds();
    // Réinitialiser le mouvement à zéro après l'avoir appliqué
    movement = {0.0f, 0.0f};
    // Calculer la nouvelle position
    scaledMovement *= 0.25f; // Réduire la vitesse de mouvement d'un quart
    sf::Vector2f newPosition = playerPosition + scaledMovement;

    // Vérifier la collision avec le labyrinthe
    if (!isPixelBlack(newPosition)) {
        // Mettre à jour la position du joueur si la nouvelle position n'est pas noire
        playerPosition = newPosition;
        playerSprite.setPosition(playerPosition);
    }

    // Vérifier si le joueur a atteint la sortie
    if (playerPosition.x > 955.0f && playerPosition.y > 950.0f) {
        completed = true;
    }
}
// fonction qui dessine le labyrinthe et le joueur
void MazeGame::Draw() {
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Maze Game"); // Créer une fenêtre de 1000x1000

    Init(); // Initialiser le jeu

    while (window.isOpen()) { // Boucle principale du jeu
        sf::Event event; // Gérer les événements
        while (window.pollEvent(event)) { // Parcourir tous les événements
            if (event.type == sf::Event::Closed) { // Vérifier si la fenêtre est fermée
                window.close(); // Fermer la fenêtre
            } 
        }

        window.clear(sf::Color::White); // avoir un fond blanc
        window.draw(mazeSprite);    // dessiner le labyrinthe
        window.draw(playerSprite); // dessiner le joueur
        window.display(); // afficher le contenu de la fenêtre

        ProcessInput(); 
        Update(sf::seconds(1.f / 60.f)); 

        if (completed) { // Si le jeu est terminé
            window.close(); // Fermer la fenêtre
            m_context->m_states->PopCurrent(); // Retourner à l'état précédent
            m_context->m_states->Add(std::make_unique<MECPuzzle>(m_context)); // Ajouter un nouvel état
        }
    }
}

bool MazeGame::isCompleted() const { // fonction qui retourne si le jeu est terminé
    return completed;
}