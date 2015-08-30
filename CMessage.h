#ifndef CMESSAGE_H
#define CMESSAGE_H
#include <iostream>
#include "CLogFile.h"

class CMessage
{
private:
    std::string Message;
    #ifdef LOGFILE
    //
    static CLogFile* LogFile;
    #endif
public:
    void Set_Message(std::string Msg) {Message = Msg;}
    std::string Get_Message() {return Message;}
    #ifdef LOGFILE
    void static Set_LogFile(CLogFile* logfile);
    #endif
    CMessage();
    ~CMessage() {};
};

struct St_MessageStore
{
    St_MessageStore* Next;
    St_MessageStore* Prev;
    CMessage* MyMsg;
};

class CMessageLoop
{
private:
    // Die Nachrichten ablage
    St_MessageStore* MessageStore;
    // springt eine Nachricht nach vorne
    bool Prev();
    // springt eine Nachricht nach hinten
    bool Next();
    // geht zu ersten Nachricht
    void First();
    // geht zur letzten Nachricht
    void Last();
    // löscht die gesammte Loop
    void Clear_Loop();
    #ifdef LOGFILE
    //
    static CLogFile* LogFile;
    #endif
public:
    // Nachricht auf die Ablage legen
    void Create_Message(std::string Msg);
    // Holt eine Nachricht ab
    CMessage Get_Message();
    #ifdef LOGFILE
    //
    void static Set_LogFile(CLogFile* logfile);
    #endif
    // Konstruktor
    CMessageLoop();
    // Destruktor
    ~CMessageLoop();
};
#endif //  CMESSAGE_H
