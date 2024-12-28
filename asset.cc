#include "asset.hh"

void Engine::AssetManager::AddTexture(int id, const std::string &fileName)
{
    auto texture = std::make_unique<sf::Texture>();

    if (texture->loadFromFile(fileName))
    {
        texture->setRepeated(false);
        m_textures[id] = std::move(texture);
    }
}

void Engine::AssetManager::AddFont(int id, const std::string &fileName)
{
    auto font = std::make_unique<sf::Font>();
    if (font->loadFromFile(fileName)){
        m_fonts[id] = std::move(font);
    }
}

const sf::Texture &Engine::AssetManager::GetTexture(int id) const
{
    return *(m_textures.at(id).get());
}

const sf::Font &Engine::AssetManager::GetFont(int id) const
{
    return *(m_fonts.at(id).get());
}
