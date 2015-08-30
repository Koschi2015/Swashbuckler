#include "CStateMachine.h"

#ifdef LOGFILE
CLogFile* CState::LogFile=0;
#endif

CState::CState()
{
    /*#ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_GREEN;
        *LogFile << "CState" << this << ": Aufruf des Konstruktors." << CLogFile::endl();
    }
    #endif */
    CurrentState.State = SM_NOTHING;
    CurrentState.Transparency = false;
    CurrentState.Init = false;
    /*#ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << LFF_GREEN;
        *LogFile << "CState" << this << ": Verlassen des Konstruktors." << CLogFile::endl();
    }
    #endif*/
}
#ifdef LOGFILE
void CState::Set_LogFile(CLogFile* logfile)
{
    LogFile = logfile;
    *LogFile << "Setzen des LogFiles (" << LogFile << ") für die State Klasse." << CLogFile::endl();
}
#endif

#ifdef LOGFILE
CLogFile* CStateStack::LogFile=0;
#endif

CStateStack::CStateStack()
{
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_GREEN;
        *LogFile << "CStateStack" << this << ": Aufruf des Konstruktors." << CLogFile::endl();
    }
    #endif
    State = 0;
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << LFF_GREEN;
        *LogFile << "CStateStack" << this << ": Verlassen des Konstruktors." << CLogFile::endl();
    }
    #endif
}
CStateStack::~CStateStack()
{
    Clear_Stack();
}
void CStateStack::Add_State(CState state)
{
    if(State == 0)
    {
        State = new St_StateStack;
        State->CurrentState = new CState;
        State->CurrentState->Set_State(state.Get_State());
        State->CurrentState->Set_Transparency(state.Get_Transparency());
        State->ButtomState = 0;
        State->UpperState = 0;
    }
    else
    {
        State->UpperState = new St_StateStack;
        State->UpperState->CurrentState = new CState;
        State->UpperState->ButtomState = State;
        State->UpperState->CurrentState->Set_State(state.Get_State());
        State->UpperState->CurrentState->Set_Transparency(state.Get_Transparency());
        State = State->UpperState;
        State->UpperState = 0;
    }
}
void CStateStack::Remove_State()
{
    if(State)
    {
        delete State->CurrentState;
        State->CurrentState = 0;
        if(State->ButtomState)
        {
            State = State->ButtomState;
            delete State->UpperState;
            State->UpperState = 0;
        }
        else
        {
            delete State;
            State = 0;
        }
    }
}
void CStateStack::Clear_Stack()
{
    do
        Remove_State();
    while(State != 0);
}
#ifdef LOGFILE
void CStateStack::Set_LogFile(CLogFile* logfile)
{
    LogFile = logfile;
    *LogFile << "Setzen des LogFiles (" << LogFile << ") für die StateStack Klasse." << CLogFile::endl();
}
#endif
