#include <SFML/Graphics.hpp>
#include "CRessourcenManager.h"
#include <iostream>
#ifndef CMANAGEDFONT_H
#define CMANAGEDFONT_H

class CManagedFont
{
private:
    // Pointer auf eine Font
    sf::Font* Font;
    // Dateiname
    std::string Path;
    // Ressourcen Manager
	static CRessourcenManager* RessourcenManager;
	// true bedeutet Klasse ist Managed von einem Ressourcen Managaer
	static bool Managed;
public:
    // Setzt den Ressourcen Manager
    static void Set_RessourcenManager(CRessourcenManager* RM);
    //
    void Load(std::string pfad);
    //
    sf::Font* Get_Font() {return Font;}
    // KopierKonstruktor
	CManagedFont(const CManagedFont& Value);
	//
	CManagedFont operator= (const CManagedFont& Value);
    // Konstruktor
    CManagedFont();
    // Destruktor
    ~CManagedFont();
};

#endif //CMANAGEDFONT_H
