#include "CGameEngine.h"

#ifdef LOGFILE
CLogFile* CGameEngine::LogFile = 0;
#endif

CGameEngine::CGameEngine()
{
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_GREEN;
        *LogFile << "CGameEngine" << this << ": Aufruf des Konstruktor." << CLogFile::endl();
        *LogFile << "CGameEngine" << this << ": (CRessourcenManager) RessourcenManager erstellt(" << &RessourcenManager << ")" << CLogFile::endl();
        *LogFile << "CGameEngine" << this << ": (CIsoMap) IsoMap erstellt(" << &IsoMap << ")" << CLogFile::endl();
        *LogFile << "CGameEngine" << this << ": (CGameStateStack) GameStateStack erstellt(" << &GameStateStack << ")" << CLogFile::endl();
        *LogFile << "CGameEngine" << this << ": (CMessageLoop) Loop erstellt(" << &Loop << ")" << CLogFile::endl();
        *LogFile << "CGameEngine" << this << ": (CWindowHandle) Window erstellt(" << &Window << ")" << CLogFile::endl();
    }
    #endif
    // Ressourcen Manager für die Spritesheet klasse setzen
    CSpriteSheet::Set_RessourcenManager(&RessourcenManager);
    // Vorläufige Init des Fensters
    Window.Set_FullScreen(false);
    Window.Select_VideoMode(1);
    Window.Set_WindowName("Swashbuckler");
    Window.Create_Window();
    // Übergeben des InputHandlers
    InputHandle = Window.Get_Input_as_Pointer();
    // Erstellen des EventHandlers
    EventHandler = new sf::Event;
    // Maus ausschalten
    Switch_Mouse_On(false);
    // InputHandle für UI
    CUI_Surface::Set_Input(InputHandle);
    // MessageLoop für UI
    CUI_Surface::Set_MessageLoop(&Loop);
    //neue Mouse Icon
    Mouse = new CMouse(InputHandle);
    Mouse->Set_MouseImage("Spritesheet/Mouse Set.png");
    Mouse->Set_Animation(5,9,20,0.2f);
    Mouse->Animation_On(true);
    IsoMap.Creat_RandomMap(50,50,15,10,75,25);
    SceneGraph = new CSceneGraph(&Window);
    // Spiel Status
    CState StartState;
    StartState.Set_Transparency(false);
    StartState.Set_State(SM_GAMEQUIT);
    GameStateStack.Add_State(StartState);
    StartState.Set_State(SM_MAINMENU);
    GameStateStack.Add_State(StartState);
    StartState.Set_State(SM_INTRO);
    GameStateStack.Add_State(StartState);
    // Setzt den Gamestatus für den Scenegraph
    SceneGraph->Set_GameState(&GameStateStack);
    // fügt der Scene die Maus hinzu
    SceneGraph->Add_to_Scene(Mouse);
    // UI für das Hauptmenü noch nicht gesetzt
    MainMenu_UI = 0;
    Option_UI = 0;
    Game_UI = 0;
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << LFF_GREEN;
        *LogFile << "CGameEngine" << this << ": Verlassen des Konstruktors." << CLogFile::endl();
    }
    #endif
}
CGameEngine::~CGameEngine()
{
    //Inputhandler Reseten
    InputHandle = 0;
    std::cout << "GameEngine Destruktor" << std::endl;
    if(Mouse)
    {
        std::cout << "Mouse Löschen" << std::endl;
        delete Mouse;
        Mouse = 0;
        std::cout << "Mouse Löschen beendet" << std::endl;
    }
    //Eventhandler löschen
    if(EventHandler)
    {
        std::cout << "EvebtHandle Löschen" << std::endl;
        delete EventHandler;
        EventHandler = 0;
        std::cout << "EvebtHandle Löschen beendet" << std::endl;
    }
    if(SceneGraph)
    {
        delete SceneGraph;
        SceneGraph = 0;
    }
    if(MainMenu_UI)
    {
        delete MainMenu_UI;
        MainMenu_UI = 0;
    }
    if(Option_UI)
    {
        delete Option_UI;
        Option_UI = 0;
    }
}
CState CGameEngine::GameLoop()
{
    if(Game_UI == 0)
    {
        Init_GameUI();
    }
    else
    {
        SceneGraph->Add_to_Scene(Game_UI);
    }
    int X = 25;
    int Y = 20;
    CState nState;
    SceneGraph->Add_to_Scene(&IsoMap);
    SceneGraph->Set_Map_Center(X,Y);
    while (Window.Get_Window_as_Pointer()->IsOpened())
     {
         while (Window.Get_Window_as_Pointer()->GetEvent(*EventHandler))
         {
             // Close window : exit
             if (EventHandler->Type == sf::Event::Closed)
                 Window.Get_Window_as_Pointer()->Close();
            if(EventHandler->Type == sf::Event::MouseButtonPressed)
                IsoMap.Rotate_AntiClockwise();
         }
         if(InputHandle->IsKeyDown(sf::Key::S))
         {
             Y++;
             std::cout << "S";
             SceneGraph->Set_Map_Center(X,Y);
         }
         if(InputHandle->IsKeyDown(sf::Key::W))
         {
             Y--;
             std::cout << "W";
             SceneGraph->Set_Map_Center(X,Y);
         }
         if(InputHandle->IsKeyDown(sf::Key::D))
         {
             X++;
             std::cout << "D";
             SceneGraph->Set_Map_Center(X,Y);
         }
         if(InputHandle->IsKeyDown(sf::Key::A))
         {
             X--;
             std::cout << "A";
             SceneGraph->Set_Map_Center(X,Y);
         }
         if(InputHandle->IsKeyDown(sf::Key::B))
         {
             this->Capture_Screenshot();
             nState.Set_State(SM_REMOVELASTSTATE);
             nState.Set_Transparency(false);
             return nState;
         }
         if(Check_UI_Input(Game_UI))
         {
             return CState();
         }
         // Clear screen
         Window.Get_Window_as_Pointer()->Clear();
         //
         SceneGraph->Render_Scene();
         //Window.Get_Window_as_Pointer()->Draw(Mouse->Mouse_Update());
         // Update the window
         Window.Get_Window_as_Pointer()->Display();
     }
     return CState();
}
int CGameEngine::MainLoop()
{
    CState nState;
    while (Window.Get_Window_as_Pointer()->IsOpened())
    {
         while (Window.Get_Window_as_Pointer()->GetEvent(*EventHandler))
         {
             // Close window : exit
             if (EventHandler->Type == sf::Event::Closed)
                 Window.Get_Window_as_Pointer()->Close();
         }
         switch(GameStateStack.Get_State()->Get_State())
         {
             case SM_GAME:
                nState = GameLoop();
                GameStateStack.Add_State(nState);
             break;
             case SM_INTRO:
                std::cout << "Der Zeit kein Intro vorhanden." << std::endl;
                GameStateStack.Remove_State();
             break;
             case SM_OPTION:
                std::cout << "Im Optionmenü" << std::endl;
                nState = OptionLoop();
                GameStateStack.Add_State(nState);
             break;
             case SM_OUTRO:
                std::cout << "Der Zeit kein Outro vorhanden." << std::endl;
                GameStateStack.Get_State()->Set_State(SM_MAINMENU);
                GameStateStack.Get_State()->Set_Transparency(false);
             break;
             case SM_MAINMENU:
                std::cout << "Im Hauptmenü" << std::endl;
                SceneGraph->Remove_from_Scene(&IsoMap);
                nState = MainMenuLoop();
                GameStateStack.Add_State(nState);
             break;
             case SM_REMOVELASTSTATE:
             std::cout << "Entferne Status" << std::endl;
                GameStateStack.Remove_State();
                GameStateStack.Remove_State();
             break;
             case SM_GAMEQUIT:
                std::cout << "Spiel Beenden" << std::endl;
                return 0;
             break;
             case SM_NOTHING:
                GameStateStack.Remove_State();
             break;
             default:
             break;
         }
     }
    return 0;
}
CState CGameEngine::MainMenuLoop()
{
    if(MainMenu_UI == 0)
    {
        Init_MainMenu();
    }
    else
    {
        SceneGraph->Add_to_Scene(MainMenu_UI);
    }
    CState nState;
    while (Window.Get_Window_as_Pointer()->IsOpened())
    {
         while (Window.Get_Window_as_Pointer()->GetEvent(*EventHandler))
         {
             // Close window : exit
             if (EventHandler->Type == sf::Event::Closed)
                 Window.Get_Window_as_Pointer()->Close();
         }
         if(InputHandle->IsKeyDown(sf::Key::Escape))
         {
             nState.Set_State(SM_REMOVELASTSTATE);
             nState.Set_Transparency(false);
             return nState;
         }
         //
         if(Check_UI_Input(MainMenu_UI))
         {
             return CState();
         }
         // Clear screen
         Window.Get_Window_as_Pointer()->Clear();
         // Render Scene
         SceneGraph->Render_Scene();
         // Update the window
         Window.Get_Window_as_Pointer()->Display();
    }
    nState.Set_State(SM_GAMEQUIT);
    return nState;
}
CState CGameEngine::OptionLoop()
{
    if(Option_UI == 0)
    {
        Init_OptionMenu();
    }
    else
    {
        SceneGraph->Add_to_Scene(Option_UI);
    }
    CState nState;
    while (Window.Get_Window_as_Pointer()->IsOpened())
    {
         while (Window.Get_Window_as_Pointer()->GetEvent(*EventHandler))
         {
             // Close window : exit
             if (EventHandler->Type == sf::Event::Closed)
                 Window.Get_Window_as_Pointer()->Close();
         }
         if(InputHandle->IsKeyDown(sf::Key::Escape))
         {
             nState.Set_State(SM_REMOVELASTSTATE);
             nState.Set_Transparency(false);
             return nState;
         }
         if(Check_UI_Input(Option_UI))
         {
             return CState();
         }
         Window.Get_Window_as_Pointer()->Clear();
         // Render Scene
         SceneGraph->Render_Scene();
         // Update the window
         Window.Get_Window_as_Pointer()->Display();
    }
    nState.Set_State(SM_GAMEQUIT);
    return nState;
}
void CGameEngine::Init_MainMenu()
{
    if(MainMenu_UI == 0)
    {
        MainMenu_UI = new CUI_Surface;
        CUI_Button Button;
        Button.Load_SpriteSheet("Spritesheet/Menu Set 1.png",256,128);
        Button.Set_ArrayNummber(1);
        Button.Set_LMB_Msg("SpielenKlick");
        Button.Set_Position(Window.Get_Window_as_Pointer()->GetWidth() / 2 - 128 , (Window.Get_Window_as_Pointer()->GetHeight() - 4*128) / 2);
        MainMenu_UI->Add_Element(Button);
        Button.Set_ArrayNummber(2);
        Button.Set_LMB_Msg("OptionKlick");
        Button.Set_Position(Window.Get_Window_as_Pointer()->GetWidth() / 2 - 128 , (Window.Get_Window_as_Pointer()->GetHeight() - 4*128) / 2 + 128);
        MainMenu_UI->Add_Element(Button);
        Button.Set_ArrayNummber(4);
        Button.Set_LMB_Msg("IntroKlick");
        Button.Set_Position(Window.Get_Window_as_Pointer()->GetWidth() / 2 - 128 , (Window.Get_Window_as_Pointer()->GetHeight() - 4*128) / 2 + 256);
        MainMenu_UI->Add_Element(Button);
        Button.Set_ArrayNummber(3);
        Button.Set_LMB_Msg("EndeKlick");
        Button.Set_Position(Window.Get_Window_as_Pointer()->GetWidth() / 2 - 128 , (Window.Get_Window_as_Pointer()->GetHeight() - 4*128) / 2 + 384);
        MainMenu_UI->Add_Element(Button);
        GameStateStack.Get_State()->Set_Init(true);
        SceneGraph->Add_to_Scene(MainMenu_UI);
    }
}
void CGameEngine::Init_OptionMenu()
{
    if(Option_UI == 0)
    {
        Option_UI = new CUI_Surface;
        CUI_Button Button;
        CUI_Text Text;
        int TextCoordX = 30 ,TextCoordY = 152;
        Text.Load("Font/ModerneFraktur.ttf",29.0f,sf::String::Regular);
        Button.Load_SpriteSheet("Spritesheet/Menu Set 2.png",32,45);
        //
        Text.Set_Text("Bildschirm Auflösung");
        Text.Set_Position(TextCoordX,TextCoordY - 50);
        Text.Set_Color(sf::Color::White);
        Option_UI->Add_Element(Text);
        // 800 x 600 Fenstergröße
        int c = Window.VideoMode_Possible(800,600,32);
        if(c != -1 )
        {
            Button.Set_ArrayNummber(4);
            Button.Set_Position(TextCoordX - 50 + 32,TextCoordY - 2);
            Button.Set_LMB_Msg("800x600x32.Button1");
            Option_UI->Add_Element(Button);
            Button.Set_ArrayNummber(5);
            Button.Set_Position(TextCoordX - 50 + 32 + 32,TextCoordY - 2);
            Button.Set_LMB_Msg("800x600x32.Button2");
            Option_UI->Add_Element(Button);
            Button.Set_ArrayNummber(5);
            Button.Set_Position(TextCoordX - 50 + 64 + 32,TextCoordY - 2);
            Button.Set_LMB_Msg("800x600x32.Button3");
            Option_UI->Add_Element(Button);
            Button.Set_ArrayNummber(5);
            Button.Set_Position(TextCoordX - 50 + 96 + 32,TextCoordY - 2);
            Button.Set_LMB_Msg("800x600x32.Button4");
            Option_UI->Add_Element(Button);
            Button.Set_ArrayNummber(5);
            Button.Set_Position(TextCoordX - 50 + 128 + 32,TextCoordY - 2);
            Button.Set_LMB_Msg("800x600x32.Button5");
            Option_UI->Add_Element(Button);
            Button.Set_ArrayNummber(5);
            Button.Set_Position(TextCoordX - 50 + 160 + 32,TextCoordY - 2);
            Button.Set_LMB_Msg("800x600x32.Button6");
            Option_UI->Add_Element(Button);
            Button.Set_ArrayNummber(6);
            Button.Set_Position(TextCoordX - 50 + 192 + 32,TextCoordY - 2);
            Button.Set_LMB_Msg("800x600x32.Button7");
            Option_UI->Add_Element(Button);
            Text.Set_Position(TextCoordX,TextCoordY);
            Text.Set_LMB_Msg("800x600x32.txt");
            Text.Set_MouseOver_Msg("800x600x32.MO");
            Text.Set_Text("800 x 600 x 32");
            if (Window.Get_VideoMode().Height == 600)
            {
                Text.Set_Color(sf::Color::Blue);
            }
            else
            {
                Text.Set_Color(sf::Color::Yellow);
            }
            Option_UI->Add_Element(Text);
            TextCoordY = TextCoordY +50;
        }
        // 1024 x 768 Fenstergröße
        c = Window.VideoMode_Possible(1024,768,32);
        if (c != -1)
        {
            Button.Set_ArrayNummber(4);
            Button.Set_Position(TextCoordX - 50 + 32,TextCoordY - 2);
            Button.Set_LMB_Msg("1024x768x32.Button1");
            Option_UI->Add_Element(Button);
            Button.Set_ArrayNummber(5);
            Button.Set_Position(TextCoordX - 50 + 32 + 32,TextCoordY - 2);
            Button.Set_LMB_Msg("1024x768x32.Button2");
            Option_UI->Add_Element(Button);
            Button.Set_ArrayNummber(5);
            Button.Set_Position(TextCoordX - 50 + 64 + 32,TextCoordY - 2);
            Button.Set_LMB_Msg("1024x768x32.Button3");
            Option_UI->Add_Element(Button);
            Button.Set_ArrayNummber(5);
            Button.Set_Position(TextCoordX - 50 + 96 + 32,TextCoordY - 2);
            Button.Set_LMB_Msg("1024x768x32.Button4");
            Option_UI->Add_Element(Button);
            Button.Set_ArrayNummber(5);
            Button.Set_Position(TextCoordX - 50 + 128 + 32,TextCoordY - 2);
            Button.Set_LMB_Msg("1024x768x32.Button5");
            Option_UI->Add_Element(Button);
            Button.Set_ArrayNummber(5);
            Button.Set_Position(TextCoordX - 50 + 160 + 32,TextCoordY - 2);
            Button.Set_LMB_Msg("1024x768x32.Button6");
            Option_UI->Add_Element(Button);
            Button.Set_ArrayNummber(6);
            Button.Set_Position(TextCoordX - 50 + 192 + 32,TextCoordY - 2);
            Button.Set_LMB_Msg("1024x768x32.Button7");
            Option_UI->Add_Element(Button);
            Text.Set_Position(TextCoordX,TextCoordY);
            Text.Set_LMB_Msg("1024x768x32.txt");
            Text.Set_MouseOver_Msg("1024x768x32.MO");
            Text.Set_Text("1024 x 768 x 32");
            if (Window.Get_VideoMode().Height == 768)
            {
                Text.Set_Color(sf::Color::Blue);
            }
            else
            {
                Text.Set_Color(sf::Color::Yellow);
            }
            Option_UI->Add_Element(Text);
            TextCoordY = TextCoordY + 50;
        }
        // 1600 x 900 Fenstergröße
        c = Window.VideoMode_Possible(1600,900,32);
        if (c != -1)
        {

            Button.Set_ArrayNummber(4);
            Button.Set_Position(TextCoordX - 50 + 32,TextCoordY - 2);
            Button.Set_LMB_Msg("1600x900x32.Button1");
            Option_UI->Add_Element(Button);
            Button.Set_ArrayNummber(5);
            Button.Set_Position(TextCoordX - 50 + 32 + 32,TextCoordY - 2);
            Button.Set_LMB_Msg("1600x900x32.Button2");
            Option_UI->Add_Element(Button);
            Button.Set_ArrayNummber(5);
            Button.Set_Position(TextCoordX - 50 + 64 + 32,TextCoordY - 2);
            Button.Set_LMB_Msg("1600x900x32.Button3");
            Option_UI->Add_Element(Button);
            Button.Set_ArrayNummber(5);
            Button.Set_Position(TextCoordX - 50 + 96 + 32,TextCoordY - 2);
            Button.Set_LMB_Msg("1600x900x32.Button4");
            Option_UI->Add_Element(Button);
            Button.Set_ArrayNummber(5);
            Button.Set_Position(TextCoordX - 50 + 128 + 32,TextCoordY - 2);
            Button.Set_LMB_Msg("1600x900x32.Button5");
            Option_UI->Add_Element(Button);
            Button.Set_ArrayNummber(5);
            Button.Set_Position(TextCoordX - 50 + 160 + 32,TextCoordY - 2);
            Button.Set_LMB_Msg("1600x900x32.Button6");
            Option_UI->Add_Element(Button);
            Button.Set_ArrayNummber(6);
            Button.Set_Position(TextCoordX - 50 + 192 + 32,TextCoordY - 2);
            Button.Set_LMB_Msg("1600x900x32.Button7");
            Option_UI->Add_Element(Button);
            Text.Set_Position(TextCoordX,TextCoordY);
            Text.Set_LMB_Msg("1600x900x32.txt");
            Text.Set_MouseOver_Msg("1600x900x32.MO");
            Text.Set_Text("1600 x 900 x 32");
            if (Window.Get_VideoMode().Height == 900)
            {
                Text.Set_Color(sf::Color::Blue);
            }
            else
            {
                Text.Set_Color(sf::Color::Yellow);
            }
            Option_UI->Add_Element(Text);
            TextCoordY = TextCoordY + 50;
        }
        // Text Fenstermodus
        Text.Set_LMB_Msg("Fenstermodus.txt");
        Text.Set_MouseOver_Msg("Fenstermodus.MO");
        Text.Set_Position(TextCoordX + 32 ,TextCoordY);
        Text.Set_Color(sf::Color::White);
        Text.Set_Text("Fenstermodus");
        Option_UI->Add_Element(Text);
        Button.Set_LMB_Msg("Fenstermodus.Button");
        Button.Set_Position(TextCoordX ,TextCoordY);
        if(Window.Get_FullScreen())
        {
            Button.Set_ArrayNummber(3);
        }
        else
        {
            Button.Set_ArrayNummber(7);
        }
        Option_UI->Add_Element(Button);
        // Text Vollbild
        TextCoordY = TextCoordY + 50;
        Text.Set_LMB_Msg("Vollbild.txt");
        Text.Set_MouseOver_Msg("Vollbild.MO");
        Text.Set_Position(TextCoordX + 32,TextCoordY);
        Text.Set_Text("Vollbild");
        Option_UI->Add_Element(Text);
        Button.Set_LMB_Msg("Vollbild.Button");
        Button.Set_Position(TextCoordX ,TextCoordY);
        if(Window.Get_FullScreen())
        {
            Button.Set_ArrayNummber(7);
        }
        else
        {
            Button.Set_ArrayNummber(3);
        }
        Option_UI->Add_Element(Button);
        Text.Set_LMB_Msg("");
        Text.Set_MouseOver_Msg("");
        // Sound + Musik
        Button.Set_ArrayNummber(2);
        Button.Set_Position(10,10);
        Button.Set_LMB_Msg("SoundFXMinus");
        Option_UI->Add_Element(Button);
        // Sound - Musik
        Button.Set_ArrayNummber(1);
        Button.Set_Position(158,10);
        Button.Set_LMB_Msg("SoundFXPlus");
        Option_UI->Add_Element(Button);
        Text.Set_Color(sf::Color::White);
        Text.Set_Text("Volume Musik");
        Text.Set_Position(195,14);
        Option_UI->Add_Element(Text);
        // Balken Sound
        Button.Set_LMB_Msg("");
        Button.Set_ArrayNummber(17);
        Button.Set_Position(52,10);
        Option_UI->Add_Element(Button);
        Button.Set_ArrayNummber(18);
        Button.Set_Position(84,10);
        Option_UI->Add_Element(Button);
        Button.Set_ArrayNummber(19);
        Button.Set_Position(116,10);
        Option_UI->Add_Element(Button);
        Button.Set_ArrayNummber(11);
        Button.Set_Position(116,10);
        Button.Set_LMB_Msg("ReglerFX");
        Option_UI->Add_Element(Button);
        // Sound + FX
        Button.Set_ArrayNummber(2);
        Button.Set_Position(10,50);
        Button.Set_LMB_Msg("SoundMusikMinus");
        Option_UI->Add_Element(Button);
        // Sound - FX
        Button.Set_ArrayNummber(1);
        Button.Set_Position(158,50);
        Button.Set_LMB_Msg("SoundMusikPlus");
        Option_UI->Add_Element(Button);
        Text.Set_Text("Volume FX");
        Text.Set_Position(195,54);
        Option_UI->Add_Element(Text);
        // Balken Sound
        Button.Set_LMB_Msg("");
        Button.Set_ArrayNummber(17);
        Button.Set_Position(52,50);
        Option_UI->Add_Element(Button);
        Button.Set_ArrayNummber(18);
        Button.Set_Position(84,50);
        Option_UI->Add_Element(Button);
        Button.Set_ArrayNummber(19);
        Button.Set_Position(116,50);
        Option_UI->Add_Element(Button);
        Button.Set_ArrayNummber(11);
        Button.Set_Position(116,50);
        Button.Set_LMB_Msg("ReglerMusik");
        Option_UI->Add_Element(Button);
        // Hauptmenü Knopf
        TextCoordY = 550;
        Button.Set_ArrayNummber(8);
        Button.Set_Position(400 - 50 + 32,TextCoordY - 2);
        Button.Set_LMB_Msg("Hauptmenü.Button");
        Button.Set_MouseOver_Msg("");
        Option_UI->Add_Element(Button);
        Button.Set_ArrayNummber(9);
        Button.Set_Position(400 - 50 + 32 + 32,TextCoordY - 2);
        Button.Set_LMB_Msg("Hauptmenü.Button");
        Option_UI->Add_Element(Button);
        Button.Set_ArrayNummber(9);
        Button.Set_Position(400 - 50 + 64 + 32,TextCoordY - 2);
        Button.Set_LMB_Msg("Hauptmenü.Button");
        Option_UI->Add_Element(Button);
        Button.Set_ArrayNummber(9);
        Button.Set_Position(400 - 50 + 96 + 32,TextCoordY - 2);
        Button.Set_LMB_Msg("Hauptmenü.Button");
        Option_UI->Add_Element(Button);
        Button.Set_ArrayNummber(9);
        Button.Set_Position(400 - 50 + 128 + 32,TextCoordY - 2);
        Button.Set_LMB_Msg("Hauptmenü.Button");
        Option_UI->Add_Element(Button);
        Button.Set_ArrayNummber(9);
        Button.Set_Position(400 - 50 + 160 + 32,TextCoordY - 2);
        Button.Set_LMB_Msg("Hauptmenü.Button");
        Option_UI->Add_Element(Button);
        Button.Set_ArrayNummber(10);
        Button.Set_Position(400 - 50 + 192 + 32,TextCoordY - 2);
        Button.Set_LMB_Msg("Hauptmenü.Button");
        Option_UI->Add_Element(Button);
        Text.Set_LMB_Msg("Hauptmenue.txt");
        Text.Set_MouseOver_Msg("");
        Text.Set_Text("Hauptmenü");
        Text.Set_Position(423,TextCoordY);
        Option_UI->Add_Element(Text);
        GameStateStack.Get_State()->Set_Init(true);
        SceneGraph->Add_to_Scene(Option_UI);
        Option_UI->Save_UI("Test.UI");
    }
}
void CGameEngine::Init_GameUI()
{
    if(Game_UI == 0)
    {
        Game_UI = new CUI_Surface;
        CUI_Text Text;
        Text.Load("Font/ModerneFraktur.ttf",29.0f,sf::String::Regular);
        Text.Set_Text("Koschi was here!!!");
        Game_UI->Add_Element(Text);
        Text.Set_Color(sf::Color::Blue);
        Text.Set_Position(0,100);
        Text.Set_Style(sf::String::Underlined);
        Text.Set_Text("Test");
        Text.Set_Size(11.0);
        Game_UI->Add_Element(Text);
        GameStateStack.Get_State()->Set_Init(true);
        SceneGraph->Add_to_Scene(Game_UI);
    }
}
void CGameEngine::Switch_Mouse_On(bool Value)
{
    Window.Get_Window_as_Pointer()->ShowMouseCursor(Value);
}
bool CGameEngine::Check_UI_Input(CUI_Surface* UI)
{
    UI->Check_Element();
    CState nState;
    std::string Msg = Loop.Get_Message().Get_Message();
    //std::cout << Msg << std::endl;
    // Abfrage für das Main User Interface
    if(UI == MainMenu_UI)
    {
        if(Msg == "EndeKlick")
        {
            std::cout << "EndeKlick: Gamestat neu setzen" << std::endl;
            nState.Set_State(SM_REMOVELASTSTATE);
            nState.Set_Transparency(false);
            GameStateStack.Add_State(nState);
            return true;
        }
        else if(Msg == "SpielenKlick")
        {
            std::cout << "SpielenKlick: Gamestat neu setzen" << std::endl;
            nState.Set_State(SM_GAME);
            nState.Set_Transparency(false);
            GameStateStack.Add_State(nState);
            SceneGraph->Remove_from_Scene(MainMenu_UI);
            return true;
        }
        else if(Msg == "OptionKlick")
        {
            std::cout << "OptionKlick: Gamestat neu setzen" << std::endl;
            nState.Set_State(SM_OPTION);
            nState.Set_Transparency(false);
            GameStateStack.Add_State(nState);
            return true;
        }
        else if(Msg == "IntroKlick")
        {
            std::cout << "IntroKlick: Gamestat neu setzen" << std::endl;
            nState.Set_State(SM_INTRO);
            nState.Set_Transparency(false);
            GameStateStack.Add_State(nState);
            return true;
        }
        return false;
    }
    // Abfrage für das Option User Interface
    else if(UI == Option_UI)
    {
        if(Msg == "SoundFXMinus")
        {
            CUI_Base* Temp_Element = Option_UI->Get_Surface_Element("ReglerFX")->UI_Element;
            int X_Value = Temp_Element->Get_Offset_X()-1;
            if(X_Value > 42)
            {
                Temp_Element->Set_Position(X_Value,Temp_Element->Get_Offset_Y());
            }
        }
        else if (Msg == "SoundFXPlus")
        {
            CUI_Base* Temp_Element = Option_UI->Get_Surface_Element("ReglerFX")->UI_Element;
            int X_Value = Temp_Element->Get_Offset_X()+1;
            if(X_Value < 128)
            {
                Temp_Element->Set_Position(X_Value,Temp_Element->Get_Offset_Y());
            }
        }
        else if (Msg == "SoundMusikMinus")
        {
            CUI_Base* Temp_Element = Option_UI->Get_Surface_Element("ReglerMusik")->UI_Element;
            int X_Value = Temp_Element->Get_Offset_X()-1;
            if(X_Value > 42)
            {
                Temp_Element->Set_Position(X_Value,Temp_Element->Get_Offset_Y());
            }
        }
        else if (Msg == "SoundMusikPlus")
        {
            CUI_Base* Temp_Element = Option_UI->Get_Surface_Element("ReglerMusik")->UI_Element;
            int X_Value = Temp_Element->Get_Offset_X()+1;
            if(X_Value < 128)
            {
                Temp_Element->Set_Position(X_Value,Temp_Element->Get_Offset_Y());
            }
        }
        else if (Msg == "800x600x32.txt")
        {
            Window.Select_VideoMode(Window.VideoMode_Possible(800,600,32));
            CUI_Text* Temp_Element1 = static_cast <CUI_Text*> (Option_UI->Get_Surface_Element("800x600x32.txt")->UI_Element);
            CUI_Text* Temp_Element2 = static_cast <CUI_Text*> (Option_UI->Get_Surface_Element("1024x768x32.txt")->UI_Element);
            CUI_Text* Temp_Element5 = static_cast <CUI_Text*> (Option_UI->Get_Surface_Element("1600x900x32.txt")->UI_Element);
            if(Temp_Element1)
            {
                Temp_Element1->Set_Color(sf::Color::Blue);
            }
            if(Temp_Element2)
            {
                Temp_Element2->Set_Color(sf::Color::Yellow);
            }
            if(Temp_Element5)
            {
                Temp_Element5->Set_Color(sf::Color::Yellow);
            }
            Window.Create_Window(Window.VideoMode_Possible(800,600,32));
            Switch_Mouse_On(false);
        }
        else if (Msg == "1024x768x32.txt")
        {
            Window.Select_VideoMode(Window.VideoMode_Possible(1024,768,32));
            CUI_Text* Temp_Element2 = static_cast <CUI_Text*> (Option_UI->Get_Surface_Element("800x600x32.txt")->UI_Element);
            CUI_Text* Temp_Element1 = static_cast <CUI_Text*> (Option_UI->Get_Surface_Element("1024x768x32.txt")->UI_Element);
            CUI_Text* Temp_Element5 = static_cast <CUI_Text*> (Option_UI->Get_Surface_Element("1600x900x32.txt")->UI_Element);
            {
                Temp_Element1->Set_Color(sf::Color::Blue);
            }
            if(Temp_Element2)
            {
                Temp_Element2->Set_Color(sf::Color::Yellow);
            }
            if(Temp_Element5)
            {
                Temp_Element5->Set_Color(sf::Color::Yellow);
            }
            Window.Create_Window(Window.VideoMode_Possible(1024,768,32));
            Switch_Mouse_On(false);
        }
        else if (Msg == "1600x900x32.txt")
        {
            Window.Select_VideoMode(Window.VideoMode_Possible(1600,900,32));
            CUI_Text* Temp_Element5 = static_cast <CUI_Text*> (Option_UI->Get_Surface_Element("800x600x32.txt")->UI_Element);
            CUI_Text* Temp_Element2 = static_cast <CUI_Text*> (Option_UI->Get_Surface_Element("1024x768x32.txt")->UI_Element);
            CUI_Text* Temp_Element1 = static_cast <CUI_Text*> (Option_UI->Get_Surface_Element("1600x900x32.txt")->UI_Element);
            if(Temp_Element1)
            {
                Temp_Element1->Set_Color(sf::Color::Blue);
            }
            if(Temp_Element2)
            {
                Temp_Element2->Set_Color(sf::Color::Yellow);
            }
            if(Temp_Element5)
            {
                Temp_Element5->Set_Color(sf::Color::Yellow);
            }
            Window.Create_Window(Window.VideoMode_Possible(1600,900,32));
            Switch_Mouse_On(false);
        }
        else if (Msg == "Vollbild.txt")
        {
            Window.Set_FullScreen(true);
            CUI_Button* Temp_Element1 = static_cast <CUI_Button*> (Option_UI->Get_Surface_Element("Vollbild.Button")->UI_Element);
            CUI_Button* Temp_Element2 = static_cast <CUI_Button*> (Option_UI->Get_Surface_Element("Fenstermodus.Button")->UI_Element);
            if(Temp_Element1)
            {
                Temp_Element1->Set_ArrayNummber(7);
            }
            if(Temp_Element2)
            {
                Temp_Element2->Set_ArrayNummber(3);
            }
            Window.Create_Window();
            Switch_Mouse_On(false);
        }
        else if (Msg == "Fenstermodus.txt")
        {
            Window.Set_FullScreen(false);
            CUI_Button* Temp_Element2 = static_cast <CUI_Button*> (Option_UI->Get_Surface_Element("Vollbild.Button")->UI_Element);
            CUI_Button* Temp_Element1 = static_cast <CUI_Button*> (Option_UI->Get_Surface_Element("Fenstermodus.Button")->UI_Element);
            if(Temp_Element1)
            {
                Temp_Element1->Set_ArrayNummber(7);
            }
            if(Temp_Element2)
            {
                Temp_Element2->Set_ArrayNummber(3);
            }
            Window.Create_Window();
            Switch_Mouse_On(false);
        }
        else if(Msg == "Hauptmenü.Button")
        {
            nState.Set_State(SM_REMOVELASTSTATE);
            nState.Set_Transparency(false);
            GameStateStack.Add_State(nState);
            SceneGraph->Remove_from_Scene(Option_UI);
            return true;
        }
    }
    return false;
}
void CGameEngine::Capture_Screenshot()
{
    Window.Get_Window_as_Pointer()->Capture().SaveToFile("Screenshot.png");
}
#ifdef LOGFILE
void CGameEngine::Set_LogFile(CLogFile* logfile)
{
    LogFile = logfile;
    *LogFile << LFF_AQUA;
    *LogFile << "Setzen des LogFiles (" << LogFile << ") für die GameEngine Klasse." << CLogFile::endl();
}
#endif
