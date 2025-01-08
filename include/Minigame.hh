#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "state.hh"

class MiniGame : public Engine::State{

public:
    virtual bool isCompleted() const = 0;
};