#pragma once
#include <memory>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include "state.hh"
#include "asset.hh"
#include <SFML/Graphics.hpp>


enum AssetID
{
    MAIN_FONT = 0,
    BACKGROUND1,
    COMPUTER_FONT,
    MAZE,
    PLAYER,
    CLASSROOM,
};

struct Context{

    std::unique_ptr<sf::RenderWindow> m_window;
    std::unique_ptr<Engine::StateManager> m_states;
    std::unique_ptr<Engine::AssetManager> m_assets;

    Context(){
       m_assets = std::make_unique<Engine::AssetManager>();
       m_states = std::make_unique<Engine::StateManager>();
       m_window = std::make_unique<sf::RenderWindow>();
    }
};

class Game{
    private:
        std::shared_ptr<Context> m_context;
        const sf::Time TIME_PER_FRAME = sf::seconds(1.f/60.f);
    public:
        Game();
        ~Game();
        void Run();
};

