#include "SpriteSheet.hpp"
#include "../Misc/Utility.hpp"
#include <tinyxml2.h>

SpriteSheet::SpriteSheet(const std::string& fileName) :
    m_textureName(""),
    m_fileName(fileName)
{
    loadFromFile(m_fileName);
}

SpriteSheet::SpriteSheet() :
    m_textureName(""),
    m_fileName("")
{
}

bool SpriteSheet::loadFromFile(const std::string& filename)
{
    m_fileName = filename;

    tinyxml2::XMLDocument doc;
    if(tinyxml2::XML_NO_ERROR != doc.LoadFile(m_fileName.c_str()))
        throw std::runtime_error("The file '" + m_fileName + "' don't exist.");

    m_spriteKeys.clear();

    if(auto spritesheet = doc.FirstChildElement("spriteSheet"))
    {
        if(auto name = spritesheet->Attribute("texture"))
            m_textureName = name;
        else
            throw std::runtime_error("The SpriteSheet-file '" + m_fileName + "' is invalid.");

        if(auto sprites = spritesheet->FirstChildElement("sprites"))
        {
            for(auto sprite = sprites->FirstChildElement("sprite");
                sprite != nullptr; sprite = sprite->NextSiblingElement("sprite"))
            {
                SpriteData spriteData;
                std::string key = sprite->Attribute("name");
                spriteData.x = sprite->IntAttribute("x");
                spriteData.y = sprite->IntAttribute("y");
                spriteData.width = sprite->IntAttribute("width");
                spriteData.height = sprite->IntAttribute("height");
                spriteData.originX = sprite->FloatAttribute("originx");
                spriteData.originY = sprite->FloatAttribute("originy");
                insert(key, spriteData);
            }
        }
        else
            throw std::runtime_error("The XML-file '" + m_fileName + "' is invalid.");
    }

    return true;
}

void SpriteSheet::insert(const std::string& key, const SpriteData& data)
{
    for(auto it = begin(m_spriteKeys); it != end(m_spriteKeys); ++it)
    {
        if(it->first == key)
            throw std::runtime_error("The key '" + key + "' is allready registered.");
    }
    m_spriteKeys.push_back(std::make_pair(key, data));
    /*if(m_spriteKeys.find(key) == std::end(m_spriteKeys))
        m_spriteKeys[key] = data;
    else
        throw std::runtime_error("The key '" + key + "' is allready registered.");*/
}

SpriteSheet::SpriteData SpriteSheet::get(const std::string& key) const
{
    for(auto it = begin(m_spriteKeys); it != end(m_spriteKeys); ++it)
    {
        if(it->first == key)
            return it->second;
    }

    throw std::runtime_error("The key '" + key + "' is not registered.");
}

SpriteSheet::SpriteData SpriteSheet::get(unsigned int index) const
{
    if(index >= m_spriteKeys.size())
        throw std::runtime_error("The index '" + utility::toString(index) + "' is out of range.");

    auto result = begin(m_spriteKeys);
    for(unsigned int i = 0; i != index; ++i)
        ++result;

    return result->second;
}

std::string SpriteSheet::getTextureName() const
{
    return m_textureName;
}
sf::IntRect SpriteSheet::getTextureRect(const std::string& key) const
{
    auto data = get(key);
    return sf::IntRect(data.x, data.y, data.width, data.height);
}

sf::Vector2f SpriteSheet::getOrigin(const std::string& key) const
{
    auto data = get(key);
    return sf::Vector2f(data.originX, data.originY);
}

sf::IntRect SpriteSheet::getTextureRect(const std::string& key, unsigned int index) const
{
    std::string extendedKey = key + ":" + utility::toString(index);
    return getTextureRect(extendedKey);
}

sf::Vector2f SpriteSheet::getOrigin(const std::string& key, unsigned int index) const
{
    std::string extendedKey = key + ":" + utility::toString(index);
    return getOrigin(extendedKey);
}

sf::IntRect SpriteSheet::getTextureRect(unsigned int index) const
{
    auto data = get(index);
    return sf::IntRect(data.x, data.y, data.width, data.height);
}

sf::Vector2f SpriteSheet::getOrigin(unsigned int index) const
{
    auto data = get(index);
    return sf::Vector2f(data.originX, data.originY);
}
