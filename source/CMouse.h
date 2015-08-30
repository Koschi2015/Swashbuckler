#ifndef CMOUSE_H
#define CMOUSE_H

#include "CSpriteSheet.h"
#include "CLogFile.h"

class CMouse
{
private:
    // Die Klasse die das Spritesheet enthält
    CSpriteSheet* Image;
    // Zur Darstellung auf dem Bildschirm
    CAnimateSprite* MouseIcon;
    //
    const sf::Mouse* MouseInput;
    #ifdef LOGFILE
    //
    static CLogFile* LogFile;
    #endif
public:
    //
    void Set_MouseImage(std::string Path,int X_Size = 32 ,int Y_Size = 32);
    //
    void Set_Animation(int FirstFrame,int LastFrame,int StopFrame,float FrameTime);
    //
    void Animation_On(bool Value);
    //
    sf::Sprite Mouse_Update();
    //
    sf::Sprite Mouse_Update(int X,int Y);
    #ifdef LOGFILE
    //
    void static Set_LogFile(CLogFile* logfile);
    #endif
    // Kostruktor
    CMouse(const sf::Mouse* Input);
    // Destruktor
    ~CMouse();
};

#endif // CMOUSE_H
