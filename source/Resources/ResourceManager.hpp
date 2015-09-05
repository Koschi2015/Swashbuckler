#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <unordered_map>
#include <string>
#include <SFML/Graphics/Texture.hpp>

namespace tinyxml2
{
    class XMLDocument;
}

class ResourceManager
{
private:
    std::string m_fileName;

    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_textures;
    void parseTexture(tinyxml2::XMLDocument& doc);

public:
    ResourceManager(const std::string& fileName);

    const sf::Texture* getTexture(const std::string& key) const;
};

#endif