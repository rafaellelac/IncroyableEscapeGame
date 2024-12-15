// EinsteinPuzzle.h
// EinsteinPuzzle.h
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>


class Cell {

public:

    sf::Sprite maison;

    sf::Sprite nationalite;

    sf::Sprite boisson;

    sf::Sprite cigare;

    sf::Sprite animal;

};


class EinsteinPuzzle {
private:
    sf::RenderWindow window;
    std::array<sf::Texture, 5> maisonTextures;
    std::array<sf::Texture, 5> nationaliteTextures;
    std::array<sf::Texture, 5> boissonTextures;
    std::array<sf::Texture, 5> cigareTextures;
    std::array<sf::Texture, 5> animalTextures;

    std::array<Cell, 5> grid;
    bool isDragging;
    sf::Sprite* currentDraggable;
    sf::Vector2i dragOffset;

    void loadResources();
    void handleEvents();
    void update();
    void draw();
    bool checkSolution();
    void reset();

public:
    EinsteinPuzzle();
    void run();
};