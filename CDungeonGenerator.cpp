#include "CDungeonGenerator.h"

#ifdef LOGFILE
CLogFile* CDungeonGenerator::LogFile = 0;
#endif

CDungeonGenerator::CDungeonGenerator()
{
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_GREEN;
        *LogFile << "CDungeonGenerator" << this << ": Aufruf des Konstruktors." << CLogFile::endl();
    }
    #endif
    DungeonSize_X = 0;
    DungeonSize_Y = 0;
    MaxRoomSize_X = 0;
    MaxRoomSize_Y = 0;
    ChanceRoom = 0;
    ChanceFloor = 0;
    Dungeon = 0;
    CurrentCell.X = 0;
    CurrentCell.Y = 0;
    CellInUse = 0;
    MaxCells = 0;
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << LFF_GREEN;
        *LogFile << "CDungeonGenerator" << this << ": Verlassen des Konstruktors." << CLogFile::endl();
    }
    #endif
}

CDungeonGenerator::~CDungeonGenerator()
{
    if(Dungeon)
    {
        for(int i = 0;i<DungeonSize_X;i++)
        {
            delete[] Dungeon[i];
        }
        delete[] Dungeon;
    }
    Dungeon = 0;
}
void CDungeonGenerator::Set_OuterWalls()
{
    for(int i = 0; i < DungeonSize_X;i++)
    {
        for(int j = 0; j < DungeonSize_Y; j++)
        {
            if(i == 0 || j == 0 || i == DungeonSize_X-1 || j == DungeonSize_Y-1)
            {
                Dungeon[i][j].Visited = true;
                Dungeon[i][j].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[i][j].Dungeon_Layer2 = DT_WALL;
                Dungeon[i][j].Dungeon_Layer3 = DT_NOTHING;
                CellInUse++;
            }
        }
    }
}
void CDungeonGenerator::Create_RandomDungeon( int X_DungeonSize,int Y_DungeonSize,int X_MaxRoomSize,int Y_MaxRoomSize,int chanceRoom,int chanceFloor)
{
    // Prüfen der Werte falls notwenig Standard werte Setzen
    if(X_DungeonSize <= X_MaxRoomSize || Y_DungeonSize <= Y_MaxRoomSize)
    {
        X_DungeonSize = 150;
        X_MaxRoomSize = 10;
        Y_DungeonSize = 150;
        Y_MaxRoomSize = 10;
    }
    // Erst erstellen des neuen Dungeon eventuell allter wird gelöscht
    Create_Dungeon(X_DungeonSize,Y_DungeonSize);
    // Werte in Klasse übernehmen
    DungeonSize_X = X_DungeonSize;
    DungeonSize_Y = Y_DungeonSize;
    MaxRoomSize_X = X_MaxRoomSize;
    MaxRoomSize_Y = Y_MaxRoomSize;
    MaxCells = DungeonSize_X * DungeonSize_Y;
    // Chancen für einen Flur oder Raum werden berechnet
    ChanceFloor = 100; //static_cast<int>((static_cast<float>(chanceFloor) / static_cast<float> (chanceFloor + chanceRoom)) * 100.0f);
    ChanceRoom = 0; //static_cast<int>((static_cast<float>(chanceRoom) / static_cast<float> (chanceFloor + chanceRoom)) * 100.0f);
    // Setzt die aussenmauern als Besucht
    Set_OuterWalls();
    en_Direction Direction = DIR_FAULT;
    // Erste zufalls Zelle ermitteln auf der eine X Kreuzung erstellt werden kann
    do
    {
        CurrentCell.X = Dice::Dice_Roll(Dice::ANY,X_DungeonSize-4) + 1;
        CurrentCell.Y = Dice::Dice_Roll(Dice::ANY,Y_DungeonSize-4) + 1;
    }
    while(!Set_StartPoint(CurrentCell));
    int FailCounter = 0;
    do
    {
        CurrentCell = OpenEndsList.front();
        Direction = Get_Direction(CurrentCell);
        if (Direction == DIR_FAULT)
        {
            std::cout << "Force new Direction bei: " << CurrentCell.X << " " << CurrentCell.Y << std::endl;
            ForceNewDirection(CurrentCell);
            OpenEndsList.pop_front();
        }
        else
        {
            switch (Select_DungeonPart())
            {
                case DP_ROOM:
                    // Nicht erfolgreich FailCounter erhöhen
                    if(!Set_Room(CurrentCell,Direction))
                    {
                        if(FailCounter > 10)
                        {
                            OpenEndsList.pop_front();
                            FailCounter = 0;
                        }
                        else
                        {
                            FailCounter++;
                        }
                    }
                    else
                    {
                        FailCounter = 0;
                        OpenEndsList.pop_front();
                    }
                break;
                case DP_FLOOR:
                    // Nicht erfolgreich FailCounter erhöhen
                    if(!Set_Floor(CurrentCell,Direction))
                    {
                        if(FailCounter > 10)
                        {
                            OpenEndsList.pop_front();
                            FailCounter = 0;
                        }
                        else
                        {
                            FailCounter++;
                        }
                    }
                    else
                    {
                        FailCounter = 0;
                        OpenEndsList.pop_front();
                    }
                break;
                case DP_XCROSS:
                    // Nicht erfolgreich FailCounter erhöhen
                    if(!Set_XCrossWay(CurrentCell,Direction))
                    {
                        if(FailCounter > 10)
                        {
                            OpenEndsList.pop_front();
                            FailCounter = 0;
                        }
                        else
                        {
                            FailCounter++;
                        }
                    }
                    else
                    {
                        FailCounter = 0;
                        OpenEndsList.pop_front();
                    }
                break;
                case DP_TCROSS:
                    // Nicht erfolgreich FailCounter erhöhen
                    if(!Set_TCrossWay(CurrentCell,Direction))
                    {
                        if(FailCounter > 10)
                        {
                            OpenEndsList.pop_front();
                            FailCounter = 0;
                        }
                        else
                        {
                            FailCounter++;
                        }
                    }
                    else
                    {
                        FailCounter = 0;
                        OpenEndsList.pop_front();
                    }
                break;
                case DP_LEFTWAY:
                    // Nicht erfolgreich FailCounter erhöhen
                    if(!Set_LeftWay(CurrentCell,Direction))
                    {
                        if(FailCounter > 10)
                        {
                            OpenEndsList.pop_front();
                            FailCounter = 0;
                        }
                        else
                        {
                            FailCounter++;
                        }
                    }
                    else
                    {
                        FailCounter = 0;
                        OpenEndsList.pop_front();
                    }
                break;
                case DP_RIGHTWAY:
                    // Nicht erfolgreich FailCounter erhöhen
                    if(!Set_RightWay(CurrentCell,Direction))
                    {
                        if(FailCounter > 10)
                        {
                            OpenEndsList.pop_front();
                            FailCounter = 0;
                        }
                        else
                        {
                            FailCounter++;
                        }
                    }
                    else
                    {
                        FailCounter = 0;
                        OpenEndsList.pop_front();
                    }
                break;
                case DP_DEADEND:
                    //Dungeon[CurrentCell.X][CurrentCell.Y].Dungeon_Layer2
                    OpenEndsList.pop_front();
                break;
                case DP_FAIL:
                    std::cout << "Fail" << std::endl;
                break;
            }
            //OpenEndsList.pop_front();
        }
    }
    while (!OpenEndsList.empty());
    std::cout << CellInUse << " von " << MaxCells << " Benutzt." << std::endl;
}
void CDungeonGenerator::Create_Dungeon(int X_DungeonSize,int Y_DungeonSize)
{
    // Eventuellen alten Dungeon löschen
    if(Dungeon)
    {
        for(int i = 0;i<DungeonSize_X;i++)
        {
            delete[] Dungeon[i];
        }
        delete[] Dungeon;
        Dungeon = 0;
    }
    // neues Spielfeld
    Dungeon = new St_DungeonTile*[X_DungeonSize];
    for(int i = 0;i < X_DungeonSize;i++)
    {
        Dungeon[i] = new St_DungeonTile[Y_DungeonSize];
    }
    // Füllen mit Boden und Wand
    for(int i = 0;i < X_DungeonSize;i++)
    {
        for(int j = 0;j < Y_DungeonSize;j++)
        {
            Dungeon[i][j].Dungeon_Layer1 = DT_FLOOR;
            Dungeon[i][j].Dungeon_Layer2 = DT_WALL;
            Dungeon[i][j].Dungeon_Layer3 = DT_NOTHING;
            Dungeon[i][j].Visited = false;
        }
    }
}
bool CDungeonGenerator::ForceNewDirection(St_Coords Coords)
{
    en_Direction ComeFrom = DIR_FAULT;
    en_Direction toCenter[2] = {DIR_FAULT,DIR_FAULT};
    // Übrig gebliebene Offene Enden auf jetzt geraden stücken können gelöscht werden
    if ((Dungeon[Coords.X][Coords.Y+1].Dungeon_Layer2 == DT_NOTHING &&
        Dungeon[Coords.X][Coords.Y-1].Dungeon_Layer2 == DT_NOTHING) ||
        (Dungeon[Coords.X - 1][Coords.Y].Dungeon_Layer2 == DT_NOTHING &&
        Dungeon[Coords.X + 1][Coords.Y].Dungeon_Layer2 == DT_NOTHING))
    {
        std::cout << "Bereinigt" << std::endl;
        return false;
    }
    // feststellen von man kommt
    else if(Dungeon[Coords.X][Coords.Y+1].Dungeon_Layer2 == DT_NOTHING)
    {
        ComeFrom = DIR_SOUTH;
        std::cout << "Kamm von Süden" << std::endl;
    }
    else if (Dungeon[Coords.X][Coords.Y-1].Dungeon_Layer2 == DT_NOTHING)
    {
        ComeFrom = DIR_NORTH;
        std::cout << "Kamm von Norden" << std::endl;
    }
    else if (Dungeon[Coords.X + 1][Coords.Y].Dungeon_Layer2 == DT_NOTHING)
    {
        ComeFrom = DIR_EAST;
        std::cout << "Kamm von Osten" << std::endl;
    }
    else if (Dungeon[Coords.X - 1][Coords.Y].Dungeon_Layer2 == DT_NOTHING)
    {
        ComeFrom = DIR_WEST;
        std::cout << "Kamm von Westen" << std::endl;
    }
    if (Coords.X - 2 > 0 && Coords.X + 2 < DungeonSize_X &&
        Coords.Y - 2 > 0 && Coords.Y + 2 < DungeonSize_Y &&
        Dungeon[Coords.X][Coords.Y+2].Visited == true &&
        Dungeon[Coords.X][Coords.Y-2].Visited == true &&
        Dungeon[Coords.X - 2][Coords.Y].Visited == true &&
        Dungeon[Coords.X + 2][Coords.Y].Visited == true )
    {
        std::cout << "nichts zu machen hier" << std::endl;
        return false;
    }
    int Center_X = DungeonSize_X / 2;
    int Center_Y = DungeonSize_Y / 2;
    // Überprüfen in welcher Richtung das Zentrum des Levels liegt
    if(Center_X - Coords.X < 0)
    {
        toCenter[0] = DIR_WEST;
    }
    else if (Center_X - Coords.X > 0)
    {
        toCenter[0] = DIR_EAST;
    }
    if(Center_Y - Coords.Y < 0)
    {
        toCenter[1] = DIR_SOUTH;
    }
    else if (Center_Y - Coords.Y > 0)
    {
        toCenter[1] = DIR_NORTH;
    }
    if(toCenter[0] == DIR_EAST && toCenter[1] == DIR_NORTH)
    {
        if(Dungeon[Coords.X + 1][Coords.Y+0].Visited == true &&
           Dungeon[Coords.X + 2][Coords.Y+0].Visited == true &&
           Dungeon[Coords.X + 3][Coords.Y+0].Visited == true &&
           Dungeon[Coords.X + 3][Coords.Y+1].Visited == true)
        {
            return false;
        }
        else
        {
            Dungeon[Coords.X + 3][Coords.Y+1].Visited = true;
            Dungeon[Coords.X + 3][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
            Dungeon[Coords.X + 3][Coords.Y+1].Dungeon_Layer2 = DT_DOOR;
            Dungeon[Coords.X + 3][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
        }

    }
    else if(toCenter[0] == DIR_EAST && toCenter[1] == DIR_SOUTH)
    {
        if(Dungeon[Coords.X + 1][Coords.Y+0].Visited == true &&
           Dungeon[Coords.X + 2][Coords.Y+0].Visited == true &&
           Dungeon[Coords.X + 3][Coords.Y-0].Visited == true &&
           Dungeon[Coords.X + 3][Coords.Y-1].Visited == true )
        {
            return false;
        }
        else
        {
            Dungeon[Coords.X + 3][Coords.Y-1].Visited = true;
            Dungeon[Coords.X + 3][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
            Dungeon[Coords.X + 3][Coords.Y-1].Dungeon_Layer2 = DT_DOOR;
            Dungeon[Coords.X + 3][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
        }
    }
    else if(toCenter[0] == DIR_WEST && toCenter[1] == DIR_NORTH)
    {
        if(Dungeon[Coords.X - 1][Coords.Y+0].Visited == true &&
           Dungeon[Coords.X - 2][Coords.Y+0].Visited == true &&
           Dungeon[Coords.X - 3][Coords.Y+0].Visited == true &&
           Dungeon[Coords.X - 3][Coords.Y+1].Visited == true )
        {
            return false;
        }
        else
        {
            Dungeon[Coords.X - 3][Coords.Y+1].Visited = true;
            Dungeon[Coords.X - 3][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
            Dungeon[Coords.X - 3][Coords.Y+1].Dungeon_Layer2 = DT_DOOR;
            Dungeon[Coords.X - 3][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
        }
    }
    else if(toCenter[0] == DIR_WEST && toCenter[1] == DIR_SOUTH)
    {
        if(Dungeon[Coords.X - 1][Coords.Y+0].Visited == true &&
           Dungeon[Coords.X - 2][Coords.Y+0].Visited == true &&
           Dungeon[Coords.X - 3][Coords.Y-0].Visited == true &&
           Dungeon[Coords.X - 3][Coords.Y-1].Visited == true )
        {
            return false;
        }
        else
        {
            Dungeon[Coords.X - 3][Coords.Y-1].Visited = true;
            Dungeon[Coords.X - 3][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
            Dungeon[Coords.X - 3][Coords.Y-1].Dungeon_Layer2 = DT_DOOR;
            Dungeon[Coords.X - 3][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
        }
    }
    else if(toCenter[0] == DIR_FAULT && toCenter[1] != DIR_FAULT)
    {

    }
    else if(toCenter[0] != DIR_FAULT && toCenter[1] == DIR_FAULT)
    {

    }
    return false;
}
bool CDungeonGenerator::Set_Room(St_Coords Coords,en_Direction direction)
{
    int RoomSize_X = Dice::Dice_Roll(Dice::ANY,MaxRoomSize_X-4) + 4;
    int RoomSize_Y = Dice::Dice_Roll(Dice::ANY,MaxRoomSize_Y-4) + 4;
    bool newTry = false;
    switch(direction)
    {
        // North
        case DIR_NORTH:
            // for schleife um Raum auf der X-Achse zu verschieben
            for (int k = Coords.X - RoomSize_X + 2;k < Coords.X;k++)
            {
                // überprüfen ob Raum innerhalb des Dungeons liegt
                if(k + RoomSize_X > DungeonSize_X - 1 || k < 1 || Coords.Y - RoomSize_Y < 1)
                {
                    return false;
                }
                // NewTry reseten
                if(newTry)
                {
                    newTry = false;
                }
                // for schleife für X Achse
                for(int i = 0;i<RoomSize_X;i++)
                {
                    // for schleife für Y Achse
                    for(int j = 0;j<RoomSize_Y;j++)
                    {
                        // Überprüfen ob Teil schon besetzt ist
                        if(Dungeon[k+i][Coords.Y - RoomSize_Y + j].Visited == true)
                        {
                            newTry = true;
                        }
                        // Besetzt for schleife Verlassen
                        if(newTry)
                        {
                            break;
                        }
                    }
                    // Besetzt for schleife Verlassen
                    if(newTry)
                    {
                        break;
                    }
                }
                // Wenn die for schleife durchlaufen wurde ohne das newTry = true ist
                // wird der Raum erschaffen
                if(newTry == false)
                {
                    for(int i = 0;i<RoomSize_X;i++)
                    {
                        for(int j = 0;j<RoomSize_Y;j++)
                        {
                            Dungeon[k+i][Coords.Y - RoomSize_Y + j].Visited = true;
                            // Die Koordinate direkt über dem Startpunkt frei halten
                            if(k+i == Coords.X && Coords.Y - RoomSize_Y + j == Coords.Y - 1)
                            {
                                Dungeon[k+i][Coords.Y - RoomSize_Y + j].Dungeon_Layer1 = DT_ROOM;
                                Dungeon[k+i][Coords.Y - RoomSize_Y + j].Dungeon_Layer2 = DT_NOTHING;
                                Dungeon[k+i][Coords.Y - RoomSize_Y + j].Dungeon_Layer3 = DT_NOTHING;
                                CellInUse++;
                            }
                            // alle Kanten als Mauer
                            else if (i == 0 || j == 0 || i == RoomSize_X-1 || j == RoomSize_Y-1)
                            {
                                Dungeon[k+i][Coords.Y - RoomSize_Y + j].Dungeon_Layer1 = DT_ROOM;
                                Dungeon[k+i][Coords.Y - RoomSize_Y + j].Dungeon_Layer2 = DT_WALL;
                                Dungeon[k+i][Coords.Y - RoomSize_Y + j].Dungeon_Layer3 = DT_NOTHING;
                                CellInUse++;
                            }
                            // rest als Floor
                            else
                            {
                                Dungeon[k+i][Coords.Y - RoomSize_Y + j].Dungeon_Layer1 = DT_ROOM;
                                Dungeon[k+i][Coords.Y - RoomSize_Y + j].Dungeon_Layer2 = DT_NOTHING;
                                Dungeon[k+i][Coords.Y - RoomSize_Y + j].Dungeon_Layer3 = DT_NOTHING;
                                CellInUse++;
                            }
                        }
                    }
                    return true;
                }
            }
        return false;
        break;
        // Süden
        case DIR_SOUTH:
            // for schleife um Raum auf der X-Achse zu verschieben
            for (int k = Coords.X - RoomSize_X + 2;k < Coords.X;k++)
            {
                // überprüfen ob Raum innerhalb des Dungeons liegt
                if(k + RoomSize_X > DungeonSize_X - 1 || k < 1 || Coords.Y + RoomSize_Y > DungeonSize_Y - 1)
                {
                    return false;
                }
                // NewTry reseten
                if(newTry)
                {
                    newTry = false;
                }
                // for schleife für X Achse
                for(int i = 0;i<RoomSize_X;i++)
                {
                    // for schleife für Y Achse
                    for(int j = 1;j<RoomSize_Y+1;j++)
                    {
                        // Überprüfen ob Teil schon besetzt ist
                        if(Dungeon[k+i][Coords.Y + j].Visited == true)
                        {
                            newTry = true;
                        }
                        // Besetzt for schleife Verlassen
                        if(newTry)
                        {
                            break;
                        }
                    }
                    // Besetzt for schleife Verlassen
                    if(newTry)
                    {
                        break;
                    }
                }
                // Wenn die for schleife durchlaufen wurde ohne das newTry = true ist
                // wird der Raum erschaffen
                if(newTry == false)
                {
                    for(int i = 0;i<RoomSize_X;i++)
                    {
                        for(int j = 1;j<RoomSize_Y+1;j++)
                        {
                            Dungeon[k+i][Coords.Y + j].Visited = true;
                            // Die Koordinate direkt über dem Startpunkt frei halten
                            if(k+i == Coords.X && Coords.Y + j == Coords.Y + 1)
                            {
                                Dungeon[k+i][Coords.Y + j].Dungeon_Layer1 = DT_ROOM;
                                Dungeon[k+i][Coords.Y + j].Dungeon_Layer2 = DT_NOTHING;
                                Dungeon[k+i][Coords.Y + j].Dungeon_Layer3 = DT_NOTHING;
                                CellInUse++;
                            }
                            // alle Kanten als Mauer
                            else if (i == 0 || j == 1 || i == RoomSize_X-1 || j == RoomSize_Y)
                            {
                                Dungeon[k+i][Coords.Y + j].Dungeon_Layer1 = DT_ROOM;
                                Dungeon[k+i][Coords.Y + j].Dungeon_Layer2 = DT_WALL;
                                Dungeon[k+i][Coords.Y + j].Dungeon_Layer3 = DT_NOTHING;
                                CellInUse++;
                            }
                            // rest als Floor
                            else
                            {
                                Dungeon[k+i][Coords.Y + j].Dungeon_Layer1 = DT_ROOM;
                                Dungeon[k+i][Coords.Y + j].Dungeon_Layer2 = DT_NOTHING;
                                Dungeon[k+i][Coords.Y + j].Dungeon_Layer3 = DT_NOTHING;
                                CellInUse++;
                            }
                        }
                    }
                    return true;
                }
            }
        return false;
        break;
        // West
        case DIR_WEST:
            // for schleife um Raum auf der Y-Achse zu verschieben
            for (int k = Coords.Y - RoomSize_Y + 2;k < Coords.Y;k++)
            {
                // überprüfen ob Raum innerhalb des Dungeons liegt
                if(k + RoomSize_Y > DungeonSize_Y - 1 || k < 1 || Coords.X - RoomSize_X < 1)
                {
                    return false;
                }
                // NewTry reseten
                if(newTry)
                {
                    newTry = false;
                }
                // for schleife für X Achse
                for(int i = 0;i<RoomSize_X;i++)
                {
                    // for schleife für Y Achse
                    for(int j = 0;j<RoomSize_Y;j++)
                    {
                        // Überprüfen ob Teil schon besetzt ist
                        if(Dungeon[Coords.X - RoomSize_X + i][k + j].Visited == true)
                        {
                            newTry = true;
                        }
                        // Besetzt for schleife Verlassen
                        if(newTry)
                        {
                            break;
                        }
                    }
                    // Besetzt for schleife Verlassen
                    if(newTry)
                    {
                        break;
                    }
                }
                // Wenn die for schleife durchlaufen wurde ohne das newTry = true ist
                // wird der Raum erschaffen
                if(newTry == false)
                {
                    for(int i = 0;i<RoomSize_X;i++)
                    {
                        for(int j = 0;j<RoomSize_Y;j++)
                        {
                            Dungeon[Coords.X - RoomSize_X + i][k + j].Visited = true;
                            // Die Koordinate direkt über dem Startpunkt frei halten
                            if(k+j == Coords.Y && Coords.X - RoomSize_X + i == Coords.X - 1)
                            {
                                Dungeon[Coords.X - RoomSize_X + i][k + j].Dungeon_Layer1 = DT_ROOM;
                                Dungeon[Coords.X - RoomSize_X + i][k + j].Dungeon_Layer2 = DT_NOTHING;
                                Dungeon[Coords.X - RoomSize_X + i][k + j].Dungeon_Layer3 = DT_NOTHING;
                                CellInUse++;
                            }
                            // alle Kanten als Mauer
                            else if (i == 0 || j == 0 || i == RoomSize_X-1 || j == RoomSize_Y-1)
                            {
                                Dungeon[Coords.X - RoomSize_X + i][k + j].Dungeon_Layer1 = DT_ROOM;
                                Dungeon[Coords.X - RoomSize_X + i][k + j].Dungeon_Layer2 = DT_WALL;
                                Dungeon[Coords.X - RoomSize_X + i][k + j].Dungeon_Layer3 = DT_NOTHING;
                                CellInUse++;
                            }
                            // rest als Floor
                            else
                            {
                                Dungeon[Coords.X - RoomSize_X + i][k + j].Dungeon_Layer1 = DT_ROOM;
                                Dungeon[Coords.X - RoomSize_X + i][k + j].Dungeon_Layer2 = DT_NOTHING;
                                Dungeon[Coords.X - RoomSize_X + i][k + j].Dungeon_Layer3 = DT_NOTHING;
                                CellInUse++;
                            }
                        }
                    }
                    return true;
                }
            }
        return false;
        break;
        // Ost
        case DIR_EAST:
            // for schleife um Raum auf der Y-Achse zu verschieben
            for (int k = Coords.Y - RoomSize_Y + 2;k < Coords.Y;k++)
            {
                // überprüfen ob Raum innerhalb des Dungeons liegt
                if(k + RoomSize_Y > DungeonSize_Y - 1 || k < 1 || Coords.X + RoomSize_X > DungeonSize_X - 1)
                {
                    return false;
                }
                // NewTry reseten
                if(newTry)
                {
                    newTry = false;
                }
                // for schleife für X Achse
                for(int i = 1;i<RoomSize_X+1;i++)
                {
                    // for schleife für Y Achse
                    for(int j = 0;j<RoomSize_Y;j++)
                    {
                        // Überprüfen ob Teil schon besetzt ist
                        if(Dungeon[Coords.X + i][k + j].Visited == true)
                        {
                            newTry = true;
                        }
                        // Besetzt for schleife Verlassen
                        if(newTry)
                        {
                            break;
                        }
                    }
                    // Besetzt for schleife Verlassen
                    if(newTry)
                    {
                        break;
                    }
                }
                // Wenn die for schleife durchlaufen wurde ohne das newTry = true ist
                // wird der Raum erschaffen
                if(newTry == false)
                {
                    for(int i = 1;i<RoomSize_X+1;i++)
                    {
                        for(int j = 0;j<RoomSize_Y;j++)
                        {
                            Dungeon[Coords.X + i][k + j].Visited = true;
                            // Die Koordinate direkt über dem Startpunkt frei halten
                            if(k+j == Coords.Y && Coords.X + i == Coords.X + 1)
                            {
                                Dungeon[Coords.X + i][k + j].Dungeon_Layer1 = DT_ROOM;
                                Dungeon[Coords.X + i][k + j].Dungeon_Layer2 = DT_NOTHING;
                                Dungeon[Coords.X + i][k + j].Dungeon_Layer3 = DT_NOTHING;
                                CellInUse++;
                            }
                            // alle Kanten als Mauer
                            else if (i == 1 || j == 0 || i == RoomSize_X || j == RoomSize_Y-1)
                            {
                                Dungeon[Coords.X + i][k + j].Dungeon_Layer1 = DT_ROOM;
                                Dungeon[Coords.X + i][k + j].Dungeon_Layer2 = DT_WALL;
                                Dungeon[Coords.X + i][k + j].Dungeon_Layer3 = DT_NOTHING;
                                CellInUse++;
                            }
                            // rest als Floor
                            else
                            {
                                Dungeon[Coords.X + i][k + j].Dungeon_Layer1 = DT_ROOM;
                                Dungeon[Coords.X + i][k + j].Dungeon_Layer2 = DT_NOTHING;
                                Dungeon[Coords.X + i][k + j].Dungeon_Layer3 = DT_NOTHING;
                                CellInUse++;
                            }
                        }
                    }
                    return true;
                }
            }
        return false;
        break;
        // Fail
        case DIR_FAULT:
            return false;
        break;
    }
    return false;
}
bool CDungeonGenerator::Set_TCrossWay(St_Coords Coords,en_Direction direction)
{
    switch(direction)
    {
        case DIR_NORTH:
            if(Coords.X - 1 < 1 || Coords.X + 1 > DungeonSize_X-1 || Coords.Y - 1 < 1 || Coords.Y - 2 < 1)
            {
                return false;
            }
            else if(Dungeon[Coords.X-1][Coords.Y-2].Visited == false && Dungeon[Coords.X][Coords.Y-2].Visited == false && Dungeon[Coords.X+1][Coords.Y-2].Visited == false &&
                    Dungeon[Coords.X-1][Coords.Y-1].Visited == false && Dungeon[Coords.X][Coords.Y-1].Visited == false && Dungeon[Coords.X+1][Coords.Y-1].Visited == false &&
                    Dungeon[Coords.X-1][Coords.Y-3].Visited == false && Dungeon[Coords.X][Coords.Y-3].Visited == false && Dungeon[Coords.X+1][Coords.Y-3].Visited == false)
            {
                // Teile auf besucht setzen
                Dungeon[Coords.X-1][Coords.Y-3].Visited = true;
                Dungeon[Coords.X][Coords.Y-3].Visited = true;
                Dungeon[Coords.X+1][Coords.Y-3].Visited = true;
                Dungeon[Coords.X-1][Coords.Y-2].Visited = true;
                Dungeon[Coords.X][Coords.Y-2].Visited = true;
                Dungeon[Coords.X+1][Coords.Y-2].Visited = true;
                Dungeon[Coords.X-1][Coords.Y-1].Visited = true;
                Dungeon[Coords.X][Coords.Y-1].Visited = true;
                Dungeon[Coords.X+1][Coords.Y-1].Visited = true;
                // Layer 1 setzen
                Dungeon[Coords.X-1][Coords.Y-3].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X][Coords.Y-3].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X+1][Coords.Y-3].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X-1][Coords.Y-2].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X][Coords.Y-2].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X+1][Coords.Y-2].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X-1][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X+1][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                // Layer 2 setzen
                Dungeon[Coords.X-1][Coords.Y-3].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X][Coords.Y-3].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X+1][Coords.Y-3].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X-1][Coords.Y-2].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X][Coords.Y-2].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y-2].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X-1][Coords.Y-1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X][Coords.Y-1].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y-1].Dungeon_Layer2 = DT_WALL;
                // Layer 3 setzen
                Dungeon[Coords.X-1][Coords.Y-3].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X][Coords.Y-3].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y-3].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X-1][Coords.Y-2].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X][Coords.Y-2].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y-2].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X-1][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                // die Offenen Enden der Liste OpenEndsList zufügen
                Coords.X = Coords.X - 1;
                Coords.Y = Coords.Y - 2;
                if(!Dungeon[Coords.X-1][Coords.Y].Dungeon_Layer2 == DT_NOTHING)
                {
                    OpenEndsList.push_back(Coords);
                }
                Coords.X = Coords.X + 2;
                if(!Dungeon[Coords.X+1][Coords.Y].Dungeon_Layer2 == DT_NOTHING)
                {
                    OpenEndsList.push_back(Coords);
                }
                CellInUse = CellInUse + 9;
                return true;
            }
            else
            {
                return false;
            }
        break;
        // Süden
        case DIR_SOUTH:
            if(Coords.X - 1 < 1 || Coords.X + 1 > DungeonSize_X-1 || Coords.Y + 1 > DungeonSize_Y-1 || Coords.Y + 2 > DungeonSize_Y-1)
            {
                return false;
            }
            else if(Dungeon[Coords.X-1][Coords.Y+2].Visited == false && Dungeon[Coords.X][Coords.Y+2].Visited == false && Dungeon[Coords.X+1][Coords.Y+2].Visited == false &&
                    Dungeon[Coords.X-1][Coords.Y+1].Visited == false && Dungeon[Coords.X][Coords.Y+1].Visited == false && Dungeon[Coords.X+1][Coords.Y+1].Visited == false &&
                    Dungeon[Coords.X-1][Coords.Y+3].Visited == false && Dungeon[Coords.X][Coords.Y+3].Visited == false && Dungeon[Coords.X+1][Coords.Y+3].Visited == false)
            {
                // Teile auf besucht setzen
                Dungeon[Coords.X-1][Coords.Y+3].Visited = true;
                Dungeon[Coords.X][Coords.Y+3].Visited = true;
                Dungeon[Coords.X+1][Coords.Y+3].Visited = true;
                Dungeon[Coords.X-1][Coords.Y+2].Visited = true;
                Dungeon[Coords.X][Coords.Y+2].Visited = true;
                Dungeon[Coords.X+1][Coords.Y+2].Visited = true;
                Dungeon[Coords.X-1][Coords.Y+1].Visited = true;
                Dungeon[Coords.X][Coords.Y+1].Visited = true;
                Dungeon[Coords.X+1][Coords.Y+1].Visited = true;
                // Layer 1 setzen
                Dungeon[Coords.X-1][Coords.Y+3].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X][Coords.Y+3].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X+1][Coords.Y+3].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X-1][Coords.Y+2].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X][Coords.Y+2].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X+1][Coords.Y+2].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X-1][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X+1][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                // Layer 2 setzen
                Dungeon[Coords.X-1][Coords.Y+3].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X][Coords.Y+3].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X+1][Coords.Y+3].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X-1][Coords.Y+2].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X][Coords.Y+2].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y+2].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X-1][Coords.Y+1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X][Coords.Y+1].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y+1].Dungeon_Layer2 = DT_WALL;
                // Layer 3 setzen
                Dungeon[Coords.X-1][Coords.Y+3].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X][Coords.Y+3].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y+3].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X-1][Coords.Y+2].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X][Coords.Y+2].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y+2].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X-1][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                // die Offenen Enden der Liste OpenEndsList zufügen
                Coords.X = Coords.X - 1;
                Coords.Y = Coords.Y + 2;
                if(!Dungeon[Coords.X-1][Coords.Y].Dungeon_Layer2 == DT_NOTHING)
                {
                    OpenEndsList.push_back(Coords);
                }
                Coords.X = Coords.X + 2;
                if(!Dungeon[Coords.X+1][Coords.Y].Dungeon_Layer2 == DT_NOTHING)
                {
                    OpenEndsList.push_back(Coords);
                }
                CellInUse = CellInUse + 9;
                return true;
            }
            else
            {
                return false;
            }
        break;
    // osten
        case DIR_EAST:
            if(Coords.X + 1 > DungeonSize_X - 1 || Coords.X + 2 > DungeonSize_X-1 || Coords.Y - 1 < 1 || Coords.Y + 1 > DungeonSize_Y - 1)
            {
                return false;
            }
            else if(Dungeon[Coords.X+1][Coords.Y+1].Visited == false && Dungeon[Coords.X + 2][Coords.Y+1].Visited == false && Dungeon[Coords.X + 3][Coords.Y+1].Visited == false &&
                    Dungeon[Coords.X+1][Coords.Y].Visited == false && Dungeon[Coords.X + 2][Coords.Y].Visited == false && Dungeon[Coords.X + 3][Coords.Y].Visited == false &&
                    Dungeon[Coords.X+1][Coords.Y-1].Visited == false && Dungeon[Coords.X + 2][Coords.Y-1].Visited == false && Dungeon[Coords.X + 3][Coords.Y-1].Visited == false)
            {
                // Teile auf besucht setzen
                Dungeon[Coords.X+1][Coords.Y+1].Visited = true;
                Dungeon[Coords.X + 2][Coords.Y+1].Visited = true;
                Dungeon[Coords.X + 3][Coords.Y+1].Visited = true;
                Dungeon[Coords.X+1][Coords.Y].Visited = true;
                Dungeon[Coords.X + 2][Coords.Y].Visited = true;
                Dungeon[Coords.X + 3][Coords.Y].Visited = true;
                Dungeon[Coords.X+1][Coords.Y-1].Visited = true;
                Dungeon[Coords.X + 2][Coords.Y-1].Visited = true;
                Dungeon[Coords.X + 3][Coords.Y-1].Visited = true;
                // Layer 1 setzen
                Dungeon[Coords.X+1][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X + 2][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X + 3][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X+1][Coords.Y].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X + 2][Coords.Y].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X + 3][Coords.Y].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X+1][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X + 2][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X + 3][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                // Layer 2 setzen
                Dungeon[Coords.X+1][Coords.Y+1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X + 2][Coords.Y+1].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X + 3][Coords.Y+1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X+1][Coords.Y].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X + 2][Coords.Y].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X + 3][Coords.Y].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X+1][Coords.Y-1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X + 2][Coords.Y-1].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X + 3][Coords.Y-1].Dungeon_Layer2 = DT_WALL;
                // Layer 3 setzen
                Dungeon[Coords.X+1][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X + 2][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X + 3][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X + 2][Coords.Y].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X + 3][Coords.Y].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X + 2][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X + 3][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                // die Offenen Enden der Liste OpenEndsList zufügen
                Coords.X = Coords.X + 2;
                Coords.Y = Coords.Y + 1;
                if(!Dungeon[Coords.X][Coords.Y+1].Dungeon_Layer2 == DT_NOTHING)
                {
                    OpenEndsList.push_back(Coords);
                }
                Coords.Y = Coords.Y - 2;
                if(!Dungeon[Coords.X][Coords.Y-1].Dungeon_Layer2 == DT_NOTHING)
                {
                    OpenEndsList.push_back(Coords);
                }
                CellInUse = CellInUse + 9;
                return true;
            }
            else
            {
                return false;
            }
        break;
        // westen
        case DIR_WEST:
            if(Coords.X - 1 <  1 || Coords.X - 2 < 1 || Coords.Y - 1 < 1 || Coords.Y + 1 > DungeonSize_Y - 1)
            {
                return false;
            }
            else if(Dungeon[Coords.X-1][Coords.Y+1].Visited == false && Dungeon[Coords.X - 2][Coords.Y+1].Visited == false && Dungeon[Coords.X - 3][Coords.Y+1].Visited == false &&
                    Dungeon[Coords.X-1][Coords.Y].Visited == false && Dungeon[Coords.X - 2][Coords.Y].Visited == false && Dungeon[Coords.X - 3][Coords.Y].Visited == false &&
                    Dungeon[Coords.X-1][Coords.Y-1].Visited == false && Dungeon[Coords.X - 2][Coords.Y-1].Visited == false && Dungeon[Coords.X - 3][Coords.Y-1].Visited == false)
            {
                // Teile auf besucht setzen
                Dungeon[Coords.X - 1][Coords.Y + 1].Visited = true;
                Dungeon[Coords.X - 2][Coords.Y + 1].Visited = true;
                Dungeon[Coords.X - 3][Coords.Y + 1].Visited = true;
                Dungeon[Coords.X - 1][Coords.Y].Visited = true;
                Dungeon[Coords.X - 2][Coords.Y].Visited = true;
                Dungeon[Coords.X - 3][Coords.Y].Visited = true;
                Dungeon[Coords.X - 1][Coords.Y - 1].Visited = true;
                Dungeon[Coords.X - 2][Coords.Y - 1].Visited = true;
                Dungeon[Coords.X - 3][Coords.Y - 1].Visited = true;
                // Layer 1 setzen
                Dungeon[Coords.X-1][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X - 2][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X - 3][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X-1][Coords.Y].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X - 2][Coords.Y].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X - 3][Coords.Y].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X-1][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X + 2][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X + 3][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                // Layer 2 setzen
                Dungeon[Coords.X-1][Coords.Y+1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X - 2][Coords.Y+1].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X - 3][Coords.Y+1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X-1][Coords.Y].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X - 2][Coords.Y].Dungeon_Layer2 =DT_NOTHING;
                Dungeon[Coords.X - 3][Coords.Y].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X-1][Coords.Y-1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X - 2][Coords.Y-1].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X - 3][Coords.Y-1].Dungeon_Layer2 = DT_WALL;
                // Layer 3 setzen
                Dungeon[Coords.X-1][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X - 2][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X - 3][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X-1][Coords.Y].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X - 2][Coords.Y].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X - 3][Coords.Y].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X-1][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X - 2][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X - 3][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                // die Offenen Enden der Liste OpenEndsList zufügen
                Coords.X = Coords.X - 2;
                Coords.Y = Coords.Y - 1;
                if(!Dungeon[Coords.X][Coords.Y-1].Dungeon_Layer2 == DT_NOTHING)
                {
                    OpenEndsList.push_back(Coords);
                }
                Coords.Y = Coords.Y + 2;
                if(!Dungeon[Coords.X][Coords.Y+1].Dungeon_Layer2 == DT_NOTHING)
                {
                    OpenEndsList.push_back(Coords);
                }
                CellInUse = CellInUse + 9;
                return true;
            }
            else
            {
                return false;
            }
        break;
        case DIR_FAULT:
            return false;
        break;
    }
    return false;
}
bool CDungeonGenerator::Set_XCrossWay(St_Coords Coords,en_Direction direction)
{
    switch(direction)
    {
        case DIR_NORTH:
            if(Coords.X - 1 < 1 || Coords.X + 1 > DungeonSize_X-1 || Coords.Y - 1 < 1 || Coords.Y - 2 < 1)
            {
                return false;
            }
            else if(Dungeon[Coords.X-1][Coords.Y-3].Visited == false && Dungeon[Coords.X][Coords.Y-3].Visited == false && Dungeon[Coords.X+1][Coords.Y-3].Visited == false &&
                    Dungeon[Coords.X-1][Coords.Y-2].Visited == false && Dungeon[Coords.X][Coords.Y-2].Visited == false && Dungeon[Coords.X+1][Coords.Y-2].Visited == false &&
                    Dungeon[Coords.X-1][Coords.Y-1].Visited == false && Dungeon[Coords.X][Coords.Y-1].Visited == false && Dungeon[Coords.X+1][Coords.Y-1].Visited == false)
            {
                // Teile auf besucht setzen
                Dungeon[Coords.X-1][Coords.Y-3].Visited = true;
                Dungeon[Coords.X][Coords.Y-3].Visited = true;
                Dungeon[Coords.X+1][Coords.Y-3].Visited = true;
                Dungeon[Coords.X-1][Coords.Y-2].Visited = true;
                Dungeon[Coords.X][Coords.Y-2].Visited = true;
                Dungeon[Coords.X+1][Coords.Y-2].Visited = true;
                Dungeon[Coords.X-1][Coords.Y-1].Visited = true;
                Dungeon[Coords.X][Coords.Y-1].Visited = true;
                Dungeon[Coords.X+1][Coords.Y-1].Visited = true;
                // Layer 1 setzen
                Dungeon[Coords.X-1][Coords.Y-3].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X][Coords.Y-3].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X+1][Coords.Y-3].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X-1][Coords.Y-2].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X][Coords.Y-2].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X+1][Coords.Y-2].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X-1][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X+1][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                // Layer 2 setzen
                Dungeon[Coords.X-1][Coords.Y-3].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X][Coords.Y-3].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y-3].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X-1][Coords.Y-2].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X][Coords.Y-2].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y-2].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X-1][Coords.Y-1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X][Coords.Y-1].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y-1].Dungeon_Layer2 = DT_WALL;
                // Layer 3 setzen
                Dungeon[Coords.X-1][Coords.Y-3].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X][Coords.Y-3].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y-3].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X-1][Coords.Y-2].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X][Coords.Y-2].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y-2].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X-1][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                // die Offenen Enden der Liste OpenEndsList zufügen
                Coords.X = Coords.X - 1;
                Coords.Y = Coords.Y - 2;
                if(!Dungeon[Coords.X-1][Coords.Y].Dungeon_Layer2 == DT_NOTHING)
                {
                    OpenEndsList.push_back(Coords);
                }
                Coords.X = Coords.X + 2;
                if(!Dungeon[Coords.X+1][Coords.Y].Dungeon_Layer2 == DT_NOTHING)
                {
                    OpenEndsList.push_back(Coords);
                }
                Coords.X = Coords.X - 1;
                Coords.Y = Coords.Y - 1;
                if(!Dungeon[Coords.X][Coords.Y-1].Dungeon_Layer2 == DT_NOTHING)
                {
                    OpenEndsList.push_back(Coords);
                }
                CellInUse = CellInUse + 9;
                return true;
            }
            else
            {
                return false;
            }
        break;
        // Süden
        case DIR_SOUTH:
            if(Coords.X - 1 < 1 || Coords.X + 1 > DungeonSize_X-1 || Coords.Y + 1 > DungeonSize_Y-1 || Coords.Y + 2 > DungeonSize_Y-1)
            {
                return false;
            }
            else if(Dungeon[Coords.X-1][Coords.Y+3].Visited == false && Dungeon[Coords.X][Coords.Y+3].Visited == false && Dungeon[Coords.X+1][Coords.Y+3].Visited == false &&
                    Dungeon[Coords.X-1][Coords.Y+2].Visited == false && Dungeon[Coords.X][Coords.Y+2].Visited == false && Dungeon[Coords.X+1][Coords.Y+2].Visited == false &&
                    Dungeon[Coords.X-1][Coords.Y+1].Visited == false && Dungeon[Coords.X][Coords.Y+1].Visited == false && Dungeon[Coords.X+1][Coords.Y+1].Visited == false)
            {
                // Teile auf besucht setzen
                Dungeon[Coords.X-1][Coords.Y+3].Visited = true;
                Dungeon[Coords.X][Coords.Y+3].Visited = true;
                Dungeon[Coords.X+1][Coords.Y+3].Visited = true;
                Dungeon[Coords.X-1][Coords.Y+2].Visited = true;
                Dungeon[Coords.X][Coords.Y+2].Visited = true;
                Dungeon[Coords.X+1][Coords.Y+2].Visited = true;
                Dungeon[Coords.X-1][Coords.Y+1].Visited = true;
                Dungeon[Coords.X][Coords.Y+1].Visited = true;
                Dungeon[Coords.X+1][Coords.Y+1].Visited = true;
                // Layer 1 setzen
                Dungeon[Coords.X-1][Coords.Y+3].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X][Coords.Y+3].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X+1][Coords.Y+3].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X-1][Coords.Y+2].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X][Coords.Y+2].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X+1][Coords.Y+2].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X-1][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X+1][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                // Layer 2 setzen
                Dungeon[Coords.X-1][Coords.Y+3].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X][Coords.Y+3].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y+3].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X-1][Coords.Y+2].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X][Coords.Y+2].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y+2].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X-1][Coords.Y+1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X][Coords.Y+1].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y+1].Dungeon_Layer2 = DT_WALL;
                // Layer 3 setzen
                Dungeon[Coords.X-1][Coords.Y+3].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X][Coords.Y+3].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y+3].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X-1][Coords.Y+2].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X][Coords.Y+2].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y+2].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X-1][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                // die Offenen Enden der Liste OpenEndsList zufügen
                Coords.X = Coords.X - 1;
                Coords.Y = Coords.Y + 2;
                if(!Dungeon[Coords.X-1][Coords.Y].Dungeon_Layer2 == DT_NOTHING)
                {
                    OpenEndsList.push_back(Coords);
                }
                Coords.X = Coords.X + 2;
                if(!Dungeon[Coords.X+1][Coords.Y].Dungeon_Layer2 == DT_NOTHING)
                {
                    OpenEndsList.push_back(Coords);
                }
                Coords.X = Coords.X - 1;
                Coords.Y = Coords.Y + 1;
                if(!Dungeon[Coords.X+1][Coords.Y].Dungeon_Layer2 == DT_NOTHING)
                {
                    OpenEndsList.push_back(Coords);
                }
                CellInUse = CellInUse + 9;
                return true;
            }
            else
            {
                return false;
            }
        break;
    // osten
        case DIR_EAST:
            if(Coords.X + 1 > DungeonSize_X - 1 || Coords.X + 2 > DungeonSize_X-1 || Coords.Y - 1 < 1 || Coords.Y + 1 > DungeonSize_Y - 1)
            {
                return false;
            }
            else if(Dungeon[Coords.X+1][Coords.Y+1].Visited == false && Dungeon[Coords.X + 2][Coords.Y+1].Visited == false && Dungeon[Coords.X + 3][Coords.Y+1].Visited == false &&
                    Dungeon[Coords.X+1][Coords.Y].Visited == false && Dungeon[Coords.X + 2][Coords.Y].Visited == false && Dungeon[Coords.X + 3][Coords.Y].Visited == false &&
                    Dungeon[Coords.X+1][Coords.Y-1].Visited == false && Dungeon[Coords.X + 2][Coords.Y-1].Visited == false && Dungeon[Coords.X + 3][Coords.Y-1].Visited == false)
            {
                // Teile auf besucht setzen
                Dungeon[Coords.X+1][Coords.Y+1].Visited = true;
                Dungeon[Coords.X + 2][Coords.Y+1].Visited = true;
                Dungeon[Coords.X + 3][Coords.Y+1].Visited = true;
                Dungeon[Coords.X+1][Coords.Y].Visited = true;
                Dungeon[Coords.X + 2][Coords.Y].Visited = true;
                Dungeon[Coords.X + 3][Coords.Y].Visited = true;
                Dungeon[Coords.X+1][Coords.Y-1].Visited = true;
                Dungeon[Coords.X + 2][Coords.Y-1].Visited = true;
                Dungeon[Coords.X + 3][Coords.Y-1].Visited = true;
                // Layer 1 setzen
                Dungeon[Coords.X+1][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X + 2][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X + 3][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X+1][Coords.Y].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X + 2][Coords.Y].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X + 3][Coords.Y].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X+1][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X + 2][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X + 3][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                // Layer 2 setzen
                Dungeon[Coords.X+1][Coords.Y+1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X + 2][Coords.Y+1].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X + 3][Coords.Y+1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X+1][Coords.Y].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X + 2][Coords.Y].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X + 3][Coords.Y].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y-1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X + 2][Coords.Y-1].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X + 3][Coords.Y-1].Dungeon_Layer2 = DT_WALL;
                // Layer 3 setzen
                Dungeon[Coords.X+1][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X + 2][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X + 3][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X + 2][Coords.Y].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X + 3][Coords.Y].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X + 2][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X + 3][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                // die Offenen Enden der Liste OpenEndsList zufügen
                Coords.X = Coords.X + 2;
                Coords.Y = Coords.Y + 1;
                if(!Dungeon[Coords.X][Coords.Y+1].Dungeon_Layer2 == DT_NOTHING)
                {
                    OpenEndsList.push_back(Coords);
                }
                Coords.Y = Coords.Y - 2;
                if(!Dungeon[Coords.X][Coords.Y-1].Dungeon_Layer2 == DT_NOTHING)
                {
                    OpenEndsList.push_back(Coords);
                }
                Coords.X = Coords.X + 1;
                Coords.Y = Coords.Y + 1;
                if(!Dungeon[Coords.X+1][Coords.Y].Dungeon_Layer2 == DT_NOTHING)
                {
                    OpenEndsList.push_back(Coords);
                }
                CellInUse = CellInUse + 9;
                return true;
            }
            else
            {
                return false;
            }
        break;
        // westen
        case DIR_WEST:
            if(Coords.X - 1 <  1 || Coords.X - 2 < 1 || Coords.Y - 1 < 1 || Coords.Y + 1 > DungeonSize_Y - 1)
            {
                return false;
            }
            else if(Dungeon[Coords.X-1][Coords.Y+1].Visited == false && Dungeon[Coords.X - 2][Coords.Y+1].Visited == false && Dungeon[Coords.X - 3][Coords.Y+1].Visited == false &&
                    Dungeon[Coords.X-1][Coords.Y].Visited == false && Dungeon[Coords.X - 2][Coords.Y].Visited == false && Dungeon[Coords.X - 3][Coords.Y].Visited == false &&
                    Dungeon[Coords.X-1][Coords.Y-1].Visited == false && Dungeon[Coords.X - 2][Coords.Y-1].Visited == false && Dungeon[Coords.X - 3][Coords.Y-1].Visited == false)
            {
                // Teile auf besucht setzen
                Dungeon[Coords.X-1][Coords.Y+1].Visited = true;
                Dungeon[Coords.X - 2][Coords.Y+1].Visited = true;
                Dungeon[Coords.X - 3][Coords.Y+1].Visited = true;
                Dungeon[Coords.X-1][Coords.Y].Visited = true;
                Dungeon[Coords.X - 2][Coords.Y].Visited = true;
                Dungeon[Coords.X - 3][Coords.Y].Visited = true;
                Dungeon[Coords.X-1][Coords.Y-1].Visited = true;
                Dungeon[Coords.X - 2][Coords.Y-1].Visited = true;
                Dungeon[Coords.X - 3][Coords.Y-1].Visited = true;
                // Layer 1 setzen
                Dungeon[Coords.X-1][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X - 2][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X - 3][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X-1][Coords.Y].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X - 2][Coords.Y].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X - 3][Coords.Y].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X-1][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X + 2][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X + 3][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                // Layer 2 setzen
                Dungeon[Coords.X-1][Coords.Y+1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X - 2][Coords.Y+1].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X - 3][Coords.Y+1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X-1][Coords.Y].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X - 2][Coords.Y].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X - 3][Coords.Y].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X-1][Coords.Y-1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X - 2][Coords.Y-1].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X - 3][Coords.Y-1].Dungeon_Layer2 = DT_WALL;
                // Layer 3 setzen
                Dungeon[Coords.X-1][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X - 2][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X - 3][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X-1][Coords.Y].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X - 2][Coords.Y].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X - 3][Coords.Y].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X-1][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X - 2][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X - 3][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                // die Offenen Enden der Liste OpenEndsList zufügen
                Coords.X = Coords.X - 2;
                Coords.Y = Coords.Y - 1;
                if(!Dungeon[Coords.X][Coords.Y-1].Dungeon_Layer2 == DT_NOTHING)
                {
                    OpenEndsList.push_back(Coords);
                }
                Coords.Y = Coords.Y + 2;
                if(!Dungeon[Coords.X][Coords.Y+1].Dungeon_Layer2 == DT_NOTHING)
                {
                    OpenEndsList.push_back(Coords);
                }
                Coords.X = Coords.X - 1;
                Coords.Y = Coords.Y - 1;
                if(!Dungeon[Coords.X-1][Coords.Y].Dungeon_Layer2 == DT_NOTHING)
                {
                    OpenEndsList.push_back(Coords);
                }
                CellInUse = CellInUse + 9;
                return true;
            }
            else
            {
                return false;
            }
        break;
        case DIR_FAULT:
            return false;
        break;
    }
    return false;
}
bool CDungeonGenerator::Set_Floor(St_Coords Coords,en_Direction direction)
{
    int HowLongPossible = 0;
    St_Coords StartCoords = Coords;
    bool End = false;
    switch (direction)
    {
        // North
        case DIR_NORTH:
            while(!End)
            {
                Coords.Y = Coords.Y - 1;
                if(Dungeon[Coords.X-1][Coords.Y].Visited == false && Dungeon[Coords.X][Coords.Y].Visited == false && Dungeon[Coords.X + 1][Coords.Y].Visited == false)
                {
                    HowLongPossible++;
                }
                else
                {
                    End = true;
                }
            }
        break;
        // South
        case DIR_SOUTH:
            while(!End)
            {
                Coords.Y = Coords.Y + 1;
                if(Dungeon[Coords.X-1][Coords.Y].Visited == false && Dungeon[Coords.X][Coords.Y].Visited == false && Dungeon[Coords.X + 1][Coords.Y].Visited == false)
                {
                    HowLongPossible++;
                }
                else
                {
                    End = true;
                }
            }
        break;
        // West
        case DIR_WEST:
            while(!End)
            {
                Coords.X = Coords.X - 1;
                if(Dungeon[Coords.X][Coords.Y-1].Visited == false &&
                   Dungeon[Coords.X][Coords.Y].Visited == false &&
                   Dungeon[Coords.X][Coords.Y+1].Visited == false)
                {
                    HowLongPossible++;
                }
                else
                {
                    End = true;
                }
            }
        break;
        // ost
        case DIR_EAST:
            while(!End)
            {
                Coords.X = Coords.X + 1;
                if(Dungeon[Coords.X][Coords.Y-1].Visited == false &&
                   Dungeon[Coords.X][Coords.Y].Visited == false &&
                   Dungeon[Coords.X][Coords.Y+1].Visited == false)
                {
                    HowLongPossible++;
                }
                else
                {
                    End = true;
                }
            }
        break;
        // Fehler
        case DIR_FAULT:
            return false;
        break;
    }
    if(HowLongPossible == 0)
    {
        return false;
    }
    int FloorLength = Dice::Dice_Roll(Dice::ANY,HowLongPossible);
    switch (direction)
    {
        // North
        case DIR_NORTH:
            for(int i = 1;i <= FloorLength;i++)
            {
                // als besucht Markieren
                Dungeon[StartCoords.X-1][StartCoords.Y - i].Visited = true;
                Dungeon[StartCoords.X][StartCoords.Y - i].Visited = true;
                Dungeon[StartCoords.X+1][StartCoords.Y - i].Visited = true;
                // Layer 1 setzen
                Dungeon[StartCoords.X-1][StartCoords.Y - i].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[StartCoords.X][StartCoords.Y - i].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[StartCoords.X+1][StartCoords.Y - i].Dungeon_Layer1 = DT_FLOOR;
                // Layer 2 setzen
                Dungeon[StartCoords.X-1][StartCoords.Y - i].Dungeon_Layer2 = DT_WALL;
                Dungeon[StartCoords.X][StartCoords.Y - i].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[StartCoords.X+1][StartCoords.Y - i].Dungeon_Layer2 = DT_WALL;
                // Layer 3 setzen
                Dungeon[StartCoords.X-1][StartCoords.Y - i].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[StartCoords.X][StartCoords.Y - i].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[StartCoords.X+1][StartCoords.Y - i].Dungeon_Layer3 = DT_NOTHING;
                CellInUse = CellInUse + 3;
            }
            Coords.X = StartCoords.X;
            Coords.Y = StartCoords.Y - FloorLength;
            OpenEndsList.push_back(Coords);
            return true;
        break;
        // South
        case DIR_SOUTH:
            for(int i = 1;i <= FloorLength;i++)
            {
                // als besucht Markieren
                Dungeon[StartCoords.X-1][StartCoords.Y + i].Visited = true;
                Dungeon[StartCoords.X][StartCoords.Y + i].Visited = true;
                Dungeon[StartCoords.X+1][StartCoords.Y + i].Visited = true;
                // Layer 1 setzen
                Dungeon[StartCoords.X-1][StartCoords.Y + i].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[StartCoords.X][StartCoords.Y + i].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[StartCoords.X+1][StartCoords.Y + i].Dungeon_Layer1 = DT_FLOOR;
                // Layer 2 setzen
                Dungeon[StartCoords.X-1][StartCoords.Y + i].Dungeon_Layer2 = DT_WALL;
                Dungeon[StartCoords.X][StartCoords.Y + i].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[StartCoords.X+1][StartCoords.Y + i].Dungeon_Layer2 = DT_WALL;
                // Layer 3 setzen
                Dungeon[StartCoords.X-1][StartCoords.Y + i].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[StartCoords.X][StartCoords.Y + i].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[StartCoords.X+1][StartCoords.Y + i].Dungeon_Layer3 = DT_NOTHING;
                CellInUse = CellInUse + 3;
            }
            Coords.X = StartCoords.X;
            Coords.Y = StartCoords.Y + FloorLength;
            OpenEndsList.push_back(Coords);
            return true;
        break;
        // West
        case DIR_WEST:
            for(int i = 1;i <= FloorLength;i++)
            {
                // als besucht Markieren
                Dungeon[StartCoords.X-i][StartCoords.Y - 1].Visited = true;
                Dungeon[StartCoords.X-i][StartCoords.Y].Visited = true;
                Dungeon[StartCoords.X-i][StartCoords.Y + 1].Visited = true;
                // Layer 1 setzen
                Dungeon[StartCoords.X-i][StartCoords.Y - 1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[StartCoords.X-i][StartCoords.Y].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[StartCoords.X-i][StartCoords.Y + 1].Dungeon_Layer1 = DT_FLOOR;
                // Layer 2 setzen
                Dungeon[StartCoords.X-i][StartCoords.Y - 1].Dungeon_Layer2 = DT_WALL;
                Dungeon[StartCoords.X-i][StartCoords.Y].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[StartCoords.X-i][StartCoords.Y + 1].Dungeon_Layer2 = DT_WALL;
                // Layer 3 setzen
                Dungeon[StartCoords.X-i][StartCoords.Y - 1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[StartCoords.X-i][StartCoords.Y].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[StartCoords.X-i][StartCoords.Y + 1].Dungeon_Layer3 = DT_NOTHING;
                CellInUse = CellInUse + 3;
            }
            Coords.X = StartCoords.X - FloorLength;
            Coords.Y = StartCoords.Y;
            OpenEndsList.push_back(Coords);
            return true;
        break;
        // ost
        case DIR_EAST:
            for(int i = 1;i <= FloorLength;i++)
            {
                // als besucht Markieren
                Dungeon[StartCoords.X+i][StartCoords.Y - 1].Visited = true;
                Dungeon[StartCoords.X+i][StartCoords.Y].Visited = true;
                Dungeon[StartCoords.X+i][StartCoords.Y + 1].Visited = true;
                // Layer 1 setzen
                Dungeon[StartCoords.X+i][StartCoords.Y - 1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[StartCoords.X+i][StartCoords.Y].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[StartCoords.X+i][StartCoords.Y + 1].Dungeon_Layer1 = DT_FLOOR;
                // Layer 2 setzen
                Dungeon[StartCoords.X+i][StartCoords.Y - 1].Dungeon_Layer2 = DT_WALL;
                Dungeon[StartCoords.X+i][StartCoords.Y].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[StartCoords.X+i][StartCoords.Y + 1].Dungeon_Layer2 = DT_WALL;
                // Layer 3 setzen
                Dungeon[StartCoords.X+i][StartCoords.Y - 1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[StartCoords.X+i][StartCoords.Y].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[StartCoords.X+i][StartCoords.Y + 1].Dungeon_Layer3 = DT_NOTHING;
                CellInUse = CellInUse + 3;
            }
            Coords.X = StartCoords.X + FloorLength;
            Coords.Y = StartCoords.Y;
            OpenEndsList.push_back(Coords);
            return true;
        break;
        // Fehler
        case DIR_FAULT:
            return false;
        break;
    }
    return false;
}
bool CDungeonGenerator::Set_RightWay(St_Coords Coords,en_Direction direction)
{
    switch(direction)
    {
        // Norden
        case DIR_NORTH:
            if(Coords.X - 1 < 1 || Coords.X + 1 > DungeonSize_X-1 || Coords.Y - 1 < 1 || Coords.Y - 2 < 1)
            {
                return false;
            }
            else if(Dungeon[Coords.X-1][Coords.Y-2].Visited == false && Dungeon[Coords.X][Coords.Y-3].Visited == false && Dungeon[Coords.X+1][Coords.Y-3].Visited == false &&
                    Dungeon[Coords.X-1][Coords.Y-2].Visited == false && Dungeon[Coords.X][Coords.Y-2].Visited == false && Dungeon[Coords.X+1][Coords.Y-2].Visited == false &&
                    Dungeon[Coords.X-1][Coords.Y-1].Visited == false && Dungeon[Coords.X][Coords.Y-1].Visited == false && Dungeon[Coords.X+1][Coords.Y-1].Visited == false)
            {
                // Teile auf besucht setzen
                Dungeon[Coords.X-1][Coords.Y-3].Visited = true;
                Dungeon[Coords.X][Coords.Y-3].Visited = true;
                Dungeon[Coords.X+1][Coords.Y-3].Visited = true;
                Dungeon[Coords.X-1][Coords.Y-2].Visited = true;
                Dungeon[Coords.X][Coords.Y-2].Visited = true;
                Dungeon[Coords.X+1][Coords.Y-2].Visited = true;
                Dungeon[Coords.X-1][Coords.Y-1].Visited = true;
                Dungeon[Coords.X][Coords.Y-1].Visited = true;
                Dungeon[Coords.X+1][Coords.Y-1].Visited = true;
                // Layer 1 setzen
                Dungeon[Coords.X-1][Coords.Y-3].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X][Coords.Y-3].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X+1][Coords.Y-3].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X-1][Coords.Y-2].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X][Coords.Y-2].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X+1][Coords.Y-2].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X-1][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X+1][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                // Layer 2 setzen
                Dungeon[Coords.X-1][Coords.Y-3].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X][Coords.Y-3].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X+1][Coords.Y-3].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X-1][Coords.Y-2].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X][Coords.Y-2].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y-2].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X-1][Coords.Y-1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X][Coords.Y-1].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y-1].Dungeon_Layer2 = DT_WALL;
                // Layer 3 setzen
                Dungeon[Coords.X-1][Coords.Y-3].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X][Coords.Y-3].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y-3].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X-1][Coords.Y-2].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X][Coords.Y-2].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y-2].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X-1][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                // die Offenen Enden der Liste OpenEndsList zufügen
                Coords.X = Coords.X + 1;
                Coords.Y = Coords.Y - 2;
                if(!Dungeon[Coords.X+1][Coords.Y].Dungeon_Layer2 == DT_NOTHING)
                {
                    OpenEndsList.push_back(Coords);
                }
                CellInUse = CellInUse + 9;
                return true;
            }
            else
            {
                return false;
            }
        break;
        // Süden
        case DIR_SOUTH:
            if(Coords.X - 1 < 1 || Coords.X + 1 > DungeonSize_X-1 || Coords.Y + 1 > DungeonSize_Y-1 || Coords.Y + 2 > DungeonSize_Y-1)
            {
                return false;
            }
            else if(Dungeon[Coords.X-1][Coords.Y+3].Visited == false && Dungeon[Coords.X][Coords.Y+3].Visited == false && Dungeon[Coords.X+1][Coords.Y+3].Visited == false &&
                    Dungeon[Coords.X-1][Coords.Y+2].Visited == false && Dungeon[Coords.X][Coords.Y+2].Visited == false && Dungeon[Coords.X+1][Coords.Y+2].Visited == false &&
                    Dungeon[Coords.X-1][Coords.Y+1].Visited == false && Dungeon[Coords.X][Coords.Y+1].Visited == false && Dungeon[Coords.X+1][Coords.Y+1].Visited == false)
            {
                // Teile auf besucht setzen
                Dungeon[Coords.X-1][Coords.Y+3].Visited = true;
                Dungeon[Coords.X][Coords.Y+3].Visited = true;
                Dungeon[Coords.X+1][Coords.Y+3].Visited = true;
                Dungeon[Coords.X-1][Coords.Y+2].Visited = true;
                Dungeon[Coords.X][Coords.Y+2].Visited = true;
                Dungeon[Coords.X+1][Coords.Y+2].Visited = true;
                Dungeon[Coords.X-1][Coords.Y+1].Visited = true;
                Dungeon[Coords.X][Coords.Y+1].Visited = true;
                Dungeon[Coords.X+1][Coords.Y+1].Visited = true;
                // Layer 1 setzen
                Dungeon[Coords.X-1][Coords.Y+3].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X][Coords.Y+3].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X+1][Coords.Y+3].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X-1][Coords.Y+2].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X][Coords.Y+2].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X+1][Coords.Y+2].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X-1][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X+1][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                // Layer 2 setzen
                Dungeon[Coords.X-1][Coords.Y+3].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X][Coords.Y+3].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X+1][Coords.Y+3].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X-1][Coords.Y+2].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X][Coords.Y+2].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y+2].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X-1][Coords.Y+1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X][Coords.Y+1].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y+1].Dungeon_Layer2 = DT_WALL;
                // Layer 3 setzen
                Dungeon[Coords.X-1][Coords.Y+3].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X][Coords.Y+3].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y+3].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X-1][Coords.Y+2].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X][Coords.Y+2].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y+2].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X-1][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                // die Offenen Enden der Liste OpenEndsList zufügen
                Coords.X = Coords.X - 1;
                Coords.Y = Coords.Y + 2;
                if(!Dungeon[Coords.X-1][Coords.Y].Dungeon_Layer2 == DT_NOTHING)
                {
                    OpenEndsList.push_back(Coords);
                }
                CellInUse = CellInUse + 9;
                return true;
            }
            else
            {
                return false;
            }
        break;
        // osten
        case DIR_EAST:
            if(Coords.X + 1 > DungeonSize_X - 1 || Coords.X + 2 > DungeonSize_X-1 || Coords.Y - 1 < 1 || Coords.Y + 1 > DungeonSize_Y - 1)
            {
                return false;
            }
            else if(Dungeon[Coords.X+1][Coords.Y+1].Visited == false && Dungeon[Coords.X + 2][Coords.Y+1].Visited == false && Dungeon[Coords.X + 3][Coords.Y+1].Visited == false &&
                    Dungeon[Coords.X+1][Coords.Y].Visited == false && Dungeon[Coords.X + 2][Coords.Y].Visited == false && Dungeon[Coords.X + 3][Coords.Y].Visited == false &&
                    Dungeon[Coords.X+1][Coords.Y-1].Visited == false && Dungeon[Coords.X + 2][Coords.Y-1].Visited == false && Dungeon[Coords.X + 3][Coords.Y-1].Visited == false)
            {
                // Teile auf besucht setzen
                Dungeon[Coords.X+1][Coords.Y+1].Visited = true;
                Dungeon[Coords.X + 2][Coords.Y+1].Visited = true;
                Dungeon[Coords.X + 3][Coords.Y+1].Visited = true;
                Dungeon[Coords.X+1][Coords.Y].Visited = true;
                Dungeon[Coords.X + 2][Coords.Y].Visited = true;
                Dungeon[Coords.X + 3][Coords.Y].Visited = true;
                Dungeon[Coords.X+1][Coords.Y-1].Visited = true;
                Dungeon[Coords.X + 2][Coords.Y-1].Visited = true;
                Dungeon[Coords.X + 3][Coords.Y-1].Visited = true;
                // Layer 1 setzen
                Dungeon[Coords.X+1][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X + 2][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X + 3][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X+1][Coords.Y].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X + 2][Coords.Y].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X + 3][Coords.Y].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X+1][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X + 2][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X + 3][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                // Layer 2 setzen
                Dungeon[Coords.X+1][Coords.Y+1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X + 2][Coords.Y+1].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X + 3][Coords.Y+1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X+1][Coords.Y].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X + 2][Coords.Y].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X + 3][Coords.Y].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X+1][Coords.Y-1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X + 2][Coords.Y-1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X + 3][Coords.Y-1].Dungeon_Layer2 = DT_WALL;
                // Layer 3 setzen
                Dungeon[Coords.X+1][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X + 2][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X + 3][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X + 2][Coords.Y].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X + 3][Coords.Y].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X + 2][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X + 3][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                // die Offenen Enden der Liste OpenEndsList zufügen
                Coords.X = Coords.X + 2;
                Coords.Y = Coords.Y + 1;
                if(!Dungeon[Coords.X][Coords.Y+1].Dungeon_Layer2 == DT_NOTHING)
                {
                    OpenEndsList.push_back(Coords);
                }
                CellInUse = CellInUse + 9;
                return true;
            }
            else
            {
                return false;
            }
        break;
        // westen
        case DIR_WEST:
            if(Coords.X - 1 <  1 || Coords.X - 2 < 1 || Coords.Y - 1 < 1 || Coords.Y + 1 > DungeonSize_Y - 1)
            {
                return false;
            }
            else if(Dungeon[Coords.X-1][Coords.Y+1].Visited == false && Dungeon[Coords.X - 2][Coords.Y+1].Visited == false && Dungeon[Coords.X - 3][Coords.Y+1].Visited == false &&
                    Dungeon[Coords.X-1][Coords.Y].Visited == false && Dungeon[Coords.X - 2][Coords.Y].Visited == false && Dungeon[Coords.X - 3][Coords.Y].Visited == false &&
                    Dungeon[Coords.X-1][Coords.Y-1].Visited == false && Dungeon[Coords.X - 2][Coords.Y-1].Visited == false && Dungeon[Coords.X - 3][Coords.Y-1].Visited == false)
            {
                // Teile auf besucht setzen
                Dungeon[Coords.X-1][Coords.Y+1].Visited = true;
                Dungeon[Coords.X - 2][Coords.Y+1].Visited = true;
                Dungeon[Coords.X - 3][Coords.Y+1].Visited = true;
                Dungeon[Coords.X-1][Coords.Y].Visited = true;
                Dungeon[Coords.X - 2][Coords.Y].Visited = true;
                Dungeon[Coords.X - 3][Coords.Y].Visited = true;
                Dungeon[Coords.X-1][Coords.Y-1].Visited = true;
                Dungeon[Coords.X - 2][Coords.Y-1].Visited = true;
                Dungeon[Coords.X - 3][Coords.Y-1].Visited = true;
                // Layer 1 setzen
                Dungeon[Coords.X-1][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X - 2][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X - 3][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X-1][Coords.Y].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X - 2][Coords.Y].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X - 3][Coords.Y].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X-1][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X + 2][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X + 3][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                // Layer 2 setzen
                Dungeon[Coords.X-1][Coords.Y+1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X - 2][Coords.Y+1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X - 3][Coords.Y+1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X-1][Coords.Y].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X - 2][Coords.Y].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X - 3][Coords.Y].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X-1][Coords.Y-1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X - 2][Coords.Y-1].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X - 3][Coords.Y-1].Dungeon_Layer2 = DT_WALL;
                // Layer 3 setzen
                Dungeon[Coords.X-1][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X - 2][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X - 3][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X-1][Coords.Y].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X - 2][Coords.Y].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X - 3][Coords.Y].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X-1][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X - 2][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X - 3][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                // die Offenen Enden der Liste OpenEndsList zufügen
                Coords.X = Coords.X - 2;
                Coords.Y = Coords.Y - 1;
                if(!Dungeon[Coords.X][Coords.Y-1].Dungeon_Layer2 == DT_NOTHING)
                {
                    OpenEndsList.push_back(Coords);
                }
                CellInUse = CellInUse + 9;
                return true;
            }
            else
            {
                return false;
            }
        break;
        case DIR_FAULT:
            return false;
        break;
    }
    return false;
}
bool CDungeonGenerator::Set_LeftWay(St_Coords Coords,en_Direction direction)
{
    switch(direction)
    {
        // Norden
        case DIR_NORTH:
            if(Coords.X - 1 < 1 || Coords.X + 1 > DungeonSize_X-1 || Coords.Y - 1 < 1 || Coords.Y - 2 < 1)
            {
                return false;
            }
            else if(Dungeon[Coords.X-1][Coords.Y-3].Visited == false && Dungeon[Coords.X][Coords.Y-3].Visited == false && Dungeon[Coords.X+1][Coords.Y-3].Visited == false &&
                    Dungeon[Coords.X-1][Coords.Y-2].Visited == false && Dungeon[Coords.X][Coords.Y-2].Visited == false && Dungeon[Coords.X+1][Coords.Y-2].Visited == false &&
                    Dungeon[Coords.X-1][Coords.Y-1].Visited == false && Dungeon[Coords.X][Coords.Y-1].Visited == false && Dungeon[Coords.X+1][Coords.Y-1].Visited == false)
            {
                // Teile auf besucht setzen
                Dungeon[Coords.X-1][Coords.Y-3].Visited = true;
                Dungeon[Coords.X][Coords.Y-3].Visited = true;
                Dungeon[Coords.X+1][Coords.Y-3].Visited = true;
                Dungeon[Coords.X-1][Coords.Y-2].Visited = true;
                Dungeon[Coords.X][Coords.Y-2].Visited = true;
                Dungeon[Coords.X+1][Coords.Y-2].Visited = true;
                Dungeon[Coords.X-1][Coords.Y-1].Visited = true;
                Dungeon[Coords.X][Coords.Y-1].Visited = true;
                Dungeon[Coords.X+1][Coords.Y-1].Visited = true;
                // Layer 1 setzen
                Dungeon[Coords.X-1][Coords.Y-3].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X][Coords.Y-3].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X+1][Coords.Y-3].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X-1][Coords.Y-2].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X][Coords.Y-2].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X+1][Coords.Y-2].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X-1][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X+1][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                // Layer 2 setzen
                Dungeon[Coords.X-1][Coords.Y-3].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X][Coords.Y-3].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X+1][Coords.Y-3].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X-1][Coords.Y-2].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X][Coords.Y-2].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y-2].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X-1][Coords.Y-1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X][Coords.Y-1].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y-1].Dungeon_Layer2 = DT_WALL;
                // Layer 3 setzen
                Dungeon[Coords.X-1][Coords.Y-3].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X][Coords.Y-3].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y-3].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X-1][Coords.Y-2].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X][Coords.Y-2].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y-2].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X-1][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                // die Offenen Enden der Liste OpenEndsList zufügen
                Coords.X = Coords.X - 1;
                Coords.Y = Coords.Y - 2;
                if(!Dungeon[Coords.X-1][Coords.Y].Dungeon_Layer2 == DT_NOTHING)
                {
                    OpenEndsList.push_back(Coords);
                }
                CellInUse = CellInUse + 9;
                return true;
            }
            else
            {
                return false;
            }
        break;
        // Süden
        case DIR_SOUTH:
            if(Coords.X - 1 < 1 || Coords.X + 1 > DungeonSize_X-1 || Coords.Y + 1 > DungeonSize_Y-1 || Coords.Y + 2 > DungeonSize_Y-1)
            {
                return false;
            }
            else if(Dungeon[Coords.X-1][Coords.Y+3].Visited == false && Dungeon[Coords.X][Coords.Y+3].Visited == false && Dungeon[Coords.X+1][Coords.Y+3].Visited == false &&
                    Dungeon[Coords.X-1][Coords.Y+2].Visited == false && Dungeon[Coords.X][Coords.Y+2].Visited == false && Dungeon[Coords.X+1][Coords.Y+2].Visited == false &&
                    Dungeon[Coords.X-1][Coords.Y+1].Visited == false && Dungeon[Coords.X][Coords.Y+1].Visited == false && Dungeon[Coords.X+1][Coords.Y+1].Visited == false)
            {
                // Teile auf besucht setzen
                Dungeon[Coords.X-1][Coords.Y+3].Visited = true;
                Dungeon[Coords.X][Coords.Y+3].Visited = true;
                Dungeon[Coords.X+1][Coords.Y+3].Visited = true;
                Dungeon[Coords.X-1][Coords.Y+2].Visited = true;
                Dungeon[Coords.X][Coords.Y+2].Visited = true;
                Dungeon[Coords.X+1][Coords.Y+2].Visited = true;
                Dungeon[Coords.X-1][Coords.Y+1].Visited = true;
                Dungeon[Coords.X][Coords.Y+1].Visited = true;
                Dungeon[Coords.X+1][Coords.Y+1].Visited = true;
                // Layer 1 setzen
                Dungeon[Coords.X-1][Coords.Y+3].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X][Coords.Y+3].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X+1][Coords.Y+3].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X-1][Coords.Y+2].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X][Coords.Y+2].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X+1][Coords.Y+2].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X-1][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X+1][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                // Layer 2 setzen
                Dungeon[Coords.X-1][Coords.Y+3].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X][Coords.Y+3].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X+1][Coords.Y+3].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X-1][Coords.Y+2].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X][Coords.Y+2].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y+2].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X-1][Coords.Y+1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X][Coords.Y+1].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y+1].Dungeon_Layer2 = DT_WALL;
                // Layer 3 setzen
                Dungeon[Coords.X-1][Coords.Y+3].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X][Coords.Y+3].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y+3].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X-1][Coords.Y+2].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X][Coords.Y+2].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y+2].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X-1][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                // die Offenen Enden der Liste OpenEndsList zufügen
                Coords.X = Coords.X + 1;
                Coords.Y = Coords.Y + 2;
                if(!Dungeon[Coords.X+1][Coords.Y].Dungeon_Layer2 == DT_NOTHING)
                {
                    OpenEndsList.push_back(Coords);
                }
                CellInUse = CellInUse + 9;
                return true;
            }
            else
            {
                return false;
            }
        break;
        // osten
        case DIR_EAST:
            if(Coords.X + 1 > DungeonSize_X - 1 || Coords.X + 2 > DungeonSize_X-1 || Coords.Y - 1 < 1 || Coords.Y + 1 > DungeonSize_Y - 1)
            {
                return false;
            }
            else if(Dungeon[Coords.X+1][Coords.Y+1].Visited == false && Dungeon[Coords.X + 2][Coords.Y+1].Visited == false && Dungeon[Coords.X + 3][Coords.Y+1].Visited == false &&
                    Dungeon[Coords.X+1][Coords.Y].Visited == false && Dungeon[Coords.X + 2][Coords.Y].Visited == false && Dungeon[Coords.X + 3][Coords.Y].Visited == false &&
                    Dungeon[Coords.X+1][Coords.Y-1].Visited == false && Dungeon[Coords.X + 2][Coords.Y-1].Visited == false && Dungeon[Coords.X + 3][Coords.Y-1].Visited == false)
            {
                // Teile auf besucht setzen
                Dungeon[Coords.X+1][Coords.Y+1].Visited = true;
                Dungeon[Coords.X + 2][Coords.Y+1].Visited = true;
                Dungeon[Coords.X + 3][Coords.Y+1].Visited = true;
                Dungeon[Coords.X+1][Coords.Y].Visited = true;
                Dungeon[Coords.X + 2][Coords.Y].Visited = true;
                Dungeon[Coords.X + 3][Coords.Y].Visited = true;
                Dungeon[Coords.X+1][Coords.Y-1].Visited = true;
                Dungeon[Coords.X + 2][Coords.Y-1].Visited = true;
                Dungeon[Coords.X + 3][Coords.Y-1].Visited = true;
                // Layer 1 setzen
                Dungeon[Coords.X+1][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X + 2][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X + 3][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X+1][Coords.Y].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X + 2][Coords.Y].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X + 3][Coords.Y].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X+1][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X + 2][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X + 3][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                // Layer 2 setzen
                Dungeon[Coords.X+1][Coords.Y+1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X + 2][Coords.Y+1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X + 3][Coords.Y+1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X+1][Coords.Y].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X + 2][Coords.Y].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X + 3][Coords.Y].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X+1][Coords.Y-1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X + 2][Coords.Y-1].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X + 3][Coords.Y-1].Dungeon_Layer2 = DT_WALL;
                // Layer 3 setzen
                Dungeon[Coords.X+1][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X + 2][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X + 3][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X + 2][Coords.Y].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X + 3][Coords.Y].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X+1][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X + 2][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X + 3][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                // die Offenen Enden der Liste OpenEndsList zufügen
                Coords.X = Coords.X + 2;
                Coords.Y = Coords.Y - 1;
                if(!Dungeon[Coords.X][Coords.Y-1].Dungeon_Layer2 == DT_NOTHING)
                {
                    OpenEndsList.push_back(Coords);
                }
                CellInUse = CellInUse + 9;
                return true;
            }
            else
            {
                return false;
            }
        break;
        // westen
        case DIR_WEST:
            if(Coords.X - 1 >  1 || Coords.X - 2 > 1 || Coords.Y - 1 < 1 || Coords.Y + 1 > DungeonSize_Y - 1)
            {
                return false;
            }
            else if(Dungeon[Coords.X-1][Coords.Y+1].Visited == false && Dungeon[Coords.X - 2][Coords.Y+1].Visited == false && Dungeon[Coords.X - 3][Coords.Y+1].Visited == false &&
                    Dungeon[Coords.X-1][Coords.Y].Visited == false && Dungeon[Coords.X - 2][Coords.Y].Visited == false && Dungeon[Coords.X - 3][Coords.Y].Visited == false &&
                    Dungeon[Coords.X-1][Coords.Y-1].Visited == false && Dungeon[Coords.X - 2][Coords.Y-1].Visited == false && Dungeon[Coords.X - 3][Coords.Y-1].Visited == false)
            {
                // Teile auf besucht setzen
                Dungeon[Coords.X-1][Coords.Y+1].Visited = true;
                Dungeon[Coords.X - 2][Coords.Y+1].Visited = true;
                Dungeon[Coords.X - 3][Coords.Y+1].Visited = true;
                Dungeon[Coords.X-1][Coords.Y].Visited = true;
                Dungeon[Coords.X - 2][Coords.Y].Visited = true;
                Dungeon[Coords.X - 3][Coords.Y].Visited = true;
                Dungeon[Coords.X-1][Coords.Y-1].Visited = true;
                Dungeon[Coords.X - 2][Coords.Y-1].Visited = true;
                Dungeon[Coords.X - 3][Coords.Y-1].Visited = true;
                // Layer 1 setzen
                Dungeon[Coords.X-1][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X - 2][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X - 3][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X-1][Coords.Y].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X - 2][Coords.Y].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X - 3][Coords.Y].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X-1][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X + 2][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                Dungeon[Coords.X + 3][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
                // Layer 2 setzen
                Dungeon[Coords.X-1][Coords.Y+1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X - 2][Coords.Y+1].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X - 3][Coords.Y+1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X-1][Coords.Y].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X - 2][Coords.Y].Dungeon_Layer2 = DT_NOTHING;
                Dungeon[Coords.X - 3][Coords.Y].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X-1][Coords.Y-1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X - 2][Coords.Y-1].Dungeon_Layer2 = DT_WALL;
                Dungeon[Coords.X - 3][Coords.Y-1].Dungeon_Layer2 = DT_WALL;
                // Layer 3 setzen
                Dungeon[Coords.X-1][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X - 2][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X-1][Coords.Y].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X - 2][Coords.Y].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X-1][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                Dungeon[Coords.X - 2][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
                // die Offenen Enden der Liste OpenEndsList zufügen
                Coords.X = Coords.X - 2;
                Coords.Y = Coords.Y + 1;
                if(!Dungeon[Coords.X][Coords.Y+1].Dungeon_Layer2 == DT_NOTHING)
                {
                    OpenEndsList.push_back(Coords);
                }
                CellInUse = CellInUse + 9;
                return true;
            }
            else
            {
                return false;
            }
        break;
        case DIR_FAULT:
            return false;
        break;
    }
    return false;
}
en_Direction CDungeonGenerator::Get_Direction(St_Coords Coords)
{
    // Überprüfen ob die Koordinate direkt am rand liegt
    if(Coords.X - 1 < 1 || Coords.Y - 1 < 1 || Coords.X + 1 > DungeonSize_X-1 || Coords.Y + 1 > DungeonSize_Y-1)
    {
        return DIR_FAULT;
    }
    // Norden
    if(Dungeon[Coords.X][Coords.Y - 1].Visited == false)
    {
        return DIR_NORTH;
    }
    // Süden
    else if(Dungeon[Coords.X][Coords.Y + 1].Visited == false)
    {
        return DIR_SOUTH;
    }
    // Osten
    else if(Dungeon[Coords.X + 1][Coords.Y].Visited == false)
    {
        return DIR_EAST;
    }
    // Westen
    else if(Dungeon[Coords.X - 1][Coords.Y].Visited == false)
    {
        return DIR_WEST;
    }
    else
    {
        return DIR_FAULT;
    }

}
en_DungeonParts CDungeonGenerator::Select_DungeonPart()
{
    int DiceRoll = Dice::Dice_Roll(Dice::ANY,100);
    // Raum teil
    if(DiceRoll > ChanceFloor)
    {
       return DP_ROOM;
    }
    // Floor teile
    else
    {
        DiceRoll = Dice::Dice_Roll(Dice::ANY,100);
        // Sackgase 5%
        if(DiceRoll > 0 && DiceRoll <= 5)
        {
            return DP_DEADEND;
        }
        // Linkskurve 12 %
        else if (DiceRoll > 5 && DiceRoll <= 17)
        {
            return DP_LEFTWAY;
        }
        // Rechtskurve 12 %
        else if (DiceRoll > 17 && DiceRoll <= 29)
        {
            return DP_RIGHTWAY;
        }
        // Floor 29 %
        else if (DiceRoll > 29 && DiceRoll <= 58)
        {
            return DP_FLOOR;
        }
        // X Cross 21 %
        else if (DiceRoll > 58 && DiceRoll <= 79)
        {
            return DP_XCROSS;
        }
        // X Cross 21 %
        else if (DiceRoll > 79 && DiceRoll <= 100)
        {
            return DP_TCROSS;
        }
    }
    return DP_FAIL;

}
bool CDungeonGenerator::Set_StartPoint(St_Coords Coords)
{
    // Überprüfen ob eine X Kreuzung im Dungeon liegt
    if(Coords.X - 1 < 4 || Coords.Y - 1 < 4 || Coords.X + 1 > DungeonSize_X-4 || Coords.Y + 1 > DungeonSize_Y-4)
    {
        return false;
    }
    // Überprüfen ob einer der 9 Felder schon besucht ist
    if(Dungeon[Coords.X-1][Coords.Y-1].Visited == true || Dungeon[Coords.X][Coords.Y-1].Visited == true || Dungeon[Coords.X + 1][Coords.Y-1].Visited == true ||
       Dungeon[Coords.X-1][Coords.Y].Visited == true || Dungeon[Coords.X][Coords.Y].Visited == true || Dungeon[Coords.X + 1][Coords.Y].Visited == true ||
       Dungeon[Coords.X-1][Coords.Y+1].Visited == true || Dungeon[Coords.X][Coords.Y+1].Visited == true || Dungeon[Coords.X + 1][Coords.Y+1].Visited == true)
    {
       return false;
    }
    else
    {
        // Alle 9 Teile auf Besucht setzen
        Dungeon[Coords.X-1][Coords.Y-1].Visited = true;
        Dungeon[Coords.X][Coords.Y-1].Visited = true;
        Dungeon[Coords.X + 1][Coords.Y-1].Visited = true;
        Dungeon[Coords.X-1][Coords.Y].Visited = true;
        Dungeon[Coords.X][Coords.Y].Visited = true;
        Dungeon[Coords.X + 1][Coords.Y].Visited = true;
        Dungeon[Coords.X-1][Coords.Y+1].Visited = true;
        Dungeon[Coords.X][Coords.Y+1].Visited = true;
        Dungeon[Coords.X + 1][Coords.Y+1].Visited =true;
        // Den ersten Layer setzen
        Dungeon[Coords.X-1][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
        Dungeon[Coords.X][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
        Dungeon[Coords.X + 1][Coords.Y-1].Dungeon_Layer1 = DT_FLOOR;
        Dungeon[Coords.X-1][Coords.Y].Dungeon_Layer1 = DT_FLOOR;
        Dungeon[Coords.X][Coords.Y].Dungeon_Layer1 = DT_FLOOR;
        Dungeon[Coords.X + 1][Coords.Y].Dungeon_Layer1 = DT_FLOOR;
        Dungeon[Coords.X-1][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
        Dungeon[Coords.X][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
        Dungeon[Coords.X + 1][Coords.Y+1].Dungeon_Layer1 = DT_FLOOR;
        // Den zweiten Layer setzen
        Dungeon[Coords.X-1][Coords.Y-1].Dungeon_Layer2 = DT_WALL;
        Dungeon[Coords.X][Coords.Y-1].Dungeon_Layer2 = DT_NOTHING;
        Dungeon[Coords.X + 1][Coords.Y-1].Dungeon_Layer2 = DT_WALL;
        Dungeon[Coords.X-1][Coords.Y].Dungeon_Layer2 = DT_NOTHING;
        Dungeon[Coords.X][Coords.Y].Dungeon_Layer2 = DT_NOTHING;
        Dungeon[Coords.X + 1][Coords.Y].Dungeon_Layer2 = DT_NOTHING;
        Dungeon[Coords.X-1][Coords.Y+1].Dungeon_Layer2 = DT_WALL;
        Dungeon[Coords.X][Coords.Y+1].Dungeon_Layer2 = DT_NOTHING;
        Dungeon[Coords.X + 1][Coords.Y+1].Dungeon_Layer2 = DT_WALL;
        // Den dritten Layer setzen
        Dungeon[Coords.X-1][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
        Dungeon[Coords.X][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
        Dungeon[Coords.X + 1][Coords.Y-1].Dungeon_Layer3 = DT_NOTHING;
        Dungeon[Coords.X-1][Coords.Y].Dungeon_Layer3 = DT_NOTHING;
        Dungeon[Coords.X][Coords.Y].Dungeon_Layer3 = DT_NOTHING;
        Dungeon[Coords.X + 1][Coords.Y].Dungeon_Layer3 = DT_NOTHING;
        Dungeon[Coords.X-1][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
        Dungeon[Coords.X][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
        Dungeon[Coords.X + 1][Coords.Y+1].Dungeon_Layer3 = DT_NOTHING;
        // die Offenen Enden der Liste OpenEndsList zufügen
        CurrentCell.X = Coords.X - 1;
        CurrentCell.Y = Coords.Y;
        OpenEndsList.push_back(CurrentCell);
        CurrentCell.X = Coords.X + 1;
        CurrentCell.Y = Coords.Y;
        OpenEndsList.push_back(CurrentCell);
        CurrentCell.X = Coords.X;
        CurrentCell.Y = Coords.Y - 1;
        OpenEndsList.push_back(CurrentCell);
        CurrentCell.X = Coords.X;
        CurrentCell.Y = Coords.Y + 1;
        OpenEndsList.push_back(CurrentCell);
        CurrentCell = Coords;
        CellInUse = CellInUse + 9;
        return true;
    }
}
#ifdef LOGFILE
void CDungeonGenerator::Set_LogFile(CLogFile* logfile)
{
    LogFile = logfile;
    *LogFile << "Setzen des LogFiles (" << LogFile << ") für die DungeonGenerator Klasse." << CLogFile::endl();
}
#endif
