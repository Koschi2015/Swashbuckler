#include "CSpriteSheet.h"

CRessourcenManager* CSpriteSheet::RessourcenManager = 0;
bool CSpriteSheet::Managed = false;

#ifdef LOGFILE
CLogFile* CSpriteSheet::LogFile=0;
#endif

void CSpriteSheet::Set_RessourcenManager(CRessourcenManager* RM)
{
    if(RM && !RessourcenManager)
    {
        RessourcenManager = RM;
        Managed = true;
        #ifdef LOGFILE
        if(LogFile)
        {
            *LogFile << LFF_AQUA;
            *LogFile << "CSpriteSheet: Klasse ist Managed by RessourcenManager (" << RessourcenManager << ")" << CLogFile::endl();
        }
        #endif
    }
}
CSpriteSheet::CSpriteSheet()
{
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_GREEN;
        *LogFile << "CSpriteSheet" << this << ": Aufruf des Konstruktors." << CLogFile::endl();
    }
    #endif
	SpriteSheetImg = 0;
	SpriteSheet = 0;
	Pixel_X = 0;
	Pixel_Y = 0;
	Image_X = 0;
	Image_Y = 0;
	MaxImage = 0;
	ImageRow = 0;
	ImageColum = 0;
	#ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << LFF_GREEN;
        *LogFile << "CSpriteSheet" << this << ": Verlassen des Konstruktors." << CLogFile::endl();
    }
    #endif
}
void CSpriteSheet::Load(std::string Pfad,int SpriteSize_X,int SpriteSize_Y)
{
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_BLUE;
        *LogFile << "CSpriteSheet" << this << ": Load(std::string Pfad,int SpriteSize_X,int SpriteSize_Y) Ausführen" << CLogFile::endl();
    }
    #endif
    if(Managed)
    {
        Path = Pfad;
        Pixel_X = SpriteSize_X;
        Pixel_Y = SpriteSize_Y;
        if(SpriteSheetImg)
        {
            RessourcenManager->Release(SpriteSheetImg);
            SpriteSheetImg = RessourcenManager->Load_Image(Path);
            #ifdef LOGFILE
            if(LogFile)
            {
                *LogFile << LFF_BLUE;
                *LogFile << "CSpriteSheet" << this << ": (sf::Image) SpriteSheetImg geladen (" << SpriteSheetImg << ")" << CLogFile::endl();
            }
            #endif
        }
        else
        {
            SpriteSheetImg = RessourcenManager->Load_Image(Path);
            #ifdef LOGFILE
            if(LogFile)
            {
                *LogFile << LFF_BLUE;
                *LogFile << "CSpriteSheet" << this << ": (sf::Image) SpriteSheetImg geladen (" << SpriteSheetImg << ")" << CLogFile::endl();
            }
            #endif
        }
        SpriteSheetImg->createMaskFromColor(sf::Color(255,0,255));
        //SpriteSheetImg->setSmooth(false);
        Image_Y = SpriteSheetImg->getSize().x;
        Image_X = SpriteSheetImg->getSize().y;
        ImageRow = Image_X / Pixel_X;
        ImageColum = Image_Y / Pixel_Y;
        MaxImage = ImageRow * ImageColum -1;
        // sprite
        if(SpriteSheet)
        {
            delete SpriteSheet;
            SpriteSheet = 0;
        }
        SpriteSheet = new sf::Sprite;
        #ifdef LOGFILE
        if(LogFile)
        {
            *LogFile << LFF_BLUE;
            *LogFile << "CSpriteSheet" << this << ": (sf::Sprite) SpriteSheet erstellt (" << SpriteSheet << ")" << CLogFile::endl();
        }
        #endif
        m_texture.loadFromImage(*SpriteSheetImg);
        SpriteSheet->setTexture(m_texture);
    }
    else
    {
        Path = Pfad;
        Pixel_X = SpriteSize_X;
        Pixel_Y = SpriteSize_Y;
        if(SpriteSheetImg)
        {
            delete SpriteSheetImg;
            Image_X = 0;
            Image_Y = 0;
            SpriteSheetImg = 0;
        }
        // Image
        SpriteSheetImg = new sf::Image;
        SpriteSheetImg->loadFromFile(Path);
        SpriteSheetImg->createMaskFromColor(sf::Color(255,0,255));
        //SpriteSheetImg->setSmooth(false);
        Image_Y = SpriteSheetImg->getSize().x;
        Image_X = SpriteSheetImg->getSize().y;
        ImageRow = Image_X / Pixel_X;
        ImageColum = Image_Y / Pixel_Y;
        MaxImage = ImageRow * ImageColum -1;
        // sprite
        SpriteSheet = new sf::Sprite;
        m_texture.loadFromImage(*SpriteSheetImg);
        SpriteSheet->setTexture(m_texture);
    }
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << LFF_BLUE;
        *LogFile << "CSpriteSheet" << this << ": Load(std::string Pfad,int SpriteSize_X,int SpriteSize_Y) Verlassen" << CLogFile::endl();
    }
    #endif
}
sf::Sprite* CSpriteSheet::operator[] (int Zahl) const
{
	if(Zahl > MaxImage)
	{
		std::cout << "Unzulässiger Index." << std::endl;
	}
	int Spalte = Zahl / ImageRow;
	int Reihe = Zahl % ImageRow;
	sf::IntRect Part(Reihe * Pixel_X,Spalte * Pixel_Y,Reihe * Pixel_X + Pixel_X,Spalte * Pixel_Y + Pixel_Y);
	SpriteSheet->setTextureRect(Part);
	return SpriteSheet;
}
sf::Sprite CSpriteSheet::Get_Sprite(int Zahl) const
{
    if(Zahl > MaxImage)
	{
		std::cout << "Unzulässiger Index." << std::endl;
	}
	int Spalte = Zahl / ImageRow;
	int Reihe = Zahl % ImageRow;
	sf::IntRect Part(Reihe * Pixel_X,Spalte * Pixel_Y,Reihe * Pixel_X + Pixel_X,Spalte * Pixel_Y + Pixel_Y);
	SpriteSheet->setTextureRect(Part);
	return *SpriteSheet;
}
void CSpriteSheet::Set_Display_Coord(float X,float Y)
{
	SpriteSheet->setPosition(X,Y);
}
void CSpriteSheet::Set_Display_Coord(int X,int Y)
{
	SpriteSheet->setPosition(float(X),float(Y));
}
CSpriteSheet::~CSpriteSheet(void)
{
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_RED;
        *LogFile << "CSpriteSheet" << this << ": Aufruf des Denstruktors." << CLogFile::endl();
    }
    #endif
    if(Managed)
    {
        RessourcenManager->Release(SpriteSheetImg);
        #ifdef LOGFILE
        if(LogFile)
        {
            *LogFile << LFF_RED;
            *LogFile << "CSpriteSheet" << this << ": Lösche (sf::Sprite) SpriteSheet (" << SpriteSheet << ")." << CLogFile::endl();
        }
        #endif
        delete SpriteSheet;
        Image_X = 0;
        Image_Y = 0;
        SpriteSheetImg = 0;
        SpriteSheet = 0;
    }
    else
    {
        delete SpriteSheet;
        delete SpriteSheetImg;
        Image_X = 0;
        Image_Y = 0;
        SpriteSheetImg = 0;
        SpriteSheet = 0;
    }
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << LFF_RED;
        *LogFile << "CSpriteSheet" << this << ": Verlassen des Denstruktors." << CLogFile::endl();
    }
    #endif
}
CSpriteSheet::CSpriteSheet(const CSpriteSheet& Value)
{
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_GREEN;
        *LogFile << "CSpriteSheet" << this << ": Aufruf des KopierKonstruktors." << CLogFile::endl();
    }
    #endif
    if(Managed)
    {
        Path = Value.Path;
        Pixel_X = Value.Pixel_X;
        Pixel_Y = Value.Pixel_Y;
        Image_X = Value.Image_X;
        Image_Y = Value.Image_Y;
        MaxImage = Value.MaxImage;
        ImageRow = Value.ImageRow;
        ImageColum = Value.ImageColum;
        SpriteSheetImg = RessourcenManager->Load_Image(Path);
        SpriteSheet = new sf::Sprite;
        #ifdef LOGFILE
        if(LogFile)
        {
            *LogFile << LFF_GREEN;
            *LogFile << "CSpriteSheet" << this << ": (sf::Sprite) SpriteSheet erstellt (" << SpriteSheet << ")" << CLogFile::endl();
        }
        #endif
        m_texture.loadFromImage(*SpriteSheetImg);
        SpriteSheet->setTexture(m_texture);
    }
}
CSpriteSheet CSpriteSheet::operator= (const CSpriteSheet& Value)
{
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_BLUE;
        *LogFile << "CSpriteSheet" << this << ": Aufruf des Operator =." << CLogFile::endl();
    }
    #endif
    if (Managed)
    {
        Path = Value.Path;
        Pixel_X = Value.Pixel_X;
        Pixel_Y = Value.Pixel_Y;
        Image_X = Value.Image_X;
        Image_Y = Value.Image_Y;
        MaxImage = Value.MaxImage;
        ImageRow = Value.ImageRow;
        ImageColum = Value.ImageColum;
        if(SpriteSheetImg)
        {
            SpriteSheetImg = 0;
            SpriteSheetImg = RessourcenManager->Load_Image(Path);
        }
        else
        {
            SpriteSheetImg = RessourcenManager->Load_Image(Path);
        }
        //SpriteSheetImg->setSmooth(false);
        Image_Y = SpriteSheetImg->getSize().x;
        Image_X = SpriteSheetImg->getSize().y;
        ImageRow = Image_X / Pixel_X;
        ImageColum = Image_Y / Pixel_Y;
        MaxImage = ImageRow * ImageColum -1;
        SpriteSheet = new sf::Sprite;
        #ifdef LOGFILE
        if(LogFile)
        {
            *LogFile << LFF_BLUE;
            *LogFile << "CSpriteSheet" << this << ": (sf::Sprite) SpriteSheet erstellt (" << SpriteSheet << ")" << CLogFile::endl();
        }
        #endif
        m_texture.loadFromImage(*SpriteSheetImg);
        SpriteSheet->setTexture(m_texture);
    }
    else
    {
        // Hier für nicht Managed klasse eintragen
    }
    return *this;
}
#ifdef LOGFILE
void CSpriteSheet::Set_LogFile(CLogFile* logfile)
{
    LogFile = logfile;
    *LogFile << LFF_AQUA;
    *LogFile << "Setzen des LogFiles (" << LogFile << ") für die SpriteSheet Klasse." << CLogFile::endl();
}
#endif
sf::Clock CAnimateSprite::Timer;
#ifdef LOGFILE
CLogFile* CAnimateSprite::LogFile=0;
#endif
CAnimateSprite::CAnimateSprite(CSpriteSheet* Sprite)
{
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_GREEN;
        *LogFile << "CAnimateSprite" << this << ": Aufruf des Konstruktors (nur SpriteSheet gesetzt)." << CLogFile::endl();
    }
    #endif
    Sheet = Sprite;
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << "CAnimateSprite" << this << "Setzen (CSpriteSheet) Sheet = " << Sheet << CLogFile::endl();
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
        *LogFile << CLogFile::endl();
        *LogFile << "CAnimateSprite" << this << ": Verlassen des Konstruktors." << CLogFile::endl();
    }
    #endif
}
CAnimateSprite::CAnimateSprite(CSpriteSheet* Sprite,int firstFrame,int lastFrame,int stopFrame,float frameTime)
{
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_GREEN;
        *LogFile << "CAnimateSprite" << this << ": Aufruf des Konstruktors (ganze Animation gesetzt)." << CLogFile::endl();
    }
    #endif
    Sheet = Sprite;
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << "CAnimateSprite" << this << "Setzen (CSpriteSheet) Sheet = " << Sheet << CLogFile::endl();
    }
    #endif
    FrameTime = frameTime;
    LastFrame = lastFrame;
    FirstFrame = firstFrame;
    StopFrame = stopFrame;
    CurrentFrame = -1;
    TimeNextFrame = 0;
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << "CAnimateSprite" << this << ": Verlassen des Konstruktors." << CLogFile::endl();
    }
    #endif
}
CAnimateSprite::~CAnimateSprite()
{
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_RED;
        *LogFile << "CAnimateSprite" << this << ": Aufruf des Destruktors." << CLogFile::endl();
    }
    #endif
    Sheet = 0;
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << "CAnimateSprite" << this << ": Setzen Sheet = 0" << CLogFile::endl();
        *LogFile << "CAnimateSprite" << this << ": Verlassen des Destruktors." << CLogFile::endl();
    }
    #endif
}
sf::Sprite CAnimateSprite::operator() ()
{
    if(Animation_On)
    {
        if(CurrentFrame == -1)
        {
            CurrentFrame = FirstFrame;
            TimeNextFrame = Timer.getElapsedTime().asSeconds() + FrameTime;
            return Sheet->Get_Sprite(CurrentFrame);
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
            return Sheet->Get_Sprite(CurrentFrame);
        }
    }
    else
    {
        CurrentFrame = -1;
        return Sheet->Get_Sprite(StopFrame);
    }
}
sf::Sprite CAnimateSprite::Get_CurrentSprite()
{
    if(Animation_On)
    {
        if(CurrentFrame == -1)
        {
            CurrentFrame = FirstFrame;
            TimeNextFrame = Timer.getElapsedTime().asSeconds() + FrameTime;
            return Sheet->Get_Sprite(CurrentFrame);
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
            return Sheet->Get_Sprite(CurrentFrame);
        }
    }
    else
    {
        CurrentFrame = -1;
        return Sheet->Get_Sprite(StopFrame);
    }
}
#ifdef LOGFILE
void CAnimateSprite::Set_LogFile(CLogFile* logfile)
{
    LogFile = logfile;
    *LogFile << LFF_AQUA;
    *LogFile << "Setzen des LogFiles (" << LogFile << ") für die SpriteAnimations Klasse." << CLogFile::endl();
}
#endif
