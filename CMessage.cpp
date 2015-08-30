#include "CMessage.h"

#ifdef LOGFILE
CLogFile* CMessage::LogFile = 0;
#endif
CMessage::CMessage()
{
    /*#ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_GREEN;
        *LogFile << "CMessage" << this << ": Aufruf des Konstruktors." << CLogFile::endl();
    }
    #endif*/
    Message = "";
    /*
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_GREEN;
        *LogFile << "CMessage" << this << ": Verlassen des Konstruktors." << CLogFile::endl();
    }
    #endif */
}
#ifdef LOGFILE
void CMessage::Set_LogFile(CLogFile* logfile)
{
    LogFile = logfile;
    *LogFile << "Setzen des LogFiles (" << LogFile << ") für die MessageLoop Klasse." << CLogFile::endl();
}
#endif

#ifdef LOGFILE
CLogFile* CMessageLoop::LogFile = 0;
#endif

CMessageLoop::CMessageLoop()
{
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_GREEN;
        *LogFile << "CMessageLoop" << this << ": Aufruf des Konstruktors." << CLogFile::endl();
    }
    #endif
    MessageStore = 0;
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << LFF_GREEN;
        *LogFile << "CMessageLoop" << this << ": Verlassen des Konstruktors." << CLogFile::endl();
    }
    #endif
}
CMessageLoop::~CMessageLoop()
{
    std::cout << "MessageLoop löschen." << std::endl;
    if(MessageStore)
    {
        Clear_Loop();
    }
    std::cout << "... Beendet." << std::endl;
}
CMessage CMessageLoop::Get_Message()
{
    if(MessageStore)
    {
        First();
        CMessage Temp = *MessageStore->MyMsg;
        if(MessageStore && MessageStore->Next)
        {
            MessageStore = MessageStore->Next;
            delete MessageStore->Prev->MyMsg;
            MessageStore->Prev->MyMsg = 0;
            delete MessageStore->Prev;
            MessageStore->Prev = 0;
        }
        else if(MessageStore && MessageStore->Next == 0 && MessageStore->Prev == 0)
        {
            delete MessageStore->MyMsg;
            MessageStore->MyMsg = 0;
            delete MessageStore;
            MessageStore = 0;
        }
        return Temp;
    }
    return CMessage();
}
bool CMessageLoop::Prev()
{
    if(MessageStore->Prev)
    {
        MessageStore = MessageStore->Prev;
        return true;
    }
    else
    {
        return false;
    }
}
bool CMessageLoop::Next()
{
    if(MessageStore && MessageStore->Next)
    {
        MessageStore = MessageStore->Next;
        return true;
    }
    else
    {
        return false;
    }
}
void CMessageLoop::First()
{
    while(Prev());
}
void CMessageLoop::Last()
{
    while(Next());
}
void CMessageLoop::Create_Message(std::string Msg)
{
    if(MessageStore == 0 && Msg != "")
    {
        MessageStore = new St_MessageStore;
        MessageStore->Next = 0;
        MessageStore->Prev = 0;
        MessageStore->MyMsg = new CMessage;
        MessageStore->MyMsg->Set_Message(Msg);
    }
    else if (MessageStore && Msg != "")
    {
        Last();
        if(MessageStore->MyMsg->Get_Message() != Msg)
        {
            MessageStore->Next = new St_MessageStore;
            MessageStore->Next->Prev = MessageStore;
            MessageStore = MessageStore->Next;
            MessageStore->Next = 0;
            MessageStore->MyMsg = new CMessage;
            MessageStore->MyMsg->Set_Message(Msg);
        }
    }
}
void CMessageLoop::Clear_Loop()
{
    Last();
    do
    {
        if(MessageStore && MessageStore->Prev)
        {
            MessageStore = MessageStore->Prev;
            delete MessageStore->Next->MyMsg;
            MessageStore->Next->MyMsg = 0;
            MessageStore->Next->Prev = 0;
            delete MessageStore->Next;
            MessageStore->Next = 0;
        }
        else if (MessageStore && MessageStore->Prev == 0 && MessageStore->Next == 0)
        {
            delete MessageStore->MyMsg;
            MessageStore->MyMsg = 0;
            delete MessageStore;
            MessageStore = 0;
        }
    }
    while(MessageStore && MessageStore->Prev);
}
#ifdef LOGFILE
void CMessageLoop::Set_LogFile(CLogFile* logfile)
{
    LogFile = logfile;
    *LogFile << "Setzen des LogFiles (" << LogFile << ") für die MessageLoop Klasse." << CLogFile::endl();
}
#endif
