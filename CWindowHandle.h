#ifndef CWINDOWHANDLE_H
#define CWINDOWHANDLE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "CLogFile.h"

// Struct um die Video Formate speichern zu können
struct St_VideoMode
{
    int Width;
    int Height;
    int BitsPerPixel;
};
// Classe um auf das Fenster Handeln zu können
class CWindowHandle
{
private:
    // Fenster des Handler
    sf::RenderWindow* Window;
    // der Video Modus des Fenster
    sf::VideoMode Mode;
    // Speicherung aller möglichen Formate auf dem aktuellen Rechner
    St_VideoMode* ModeArray;
    // Maximal Anzahl der möglichen Formate
    int ModeCount;
    // true für Vollbildschirm false für Fenstermodus
    bool FullScreen;
    // Name des Fensters
    std::string WindowName;
    #ifdef LOGFILE
    //
    static CLogFile* LogFile;
    #endif
public:
    // Setzt einen neuen Video Modus
    bool Select_VideoMode(int Index);
    // erstellt das Fenster
    void Create_Window();
    //
    void Create_Window(int VideoMode);
    // Setzt Name des Fensters
    void Set_WindowName(std::string Name) {WindowName = Name;}
    // Setzt das Fenster auf Vollbild oder nicht
    void Set_FullScreen(bool Set){FullScreen = Set;}
    // Gibt den Namen des Fensters zurück
    std::string Get_WindowName() const {return WindowName;}
    // Gibt zurück ob Vollbild Flag gesetzt ist.
    bool Get_FullScreen() const {return FullScreen;}
    // gibt den Pointer auf das Window zurück
    sf::RenderWindow* Get_Window_as_Pointer() const {return Window;}
    // gibt den Pointer auf den Inputhandler wieder
    const sf::Input* Get_Input_as_Pointer() const {return &Window->GetInput();}
    // überprüft ob ein Video Modus zur verfügung steht
    int VideoMode_Possible(int X,int Y,int col);
    //
    sf::VideoMode Get_VideoMode() {return Mode;}
    #ifdef LOGFILE
    //
    void static Set_LogFile(CLogFile* logfile);
    #endif
    // Default Konstruktor
    CWindowHandle();
    // Destruktor
    virtual ~CWindowHandle();
};
#endif // CWINDOWHANDLE_H
