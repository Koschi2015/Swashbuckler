#include "CDice.h"

bool Dice::Init = false;

#ifdef LOGFILE
CLogFile* Dice::LogFile = 0;
#endif

int Dice::Dice_Roll(en_Dice Wuerfelart,int Anzahl)
{
    /*#ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << LFF_AQUA;
        *LogFile << CLogFile::endl();
        *LogFile << "Dice" << ": Aufruf Dice_Roll(en_Dice Wuerfelart,int Anzahl)." << CLogFile::endl();
    }
    #endif */
    int Ergebnis = 0;
    if(Init == false)
    {
        srand ( time(NULL) );
        Init = true;
    }
    for(int i=0 ;i < Anzahl ;i++)
    {
        switch (Wuerfelart)
        {
            case Dice::W2:
                Ergebnis = Ergebnis + rand() % 2 + 1;
            break;
            case Dice::W3:
                Ergebnis = Ergebnis + rand() % 3 + 1;
            break;
            case Dice::W4:
                Ergebnis = Ergebnis + rand() % 4 + 1;
            break;
            case Dice::W6:
                Ergebnis = Ergebnis + rand() % 6 + 1;
            break;
            case Dice::W8:
                Ergebnis = Ergebnis + rand() % 8 + 1;
            break;
            case Dice::W10:
                Ergebnis = Ergebnis + rand() % 10 + 1;
            break;
            case Dice::W12:
                Ergebnis = Ergebnis + rand() % 12 + 1;
            break;
            case Dice::W20:
                Ergebnis = Ergebnis + rand() % 20 + 1;
            break;
            case Dice::W100:
                Ergebnis = Ergebnis + rand() % 100 + 1;
            break;
            case Dice::ANY:
                Ergebnis = Ergebnis + rand() % Anzahl + 1;
                i = Anzahl;
            break;
        }
    }
    /*
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << LFF_AQUA;
        *LogFile << "Dice" << ": Verlassen Dice_Roll(en_Dice Wuerfelart,int Anzahl). Rückgabewert -> " << Ergebnis << CLogFile::endl();
    }
    #endif */
    return Ergebnis;
}
#ifdef LOGFILE
void Dice::Set_LogFile(CLogFile* logfile)
{
    LogFile = logfile;
    *LogFile << "Setzen des LogFiles (" << LogFile << ") für die Dice Klasse." << CLogFile::endl();
}
#endif
