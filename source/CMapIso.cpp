#include "CMapIso.h"
// Statische Member
sf::Clock CAnimation::Timer;
CDungeonGenerator CMapIso::DungeonGenerator;

#ifdef LOGFILE
CLogFile* CAnimation::LogFile = 0;
#endif

CAnimation::CAnimation()
{
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_GREEN;
        *LogFile << "CAnimation" << this << ": Aufruf des Konstruktors." << CLogFile::endl();
    }
    #endif
    FrameTime = 0;
    LastFrame = 0;
    FirstFrame = 0;
    StopFrame = 0;
    CurrentFrame = -1;
    TimeNextFrame = 0;
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << LFF_GREEN;
        *LogFile << "CAnimation" << this << ": Verlassen des Konstruktors." << CLogFile::endl();
    }
    #endif
}
int CAnimation::Get_CurrentFrame()
{
    if(Animation_On)
    {
        if(CurrentFrame == -1)
        {
            CurrentFrame = FirstFrame;
            TimeNextFrame = Timer.getElapsedTime().asSeconds() + FrameTime;
            return CurrentFrame;
        }
        else
        {
            if(Timer.getElapsedTime().asSeconds() > TimeNextFrame)
            {
                CurrentFrame++;
                TimeNextFrame = Timer.getElapsedTime().asSeconds() + FrameTime;
                if (CurrentFrame > LastFrame)
                {
                    CurrentFrame = FirstFrame;
                }
            }
            return CurrentFrame;
        }
    }
    else
    {
        CurrentFrame = -1;
        return StopFrame;
    }
}
#ifdef LOGFILE
void CAnimation::Set_LogFile(CLogFile* logfile)
{
    LogFile = logfile;
    *LogFile << "Setzen des LogFiles (" << LogFile << ") für die Animierte Tile Klasse." << CLogFile::endl();
}
#endif

#ifdef LOGFILE
CLogFile* CTileIso::LogFile = 0;
#endif

CTileIso::CTileIso()
{
    /*#ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_GREEN;
        *LogFile << "CTileIso" << this << ": Aufruf des Konstruktors." << CLogFile::endl();
    }
    #endif*/
    X_Coord = 0;
    Y_Coord = 0;
    Layer1 = 0;
    Layer2 = 0;
    LightIndex = 7;
    LightSource = false;
    Walkable = true;
    LineOfSight = false;
    Animated = false;
    Layer3.Set_FirstFrame(0);
    Layer3.Set_FrameTime(0.0f);
    Layer3.Set_LastFrame(0);
    Layer3.Set_StopFrame(0);
    /*#ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << LFF_GREEN;
        *LogFile << "CTileIso" << this << ": Verlassen des Konstruktors." << CLogFile::endl();
    }
    #endif*/
}
CTileIso::~CTileIso()
{

}
void CTileIso::Set_Layer_3(int FirstFrame,int LastFrame,int StopFrame,float FrameTime)
{
    Layer3.Set_FirstFrame(FirstFrame);
    Layer3.Set_LastFrame(LastFrame);
    Layer3.Set_StopFrame(StopFrame);
    Layer3.Set_FrameTime(FrameTime);
}
#ifdef LOGFILE
void CTileIso::Set_LogFile(CLogFile* logfile)
{
    LogFile = logfile;
    *LogFile << "Setzen des LogFiles (" << LogFile << ") für die IsoTile Klasse." << CLogFile::endl();
}
#endif

/*
    MAP
*/
#ifdef LOGFILE
CLogFile* CMapIso::LogFile = 0;
#endif

CMapIso::CMapIso()
{
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_GREEN;
        *LogFile << "CMapIso" << this << ": Aufruf des Konstruktors." << CLogFile::endl();
    }
    #endif
    X_Size = 0;
    Y_Size = 0;
    Map = 0;
    GlobalLight = true;
    Layer_1.SpriteSheet = 0;
    Layer_1.SpriteSheet_Path = "";
    Layer_1.Sprite_X_Size = 0;
    Layer_1.Sprite_Y_Size = 0;
    Layer_2.SpriteSheet = 0;
    Layer_2.SpriteSheet_Path = "";
    Layer_2.Sprite_X_Size = 0;
    Layer_2.Sprite_Y_Size = 0;
    Layer_3.SpriteSheet = 0;
    Layer_3.SpriteSheet_Path = "";
    Layer_3.Sprite_X_Size = 0;
    Layer_3.Sprite_Y_Size = 0;
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << LFF_GREEN;
        *LogFile << "CMapIso" << this << ": Verlassen des Konstruktors." << CLogFile::endl();
    }
    #endif
}
CMapIso::CMapIso(const CMapIso &NewMap)
{
    // Größe der Karte erstellen
    this->Set_MapSize(NewMap.X_Size,NewMap.Y_Size);
    // Layer 1 übernehmen
    this->Layer_1.SpriteSheet_Path = NewMap.Layer_1.SpriteSheet_Path;
    this->Layer_1.Sprite_X_Size = NewMap.Layer_1.Sprite_X_Size;
    this->Layer_1.Sprite_Y_Size = NewMap.Layer_1.Sprite_Y_Size;
    this->Set_Layer_1(Layer_1.SpriteSheet_Path,Layer_1.Sprite_X_Size,Layer_1.Sprite_Y_Size);
    // Layer 2 übernehmen
    this->Layer_2.SpriteSheet_Path = NewMap.Layer_2.SpriteSheet_Path;
    this->Layer_2.Sprite_X_Size = NewMap.Layer_2.Sprite_X_Size;
    this->Layer_2.Sprite_Y_Size = NewMap.Layer_2.Sprite_Y_Size;
    this->Set_Layer_2(Layer_2.SpriteSheet_Path,Layer_2.Sprite_X_Size,Layer_2.Sprite_Y_Size);
    // Layer 2 übernehmen
    this->Layer_3.SpriteSheet_Path = NewMap.Layer_3.SpriteSheet_Path;
    this->Layer_3.Sprite_X_Size = NewMap.Layer_3.Sprite_X_Size;
    this->Layer_3.Sprite_Y_Size = NewMap.Layer_3.Sprite_Y_Size;
    this->Set_Layer_3(Layer_3.SpriteSheet_Path,Layer_3.Sprite_X_Size,Layer_3.Sprite_Y_Size);
    // Globales Licht übernehmen
    this->GlobalLight = NewMap.GlobalLight;
    //
    for(int i = 0;i < X_Size;i++)
    {
        for(int j = 0;j < Y_Size;j++ )
        {
            this->Map[i][j] = NewMap.Map[i][j];
        }
    }
}
CMapIso::~CMapIso()
{
    if(Map)
    {
        for(int i = 0;i<X_Size;i++)
        {
            delete[] Map[i];
        }
        delete[] Map;
    }
    Map = 0;
    if(Layer_1.SpriteSheet)
    {
        delete Layer_1.SpriteSheet;
    }
    Layer_1.SpriteSheet = 0;
    if(Layer_2.SpriteSheet)
    {
        delete Layer_2.SpriteSheet;
    }
    Layer_2.SpriteSheet = 0;
    if(Layer_3.SpriteSheet)
    {
        delete Layer_3.SpriteSheet;
    }
    Layer_3.SpriteSheet = 0;
}
void CMapIso::Set_MapSize(int x,int y)
{
    if(Map)
    {
        for(int i = 0;i<X_Size;i++)
        {
            delete[] Map[i];
        }
        delete[] Map;
    }
    else
    {
        X_Size = x;
        Y_Size = y;
        Map = new CTileIso*[X_Size];
        for(int i = 0;i<X_Size;i++)
        {
            Map[i] = new CTileIso[Y_Size];
        }
    }
}
void CMapIso::Set_Layer_1(std::string Path,int X_Size,int Y_Size)
{
    Layer_1.SpriteSheet_Path = Path;
    Layer_1.Sprite_X_Size = X_Size;
    Layer_1.Sprite_Y_Size = Y_Size;
    if(Layer_1.SpriteSheet)
    {
        Layer_1.SpriteSheet->Load(Layer_1.SpriteSheet_Path,Layer_1.Sprite_X_Size,Layer_1.Sprite_Y_Size);
    }
    else
    {
        Layer_1.SpriteSheet = new CSpriteSheet;
        Layer_1.SpriteSheet->Load(Layer_1.SpriteSheet_Path,Layer_1.Sprite_X_Size,Layer_1.Sprite_Y_Size);
    }
}
void CMapIso::Set_Layer_2(std::string Path,int X_Size,int Y_Size)
{
    Layer_2.SpriteSheet_Path = Path;
    Layer_2.Sprite_X_Size = X_Size;
    Layer_2.Sprite_Y_Size = Y_Size;
    if(Layer_2.SpriteSheet)
    {
        Layer_2.SpriteSheet->Load(Layer_2.SpriteSheet_Path,Layer_2.Sprite_X_Size,Layer_2.Sprite_Y_Size);
    }
    else
    {
        Layer_2.SpriteSheet = new CSpriteSheet;
        Layer_2.SpriteSheet->Load(Layer_2.SpriteSheet_Path,Layer_2.Sprite_X_Size,Layer_2.Sprite_Y_Size);
    }
}
void CMapIso::Set_Layer_3(std::string Path,int X_Size,int Y_Size)
{
    Layer_3.SpriteSheet_Path = Path;
    Layer_3.Sprite_X_Size = X_Size;
    Layer_3.Sprite_Y_Size = Y_Size;
    if(Layer_3.SpriteSheet)
    {
        Layer_3.SpriteSheet->Load(Layer_3.SpriteSheet_Path,Layer_3.Sprite_X_Size,Layer_3.Sprite_Y_Size);
    }
    else
    {
        Layer_3.SpriteSheet = new CSpriteSheet;
        Layer_3.SpriteSheet->Load(Layer_3.SpriteSheet_Path,Layer_3.Sprite_X_Size,Layer_3.Sprite_Y_Size);
    }
}
sf::Sprite CMapIso::Get_Sprite_Layer_1(int XPos_Tile,int YPos_Tile)
{
    return Layer_1.SpriteSheet->Get_Sprite(Map[XPos_Tile][YPos_Tile].Get_Layer_1());
}
sf::Sprite CMapIso::Get_Sprite_Layer_2(int XPos_Tile,int YPos_Tile)
{
    return Layer_2.SpriteSheet->Get_Sprite(Map[XPos_Tile][YPos_Tile].Get_Layer_2());
}
sf::Sprite CMapIso::Get_Sprite_Layer_3(int XPos_Tile,int YPos_Tile)
{
    return Layer_3.SpriteSheet->Get_Sprite(Map[XPos_Tile][YPos_Tile].Get_Layer_3());
}
void CMapIso::Set_Walkable(int XPos_Tile,int YPos_Tile,bool Value)
{
    Map[XPos_Tile][YPos_Tile].Set_Walkable(Value);
}
void CMapIso::Set_LightSource(int XPos_Tile,int YPos_Tile,bool Value)
{
    Map[XPos_Tile][YPos_Tile].Set_LightSource(Value);
}
void CMapIso::Set_LightSourceIndex(int XPos_Tile,int YPos_Tile,int Value)
{
    Map[XPos_Tile][YPos_Tile].Set_LightSourceIndex(Value);
}
void CMapIso::Set_LineOfSight(int XPos_Tile,int YPos_Tile,bool Value)
{
    Map[XPos_Tile][YPos_Tile].Set_LineOfSight(Value);
}
void CMapIso::Set_Animated(int XPos_Tile,int YPos_Tile,bool Value)
{
    Map[XPos_Tile][YPos_Tile].Set_Animated(Value);
}
void CMapIso::Set_Tile_Layer1(int XPos_Tile,int YPos_Tile,int Value)
{
    Map[XPos_Tile][YPos_Tile].Set_Layer_1(Value);
}
void CMapIso::Set_Tile_Layer2(int XPos_Tile,int YPos_Tile,int Value)
{
    Map[XPos_Tile][YPos_Tile].Set_Layer_2(Value);
}
void CMapIso::Set_Tile_Layer3(int XPos_Tile,int YPos_Tile,int FirstFrame,int LastFrame,int StopFrame,float FrameTime)
{
    Map[XPos_Tile][YPos_Tile].Set_Layer_3(FirstFrame,LastFrame,StopFrame,FrameTime);
}
CMapIso CMapIso::operator = (CMapIso Map)
{
    // Größe der Karte erstellen
    this->Set_MapSize(Map.Get_X_Size(),Map.Get_Y_Size());
    // Layer 1 übernehmen
    this->Layer_1.SpriteSheet_Path = Map.Layer_1.SpriteSheet_Path;
    this->Layer_1.Sprite_X_Size = Map.Layer_1.Sprite_X_Size;
    this->Layer_1.Sprite_Y_Size = Map.Layer_1.Sprite_Y_Size;
    this->Set_Layer_1(Layer_1.SpriteSheet_Path,Layer_1.Sprite_X_Size,Layer_1.Sprite_Y_Size);
    // Layer 2 übernehmen
    this->Layer_2.SpriteSheet_Path = Map.Layer_2.SpriteSheet_Path;
    this->Layer_2.Sprite_X_Size = Map.Layer_2.Sprite_X_Size;
    this->Layer_2.Sprite_Y_Size = Map.Layer_2.Sprite_Y_Size;
    this->Set_Layer_2(Layer_2.SpriteSheet_Path,Layer_2.Sprite_X_Size,Layer_2.Sprite_Y_Size);
    // Layer 2 übernehmen
    this->Layer_3.SpriteSheet_Path = Map.Layer_3.SpriteSheet_Path;
    this->Layer_3.Sprite_X_Size = Map.Layer_3.Sprite_X_Size;
    this->Layer_3.Sprite_Y_Size = Map.Layer_3.Sprite_Y_Size;
    this->Set_Layer_3(Layer_3.SpriteSheet_Path,Layer_3.Sprite_X_Size,Layer_3.Sprite_Y_Size);
    // Globales Licht übernehmen
    this->GlobalLight = Map.GlobalLight;
    //
    for(int i = 0;i < X_Size;i++)
    {
        for(int j = 0;j < Y_Size;j++ )
        {
            this->Map[i][j] = Map.Map[i][j];
        }
    }
    return *this;
}
void CMapIso::Create_TestMap()
{
    Set_MapSize(150,150);
    Set_GlobalLight(false);
    Set_Layer_1("../Spritesheet/Dungeon Set 1 Iso.png",32,80);
    Set_Layer_2("../Spritesheet/Dungeon Set 1 Iso.png",32,80);
    Set_Layer_3("../Spritesheet/Anim Set.png",32,80);
    for(int i = 0;i<50;i++)
    {
        for(int j = 0;j<50;j++)
        {
            Set_Tile_Layer1(i,j,3);
        }
    }
    for(int i = 0;i<50;i++)
    {
        for(int j = 0;j<50;j++)
        {
            if(i==0 || j == 0)
            {
                Set_Tile_Layer2(i,j,10);
            }
            else if (i== 49 || j==49)
            {
                Set_Tile_Layer2(i,j,10);
            }
            else
            {
                Set_Tile_Layer2(i,j,0);
            }
        }
    }
    for(int i = 0;i<50;i++)
    {
        for(int j = 0;j<50;j++)
        {
            Set_Tile_Layer3(i,j,0,0,0,0.0f);
        }
    }
    for(int i = 0;i<50;i++)
    {
        for(int j = 0;j<50;j++)
        {
            Set_LightSourceIndex(i,j,4 );
            Set_LightSource(i,j,false);
        }
    }
    //Set_Tile_Layer2(4,12,10);
    //Set_LineOfSight(4,12,true);
    Set_Tile_Layer2(3,12,11);
    Set_LineOfSight(3,12,true);
    Set_Tile_Layer2(3,13,11);
    Set_LineOfSight(3,13,true);

    Set_Tile_Layer2(3,15,11);
    Set_LineOfSight(3,15,true);
    Set_Tile_Layer2(5,11,11);
    Set_LineOfSight(5,11,true);
    Set_Tile_Layer2(7,11,11);
    Set_LineOfSight(7,11,true);

    Set_Tile_Layer2(7,15,11);
    Set_LineOfSight(7,15,true);
    /*
    Set_Tile_Layer2(4,14,10);
    Set_LineOfSight(4,14,true);
    Set_Tile_Layer2(4,13,10);
    Set_LineOfSight(4,13,true);
    Set_Tile_Layer2(4,12,10);
    Set_LineOfSight(4,12,true);

    Set_Tile_Layer2(7,15,10);
    Set_LineOfSight(7,15,true);
    Set_Tile_Layer2(7,14,10);
    Set_LineOfSight(7,14,true);
    Set_Tile_Layer2(7,13,10);
    Set_LineOfSight(7,13,true);
    Set_Tile_Layer2(7,12,10);
    Set_LineOfSight(7,12,true);
    Set_Tile_Layer2(7,11,10);
    Set_LineOfSight(7,11,true);*/

    Set_Tile_Layer2(0,3,14);
    Set_Tile_Layer2(10,19,12);
    Set_Tile_Layer1(10,10,4);
    Set_Tile_Layer1(1,5,4);
    Set_Tile_Layer3(11,8,13,14,0,0.2f);
    Set_Animated(11,8,true);
    Set_LightSource(11,8,true);
    Set_LightSourceIndex(11,8,250);
    Set_Tile_Layer3(5,13,13,14,0,0.2f);
    Set_Animated(5,13,true);
    Set_LightSource(5,13,true);
    Set_LightSourceIndex(5,13,250);
    Set_Tile_Layer3(25,25,13,14,0,0.2f);
    Set_Animated(25,25,true);
    Set_LightSource(25,25,true);
    Set_LightSourceIndex(25,25,250);
    Set_Tile_Layer3(45,45,13,14,0,0.2f);
    Set_Animated(45,45,true);
    Set_LightSource(45,45,true);
    Set_LightSourceIndex(45,45,250);
    Set_Tile_Layer3(5,45,13,14,0,0.2f);
    Set_Animated(5,45,true);
    Set_LightSource(5,45,true);
    Set_LightSourceIndex(5,45,250);
    Set_Tile_Layer3(45,5,13,14,0,0.2f);
    Set_Animated(45,5,true);
    Set_LightSource(45,5,true);
    Set_LightSourceIndex(5,45,250);
    Calculate_LightMap();
    //Rotate_Clockwise();
    //Rotate_Clockwise();
    //Rotate_Clockwise();
}
void CMapIso::Creat_RandomMap(int X_DungeonSize,int Y_DungeonSize,int X_MaxRoomSize,int Y_MaxRoomSize,int chanceRoom,int chanceFloor)
{
    Set_MapSize(X_DungeonSize,Y_DungeonSize);
    Set_GlobalLight(true);
    Set_Layer_1("../Spritesheet/Dungeon Set 1 Iso.png",32,80);
    Set_Layer_2("../Spritesheet/Dungeon Set 1 Iso.png",32,80);
    Set_Layer_3("../Spritesheet/Anim Set.png",32,80);
    DungeonGenerator.Create_RandomDungeon(X_DungeonSize,Y_DungeonSize,X_MaxRoomSize,Y_MaxRoomSize,75,75);
    for(int i = 0;i < X_Size;i++)
    {
        for(int j = 0;j < Y_Size;j++)
        {
            switch(DungeonGenerator.Get_DungeonTile(i,j).Dungeon_Layer1)
            {
                case DT_DOOR:
                case DT_LIGHT:
                case DT_EXIT:
                case DT_ENTRANCE_N:
                case DT_ENTRANCE_E:
                case DT_ENTRANCE_S:
                case DT_ENTRANCE_W:
                case DT_NOTHING:
                    Set_Tile_Layer1(i,j,0);
                break;
                case DT_WALL:
                    Set_Tile_Layer1(i,j,10);
                    Set_Walkable(i,j,false);
                    Set_LineOfSight(i,j,false);
                break;
                case DT_ROOM:
                case DT_FLOOR:
                    Set_Tile_Layer1(i,j,3);
                    Set_Walkable(i,j,true);
                    Set_LineOfSight(i,j,true);
                break;
            }
            switch(DungeonGenerator.Get_DungeonTile(i,j).Dungeon_Layer2)
            {
                case DT_LIGHT:
                case DT_EXIT:
                case DT_ENTRANCE_N:
                case DT_ENTRANCE_E:
                case DT_ENTRANCE_S:
                case DT_ENTRANCE_W:
                case DT_NOTHING:
                    Set_Tile_Layer2(i,j,0);
                break;
                case DT_WALL:
                    Set_Tile_Layer2(i,j,10);
                    Set_Walkable(i,j,false);
                    Set_LineOfSight(i,j,false);
                break;
                case DT_ROOM:
                case DT_FLOOR:
                    Set_Tile_Layer2(i,j,Dice::Dice_Roll(Dice::W4));
                    Set_Walkable(i,j,true);
                    Set_LineOfSight(i,j,true);
                break;
                case DT_DOOR:
                    Set_Tile_Layer2(i,j,12);
                    Set_Walkable(i,j,false);
                    Set_LineOfSight(i,j,false);
                break;
            }
            switch(DungeonGenerator.Get_DungeonTile(i,j).Dungeon_Layer3)
            {
                case DT_EXIT:
                case DT_ENTRANCE_N:
                case DT_ENTRANCE_E:
                case DT_ENTRANCE_S:
                case DT_ENTRANCE_W:
                case DT_WALL:
                case DT_ROOM:
                case DT_FLOOR:
                case DT_DOOR:
                break;
                case DT_LIGHT:
                    Set_Animated(i,j,true);
                    Set_Tile_Layer3(i,j,13,14,13,0.3f);
                    Set_Walkable(i,j,false);
                    Set_LineOfSight(i,j,true);
                    Set_LightSource(i,j,true);
                    Set_LightSourceIndex(i,j,150);
                break;
                case DT_NOTHING:
                    //Set_Tile_Layer1(i,j,0);
                break;
            }
        }
    }
}
void CMapIso::Calculate_LightMap()
{
    int Merker1;
    int Distanz;
    for(int i = 0;i<X_Size;i++)
    {
        for(int j = 0;j<Y_Size;j++)
        {
            if(Get_LightSource(i,j))
            {
                for(int a = i - 10;a<= i+10;a++)
                {
                    for(int b = j - 10;b<=j+10;b++)
                    {
                        if(a>=0 && b>= 0 && a < X_Size && b < Y_Size)
                        {
                            Distanz = (((i-a)*(i-a)+(j-b)*(j-b)) * 2 * (255/Get_LightSourceIndex(i,j)));
                            if(Distanz < Get_LightSourceIndex(i,j))
                            {
                               if ((Get_LightSourceIndex(i,j)-Distanz > Get_LightSourceIndex(a,b)))
                               {
                                   if(Tile_in_LOS(i,j,a,b))
                                   {
                                       Merker1 = Get_LightSourceIndex(i,j)-Distanz;
                                       Set_LightSourceIndex(a,b,Merker1);
                                   }
                               }
                            }
                        }
                    }
                }
            }
        }
    }
}
bool CMapIso::Tile_in_LOS(int XPos_Start,int YPos_Start,int XPos_End,int YPos_End)
{
    float deltaX = XPos_End-XPos_Start;
    float deltaY = YPos_End-YPos_Start;
    if(deltaX == 0 && deltaY < 0)
    {
        for(int i = YPos_End; i < YPos_Start;i++)
        {
            if(Get_LineOfSight(XPos_Start,i))
            {
                if(i==YPos_End)
                {
                    return true;
                }
                return false;
            }
        }
        return true;
    }
    else if(deltaX == 0 && deltaY > 0)
    {
        for(int i = YPos_Start; i < YPos_End;i++)
        {
            if(Get_LineOfSight(XPos_Start,i))
            {
                if(i==YPos_End)
                {
                    return true;
                }
                return false;
            }
        }
        return true;
    }
    else if(deltaY == 0 && deltaX > 0)
    {
        for(int i = XPos_Start; i < XPos_End;i++)
        {
            if(Get_LineOfSight(i,YPos_End))
            {
                if(i==XPos_End)
                {
                    return true;
                }
                return false;
            }
        }
        return true;
    }
    else if(deltaY == 0 && deltaX < 0)
    {
        for(int i = XPos_End; i < XPos_Start;i++)
        {
            if(Get_LineOfSight(i,YPos_End))
            {
                if(i==XPos_End)
                {
                    return true;
                }
                return false;
            }
        }
        return true;
    }
    else
    {
        float Steigung = deltaY / deltaX;
        if(Steigung == 1.0f && deltaX < 0 && deltaY < 0)
        {
            for(int i = deltaX; i < 0;i++)
            {
                if(Get_LineOfSight(XPos_Start+i,YPos_Start+i))
                {
                    if(XPos_Start+i==XPos_End)
                    {
                        return true;
                    }
                    return false;
                }
            }
            return true;
        }
        else if(Steigung == 1.0f && deltaX > 0 && deltaY > 0)
        {
            for(int i = 0; i < deltaX ;i++)
            {
                if(Get_LineOfSight(XPos_Start+i,YPos_Start+i))
                {
                    if(XPos_Start+i==XPos_End)
                    {
                        return true;
                    }
                    return false;
                }
            }
            return true;
        }
        else if(Steigung == -1.0f && deltaX < 0 && deltaY > 0)
        {
            for(int i = 0; i < deltaY ;i++)
            {
                if(Get_LineOfSight(XPos_Start-i,YPos_Start+i))
                {
                    if(XPos_Start-i==XPos_End)
                    {
                        return true;
                    }
                    return false;
                }
            }
            return true;
        }
        else if(Steigung == -1.0f && deltaX > 0 && deltaY < 0)
        {
            for(int i = 0; i < deltaX ;i++)
            {
                if(Get_LineOfSight(XPos_Start+i,YPos_Start-i))
                {
                    if(XPos_Start+i==XPos_End)
                    {
                        return true;
                    }
                    return false;
                }
            }
            return true;
        }
        else if(deltaX < 0 && deltaY < 0)
        {
            float Abstand_X = XPos_End-XPos_Start;
            float Abstand_Y = YPos_End-YPos_Start;
            float Schrittweite_X = 0;
            float Schrittweite_Y = 0;
            float Aktuell_X = XPos_Start;
            float Aktuell_Y = YPos_Start;
            if(Abstand_X < 0)
            {
                Abstand_X = Abstand_X * -1;
            }
            if(Abstand_Y < 0)
            {
                Abstand_Y = Abstand_Y * -1;
            }
            if(Abstand_X > Abstand_Y)
            {
                Schrittweite_X = 1.0f;
                Schrittweite_Y = Abstand_Y / Abstand_X;
            }
            else
            {
                Schrittweite_Y = 1.0f;
                Schrittweite_X = Abstand_X / Abstand_Y;
            }
            do
            {
                if(Get_LineOfSight(static_cast<int>(Aktuell_X+0.5),static_cast<int>(Aktuell_Y+0.5)))
                {
                    if((static_cast<int>(Aktuell_X+0.5) == XPos_End && static_cast<int>(Aktuell_Y+0.5)== YPos_End))
                    {
                        return true;
                    }
                    return false;
                }
                Aktuell_X = Aktuell_X - Schrittweite_X;
                Aktuell_Y = Aktuell_Y - Schrittweite_Y;
            }
            while(static_cast<int>(Aktuell_X+0.5) >= XPos_End && static_cast<int>(Aktuell_Y+0.5) >= YPos_End);
            return true;
        }
        else if(deltaX < 0 && deltaY > 0)
        {
            float Abstand_X = XPos_End-XPos_Start;
            float Abstand_Y = YPos_End-YPos_Start;
            float Schrittweite_X = 0;
            float Schrittweite_Y = 0;
            float Aktuell_X = XPos_Start;
            float Aktuell_Y = YPos_Start;
            if(Abstand_X < 0)
            {
                Abstand_X = Abstand_X * -1;
            }
            if(Abstand_Y < 0)
            {
                Abstand_Y = Abstand_Y * -1;
            }
            if(Abstand_X > Abstand_Y)
            {
                Schrittweite_X = 1.0f;
                Schrittweite_Y = Abstand_Y / Abstand_X;
            }
            else
            {
                Schrittweite_Y = 1.0f;
                Schrittweite_X = Abstand_X / Abstand_Y;
            }
            do
            {
                if(Get_LineOfSight(static_cast<int>(Aktuell_X+0.5),static_cast<int>(Aktuell_Y+0.5)))
                {
                    if((static_cast<int>(Aktuell_X+0.5) == XPos_End && static_cast<int>(Aktuell_Y+0.5)== YPos_End))
                    {
                        return true;
                    }
                    return false;
                }
                Aktuell_X = Aktuell_X - Schrittweite_X;
                Aktuell_Y = Aktuell_Y + Schrittweite_Y;
            }
            while(static_cast<int>(Aktuell_X+0.5) >= XPos_End && static_cast<int>(Aktuell_Y+0.5) <= YPos_End);
            return true;
        }
        else if(deltaX > 0 && deltaY > 0)
        {
            float Abstand_X = XPos_End-XPos_Start;
            float Abstand_Y = YPos_End-YPos_Start;
            float Schrittweite_X = 0;
            float Schrittweite_Y = 0;
            float Aktuell_X = XPos_Start;
            float Aktuell_Y = YPos_Start;
            if(Abstand_X < 0)
            {
                Abstand_X = Abstand_X * -1;
            }
            if(Abstand_Y < 0)
            {
                Abstand_Y = Abstand_Y * -1;
            }
            if(Abstand_X > Abstand_Y)
            {
                Schrittweite_X = 1.0f;
                Schrittweite_Y = Abstand_Y / Abstand_X;
            }
            else
            {
                Schrittweite_Y = 1.0f;
                Schrittweite_X = Abstand_X / Abstand_Y;
            }
            do
            {
                if(Get_LineOfSight(static_cast<int>(Aktuell_X+0.5),static_cast<int>(Aktuell_Y+0.5)))
                {
                    if((static_cast<int>(Aktuell_X+0.5) == XPos_End && static_cast<int>(Aktuell_Y+0.5)== YPos_End))
                    {
                        return true;
                    }
                    return false;
                }
                Aktuell_X = Aktuell_X + Schrittweite_X;
                Aktuell_Y = Aktuell_Y + Schrittweite_Y;
            }
            while(static_cast<int>(Aktuell_X+0.5) <= XPos_End && static_cast<int>(Aktuell_Y+0.5) <= YPos_End);
            return true;
        }
        else if(deltaX > 0 && deltaY < 0)
        {
            float Abstand_X = XPos_End-XPos_Start;
            float Abstand_Y = YPos_End-YPos_Start;
            float Schrittweite_X = 0;
            float Schrittweite_Y = 0;
            float Aktuell_X = XPos_Start;
            float Aktuell_Y = YPos_Start;
            if(Abstand_X < 0)
            {
                Abstand_X = Abstand_X * -1;
            }
            if(Abstand_Y < 0)
            {
                Abstand_Y = Abstand_Y * -1;
            }
            if(Abstand_X > Abstand_Y)
            {
                Schrittweite_X = 1.0f;
                Schrittweite_Y = Abstand_Y / Abstand_X;
            }
            else
            {
                Schrittweite_Y = 1.0f;
                Schrittweite_X = Abstand_X / Abstand_Y;
            }
            do
            {
                if(Get_LineOfSight(static_cast<int>(Aktuell_X+0.5),static_cast<int>(Aktuell_Y+0.5)))
                {
                    if((static_cast<int>(Aktuell_X+0.5) == XPos_End && static_cast<int>(Aktuell_Y+0.5)== YPos_End))
                    {
                        return true;
                    }
                    return false;
                }
                Aktuell_X = Aktuell_X + Schrittweite_X;
                Aktuell_Y = Aktuell_Y - Schrittweite_Y;
            }
            while(static_cast<int>(Aktuell_X+0.5) <= XPos_End && static_cast<int>(Aktuell_Y+0.5) >= YPos_End);
            return true;
        }
    }
    return true;
}
void CMapIso::Rotate_AntiClockwise()
{
    CTileIso** TempMap;
    TempMap = new CTileIso*[Y_Size];
    for (int i = 0; i < Y_Size;i++)
    {
        TempMap[i] = new CTileIso[X_Size];
    }
    for(int i = 0;i<X_Size;i++)
    {
        for(int j = 0;j<Y_Size;j++)
        {
            TempMap[((0-j)*-1)][X_Size-i-1] = Map[i][j];
            TempMap[((0-j)*-1)][X_Size-i-1].Set_X_Coord((0-j)*-1);
            TempMap[((0-j)*-1)][X_Size-i-1].Set_Y_Coord(X_Size-i-1);
        }
    }
    for(int i = 0; i< X_Size;i++)
    {
        delete[] Map[i];
        Map[i] = 0;
    }
    delete Map;
    Map = TempMap;
    int temp = X_Size;
    X_Size = Y_Size;
    Y_Size = temp;
    TempMap = 0;
}
#ifdef LOGFILE
void CMapIso::Set_LogFile(CLogFile* logfile)
{
    LogFile = logfile;
    *LogFile << "Setzen des LogFiles (" << LogFile << ") für die MapIso Klasse." << CLogFile::endl();
}
#endif
