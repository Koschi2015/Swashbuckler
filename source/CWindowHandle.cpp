#include "CWindowHandle.h"

#ifdef LOGFILE
CLogFile* CWindowHandle::LogFile = 0;
#endif

CWindowHandle::CWindowHandle()
{
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_GREEN;
        *LogFile << "CWindowHandle" << this << ": Aufruf des Konstruktor." << CLogFile::endl();
        *LogFile << "CWindowHandle" << this << ": (sf::VideoMode) Mode erstellt(" << &Mode << ")" << CLogFile::endl();
        *LogFile << "CWindowHandle" << this << ": (int) ModeCount erstellt(" << &ModeCount << ")" << CLogFile::endl();
        *LogFile << "CWindowHandle" << this << ": (bool) FullScreen erstellt(" << &FullScreen << ")" << CLogFile::endl();
        *LogFile << "CWindowHandle" << this << ": (std::string) WindowName erstellt(" << &WindowName << ")" << CLogFile::endl();
    }
    #endif
    ModeCount = Mode.getFullscreenModes().size();
    ModeArray = new St_VideoMode[ModeCount];
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << LFF_GREEN;
        *LogFile << "CWindowHandle" << this << ": ModeCount zugewiesen(" << &ModeCount << ") =" << ModeCount << CLogFile::endl();
        *LogFile << "CWindowHandle" << this << ": (St_VideoMode) ModeArray erstellt(" << ModeArray << ")" << CLogFile::endl();
    }
    #endif
    for (int i = 0;i < ModeCount;i++)
    {
        ModeArray[i].Width = sf::VideoMode::getFullscreenModes()[i].width;
        ModeArray[i].Height = sf::VideoMode::getFullscreenModes()[i].height;
        ModeArray[i].BitsPerPixel = sf::VideoMode::getFullscreenModes()[i].bitsPerPixel;
        #ifdef LOGFILE
        if(LogFile)
        {
            *LogFile << CLogFile::endl();
            *LogFile << LFF_FUCHSIA;
            *LogFile << "CWindowHandle" << this << ": ModeArray Index " << i << "(" << &ModeArray[i] << ") Width =" << ModeArray[i].Width << CLogFile::endl();
            *LogFile << "CWindowHandle" << this << ": ModeArray Index " << i << "(" << &ModeArray[i] << ") Height =" << ModeArray[i].Height << CLogFile::endl();
            *LogFile << "CWindowHandle" << this << ": ModeArray Index " << i << "(" << &ModeArray[i] << ") BitsPerPixel =" << ModeArray[i].BitsPerPixel << CLogFile::endl();
        }
        #endif
    }
    Mode = Mode.getDesktopMode();
    FullScreen = true;
    WindowName = "GameEngine";
    Window = 0;
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << LFF_GREEN;
        *LogFile << "CWindowHandle" << this << ": Verlassen des Konstruktors." << CLogFile::endl();
    }
    #endif
}
CWindowHandle::~CWindowHandle()
{
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_RED;
        *LogFile << "CWindowHandle" << this << ": Aufruf des Destruktors." << CLogFile::endl();
    }
    #endif
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << LFF_RED;
        *LogFile << "CWindowHandle" << this << ": Lösche ModeArray (" << ModeArray << ")" << CLogFile::endl();
    }
    #endif
    delete[] ModeArray;
    ModeArray = 0;
    if(Window)
    {
        #ifdef LOGFILE
        if(LogFile)
        {
            *LogFile << LFF_RED;
            *LogFile << "CWindowHandle" << this << ": Lösche Window (" << Window << ")" << CLogFile::endl();
        }
        #endif
        delete Window;
        Window = 0;
    }
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << LFF_RED;
        *LogFile << "CWindowHandle" << this << ": Verlasse des Destruktors." << CLogFile::endl();
    }
    #endif
}
bool CWindowHandle::Select_VideoMode(int Index)
{
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_BLUE;
        *LogFile << "CWindowHandle" << this << ": Select_VideoMode(int Index) Ausführen" << CLogFile::endl();
    }
    #endif
    if (Index <= ModeCount)
    {
        Mode.height = ModeArray[Index].Height;
        Mode.width = ModeArray[Index].Width;
        Mode.bitsPerPixel = ModeArray[Index].BitsPerPixel;
        #ifdef LOGFILE
        if(LogFile)
        {
            *LogFile << LFF_BLUE;
            *LogFile << "CWindowHandle" << this << ": Select_VideoMode mit Index " << Index << " ist Erfolgreich" << CLogFile::endl();
        }
        #endif
        return true;
    }
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << LFF_BLUE;
        *LogFile << "CWindowHandle" << this << ": Select_VideoMode mit Index " << Index << " ist nicht Erfolgreich" << CLogFile::endl();
    }
    #endif
    return false;
}
void CWindowHandle::Create_Window()
{
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_BLUE;
        *LogFile << "CWindowHandle" << this << ": Create_Window() Ausführen" << CLogFile::endl();
    }
    #endif
    if(Window)
    {
        if(FullScreen)
        {
            Window->create(Mode,WindowName,sf::Style::Fullscreen);
        }
        else
        {
            Window->create(Mode,WindowName,sf::Style::Titlebar | sf::Style::Close);
        }
    }
    else
    {
        if(FullScreen)
        {
            Window = new sf::RenderWindow;
            Window->create(Mode,WindowName,sf::Style::Fullscreen);
            #ifdef LOGFILE
            if(LogFile)
            {
                *LogFile << LFF_BLUE;
                *LogFile << "CWindowHandle" << this << ": Window erstellt (" << Window << ")." << CLogFile::endl();
            }
            #endif
        }
        else
        {
            Window = new sf::RenderWindow;
            Window->create(Mode,WindowName,sf::Style::Titlebar | sf::Style::Close);
            #ifdef LOGFILE
            if(LogFile)
            {
                *LogFile << LFF_BLUE;
                *LogFile << "CWindowHandle" << this << ": Window erstellt (" << Window << ")." << CLogFile::endl();
            }
            #endif
        }
    }
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << LFF_BLUE;
        *LogFile << "CWindowHandle" << this << ": Create_Window() Verlassen" << CLogFile::endl();
    }
    #endif
}
void CWindowHandle::Create_Window(int VideoMode)
{
    Mode.height = ModeArray[VideoMode].Height;
    Mode.width = ModeArray[VideoMode].Width;
    Mode.bitsPerPixel = ModeArray[VideoMode].BitsPerPixel;
    if(FullScreen)
    {
        Window->create(Mode,WindowName,sf::Style::Fullscreen);
    }
    else
    {
        Window->create(Mode,WindowName,sf::Style::Titlebar | sf::Style::Close);
    }
}
int CWindowHandle::VideoMode_Possible(int X,int Y,int col)
{
    for (int i = 0;i < ModeCount;i++)
    {
        if (ModeArray[i].Width == X && ModeArray[i].Height == Y && ModeArray[i].BitsPerPixel == col)
        {
            return i;
        }
        //ModeArray[i].BitsPerPixel;
    }
    return -1;
}
#ifdef LOGFILE
void CWindowHandle::Set_LogFile(CLogFile* logfile)
{
    LogFile = logfile;
    *LogFile << "Setzen des LogFiles (" << LogFile << ") für die WindowHandle Klasse." << CLogFile::endl();
}
#endif
