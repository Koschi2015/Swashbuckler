#ifndef __CDICE_H__
#define __CDICE_H__

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CLogFile.h"

class Dice
{
public:
    // Arten von Würfeln
    enum en_Dice {W2,W3,W4,W6,W8,W10,W12,W20,W100,ANY};
    //
    static int Dice_Roll(en_Dice Wuerfelart,int Anzahl = 1);
    #ifdef LOGFILE
    //
private:
    static CLogFile* LogFile;
    //
public:
    void static Set_LogFile(CLogFile* logfile);
    #endif
private:
    static bool Init;
};



#endif // __CDICE_H__
