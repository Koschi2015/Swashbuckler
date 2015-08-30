#ifndef CSCENEGRAPH_H
#define CSCENEGRAPH_H

#include "CWindowHandle.h"
#include "CMapIso.h"
#include "CMouse.h"
#include "CUI.h"
#include "CStateMachine.h"
#include "CLogFile.h"
//#include <list>


class CSceneGraph
{
private:
    // Fenster zum Rendern
    sf::RenderWindow* Window;
    //
    static CStateStack* GameState;
    // Normale Kamera
    sf::View Camera;
    // UI Kamera
    sf::View UI_Camera;
    // die Karte
    CMapIso* Map;
    // die Maus
    CMouse* Mouse;
    // Knöpfe (nicht mehr benötigt)
    CUI_Button* Button;
    // Die oberfläche für das UI
    CUI_Surface* Surface;
    // Sprites für die 3 Ebenen der Map
    sf::Sprite Layer1;
    sf::Sprite Layer2;
    sf::Sprite Layer3;
    // Schatten
    int Shadow;
    // Bildschirm Koordinaten
    int ScreenX;
    int ScreenY;
    //
    int Local_X;
    int Local_Y;
    #ifdef LOGFILE
    //
    static CLogFile* LogFile;
    #endif
public:
    //
    static void Set_GameState(CStateStack* State) {GameState = State;}
    //
    void Add_to_Scene(CMapIso* map);
    //
    void Add_to_Scene(CMouse* mouse) {Mouse = mouse;}
    //
    void Add_to_Scene(CUI_Button* button) {Button = button;}
    //
    void Add_to_Scene(CUI_Surface* surface) {Surface = surface;}
    //
    void Remove_from_Scene(CMapIso* map) {Map = 0;}
    //
    void Remove_from_Scene(CUI_Surface* surface) {Surface = 0;}
    //
    void Remove_from_Scene(CMouse* mouse) {Mouse = 0;}
    //
    void Set_Map_Center(int X,int Y)
    {
        Local_X=X;
        Local_Y=Y;
    }
    #ifdef LOGFILE
    //
    void static Set_LogFile(CLogFile* logfile);
    #endif
    // Konstruktor
    CSceneGraph(CWindowHandle* window);
    // Destruktor
    ~CSceneGraph();
    //
    void Render_Scene();

};
#endif // CSCENEGRAPH_H
