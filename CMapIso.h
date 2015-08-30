#ifndef CMAPISO_H
#define CMAPISO_H

#include <iostream>
#include <SFML/System/Clock.hpp>
#include "CSpriteSheet.h"
#include "CDungeonGenerator.h"
#include "CLogFile.h"


class CAnimation
{
private:
    // Zeitgeber für die Animation
    static sf::Clock Timer;
    // bei welcher zeit das nächste Bild kommt
    float FrameTime;
    // Zeit die der nächste Frame kommen soll
    float TimeNextFrame;
    // Letztes Bild im Spritesheet
    int LastFrame;
    // Erste Bild im Spritesheet
    int FirstFrame;
    // Bild was Angezeigt wird wenn keine Animation gezeigt werden soll
    int StopFrame;
    // Aktueller Zähler
    int CurrentFrame;
    // true Animation wird gespielt; false StopFrame wird angezeigt
    bool Animation_On;
    #ifdef LOGFILE
    //
    static CLogFile* LogFile;
    #endif
public:
    // Startet / Stoppt Animaation
    void Animation_on(bool Value) {Animation_On = Value;}
    // Setzt das erste Frame
    void Set_FirstFrame(int firstFrame) {FirstFrame = firstFrame;}
    // Setzt das letzte Frame
    void Set_LastFrame(int lastFrame) {LastFrame = lastFrame;}
    // Setzt das Stop Frame
    void Set_StopFrame(int stopFrame) {StopFrame = stopFrame;}
    // Frame time setzen
    void Set_FrameTime(float frameTime) {FrameTime = frameTime;}
    // Gibt den StartFrame Zurück
    int Get_FirstFrame() const {return FirstFrame;}
    // Gibt den LastFrame Zurück
    int Get_LastFrame() const {return LastFrame;}
    // Gibt den StopFrame Zurück
    int Get_StopFrame() const {return StopFrame;}
    // Gibt die zeit wieder die von Bild zu Bild verstreicht
    float Get_FrameTime() const {return FrameTime;}
    // Gibt den Aktuellen Index des Tiles von Layer 3 wieder
    int Get_CurrentFrame();
    //
    void static Set_LogFile(CLogFile* logfile);
    // default Konstruktor
    CAnimation();
    // Destruktor
    ~CAnimation() {}
};
class CTileIso
{
protected:
    // X Koordinate
    int X_Coord;
    // Y Koordinate
    int Y_Coord;
    // Sprite Layer 1 Index (Boden)
    int Layer1;
    // Sprite Layer 2 Index (Mauer)
    int Layer2;
    // Sprite Index 3 Animatited (Deko)
    CAnimation Layer3;
    // Licht Level von 0 bis 255
    int LightIndex;
    // Dieses Tile ist eine Lichtquelle (True)
    bool LightSource;
    // Dieses Tile ist begehbar (true)
    bool Walkable;
    // Dieses Tile ist in Sichtline (true)
    bool LineOfSight;
    // True wenn dieses Tile Animert werden soll
    bool Animated;
    #ifdef LOGFILE
    //
    static CLogFile* LogFile;
    #endif
public:
    // Setzt die X Koordinate
    void Set_X_Coord(int X) {X_Coord = X;}
    // Setzt die Y Koordinate
    void Set_Y_Coord(int Y) {Y_Coord = Y;}
    // Setzt den Layer 1 Index
    void Set_Layer_1(int Value) {Layer1 = Value;}
    // Setzt den Layer 2 Index
    void Set_Layer_2(int Value) {Layer2 = Value;}
    // Setzt den LichtIndex
    void Set_LightSourceIndex(int Value) {LightIndex = Value;}
    // Setzt ob dieses Tile eine Lichtquelle ist
    void Set_LightSource(bool Value) {LightSource = Value;}
    // Setzt ob dieses Begehbar ist
    void Set_Walkable(bool Value) {Walkable = Value;}
    // Setzt ob dieses Tile in Sichtline des Spieler liegt
    void Set_LineOfSight(bool Value) {LineOfSight = Value;}
    // Setzt ob das Tile Animiert ist
    void Set_Animated(bool Value) {Layer3.Animation_on(Value);}
    // Setzt die Animations Daten
    void Set_Layer_3(int FirstFrame,int LastFrame,int StopFrame,float FrameTime);
    // Gibt die X Koordinate zurücke
    int Get_X_Coord() const {return X_Coord;}
    // Gibt die Y Koordinate zurücke
    int Get_Y_Coord() const {return Y_Coord;}
    //
    int Get_Layer_1() const {return Layer1;}
    //
    int Get_Layer_2() const {return Layer2;}
    //
    int Get_Layer_3() {return Layer3.Get_CurrentFrame();}
    //
    int Get_LightIndex() const {return LightIndex;}
    //
    bool Get_LightSource() const {return LightSource;}
    //
    bool Get_Walkable() const {return Walkable;}
    //
    bool Get_LineOfSight() const {return LineOfSight;}
    //
    bool Get_Animated() const {return Animated;}
    #ifdef LOGFILE
    //
    void static Set_LogFile(CLogFile* logfile);
    #endif
    // Konstruktor
    CTileIso();
    // Destruktor
    virtual ~CTileIso();
};
// Strukture Eines Layers
struct St_Layer
{
    CSpriteSheet* SpriteSheet;
    int Sprite_X_Size;
    int Sprite_Y_Size;
    std::string SpriteSheet_Path;
};

class CMapIso
{
private:
    // Ausdehnung der karte in X Richtung
    int X_Size;
    // Ausdehnung der karte in Y Richtung
    int Y_Size;
    // Die Karte bestehend aus einem Tile Array
    CTileIso** Map;
    // Gibt an ob Karte immer hell ist oder da Tile licht genutzt werden soll
    bool GlobalLight;
    // SpriteSheet für Layer 1
    St_Layer Layer_1;
    // SpriteSheet für Layer 2
    St_Layer Layer_2;
    // SpriteSheet für Layer 3
    St_Layer Layer_3;
    // Dungeongenerator
    static CDungeonGenerator DungeonGenerator;
    // Berechnet die Lichtverhältnisse auf der Karte
    void Calculate_LightMap();
    #ifdef LOGFILE
    //
    static CLogFile* LogFile;
    #endif
public:
    // Setzt die Map Größe
    void Set_MapSize(int x,int y);
    // Setzt das Globale Licht an oder aus
    void Set_GlobalLight(bool Value) {GlobalLight = Value;}
    // Setzt den Layer 1
    void Set_Layer_1(std::string Path,int X_Size = 32,int Y_Size = 32);
    // Setzt den Layer 2
    void Set_Layer_2(std::string Path,int X_Size = 32,int Y_Size = 32);
    // Setzt den Layer 3
    void Set_Layer_3(std::string Path,int X_Size = 32,int Y_Size = 32);
    // Setzt Walkable eines Tiles der Map
    void Set_Walkable(int XPos_Tile,int YPos_Tile,bool Value);
    // Setzt ob das Tile eine Lichtuquelle ist
    void Set_LightSource(int XPos_Tile,int YPos_Tile,bool Value);
    // Setzt den Lichtindex eines Tiles
    void Set_LightSourceIndex(int XPos_Tile,int YPos_Tile,int Value);
    // Setzt Line of Sight eines Tiles
    void Set_LineOfSight(int XPos_Tile,int YPos_Tile,bool Value);
    // Setzt ob Layer 3 Animiert ist
    void Set_Animated(int XPos_Tile,int YPos_Tile,bool Value);
    // Setzt den Layer 1 Tile Index
    void Set_Tile_Layer1(int XPos_Tile,int YPos_Tile,int Value);
    // Setzt den Layer 1 Tile Index
    void Set_Tile_Layer2(int XPos_Tile,int YPos_Tile,int Value);
    // Setzt den Layer 3 Tile Index
    void Set_Tile_Layer3(int XPos_Tile,int YPos_Tile,int FirstFrame,int LastFrame,int StopFrame,float FrameTime);
    // Gibt zurück ob das Teil begehbar ist
    bool Get_Walkable(int XPos_Tile,int YPos_Tile) const {return Map[XPos_Tile][YPos_Tile].Get_Walkable();}
    // Gibt zurück ob das Tile eine Lichtquelle ist
    bool Get_LightSource(int XPos_Tile,int YPos_Tile) const {return Map[XPos_Tile][YPos_Tile].Get_LightSource();}
    // Gibt den LichtIndex zurück
    int Get_LightSourceIndex(int XPos_Tile,int YPos_Tile) const {return Map[XPos_Tile][YPos_Tile].Get_LightIndex();}
    // Gibt zurück ob das TIle LOS Blockiert
    bool Get_LineOfSight(int XPos_Tile,int YPos_Tile) const {return Map[XPos_Tile][YPos_Tile].Get_LineOfSight();}
    // Gibt zurück ob das Tile Animiert ist
    bool Get_Animated(int XPos_Tile,int YPos_Tile) const {return Map[XPos_Tile][YPos_Tile].Get_Animated();}
    // Gibt zurück ob die Karte Global beleuchtet ist.
    bool Get_GlobalLight() {return GlobalLight;}
    // Gibt den Sprite vfür Layer 1 von Koordinate X,Y zurück
    sf::Sprite Get_Sprite_Layer_1(int XPos_Tile,int YPos_Tile);
    // Gibt den Sprite vfür Layer 2 von Koordinate X,Y zurück
    sf::Sprite Get_Sprite_Layer_2(int XPos_Tile,int YPos_Tile);
    // Gibt den aktuellen Sprite für Layer 3 von Koordinate X,Y zurück
    sf::Sprite Get_Sprite_Layer_3(int XPos_Tile,int YPos_Tile);
    // gibt die X - Ausdehnung der Karte zurück
    int Get_X_Size() {return X_Size;}
    // gibt die Y - Ausdehnung der Karte zurück
    int Get_Y_Size() {return Y_Size;}
    // Erstellt eine TestMap
    void Create_TestMap();
    // Erstellen einer Zufalls generierten Karte
    void Creat_RandomMap(int X_DungeonSize,int Y_DungeonSize,int X_MaxRoomSize,int Y_MaxRoomSize,int chanceRoom,int chanceFloor);
    // Errechnet ob zwischen zwei Tilen eine Line of sight besteht
    bool Tile_in_LOS(int XPos_Start,int YPos_Start,int XPos_End,int YPos_End);
    // Rotiert die Map in Uhrzeiger sinn
    void Rotate_AntiClockwise();
    // operator =
    CMapIso operator = (CMapIso Map);
    #ifdef LOGFILE
    //
    void static Set_LogFile(CLogFile* logfile);
    #endif
    // Konstruktor
    CMapIso();
    CMapIso(const CMapIso& NewMap);
    // Destruktor
    ~CMapIso();
};

#endif // CMAPISO_H
