// MazeGame.cpp
#include "Maze.hh"
#include <iostream>

// Overload the division operator for sf::Vector2f
sf::Vector2f operator/(const sf::Vector2f& vec, const sf::Vector2f& divisor) {
    return sf::Vector2f(vec.x / divisor.x, vec.y / divisor.y);
}

MazeGame::MazeGame() : completed(false) {
    // Load the maze texture
    if (!mazeTexture.loadFromFile("maze.png")) {
        std::cerr << "Failed to load maze texture" << std::endl;
        exit(1);
    }
    mazeSprite.setTexture(mazeTexture);

    // Calculate the scale factor to fit the maze to the window
    sf::Vector2u mazeSize = mazeTexture.getSize();
    float scaleX = static_cast<float>(800) / static_cast<float>(mazeSize.x);
    float scaleY = static_cast<float>(800) / static_cast<float>(mazeSize.y);
    float scale = std::min(scaleX, scaleY); // Use the smaller scale to fit the maze within the window

    // Apply the scale factor to the maze sprite
    mazeSprite.setScale(scale, scale);

    // Debug output to check the size of the maze texture and the scale factor
    std::cout << "Maze texture size: " << mazeSize.x << " x " << mazeSize.y << std::endl;
    std::cout << "Scale factor: " << scale << std::endl;

    // Load the player texture
    if (!playerTexture.loadFromFile("player.png")) {
        std::cerr << "Failed to load player texture" << std::endl;
        exit(1);
    }
    playerSprite.setTexture(playerTexture);

    // Set the scale of the player sprite
    playerSprite.setScale(0.01f, 0.01f); // Adjust the scale as needed

    playerPosition = { 50.0f, 50.0f }; // Starting position
    playerSprite.setPosition(playerPosition);

    // Convert the maze texture to an image for pixel checking
    mazeImage = mazeTexture.copyToImage();

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
            if (unscaledX >= 0 && unscaledX < mazeImage.getSize().x && unscaledY >= 0 && unscaledY < mazeImage.getSize().y) {
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

void MazeGame::init() {
    // Initialize the game (if needed)
}

void MazeGame::update(float deltaTime) {
    // Handle player movement
    sf::Vector2f movement(0.0f, 0.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        movement.y -= 100.0f * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        movement.y += 100.0f * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        movement.x -= 100.0f * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        movement.x += 100.0f * deltaTime;
    }

    // Calculate the new position
    sf::Vector2f newPosition = playerPosition + movement;

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

void MazeGame::render(sf::RenderWindow& window) {
    // Debug output to check if render is being called
    std::cout << "Rendering maze and player" << std::endl;

    window.draw(mazeSprite);
    window.draw(playerSprite);
}

bool MazeGame::isCompleted() const {
    return completed;
}