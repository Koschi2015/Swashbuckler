#include "CManagedFont.h"
CRessourcenManager* CManagedFont::RessourcenManager = 0;
bool CManagedFont::Managed = false;

void CManagedFont::Set_RessourcenManager(CRessourcenManager* RM)
{
    if(RM && !RessourcenManager)
    {
        RessourcenManager = RM;
        Managed = true;
    }
}
CManagedFont::CManagedFont()
{
    Font = 0;
}
CManagedFont::~CManagedFont()
{
    if(Font)
    {
        if(Managed)
        {
            RessourcenManager->Release(Font);
        }
        else
        {
            delete Font;
            Font = 0;;
        }
    }
}
void CManagedFont::Load(std::string pfad)
{
    Path = pfad;
    if(Managed)
    {
        Font = RessourcenManager->Load_Font(Path);
    }
    else
    {
        Font = new sf::Font;
        Font->loadFromFile(Path);
    }
}
CManagedFont::CManagedFont(const CManagedFont& Value)
{
    if(Managed)
    {
        Path = Value.Path;
        Font = RessourcenManager->Load_Font(Path);
    }
    else
    {
        Path = Value.Path;
        Font = new sf::Font;
        Font->loadFromFile(Path);
    }
}
CManagedFont CManagedFont::operator= (const CManagedFont& Value)
{
    if(Managed)
    {
        Path = Value.Path;
        Font = RessourcenManager->Load_Font(Path);
    }
    else
    {
        Path = Value.Path;
        Font = new sf::Font;
        Font->loadFromFile(Path);
    }
    return *this;
}
