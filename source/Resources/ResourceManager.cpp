#include "ResourceManager.hpp"
#include <tinyxml2.h>

ResourceManager::ResourceManager(const std::string& fileName) :
    m_fileName(fileName)
{
    tinyxml2::XMLDocument doc;
    if(tinyxml2::XML_NO_ERROR != doc.LoadFile(m_fileName.c_str()))
        throw std::runtime_error("The file '" + m_fileName + "' don't exist.");

    parseTexture(doc);
    parseSpriteSheet(doc);
}

sf::Texture* ResourceManager::loadTexture(std::string& file)
{
    sf::Texture* texture = new sf::Texture;
    if(!texture->loadFromFile(file))
    {
        delete texture;
        texture = 0;
        throw std::runtime_error("The file '" + file + "' don't exist.");
    }

    return texture;
}

void ResourceManager::parseTexture(tinyxml2::XMLDocument& doc)
{
    if(auto group = doc.FirstChildElement("textures"))
    {
        for(auto it = group->FirstChildElement("texture");
            it != nullptr; it = it->NextSiblingElement("texture"))
        {
            std::string name = it->Attribute("name");
            std::string file = it->Attribute("file");

            auto existingKey = m_textureKeys.find(name);
            if(existingKey != end(m_textureKeys))
                throw std::runtime_error("Texturekey is allready registered.");

            m_textureKeys[name] = file;
        }
    }
}

const sf::Texture* ResourceManager::getTexture(const std::string& key)
{
    auto existingKey = m_textureKeys.find(key);
    if(existingKey == end(m_textureKeys))
        throw std::runtime_error("TextureKey '" + key + "' not found.");

    auto existingTexture = m_textures.find(key);
    if(existingTexture == end(m_textures))
        m_textures[key] = std::unique_ptr<sf::Texture>(std::move(loadTexture(existingKey->second)));

    return m_textures[key].get();
}

SpriteSheet* ResourceManager::loadSpriteSheet(std::string& file)
{
    SpriteSheet* spriteSheet = new SpriteSheet;
    if(!spriteSheet->loadFromFile(file))
    {
        delete spriteSheet;
        spriteSheet = 0;
        throw std::runtime_error("The file '" + file + "' don't exist.");
    }

    return spriteSheet;
}
void ResourceManager::parseSpriteSheet(tinyxml2::XMLDocument& doc)
{
    if(auto group = doc.FirstChildElement("spritesheets"))
    {
        for(auto it = group->FirstChildElement("spritesheet");
            it != nullptr; it = it->NextSiblingElement("spritesheet"))
        {
            std::string name = it->Attribute("name");
            std::string file = it->Attribute("file");

            auto existingKey = m_spriteSheetKeys.find(name);
            if(existingKey != end(m_spriteSheetKeys))
                throw std::runtime_error("SpriteSheetKey is allready registered.");

            m_spriteSheetKeys[name] = file;
        }
    }
}

SpriteSheet* ResourceManager::getSpriteSheet(const std::string& key)
{
    auto existingKey = m_spriteSheetKeys.find(key);
    if(existingKey == end(m_spriteSheetKeys))
        throw std::runtime_error("TextureKey '" + key + "' not found.");

    auto existingSpriteSheet = m_spriteSheets.find(key);
    if(existingSpriteSheet == end(m_spriteSheets))
        m_spriteSheets[key] = std::unique_ptr<SpriteSheet>(std::move(loadSpriteSheet(existingKey->second)));

    return m_spriteSheets[key].get();
}