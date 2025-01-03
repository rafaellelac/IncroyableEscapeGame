#pragma once
#include <SFML/System/Time.hpp>
#include <stack>
#include <memory>
#include <iostream>


namespace Engine
{
    class State{

        public:
            virtual void Init()=0;      
            virtual void ProcessInput()=0;
            virtual void Update(sf::Time deltaTime)=0;
            virtual void Draw() = 0;
            virtual void Start() {}
            virtual void Pause() {}
    };


    class StateManager{
    
        private:   
          std::stack<std::unique_ptr<State>> m_stateStack;
           std::unique_ptr<State> m_newState;
            bool m_add;
            bool m_replace;
            bool m_remove;


        public:
            StateManager():m_add(false),m_replace(false),m_remove(false){}  
            void Add(std::unique_ptr<State> toAdd, bool replace = false);
            void PopCurrent();
            void ProcessStateChange();
            std::unique_ptr<State> &GetCurrent();
    };

}