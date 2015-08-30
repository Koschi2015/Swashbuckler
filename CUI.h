#ifndef CUI_H
#define CUI_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "CSpriteSheet.h"
#include <iostream>
#include <fstream>
#include "CMessage.h"
#include "CManagedFont.h"
#include "CLogFile.h"

enum UI_Type {UIT_BASE,UIT_BUTTON,UIT_TEXT};

class CUI_Base
{
protected:
    // Wirkungsbereich
    sf::Rect<int> Scope;
    //
    int Offset_X;
    //
    int Offset_Y;
    //
    UI_Type Type;
    //
    std::string LMB_Msg;
    //
    std::string RMB_Msg;
    //
    std::string MouseOver_Msg;
    #ifdef LOGFILE
    //
    static CLogFile* LogFile;
    #endif
public:
    // Setzt den Scope
    void Set_Scope(int LeftCoord,int RightCoord,int TopCoord,int BottomCoord);
    void Set_Scope(sf::Rect<int> Value) {Scope = Value;}
    //
    UI_Type Get_UI_Type() {return Type;}
    //
    void Set_Offset(int X,int Y);
    //
    int Get_Offset_X() {return Offset_X;}
    //
    int Get_Offset_Y() {return Offset_Y;}
    //
    bool MouseInside(int X,int Y);
    //
    void Set_LMB_Msg(std::string Msg) {LMB_Msg = Msg;}
    //
    void Set_RMB_Msg(std::string Msg) {RMB_Msg = Msg;}
    //
    void Set_MouseOver_Msg(std::string Msg) {MouseOver_Msg = Msg;}
    //
    std::string Get_LMB_Msg() {return LMB_Msg;}
    //
    std::string Get_RMB_Msg() {return RMB_Msg;}
    //
    std::string Get_MouseOver_Msg() {return MouseOver_Msg;}
    //
    sf::Rect<int> Get_Scope() {return Scope;}
    // Setzen der Position
    virtual void Set_Position(int X,int Y) = 0;
    //
    virtual sf::Drawable* Render_Element() = 0;
    #ifdef LOGFILE
    //
    void static Set_LogFile(CLogFile* logfile);
    #endif
    // Konstruktor
    CUI_Base();
    // Destruktor
    virtual ~CUI_Base();
};
class CUI_Text : public CUI_Base
{
protected:
    // text
    sf::String Text;
    // Font
    sf::Font Font;
    //
    std::string FontPath;
    //
    //CManagedFont MFont;
public:
    //
    void Load(std::string Pfad,float size,sf::String::Style style);
    //
    void Set_Style(sf::String::Style style);
    //
    void Set_Position(int X,int Y) {Text.SetPosition(X,Y);}
    //
    void Set_Text(std::string text);
    void Set_Text(sf::String text) {Text = text;}
    //
    void Set_Size(float Size) {Text.SetSize(Size);}
    //
    void Set_Color(sf::Color Color) {Text.SetColor(Color);}
    //
    float Get_Size() {return Text.GetSize();}
    //
    sf::Font Get_Font() {return Font;}
    //
    sf::String Get_Text() {return Text;}
    //
    std::string Get_FontPath () {return FontPath;}
    //
    sf::Color Get_Color() {return Text.GetColor();}
    //
    sf::String::Style Get_Style() {return static_cast<sf::String::Style>(Text.GetStyle());}
    //
    sf::Drawable* Render_Element();

    CUI_Text();
    ~CUI_Text();

};
// Klasse für Benutzbare Knöpfe
class CUI_Button : public CUI_Base
{
protected:
    // Bild für die darstellung des Knopfes
    CSpriteSheet Image;
    // Nummer des Bildes wenn es sich um ein Spritesheet handelt
    int ArrayNumber;
    // Der Pfad des Bildes
    std::string ImagePath;
    // Länge X
    int Length_X;
    // Länge Y
    int Length_Y;
public:
    // Laden des Bildes
    void Load_SpriteSheet(std::string Path,int X = 32 ,int Y = 32);
    // Setzen der Position
    void Set_Position(int X,int Y);
    // Setzt die Bild Nummer
    void Set_ArrayNummber(int Value) {ArrayNumber = Value;}
    // Gibt die Bild Nummer Zurück
    int Get_ArrayNumber() {return ArrayNumber;}
    // Gibt die X Länge zurück
    int Get_Length_X() {return Length_X;}
    // Gibt die Y Länge Zurück
    int Get_Length_Y() {return Length_Y;}
    // Gibt den Pfad des Bildes Zurück
    std::string Get_ImagePath() {return ImagePath;}
    // gibt das Bild zurück das gerendet werde soll
    sf::Drawable* Render_Element();
    // Konstruktor
    CUI_Button();
    // Destruktor
    ~CUI_Button() {}
};
struct St_UISurface
{
    St_UISurface* Next;
    St_UISurface* Prev;
    CUI_Base* UI_Element;
};
class CUI_Surface
{
private:
    // Elemente der Oberfläche
    St_UISurface* Surface;
    // Funktions Pointer
    static const sf::Input* UI_InputHandle;
    //
    static CMessageLoop* MessageLoop;
    //
    void Clear_UI();
    // Timer zum Entprellen der Maus und anderer Tasten
    sf::Clock DebounceTimer;
    #ifdef LOGFILE
    //
    static CLogFile* LogFile;
    #endif
public:
    static void Set_MessageLoop(CMessageLoop* Loop) {MessageLoop = Loop;}
    //
    static void Set_Input(const sf::Input* Value) {UI_InputHandle = Value;}
    //
    void Add_Element(CUI_Button Element);
    void Add_Element(CUI_Text Element);
    //
    St_UISurface* Get_Surface_Element() {return Surface;}
    //
    sf::Drawable* Render_Element() {return Surface->UI_Element->Render_Element();}
    //
    bool Next_Element();
    //
    bool Prev_Element();
    //
    void Check_Element();
    //
    void First_Element();
    //
    void Last_Element();
    //
    void Save_UI(std::string FilePath);
    #ifdef LOGFILE
    //
    void static Set_LogFile(CLogFile* logfile);
    #endif
    //
    St_UISurface* Get_Surface_Element(std::string Command);
    // Konstruktor
    CUI_Surface();
    // Destruktor
    ~CUI_Surface();
};
#endif // CUI_H
