#include "CUI.h"

const sf::Mouse* CUI_Surface::UI_InputHandle = 0;
CMessageLoop* CUI_Surface::MessageLoop = 0;

#ifdef LOGFILE
CLogFile* CUI_Base::LogFile = 0;
#endif

CUI_Base::CUI_Base() : Scope(0,0,0,0)
{
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_GREEN;
        *LogFile << "CUI_Base" << this << ": Aufruf des Konstruktors." << CLogFile::endl();
    }
    #endif
    Type = UIT_BASE;
    Offset_X = 0;
    Offset_Y = 0;
    LMB_Msg = "";
    RMB_Msg = "";
    MouseOver_Msg = "";
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << LFF_GREEN;
        *LogFile << "CUI_Base" << this << ": Verlassen des Konstruktors." << CLogFile::endl();
    }
    #endif
}

CUI_Base::~CUI_Base()
{

}

void CUI_Base::Set_Scope(int LeftCoord,int RightCoord,int TopCoord,int BottomCoord)
{
    Scope.height = BottomCoord;
    Scope.left = LeftCoord;
    Scope.width = RightCoord;
    Scope.top = TopCoord;
}

void CUI_Base::Set_Offset(int X,int Y)
{
    Offset_X = X;
    Offset_Y = Y;
    //Scope.Offset(X,Y);
}

bool CUI_Base::MouseInside(int X,int Y)
{
    return X <= Scope.width-Offset_X && X >= Scope.left-Offset_X && Y <= Scope.height-Offset_Y && Y >= Scope.top-Offset_Y;
}
CUI_Button::CUI_Button()
{
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_GREEN;
        *LogFile << "CUI_Button" << this << ": Aufruf des Konstruktors." << CLogFile::endl();
    }
    #endif
    ArrayNumber = 0;
    Type = UIT_BUTTON;
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << LFF_GREEN;
        *LogFile << "CUI_Button" << this << ": Verlassen des Konstruktors." << CLogFile::endl();
    }
    #endif
}
void CUI_Button::Load_SpriteSheet(std::string Path,int X ,int Y)
{
    Image.Load(Path,X,Y);
    Set_Scope(0,X,0,Y);
    ImagePath = Path;
    Length_X = X;
    Length_Y = Y;
}
void CUI_Button::Set_Position(int X,int Y)
{
    Set_Scope(0+X,Length_X+X,0+Y,Length_Y+Y);
    Set_Offset(X,Y);
    Image.Set_Display_Coord(static_cast<int>(X),static_cast<int>(Y));
}
sf::Drawable* CUI_Button::Render_Element()
{
    //Image.Get_Sprite(ArrayNumber);
    return Image[ArrayNumber];
}
#ifdef LOGFILE
void CUI_Base::Set_LogFile(CLogFile* logfile)
{
    LogFile = logfile;
    *LogFile << "Setzen des LogFiles (" << LogFile << ") für die UI_Base Klasse." << CLogFile::endl();
}
#endif
/*
        UI Text Klasse
*/
CUI_Text::CUI_Text()
{
    /*Font = new sf::Font;
    Font->GetDefaultFont();
    FontPath = "";*/
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_GREEN;
        *LogFile << "CUI_Text" << this << ": Aufruf des Konstruktors." << CLogFile::endl();
    }
    #endif
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << LFF_GREEN;
        *LogFile << "CUI_Text" << this << ": Verlassen des Konstruktors." << CLogFile::endl();
    }
    #endif
}
CUI_Text::~CUI_Text()
{
    /*if(Font && FontPath == "")
    {
        delete Font;
    }
    Font = 0;*/
}
void CUI_Text::Load(std::string Pfad,float size,sf::Text::Style Style)
{
    /*if(Font && FontPath == "")
    {
        delete Font;
        Font = 0;
    }

    MFont.Load(FontPath);
    Font = MFont.Get_Font();*/
    FontPath = Pfad;
    Font.loadFromFile(FontPath);
    Text.setFont(Font);
    Text.setCharacterSize(size);
    Text.setStyle(Style);
}
void CUI_Text::Set_Text(std::string text)
{
    Text.setString(text);
    Set_Scope(static_cast<int>(Text.getLocalBounds().left),static_cast<int>(Text.getLocalBounds().width),static_cast<int>(Text.getLocalBounds().top),static_cast<int>(Text.getLocalBounds().height));
}
void CUI_Text::Set_Style(sf::Text::Style style)
{
    Text.setStyle(style);
}
sf::Drawable* CUI_Text::Render_Element()
{
    return &Text;
}
/*
        UI Surface Klasse
*/
#ifdef LOGFILE
CLogFile* CUI_Surface::LogFile = 0;
#endif

CUI_Surface::CUI_Surface()
{
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_GREEN;
        *LogFile << "CUI_Surface" << this << ": Aufruf des Konstruktors." << CLogFile::endl();
    }
    #endif
    Surface = 0;
    DebounceTimer.restart();
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << LFF_GREEN;
        *LogFile << "CUI_Surface" << this << ": Verlassen des Konstruktors." << CLogFile::endl();
    }
    #endif
}

void CUI_Surface::Add_Element(CUI_Button Element)
{
    if(Surface == 0)
    {
        Surface = new St_UISurface;
        Surface->Next = 0;
        Surface->Prev = 0;
        CUI_Button* Temp = new CUI_Button;
        Temp->Set_ArrayNummber(Element.Get_ArrayNumber());
        Temp->Load_SpriteSheet(Element.Get_ImagePath(),Element.Get_Length_X(),Element.Get_Length_Y());
        Temp->Set_Scope(Element.Get_Scope());
        Temp->Set_Position(Element.Get_Offset_X(),Element.Get_Offset_Y());
        Temp->Set_LMB_Msg(Element.Get_LMB_Msg());
        Temp->Set_RMB_Msg(Element.Get_RMB_Msg());
        Temp->Set_MouseOver_Msg(Element.Get_MouseOver_Msg());
        Surface->UI_Element = Temp;
    }
    else if(Surface->Next == 0)
    {
        Surface->Next = new St_UISurface;
        Surface->Next->Next = 0;
        Surface->Next->Prev = Surface;
        Surface = Surface->Next;
        CUI_Button* Temp = new CUI_Button;
        Temp->Set_ArrayNummber(Element.Get_ArrayNumber());
        Temp->Load_SpriteSheet(Element.Get_ImagePath(),Element.Get_Length_X(),Element.Get_Length_Y());
        Temp->Set_Scope(Element.Get_Scope());
        Temp->Set_Position(Element.Get_Offset_X(),Element.Get_Offset_Y());
        Temp->Set_LMB_Msg(Element.Get_LMB_Msg());
        Temp->Set_RMB_Msg(Element.Get_RMB_Msg());
        Temp->Set_MouseOver_Msg(Element.Get_MouseOver_Msg());
        Surface->UI_Element = Temp;
    }
    else if(Surface->Prev == 0)
    {
        Surface->Prev = new St_UISurface;
        Surface->Prev->Next = Surface;
        Surface->Prev->Prev = 0;
        Surface = Surface->Prev;
        CUI_Button* Temp = new CUI_Button;
        Temp->Set_ArrayNummber(Element.Get_ArrayNumber());
        Temp->Load_SpriteSheet(Element.Get_ImagePath(),Element.Get_Length_X(),Element.Get_Length_Y());
        Temp->Set_Scope(Element.Get_Scope());
        Temp->Set_Position(Element.Get_Offset_X(),Element.Get_Offset_Y());
        Temp->Set_LMB_Msg(Element.Get_LMB_Msg());
        Temp->Set_RMB_Msg(Element.Get_RMB_Msg());
        Temp->Set_MouseOver_Msg(Element.Get_MouseOver_Msg());
        Surface->UI_Element = Temp;
    }
    else
    {
        std::cout << "Brauchen hier noch was" << std::endl;
    }
}
void CUI_Surface::Add_Element(CUI_Text Element)
{
    if(Surface == 0)
    {
        Surface = new St_UISurface;
        Surface->Next = 0;
        Surface->Prev = 0;
        CUI_Text* Temp = new CUI_Text;
        //std::cout << "Adresse neue Text: " << &Temp->Get_Text() << std::endl;
        Temp->Set_Scope(Element.Get_Scope());
        Temp->Set_Position(Element.Get_Offset_X(),Element.Get_Offset_Y());
        Temp->Set_LMB_Msg(Element.Get_LMB_Msg());
        Temp->Set_RMB_Msg(Element.Get_RMB_Msg());
        Temp->Set_MouseOver_Msg(Element.Get_MouseOver_Msg());
        Temp->Set_Text(Element.Get_Text());
        if(Element.Get_FontPath() != "")
        {
            Temp->Load(Element.Get_FontPath(),Element.Get_Size(),Element.Get_Style());
        }
        Surface->UI_Element = Temp;
    }
    else if(Surface->Next == 0)
    {
        Surface->Next = new St_UISurface;
        Surface->Next->Next = 0;
        Surface->Next->Prev = Surface;
        Surface = Surface->Next;
        CUI_Text* Temp = new CUI_Text;
        Temp->Set_Scope(Element.Get_Scope());
        Temp->Set_Position(Element.Get_Offset_X(),Element.Get_Offset_Y());
        Temp->Set_LMB_Msg(Element.Get_LMB_Msg());
        Temp->Set_RMB_Msg(Element.Get_RMB_Msg());
        Temp->Set_MouseOver_Msg(Element.Get_MouseOver_Msg());
        Temp->Set_Text(Element.Get_Text());
        if(Element.Get_FontPath() != "")
        {
            Temp->Load(Element.Get_FontPath(),Element.Get_Size(),Element.Get_Style());
        }
        Surface->UI_Element = Temp;
    }
    else if(Surface->Prev == 0)
    {
        Surface->Prev = new St_UISurface;
        Surface->Prev->Next = Surface;
        Surface->Prev->Prev = 0;
        Surface = Surface->Prev;
        CUI_Text* Temp = new CUI_Text;
        Temp->Set_Scope(Element.Get_Scope());
        Temp->Set_Position(Element.Get_Offset_X(),Element.Get_Offset_Y());
        Temp->Set_LMB_Msg(Element.Get_LMB_Msg());
        Temp->Set_RMB_Msg(Element.Get_RMB_Msg());
        Temp->Set_MouseOver_Msg(Element.Get_MouseOver_Msg());
        Temp->Set_Text(Element.Get_Text());
        {
            Temp->Load(Element.Get_FontPath(),Element.Get_Size(),Element.Get_Style());
        }
        Surface->UI_Element = Temp;
    }
    else
    {
        std::cout << "Brauchen hier noch was" << std::endl;
    }
}
bool CUI_Surface::Next_Element()
{
    if(Surface->Next)
    {
        Surface = Surface->Next;
        return true;
    }
    return false;
}
bool CUI_Surface::Prev_Element()
{
    if(Surface->Prev)
    {
        Surface = Surface->Prev;
        return true;
    }
    return false;
}
void CUI_Surface::First_Element()
{
    while(Prev_Element());
}
void CUI_Surface::Last_Element()
{
    while(Next_Element());
}
void CUI_Surface::Check_Element()
{
    if(DebounceTimer.getElapsedTime().asSeconds() > 0.015f) // 15 ms Verzögerung
    {
        DebounceTimer.restart();
        First_Element();
        do
        {
            if(Surface->UI_Element->MouseInside(UI_InputHandle->getPosition().x,UI_InputHandle->getPosition().y))
            {

                if(CUI_Surface::UI_InputHandle->isButtonPressed(sf::Mouse::Left))
                {
                    std::string Msg = Surface->UI_Element->Get_LMB_Msg();
                    if(Msg != "")
                    {
                        if(MessageLoop->Get_Message().Get_Message() != Msg)
                        {
                            //std::cout << Msg << std::endl;
                            MessageLoop->Create_Message(Msg);
                        }
                    }
                }
                else if(CUI_Surface::UI_InputHandle->isButtonPressed(sf::Mouse::Right))
                {
                    std::string Msg = Surface->UI_Element->Get_RMB_Msg();
                    if(Msg != "")
                    {
                        MessageLoop->Create_Message(Msg);
                    }
                }
                else
                {
                    std::string Msg = Surface->UI_Element->Get_MouseOver_Msg();
                    if(Msg != "")
                    {
                        //std::cout << MessageLoop->Get_Message().Get_Message() << std::endl;
                        MessageLoop->Create_Message(Msg);
                    }
                }
            }
        }
        while(Next_Element());
    }
}
void CUI_Surface::Clear_UI()
{
    Last_Element();
    do
    {
        if(Surface->Prev)
        {
            Prev_Element();
            delete Surface->Next->UI_Element;
            Surface->Next->UI_Element = 0;
            Surface->Next->Prev = 0;
            delete Surface->Next;
            Surface->Next = 0;
        }
        else if(Surface->Next == 0 && Surface->Prev == 0 && Surface)
        {
            delete Surface->UI_Element;
            Surface->UI_Element = 0;
            delete Surface;
            Surface = 0;
        }
    }
    while(Surface->Prev);

}
CUI_Surface::~CUI_Surface()
{
    std::cout << "UI löschen." << std::endl;
    if(Surface)
    {
        Clear_UI();
    }
    std::cout << "... Beendet." << std::endl;
}
St_UISurface* CUI_Surface::Get_Surface_Element(std::string Command)
{
    First_Element();
    do
    {   // überprüft ob eines der Element diese Nachricht enthält
        if(Surface->UI_Element->Get_LMB_Msg() == Command || Surface->UI_Element->Get_MouseOver_Msg() == Command || Surface->UI_Element->Get_RMB_Msg() == Command)
        {
            return Surface;
        }
    }
    while (Next_Element());
    return 0;
}
void CUI_Surface::Save_UI(std::string FilePath)
{
    int Count = 0;
    CUI_Button* Button = 0;
    CUI_Text* Text = 0;
    First_Element();
    if(Surface)
    {
        do
        {
            Count++;
        }
        while(Next_Element());
    }
    std::cout << Count << " Elemente. " << std::endl;
    std::ofstream File;
    File.open(FilePath.c_str(), std::ios::out | std::ios::binary);
    File.write((char*)&Count,sizeof(Count));
    unsigned int Save1 = 0;
	unsigned int Save2 = 0;
	unsigned int Save3 = 0;
	unsigned int Save4 = 0;
	unsigned int Save5 = 0;
	bool Save6 = false;
	bool Save7 = false;
	bool Save8 = false;
    for (int i = 0;i<Count; i++)
    {
        if(Surface->UI_Element->Get_UI_Type() == UIT_BUTTON)
        {
            Button = static_cast<CUI_Button*>(Surface->UI_Element);
            File.write((char*)UIT_BUTTON, sizeof(UI_Type));
            File.write((char*)Button->Get_ArrayNumber(), sizeof(int));

        }
        else if(Surface->UI_Element->Get_UI_Type() == UIT_TEXT)
        {
            Text = static_cast<CUI_Text*>(Surface->UI_Element);
            File.write((char*)UIT_TEXT, sizeof(UI_Type));
        }
    }
    File.close();
}
#ifdef LOGFILE
void CUI_Surface::Set_LogFile(CLogFile* logfile)
{
    LogFile = logfile;
    *LogFile << "Setzen des LogFiles (" << LogFile << ") für die UI_Surface Klasse." << CLogFile::endl();
}
#endif
