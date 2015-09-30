#include "Map.hpp"
#include "../Resources/ResourceManager.hpp"
#include "../Provider/StaticProvider.hpp"
#include "../Provider/AnimationProvider.hpp"
#include <tinyxml2.h>

void Map::load(const std::string& mapKey)
{
    std::string file = m_resourceManager.getMapFileName(mapKey);
    tinyxml2::XMLDocument doc;
    if(tinyxml2::XML_NO_ERROR != doc.LoadFile(file.c_str()))
        throw std::runtime_error("The file '" + file + "' don't exist.");

    TilePool parsedTiles;
    ProviderPool parsedProvider;

    parseTextureData(doc);
    parseProvider(doc, parsedProvider);
    parseTile(doc, parsedTiles, parsedProvider);
    parseGrid(doc, parsedTiles);
}

void Map::parseProvider(tinyxml2::XMLDocument& doc,
                        ProviderPool& providerPool)
{
    if(auto group = doc.FirstChildElement("map")->FirstChildElement("providers"))
    {
        for(auto it = group->FirstChildElement("provider");
            it != nullptr; it = it->NextSiblingElement("provider"))
        {
            std::string name = it->Attribute("name");
            for(auto child = it->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
            {
                if(std::string(child->Name())== "static")
                {
                    float value = child->FloatAttribute("value");
                    providerPool[name] = std::unique_ptr<Provider>(new StaticProvider(value));
                }
                else if(std::string(child->Name()) == "animation")
                {
                    unsigned int firstIndex = child->IntAttribute("firstindex");
                    unsigned int lastIndex = child->IntAttribute("lastindex");
                    float frameTime = child->FloatAttribute("frametime");
                    providerPool[name] = std::unique_ptr<Provider>(new AnimationProvider(firstIndex, lastIndex, frameTime));
                }
            }
        }
    }
}

void Map::parseTile(tinyxml2::XMLDocument& doc,
                    TilePool& tilePool,
                    ProviderPool& providerPool)
{
    if(auto group = doc.FirstChildElement("map")->FirstChildElement("tiles"))
    {
        for(auto it = group->FirstChildElement("tile");
            it != nullptr; it = it->NextSiblingElement("tile"))
        {
            std::string rep = it->Attribute("rep");
            std::string name = it->Attribute("name");
            std::string textureprovider = it->Attribute("textureprovider");

            tilePool[rep] = Tile(rep, name, providerPool[textureprovider]->clone());
        }
    }
}

void Map::parseGrid(tinyxml2::XMLDocument& doc,
                    TilePool& tilePool)
{
    if(auto group = doc.FirstChildElement("map")->FirstChildElement("grid"))
    {
        std::vector<std::string> lines;

        std::string data = group->GetText();

        // Remove first and last line breaks
        data = data.substr(data.find_first_of('\n')+1, data.find_last_of('\n'));

        // Get the lines separated without the newline char
        for(std::size_t i = 0; i < data.length(); i = data.find('\n', i)+1)
            lines.push_back(data.substr(i, data.find('\n', i)-i));

        for(size_t row = 0; row < lines.size(); ++row)
        {
            for(std::size_t column = 0; column < lines[row].length(); column += 2)
            {
                std::string rep = lines[row].substr(column, 2);

                // Ignore empty 'tiles'
                if(rep == "  ")
                    continue;

                auto pos = sf::Vector2i(static_cast<unsigned int>(column / 2), static_cast<unsigned int>(row));
                Tile tile = tilePool[rep];
                tile.setGridPosition(pos);
                tile.bindSpriteSheet(*m_currentMapSheet);
                tile.bindTexture(m_currentTexture);
                m_tiles.push_back(tile);
            }
        }
    }
    else
        throw std::runtime_error("Can't find grid.");
}

void Map::parseTextureData(tinyxml2::XMLDocument& doc)
{
    if(auto group = doc.FirstChildElement("map"))
    {
        m_currentTexture = m_resourceManager.getTexture(group->Attribute("texturekey"));
        m_currentMapSheet = m_resourceManager.getSpriteSheet(group->Attribute("spritesheetkey"));
    }
}