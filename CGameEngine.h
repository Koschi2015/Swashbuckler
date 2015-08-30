#ifndef CGAMEENGINE_H
#define CGAMEENGINE_H
#include "CWindowHandle.h"
#include "CSpriteSheet.h"
#include "CMouse.h"
#include "CRessourcenManager.h"
#include "CUI.h"
#include "CMapIso.h"
#include "CScenegraph.h"
#include "CStateMachine.h"
#include "CManagedFont.h"
#include "CDungeonGenerator.h"
#include "CLogFile.h"

class CGameEngine
{
private:
    // Handler auf das Fenster
    CWindowHandle Window;
    // Eingabe der Tastatur/Joystick ect.
    const sf::Input* InputHandle;
    // Event Handler für Ereignisse wie Fensterschließen
    sf::Event* EventHandler;
    // Mouse
    CMouse* Mouse;
    // Ressourcen Manager
    CRessourcenManager RessourcenManager;
    //
    CMapIso IsoMap;
    //
    CSceneGraph* SceneGraph;
    //
    CStateStack GameStateStack;
    #ifdef LOGFILE
    //
    static CLogFile* LogFile;
    #endif
    // Hauptspielschleife
    CState GameLoop();
    // Hauptmenü
    CState MainMenuLoop();
    //
    CState OptionLoop();
    //
    void Init_Game();
    // Erstell das Hauptmenu
    void Init_MainMenu();
    //
    void Init_OptionMenu();
    //
    void Init_GameUI();
    //
    void Init_Intro();
    // Pointer auf das UI fürs Main Menu
    CUI_Surface* MainMenu_UI;
    // Pointer auf das UI für Option Menu
    CUI_Surface* Option_UI;
    // Pointer auf das UI für das Spiel
    CUI_Surface* Game_UI;
    // Versteckt oder Zeigt die Maus
    void Switch_Mouse_On(bool Value);
    // Nachrichten Schleife
    CMessageLoop Loop;
    // überprüft ein UI auf enventuelle Eingaben
    bool Check_UI_Input(CUI_Surface* UI);
    // macht einen Screenshot vom Bildschirm
    void Capture_Screenshot();
public:
    // HauptSchleife
    int MainLoop();
    //
    void static Set_LogFile(CLogFile* logfile);
    // Konstruktor
    CGameEngine();
    // Destruktor
    virtual ~CGameEngine();
    protected:
    private:
};

#endif // CGAMEENGINE_H
