#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <memory>
#include "game.hh"
#include "asset.hh"
#include "Minigame.hh"


struct Cell {
    sf::Sprite maison;
    sf::Sprite femme;
    sf::Sprite boisson;
    sf::Sprite cigare;
    sf::Sprite animal;
    int maisonID;
    int femmeID;
    int boissonID;
    int animalID;
};


class Enigme : public MiniGame {
    private:
        std::shared_ptr<Context> m_context;
        sf::RenderWindow m_window;
        sf::RectangleShape m_inputBox;
        sf::Text m_inputText;
        std::string m_playerInput;
        sf::Text m_answerText;
        sf::Text m_phraseText;
        sf::RectangleShape m_answerBox;
        std::array<sf::Texture, 5> maisonTextures;
        std::array<sf::Texture, 5> femmeTextures;
        std::array<sf::Texture, 5> boissonTextures;
        std::array<sf::Texture, 5> animalTextures;

        std::array<Cell, 3> grid;
        bool isDragging;
        sf::Sprite* currentDraggable;
        sf::Vector2i dragOffset;
        bool iscompleted;
        std::map<const sf::Texture*, int> textureIDs;


    public:
        Enigme(std::shared_ptr<Context> &context);
        void Init() override;
        void ProcessInput() override;
        void Update(sf::Time deltaTime) override;
        void Draw() override;
        bool isCompleted() const override;
};