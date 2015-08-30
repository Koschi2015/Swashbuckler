#include "CRessourcenManager.h"

#ifdef LOGFILE
CLogFile* CRessourcenManager::LogFile = 0;
#endif

CRessourcenManager::CRessourcenManager()
{
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_GREEN;
        *LogFile << "CRessourcenManager" << this << ": Aufruf des Konstruktor." << CLogFile::endl();
    }
    #endif
    Ressource = 0;
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << LFF_GREEN;
        *LogFile << "CRessourcenManager" << this << ": Verlassen des Konstruktors." << CLogFile::endl();
    }
    #endif
}
CRessourcenManager::~CRessourcenManager()
{
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_RED;
        *LogFile << "CRessourcenManager" << this << ": Aufruf des Destruktors." << CLogFile::endl();
    }
    #endif
    if(Ressource)
    {
        Clear_List();
    }
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << LFF_RED;
        *LogFile << "CRessourcenManager" << this << ": Verlassen des Destruktors." << CLogFile::endl();
    }
    #endif
}
bool CRessourcenManager::Next_Element()
{
    if(Ressource->Next)
    {
        Ressource = Ressource->Next;
        return true;
    }
    return false;
}
bool CRessourcenManager::Prev_Element()
{
    if(Ressource->Prev)
    {
        Ressource = Ressource->Prev;
        return true;
    }
    return false;
}
void CRessourcenManager::First_Element()
{
    while(Prev_Element());
}
sf::Image* CRessourcenManager::Load_Image(std::string Path)
{
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_BLUE;
        *LogFile << "CRessourcenManager" << this << ": Load_Image(std::string Path) Ausführen" << CLogFile::endl();
    }
    #endif
    // Keine Ressource vorhanden neu Aufnehmen
    if(Ressource == 0)
    {
        Ressource = new St_Ressource;
        Ressource->RessourcenName = Path;
        Ressource->Image = new sf::Image;
        #ifdef LOGFILE
        if(LogFile)
        {
            *LogFile << LFF_BLUE;
            *LogFile << "CRessourcenManager" << this << ": Neue (St_Ressource) Ressource (" <<  Ressource <<") erstellt" << CLogFile::endl();
            *LogFile << "CRessourcenManager" << this << ": Neue (sf::Image) Image (" <<  Ressource->Image <<") erstellt" << CLogFile::endl();
            *LogFile << "CRessourcenManager" << this << ": ImagePfad " <<  Ressource->RessourcenName <<CLogFile::endl();
        }
        #endif
        Ressource->Next = 0;
        Ressource->Prev = 0;
        Ressource->Counter = 1;
        Ressource->Font = 0;
        Ressource->Music = 0;
        Ressource->SoundBuffer = 0;
        Ressource->Image->LoadFromFile(Path);
        #ifdef LOGFILE
        if(LogFile)
        {
            *LogFile << LFF_BLUE;
            *LogFile << "CRessourcenManager" << this << ": Load_Image(std::string Path) verlasen" << CLogFile::endl();
        }
        #endif
        return Ressource->Image;
    }
    // es sind Resourcen vorhanden es wird überprüft ob die gesuchte Ressource schon da ist.
    else if(Ressource)
    {
        First_Element();
        do
        if(Ressource->RessourcenName == Path)
        {
            Ressource->Counter++;
            #ifdef LOGFILE
            if(LogFile)
            {
                *LogFile << LFF_BLUE;
                *LogFile << "CRessourcenManager" << this << ": Counter für Ressource (" <<  Ressource <<") erhöht auf " << Ressource->Counter << CLogFile::endl();
            }
            #endif
            #ifdef LOGFILE
            if(LogFile)
            {
                *LogFile << LFF_BLUE;
                *LogFile << "CRessourcenManager" << this << ": Load_Image(std::string Path) verlasen" << CLogFile::endl();
            }
            #endif
            return Ressource->Image;
        }
        while(Next_Element());
        // Keine Ressource gefunden neu einfügen
        if(this->Ressource->Next == 0)
        {
            Ressource->Next = new St_Ressource;
            Ressource->Next->Prev = Ressource;
            Ressource->Next->Next = 0;
            Next_Element();
            Ressource->RessourcenName = Path;
            Ressource->Image = new sf::Image;
            #ifdef LOGFILE
            if(LogFile)
            {
                *LogFile << LFF_BLUE;
                *LogFile << "CRessourcenManager" << this << ": Neue (St_Ressource) Ressource (" <<  Ressource <<") erstellt" << CLogFile::endl();
                *LogFile << "CRessourcenManager" << this << ": Neue (sf::Image) Image (" <<  Ressource->Image <<") erstellt" << CLogFile::endl();
                *LogFile << "CRessourcenManager" << this << ": ImagePfad " <<  Ressource->RessourcenName <<CLogFile::endl();
            }
            #endif
            Ressource->Counter = 1;
            Ressource->Font = 0;
            Ressource->Music = 0;
            Ressource->SoundBuffer = 0;
            Ressource->Image->LoadFromFile(Path);
            #ifdef LOGFILE
            if(LogFile)
            {
                *LogFile << LFF_BLUE;
                *LogFile << "CRessourcenManager" << this << ": Load_Image(std::string Path) verlasen" << CLogFile::endl();
            }
            #endif
            return Ressource->Image;
        }
    }
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << LFF_BLUE;
        *LogFile << "CRessourcenManager" << this << ": Load_Image(std::string Path) irregulär verlasen" << CLogFile::endl();
    }
    #endif
    return 0;
}
sf::Font* CRessourcenManager::Load_Font(std::string Path)
{
    // Keine Ressource vorhanden neu Aufnehmen
    if(Ressource == 0)
    {
        Ressource = new St_Ressource;
        Ressource->RessourcenName = Path;
        Ressource->Image = 0;
        Ressource->Next = 0;
        Ressource->Prev = 0;
        Ressource->Counter = 1;
        Ressource->Font = new sf::Font;
        Ressource->Music = 0;
        Ressource->SoundBuffer = 0;
        std::cout << "Lade: " << Path << std::endl;
        Ressource->Font->LoadFromFile(Path,8,"ABCDEFGHIJKLMNOPQRSTUVWXYZÜÄÖabcdefghijklmnopqrstuvwxyzßüäö1234567890.:,;<>'#+*-_[](){}`´^°~!?=&");
        return Ressource->Font;
    }
    // es sind Resourcen vorhanden es wird überprüft ob die gesuchte Ressource schon da ist.
    else if(Ressource)
    {
        First_Element();
        do
        if(Ressource->RessourcenName == Path)
        {
            Ressource->Counter++;
            return Ressource->Font;
        }
        while(Next_Element());
        // Keine Ressource gefunden neu einfügen
        if(this->Ressource->Next == 0)
        {
            Ressource->Next = new St_Ressource;
            Ressource->Next->Prev = Ressource;
            Ressource->Next->Next = 0;
            Next_Element();
            Ressource->RessourcenName = Path;
            Ressource->Image = 0;
            Ressource->Counter = 1;
            Ressource->Font = new sf::Font;
            Ressource->Music = 0;
            Ressource->SoundBuffer = 0;
            std::cout << "Lade: " << Path << std::endl;
            Ressource->Font->LoadFromFile(Path,8,"ABCDEFGHIJKLMNOPQRSTUVWXYZÜÄÖabcdefghijklmnopqrstuvwxyzßüäö1234567890.:,;<>'#+*-_[](){}`´^°~!?=&");
            return Ressource->Font;
        }
    }
    return 0;
}
sf::Music* CRessourcenManager::Load_Music(std::string Path)
{
    // Keine Ressource vorhanden neu Aufnehmen
    if(Ressource == 0)
    {
        Ressource = new St_Ressource;
        Ressource->RessourcenName = Path;
        Ressource->Image = 0;
        Ressource->Next = 0;
        Ressource->Prev = 0;
        Ressource->Counter = 1;
        Ressource->Font = 0;
        Ressource->Music = new sf::Music;;
        Ressource->SoundBuffer = 0;
        Ressource->Font->LoadFromFile(Path,8,"ABCDEFGHIJKLMNOPQRSTUVWXYZÜÄÖabcdefghijklmnopqrstuvwxyzßüäö1234567890.:,;<>'#+*-_[](){}`´^°~!?=&");
        return Ressource->Music;
    }
    // es sind Resourcen vorhanden es wird überprüft ob die gesuchte Ressource schon da ist.
    else if(Ressource)
    {
        First_Element();
        do
        if(Ressource->RessourcenName == Path)
        {
            Ressource->Counter++;
            return Ressource->Music;
        }
        while(Next_Element());
        // Keine Ressource gefunden neu einfügen
        if(this->Ressource->Next == 0)
        {
            Ressource->Next = new St_Ressource;
            Ressource->Next->Prev = Ressource;
            Ressource->Next->Next = 0;
            Next_Element();
            Ressource->RessourcenName = Path;
            Ressource->Image = 0;
            Ressource->Counter = 1;
            Ressource->Font = 0;
            Ressource->Music = new sf::Music;
            Ressource->SoundBuffer = 0;
            Ressource->Music->OpenFromFile(Path);
            return Ressource->Music;
        }
    }
    return 0;
}
sf::SoundBuffer* CRessourcenManager::Load_SoundBuffer(std::string Path)
{
    // Keine Ressource vorhanden neu Aufnehmen
    if(Ressource == 0)
    {
        Ressource = new St_Ressource;
        Ressource->RessourcenName = Path;
        Ressource->Image = 0;
        Ressource->Next = 0;
        Ressource->Prev = 0;
        Ressource->Counter = 1;
        Ressource->Font = 0;
        Ressource->Music = 0;
        Ressource->SoundBuffer = new sf::SoundBuffer;
        Ressource->SoundBuffer->LoadFromFile(Path);
        return Ressource->SoundBuffer;
    }
    // es sind Resourcen vorhanden es wird überprüft ob die gesuchte Ressource schon da ist.
    else if(Ressource)
    {
        First_Element();
        do
        if(Ressource->RessourcenName == Path)
        {
            Ressource->Counter++;
            return Ressource->SoundBuffer;
        }
        while(Next_Element());
        // Keine Ressource gefunden neu einfügen
        if(this->Ressource->Next == 0)
        {
            Ressource->Next = new St_Ressource;
            Ressource->Next->Prev = Ressource;
            Ressource->Next->Next = 0;
            Next_Element();
            Ressource->RessourcenName = Path;
            Ressource->Image = 0;
            Ressource->Counter = 1;
            Ressource->Font = 0;
            Ressource->Music = 0;
            Ressource->SoundBuffer = 0;
            Ressource->SoundBuffer->LoadFromFile(Path);
            return Ressource->SoundBuffer;
        }
    }
    return 0;
}
bool CRessourcenManager::Clear_Element()
{
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_BLUE;
        *LogFile << "CRessourcenManager" << this << ": Clear_Element() Ausführen" << CLogFile::endl();
    }
    #endif
    if(Ressource)
    {
        // Löschen der Ressourcen
        if(Ressource->Font)
        {
            std::cout << "Entlade: " << Ressource->RessourcenName << std::endl;
            delete Ressource->Font;
            Ressource->Font = 0;
        }
        if(Ressource->Image)
        {
            #ifdef LOGFILE
            if(LogFile)
            {
                *LogFile << LFF_BLUE;
                *LogFile << "CRessourcenManager" << this << ": Lösche Image (" << Ressource->Image << ")" << CLogFile::endl();
            }
            #endif
            delete Ressource->Image;
            Ressource->Image = 0;
        }
        if(Ressource->Music)
        {
            delete Ressource->Music;
            Ressource->Music = 0;
        }
        if(Ressource->SoundBuffer)
        {
            delete Ressource->SoundBuffer;
            Ressource->SoundBuffer = 0;
        }
        // Ändern der Verkettung
        if(Ressource->Next && Ressource->Prev)
        {
            St_Ressource* This = Ressource;
            Next_Element();
            This->Prev->Next = This->Next;
            This->Next->Prev = This->Prev;
            #ifdef LOGFILE
            if(LogFile)
            {
                *LogFile << LFF_BLUE;
                *LogFile << "CRessourcenManager" << this << ": Lösche Ressource (" << This << ")" << CLogFile::endl();
            }
            #endif
            delete This;
            This = 0;
            #ifdef LOGFILE
            if(LogFile)
            {
                *LogFile << LFF_BLUE;
                *LogFile << "CRessourcenManager" << this << ": Clear_Element() Verlassen" << CLogFile::endl();
            }
            #endif
            return true;
        }
        else if(Ressource->Next && !Ressource->Prev)
        {
            St_Ressource* This = Ressource;
            Next_Element();
            This->Next->Prev = 0;
            #ifdef LOGFILE
            if(LogFile)
            {
                *LogFile << LFF_BLUE;
                *LogFile << "CRessourcenManager" << this << ": Lösche Ressource (" << This << ")" << CLogFile::endl();
            }
            #endif
            delete This;
            This = 0;
            #ifdef LOGFILE
            if(LogFile)
            {
                *LogFile << LFF_BLUE;
                *LogFile << "CRessourcenManager" << this << ": Clear_Element() Verlassen" << CLogFile::endl();
            }
            #endif
            return true;
        }
        else if(!Ressource->Next && Ressource->Prev)
        {
            Prev_Element();
            Ressource->Next->Prev = 0;
            #ifdef LOGFILE
            if(LogFile)
            {
                *LogFile << LFF_BLUE;
                *LogFile << "CRessourcenManager" << this << ": Lösche Ressource (" << Ressource->Next << ")" << CLogFile::endl();
            }
            #endif
            delete Ressource->Next;
            Ressource->Next = 0;
            //delete This;
            //This = 0;
            #ifdef LOGFILE
            if(LogFile)
            {
                *LogFile << LFF_BLUE;
                *LogFile << "CRessourcenManager" << this << ": Clear_Element() Verlassen" << CLogFile::endl();
            }
            #endif
            return true;
        }
        else if(!Ressource->Next && !Ressource->Prev)
        {
            #ifdef LOGFILE
            if(LogFile)
            {
                *LogFile << LFF_BLUE;
                *LogFile << "CRessourcenManager" << this << ": Lösche Ressource (" << Ressource << ")" << CLogFile::endl();
            }
            #endif
            delete Ressource;
            Ressource = 0;
            #ifdef LOGFILE
            if(LogFile)
            {
                *LogFile << LFF_BLUE;
                *LogFile << "CRessourcenManager" << this << ": Clear_Element() Verlassen" << CLogFile::endl();
            }
            #endif
            return true;
        }
    }
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << LFF_BLUE;
        *LogFile << "CRessourcenManager" << this << ": Clear_Element() Verlassen" << CLogFile::endl();
    }
    #endif
    return false;
}
void CRessourcenManager::Clear_List()
{
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_BLUE;
        *LogFile << "CRessourcenManager" << this << ": Clear_List() Ausführen" << CLogFile::endl();
    }
    #endif
    while(Clear_Element());
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << LFF_BLUE;
        *LogFile << "CRessourcenManager" << this << ": Clear_List() Verlassen" << CLogFile::endl();
    }
    #endif
}
bool CRessourcenManager::Release(sf::Image* RC)
{
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_BLUE;
        *LogFile << "CRessourcenManager" << this << ": Release(sf::Image* RC) Ausführen" << CLogFile::endl();
    }
    #endif
    First_Element();
    do
        if(Ressource->Image == RC)
        {
            if(Ressource->Counter > 1)
            {
                Ressource->Counter--;
                #ifdef LOGFILE
                if(LogFile)
                {
                    *LogFile << LFF_BLUE;
                    *LogFile << "CRessourcenManager" << this << ": Counter für Ressource (" <<  Ressource <<") erniedrigt auf " << Ressource->Counter << CLogFile::endl();
                    *LogFile << "CRessourcenManager" << this << ": Release(sf::Image* RC) Verlassen" << CLogFile::endl();
                }
                #endif
                return true;
            }
            else
            {
                Clear_Element();
                #ifdef LOGFILE
                if(LogFile)
                {
                    *LogFile << LFF_BLUE;
                    *LogFile << "CRessourcenManager" << this << ": Release(sf::Image* RC) Verlassen" << CLogFile::endl();
                }
                #endif
                return true;
            }
        }
    while(Next_Element());
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << LFF_BLUE;
        *LogFile << "CRessourcenManager" << this << ": Release(sf::Image* RC) Verlassen, ohne etwas gefunden zu haben." << CLogFile::endl();
    }
    #endif
    return false;
}
bool CRessourcenManager::Release(sf::Font* RC)
{
    First_Element();
    do
        if(Ressource->Font == RC)
        {
            if(Ressource->Counter > 1)
            {
                Ressource->Counter--;
                return true;
            }
            else
            {
                Clear_Element();
                return true;
            }
        }
    while(Next_Element());
    return false;
}
bool CRessourcenManager::Release(sf::Music* RC)
{
    First_Element();
    do
        if(Ressource->Music == RC)
        {
            if(Ressource->Counter > 1)
            {
                Ressource->Counter--;
                return true;
            }
            else
            {
                Clear_Element();
                return true;
            }
        }
    while(Next_Element());
    return false;
}
bool CRessourcenManager::Release(sf::SoundBuffer* RC)
{
    First_Element();
    do
        if(Ressource->SoundBuffer == RC)
        {
            if(Ressource->Counter > 1)
            {
                Ressource->Counter--;
                return true;
            }
            else
            {
                Clear_Element();
                return true;
            }
        }
    while(Next_Element());
    return false;
}
#ifdef LOGFILE
void CRessourcenManager::Set_LogFile(CLogFile* logfile)
{
    LogFile = logfile;
    *LogFile << LFF_AQUA;
    *LogFile << "Setzen des LogFiles (" << LogFile << ") für die RessourcenManager Klasse." << CLogFile::endl();
}
#endif
