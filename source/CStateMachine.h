#ifndef CSTATEMACHINE_H
#define CSTATEMACHINE_H

#include "CLogFile.h"

enum en_State { SM_INTRO,
                SM_OPTION,
                SM_OUTRO,
                SM_GAME,
                SM_MAINMENU,
                SM_REMOVELASTSTATE,
                SM_GAMEQUIT,
                SM_NOTHING};
struct St_State
{
    en_State State;
    bool Transparency;
    bool Init;
};

class CState
{
private:
    // der Status
    St_State CurrentState;
    #ifdef LOGFILE
    //
    static CLogFile* LogFile;
    #endif
public:
    // Gibt den Status zurück
    en_State Get_State() {return CurrentState.State;}
    // Gibt die Transparenz Zurück
    bool Get_Transparency()  {return CurrentState.Transparency;}
    // gibt zurück ob der Status schon Initialisiert wurde
    bool Get_Init() {return CurrentState.Init;}
    // Setzt den Status
    void Set_State(en_State nState) {CurrentState.State = nState;}
    // Setzt die Transparenz
    void Set_Transparency(bool Value) {CurrentState.Transparency = Value;}
    // Setzt den Init Status
    void Set_Init(bool Value) {CurrentState.Init = Value;}
    #ifdef LOGFILE
    //
    void static Set_LogFile(CLogFile* logfile);
    #endif
    // Konstruktor
    CState();
    // Destruktor
    ~CState() {}
};

struct St_StateStack
{
    // Aktueller Status
    CState* CurrentState;
    // Drunterliegender Status
    St_StateStack* ButtomState;
    // Drüberligender Status
    St_StateStack* UpperState;
};

class CStateStack
{
private:
    // Aktueller Status
    St_StateStack* State;
    // löscht den ganzen Stack
    void Clear_Stack();
    #ifdef LOGFILE
    //
    static CLogFile* LogFile;
    #endif
public:
    // Legt einen neuen Status auf den Stapel
    void Add_State(CState state);
    // entfernt den obersten Status
    void Remove_State();
    // Ginbt den Aktuellen Status zurück
    CState* Get_State() {return State->CurrentState;}
    #ifdef LOGFILE
    //
    void static Set_LogFile(CLogFile* logfile);
    #endif
    // Konstruktor
    CStateStack();
    // Destruktor
    ~CStateStack();
};
#endif // CSTATEMACHINE_H
