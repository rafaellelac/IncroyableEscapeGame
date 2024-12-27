// EinsteinPuzzle.h
// EinsteinPuzzle.h
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <map>

struct GridCell {
    sf::Sprite maison;
    sf::Sprite femme;
    sf::Sprite boisson;
    sf::Sprite animal;
    int maisonID;
    int femmeID;
    int boissonID;
    int animalID;
};



class EinsteinPuzzle {
private:
    sf::Font font;
    sf::RectangleShape inputBox;  // The box behind the text
    sf::Text inputText;
    std::string playerInput;
    sf::Text answerText;
    sf::RenderWindow window;
    std::array<sf::Texture, 3> maisonTextures;
    std::array<sf::Texture, 3> femmeTextures;
    std::array<sf::Texture, 3> boissonTextures;
    std::array<sf::Texture, 3> animalTextures;
    //the grid is 3*4
    std::array<GridCell, 3> grid;

    bool isDragging;
    sf::Sprite* currentDraggable;
    sf::Vector2i dragOffset;
    std::map<const sf::Texture*, int> textureIDs; //map des IDs des textures
    void loadResources();
    void handleEvents();
    void update();
    void draw();
    bool checkSolution();
    void reset();
    bool solutionFound;
    sf::RectangleShape answerBox;
public:
    EinsteinPuzzle();
    void run();
    
};