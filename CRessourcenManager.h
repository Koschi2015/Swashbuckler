#ifndef CRESOURCENMANAGER_H
#define CRESOURCENMANAGER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "CLogFile.h"


struct St_Ressource
{
    int Counter;
    St_Ressource* Next;
    St_Ressource* Prev;
    std::string RessourcenName;
    sf::Image* Image;
    sf::Font* Font;
    sf::Music* Music;
    sf::SoundBuffer* SoundBuffer;
};

class CRessourcenManager
{
private:
    // Ressource
    St_Ressource* Ressource;
    // löscht die ganze Liste
    void Clear_List();
    // löscht ein Element
    bool Clear_Element();
    // Nächste Element
    bool Next_Element();
    // Vorherige Element
    bool Prev_Element();
    // erste Elemnet
    void First_Element();
    #ifdef LOGFILE
    //
    static CLogFile* LogFile;
    #endif
public:
    // gibt den Pointer auf ein Image zurück
    sf::Image* Load_Image(std::string Path);
    // gibt den Pointer auf ein Font zurück
    sf::Font* Load_Font(std::string Path);
    // gibt den Pointer auf eine Musikstück zurück
    sf::Music* Load_Music(std::string Path);
    // gibt den Pointer auf eine Sound zurück
    sf::SoundBuffer* Load_SoundBuffer(std::string Path);
    // Überladene Funktion gibt eine Resource frei
    bool Release(sf::Image* RC);
    bool Release(sf::Font* RC);
    bool Release(sf::Music* RC);
    bool Release(sf::SoundBuffer* RC);
    #ifdef LOGFILE
    //
    void static Set_LogFile(CLogFile* logfile);
    #endif
    // Konstruktor
    CRessourcenManager();
    // Destruktor
    ~CRessourcenManager();
};


#endif // CRESOURCENMANAGER_H

