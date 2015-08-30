#include "CMouse.h"

#ifdef LOGFILE
CLogFile* CMouse::LogFile = 0;
#endif

void CMouse::Set_MouseImage(std::string Path,int X_Size,int Y_Size)
{
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_BLUE;
        *LogFile << "CMouse" << this << ": Set_MouseImage(std::string Path,int X_Size,int Y_Size) Ausführen" << CLogFile::endl();
    }
    #endif
    Image = new CSpriteSheet;
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << "CMouse" << this << ": Neu (CSpriteSheet) Image erstell (" << Image << ")"<< CLogFile::endl();
    }
    #endif
    Image->Load(Path,X_Size,Y_Size);
    MouseIcon = new CAnimateSprite(Image);
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << "CMouse" << this << ": Neu (CAnimateSprite) MouseIcon erstell (" << Image << ")"<< CLogFile::endl();
    }
    #endif
}
void CMouse::Set_Animation(int FirstFrame,int LastFrame,int StopFrame,float FrameTime)
{
    MouseIcon->Set_FirstFrame(FirstFrame);
    MouseIcon->Set_LastFrame(LastFrame);
    MouseIcon->Set_StopFrame(StopFrame);
    MouseIcon->Set_FrameTime(FrameTime);
}
sf::Sprite CMouse::Mouse_Update()
{
    Image->Set_Display_Coord(MouseInput->GetMouseX(),MouseInput->GetMouseY());
    return MouseIcon->Get_CurrentSprite();
}
sf::Sprite CMouse::Mouse_Update(int X,int Y)
{
    Image->Set_Display_Coord(MouseInput->GetMouseX() + X,MouseInput->GetMouseY() + Y);
    return MouseIcon->Get_CurrentSprite();
}
void CMouse::Animation_On(bool Value)
{
    MouseIcon->Animation_on(Value);
}
CMouse::CMouse(const sf::Input* Input)
{
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_GREEN;
        *LogFile << "CMouse" << this << ": Aufruf des Konstruktors." << CLogFile::endl();
    }
    #endif
    MouseInput = Input;
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << LFF_GREEN;
        *LogFile << "CMouse" << this << ": Aufruf des Konstruktors." << CLogFile::endl();
    }
    #endif
}
CMouse::~CMouse()
{
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_RED;
        *LogFile << "CMouse" << this << ": Aufruf des Destruktors." << CLogFile::endl();
    }
    #endif
    if(MouseIcon)
    {
        #ifdef LOGFILE
        if(LogFile)
        {
            *LogFile << CLogFile::endl();
            *LogFile << "CMouse" << this << ": Löschen MouseIcon (" << MouseIcon << ")."<< CLogFile::endl();
        }
        #endif
        delete MouseIcon;
        MouseIcon = 0;
    }
    if(Image)
    {
        #ifdef LOGFILE
        if(LogFile)
        {
            *LogFile << CLogFile::endl();
            *LogFile << "CMouse" << this << ": Löschen Image (" << Image << ")."<< CLogFile::endl();
        }
        #endif
        delete Image;
        Image = 0;
    }

    MouseInput = 0;
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << "CMouse" << this << ": Verlassen des Destruktors." << CLogFile::endl();
    }
    #endif
}
#ifdef LOGFILE
void CMouse::Set_LogFile(CLogFile* logfile)
{
    LogFile = logfile;
    *LogFile << "Setzen des LogFiles (" << LogFile << ") für die Mouse Klasse." << CLogFile::endl();
}
#endif
