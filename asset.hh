#pragma once

#include <map>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <memory>
#include <string>



namespace Engine
{
    class AssetManager
    {
    private:
        std::map<int, std::unique_ptr<sf::Texture>> m_textures;
        std::map<int, std::unique_ptr<sf::Font>> m_fonts;
    public:

        void AddTexture(int id, const std::string& fileName);
        void AddFont(int id, const std::string& fileName);
        
        const sf::Texture &GetTexture(int id) const;
        const sf::Font &GetFont(int id) const;
    
    };
} // namespace Engine

