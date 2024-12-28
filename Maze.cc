#include "Maze.hh"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "asset.hh"

// Overload the division operator for sf::Vector2f
sf::Vector2f operator/(const sf::Vector2f& vec, const sf::Vector2f& divisor) {
    return sf::Vector2f(vec.x / divisor.x, vec.y / divisor.y);
}

MazeGame::MazeGame(std::shared_ptr<Context> &context) : m_context(context), completed(false) {
}

void MazeGame::Init() {
    // Initialize the game (if needed)
    // Load the maze texture
    m_context->m_assets->AddTexture(MAZE, "ASSETS/maze.png" );
    mazeSprite.setTexture(m_context->m_assets->GetTexture(MAZE));

    // Calculate the scale factor to fit the maze to the window
    sf::Vector2u mazeSize = mazeSprite.getTexture()->getSize();
    float scaleX = static_cast<float>(800) / static_cast<float>(mazeSize.x);
    float scaleY = static_cast<float>(800) / static_cast<float>(mazeSize.y);
    float scale = std::min(scaleX, scaleY); // Use the smaller scale to fit the maze within the window

    // Apply the scale factor to the maze sprite
    mazeSprite.setScale(scale, scale);


    // Load the player texture
    m_context->m_assets->AddTexture(PLAYER, "ASSETS/player.png" );
    playerSprite.setTexture(m_context->m_assets->GetTexture(PLAYER));

    // Set the scale of the player sprite
    playerSprite.setScale(0.01f, 0.01f); // Adjust the scale as needed

    playerPosition = { 50.0f, 50.0f }; // Starting position
    playerSprite.setPosition(playerPosition);

    // Convert the maze texture to an image for pixel checking
    mazeImage = mazeSprite.getTexture()->copyToImage();

    // Debug output to check initial state
    std::cout << "Maze and player textures loaded successfully" << std::endl;
}

bool MazeGame::isPixelBlack(const sf::Vector2f& position) {
    // Convert the position to the unscaled coordinates
    sf::Vector2f unscaledPosition = position / mazeSprite.getScale();

    // Get the player's bounds
    sf::FloatRect playerBounds = playerSprite.getGlobalBounds();

    // Check the pixels within the player's bounds
    for (int x = 0; x < playerBounds.width; ++x) {
        for (int y = 0; y < playerBounds.height; ++y) {
            int unscaledX = static_cast<int>(unscaledPosition.x + x / mazeSprite.getScale().x);
            int unscaledY = static_cast<int>(unscaledPosition.y + y / mazeSprite.getScale().y);

            // Ensure the coordinates are within the bounds of the image
            if (unscaledX >= 0 && unscaledX < static_cast<int>(mazeImage.getSize().x) && unscaledY >= 0 && unscaledY < static_cast<int>(mazeImage.getSize().y)) {
                sf::Color pixelColor = mazeImage.getPixel(unscaledX, unscaledY);

                // Check if the pixel is black
                if (pixelColor == sf::Color::Black) {
                    return true;
                }
            }
        }
    }

    return false;
}

void MazeGame::ProcessInput() {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        movement.y -= 100.0f ;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        movement.y += 100.0f ;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        movement.x -= 100.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        movement.x += 100.0f;
    }

}
void MazeGame::Update(sf::Time deltaTime) {
    //Scale movement by deltaTime
    sf::Vector2f scaledMovement = movement * deltaTime.asSeconds();
    // Reset movement to zero after applying it
    movement = {0.0f, 0.0f};
    // Calculate the new position
    scaledMovement *= 0.5f; // Reduce the movement speed by half
    sf::Vector2f newPosition = playerPosition + scaledMovement;

    // Check for collision with the maze
    if (!isPixelBlack(newPosition)) {
        // Update player position if the new position is not black
        playerPosition = newPosition;
        playerSprite.setPosition(playerPosition);
    }

    // Check if the player has reached the exit
    if (playerPosition.x > 750.0f && playerPosition.y > 750.0f) {
        completed = true;
    }
}


void MazeGame::Draw() {
    // Debug output to check if render is being called
    std::cout << "Rendering maze and player" << std::endl;
    sf::RenderWindow window(sf::VideoMode(800, 800), "Maze Game");

    Init();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        window.draw(mazeSprite);
        window.draw(playerSprite);
        window.display();

        ProcessInput();
        Update(sf::seconds(1.f / 60.f));

        if (completed) {
            std::cout << "Maze completed!" << std::endl;
            window.close();
        }
    }
}

bool MazeGame::isCompleted() const {
    return completed;
}