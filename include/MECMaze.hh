#pragma once
#include "MEC.hh"
#include "game.hh"
#include <memory>
#include <SFML/Graphics.hpp>  

class MECMaze : public MEC {

    public:
        MECMaze(std::shared_ptr<Context> &context);
        void Init() override;
        void ProcessInput() override;
        void Update(sf::Time deltaTime) override;
        void Draw() override;
};