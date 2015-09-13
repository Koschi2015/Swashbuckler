#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <unordered_map>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include "SpriteSheet.hpp"

namespace tinyxml2
{
    class XMLDocument;
}

class ResourceManager
{
private:
    std::string m_fileName;

    sf::Texture* loadTexture(const std::string& file);
    void parseTexture(tinyxml2::XMLDocument& doc);
    std::unordered_map<std::string, std::string> m_textureKeys;
    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_textures;
    
    SpriteSheet* loadSpriteSheet(const std::string& file);
    void parseSpriteSheet(tinyxml2::XMLDocument& doc);
    std::unordered_map<std::string, std::string> m_spriteSheetKeys;
    std::unordered_map<std::string, std::unique_ptr<SpriteSheet>> m_spriteSheets;

    sf::Font* loadFont(const std::string& file);
    void parseFont(tinyxml2::XMLDocument& doc);
    std::unordered_map<std::string, std::string> m_fontKeys;
    std::unordered_map<std::string, std::unique_ptr<sf::Font>> m_fonts;

    void parseMapFileName(tinyxml2::XMLDocument& doc);
    std::unordered_map<std::string, std::string> m_mapFileNames;
public:
    ResourceManager(const std::string& fileName);

    sf::Texture* getTexture(const std::string& key);
    SpriteSheet* getSpriteSheet(const std::string& key);
    sf::Font* getFont(const std::string& key);
    const std::string& getMapFileName(const std::string& key);
};

#endif