#include "asset.hh"

// Ajoute une texture à l'AssetManager
void Engine::AssetManager::AddTexture(int id, const std::string &fileName)
{
    auto texture = std::make_unique<sf::Texture>();

    // Charge la texture à partir du fichier
    if (texture->loadFromFile(fileName))
    {
        texture->setRepeated(false);
        m_textures[id] = std::move(texture); // Ajoute la texture au map des textures
    }
}

// Ajoute une police à l'AssetManager
void Engine::AssetManager::AddFont(int id, const std::string &fileName)
{
    auto font = std::make_unique<sf::Font>();
    
    // Charge la police à partir du fichier
    if (font->loadFromFile(fileName)){
        m_fonts[id] = std::move(font); // Ajoute la police au map des polices
    }
}

// Récupère une texture par son identifiant
const sf::Texture &Engine::AssetManager::GetTexture(int id) const
{
    return *(m_textures.at(id).get());
}

// Récupère une police par son identifiant
const sf::Font &Engine::AssetManager::GetFont(int id) const
{
    return *(m_fonts.at(id).get());
}
