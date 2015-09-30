#ifndef SPRITESHEET_HPP
#define SPRITESHEET_HPP

#include <vector>
#include <utility>
#include <string>
#include <SFML/Graphics/Rect.hpp>

class SpriteSheet
{
public:
    struct SpriteData
    {
        int x;
        int y;
        int width;
        int height;
        float originX;
        float originY;

        SpriteData() : x(0), y(0), width(0), height(0), originX(0), originY(0)
        { }
    };

private:
    std::vector<std::pair<std::string, SpriteData>> m_spriteKeys;
    std::string m_textureName;
    std::string m_fileName;

    void insert(const std::string& key, const SpriteData& data);

public:
    SpriteSheet(const std::string& fileName);
    SpriteSheet();
    SpriteData get(const std::string& key) const;
    SpriteData get(unsigned int index) const;
    std::string getTextureName() const;
    bool loadFromFile(const std::string& fileName);
    sf::IntRect getTextureRect(unsigned int index) const;
    sf::IntRect getTextureRect(const std::string& key) const;
    sf::IntRect getTextureRect(const std::string& key, unsigned int index) const;
    sf::Vector2f getOrigin(const std::string& key) const;
    sf::Vector2f getOrigin(const std::string& key, unsigned int index) const;
    sf::Vector2f getOrigin(unsigned int index) const;
    int getSpriteCount() const;
};

#endif