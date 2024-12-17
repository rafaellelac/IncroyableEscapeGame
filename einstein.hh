// EinsteinPuzzle.h
// EinsteinPuzzle.h
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>


class Cell {

public:

    sf::Sprite maison;

    sf::Sprite boisson;

    sf::Sprite femme;

    sf::Sprite animal;

};


class EinsteinPuzzle {
private:
    sf::RenderWindow window;
    std::array<sf::Texture, 3> maisonTextures;
    std::array<sf::Texture, 3> femmeTextures;
    std::array<sf::Texture, 3> boissonTextures;
    std::array<sf::Texture, 3> animalTextures;

    std::array<Cell, 3> grid;

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