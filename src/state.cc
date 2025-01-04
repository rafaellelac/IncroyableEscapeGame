#include "state.hh"

// Ajoute un nouvel état au StateManager
void Engine::StateManager::Add(std::unique_ptr<State> toAdd, bool replace){
    m_add = true;
    m_newState = std::move(toAdd);
    m_replace = replace;
}

// Supprime l'état actuel du StateManager
void Engine::StateManager::PopCurrent(){
    m_remove = true;
}

// Traite les changements d'état
void Engine::StateManager::ProcessStateChange(){
    if(m_remove && (!m_stateStack.empty())){
        m_stateStack.pop();
        if(!m_stateStack.empty()){
            m_stateStack.top()->Start();
        }
        m_remove = false;
    }
    if(m_add){
        if(m_replace && (!m_stateStack.empty())){
            m_stateStack.pop();
            m_replace = false;
        }

        if(!m_stateStack.empty()){
            m_stateStack.top()->Pause();
        }

        m_stateStack.push(std::move(m_newState));
        m_stateStack.top()->Init();
        m_add = false;
    }
}

// Récupère l'état actuel
std::unique_ptr<Engine::State> & Engine::StateManager::GetCurrent(){
    return m_stateStack.top();
}
