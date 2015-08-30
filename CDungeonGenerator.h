#ifndef DUNGEONGENERATOR_H
#define DUNGEONGENERATOR_H

#include "CDice.h"
#include <iostream>
#include "CLogFile.h"
#include <list>

// Teile die ein Dungeon haben kann
enum en_DungeonTiles { DT_NOTHING,
                       DT_WALL,
                       DT_DOOR,
                       DT_FLOOR,
                       DT_EXIT,
                       DT_ENTRANCE_N,
                       DT_ENTRANCE_E,
                       DT_ENTRANCE_S,
                       DT_ENTRANCE_W,
                       DT_LIGHT,
                       DT_ROOM };

enum en_Direction { DIR_SOUTH,
                    DIR_WEST,
                    DIR_EAST,
                    DIR_NORTH,
                    DIR_FAULT};

enum en_DungeonParts { DP_XCROSS,
                       DP_TCROSS,
                       DP_LEFTWAY,
                       DP_RIGHTWAY,
                       DP_ROOM,
                       DP_DEADEND,
                       DP_FLOOR,
                       DP_FAIL};
// Struktur eines DungeonTiles
struct St_DungeonTile { en_DungeonTiles Dungeon_Layer1; // Floor
                        en_DungeonTiles Dungeon_Layer2; // Wall
                        en_DungeonTiles Dungeon_Layer3; // Deko
                        bool            Visited;};      // Besucht Ja / Nein

struct St_Coords { int X;   // X Koordinaten
                   int Y;   // Y Koordinate
                 };

struct St_Room { en_Direction ComeFrom;   // Die Richtung von der man den Raum betritt
                 St_Coords    Coords;     // Koordinaten linke obere Ecke
                 int          Lenght_X;   // Länge X
                 int          Length_Y;}; // Länge Y

// Klasse zum Generieren eins Dungeons
class CDungeonGenerator
{
private:
    // Liste mit den Offenen Enden
    std::list<St_Coords> OpenEndsList;
    std::list<St_Coords>::iterator OpenEndsListIterator;
    // Länge X des Dungeons
    int DungeonSize_X;
    // Länge Y des Dungeons
    int DungeonSize_Y;
    // Maximale Raumgröße X
    int MaxRoomSize_X;
    // Maximale Raumgröße Y
    int MaxRoomSize_Y;
    // Chance einen Raum zu erschaffen
    int ChanceRoom;
    // Chance einen Raum zu erschaffen
    int ChanceFloor;
    // Aktuelle Zelle
    St_Coords CurrentCell;
    //
    int CellInUse;
    //
    int MaxCells;
    // Der Dungeon als Pointer
    St_DungeonTile** Dungeon;
    #ifdef LOGFILE
    //
    static CLogFile* LogFile;
    #endif
public:
    // Erschafft ein Dungeon
    void Create_RandomDungeon(int X_DungeonSize, // Dungengröße X
                              int Y_DungeonSize, // Dungengröße Y
                              int X_MaxRoomSize, // maximale Größe eines Raumes X
                              int Y_MaxRoomSize, // maximale Größe eines Raumes Y
                              int chanceRoom,    // Chance einen Raum zu erzeugen
                              int chanceFloor);  // Chance einen Floor zu erzeugen
    // Gibt das Dungeon Tile mit den Koordinaten X,Y zurück
    St_DungeonTile Get_DungeonTile(int x,int y) {return Dungeon[x][y];}
    #ifdef LOGFILE
    //
    void static Set_LogFile(CLogFile* logfile);
    #endif
    // Konstruktor
    CDungeonGenerator();
    // Destruktor
    ~CDungeonGenerator();
private:
    // Erschafft ein Dungeon in der Angegebenen Größe und füllt es mit Boden auf auf
    void Create_Dungeon(int X_DungeonSize,
                        int Y_DungeonSize);
    // Setzt die aussenmauern als Besucht
    void Set_OuterWalls();
    // Legt den Start punkt fest X-Kreuzung
    bool Set_StartPoint(St_Coords Coords);
    // wählt einen Element für den Dungeon aus
    en_DungeonParts Select_DungeonPart();
    // Findet die Richtung in der es weitergeht
    en_Direction Get_Direction(St_Coords Coords);
    // führt den Gang nach links fort
    bool Set_LeftWay(St_Coords Coords,en_Direction direction);
    // führt den Gnag nach rechts fort
    bool Set_RightWay(St_Coords Coords,en_Direction direction);
    // Flur auf Map erstellen
    bool Set_Floor(St_Coords Coords,en_Direction direction);
    // T-Kreuzung auf Map erstellen
    bool Set_TCrossWay(St_Coords Coords,en_Direction direction);
    // X-Kreuzung auf Map erstellen
    bool Set_XCrossWay(St_Coords Coords,en_Direction direction);
    // Raum auf Map erstellen
    bool Set_Room(St_Coords Coords,en_Direction direction);
    // Neue Richtung erzwingen
    bool ForceNewDirection(St_Coords Coords);
};
#endif // DUNGEONGENERATOR_H
