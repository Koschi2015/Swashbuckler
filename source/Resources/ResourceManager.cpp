#include "ResourceManager.hpp"
#include <tinyxml2.h>

ResourceManager::ResourceManager(const std::string& fileName) :
    m_fileName(fileName)
{
    tinyxml2::XMLDocument doc;
    if(tinyxml2::XML_NO_ERROR != doc.LoadFile(m_fileName.c_str()))
        throw std::runtime_error("The file '" + m_fileName + "' don't exist.");

    parseTexture(doc);
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

            auto existingTexture = m_textures.find(name);
            if(existingTexture != end(m_textures))
                throw std::runtime_error("Texture is allready loaded.");

            sf::Texture* texture = new sf::Texture;
            if(!texture->loadFromFile(file))
                throw std::runtime_error("The file '" + file + "' don't exist.");

            m_textures[name] = std::unique_ptr<sf::Texture>(std::move(texture));
        }
    }
}

const sf::Texture* ResourceManager::getTexture(const std::string& key) const
{
    auto result = m_textures.find(key);
    if(result == end(m_textures))
        throw std::runtime_error("TextureKey '" + key + "' not found.");
    return result->second.get();
}