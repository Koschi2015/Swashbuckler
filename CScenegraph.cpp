#include "CScenegraph.h"

CStateStack* CSceneGraph::GameState = 0;

#ifdef LOGFILE
CLogFile* CSceneGraph::LogFile = 0;
#endif

CSceneGraph::CSceneGraph(CWindowHandle* window)
{
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << CLogFile::endl();
        *LogFile << LFF_GREEN;
        *LogFile << "CSceneGraph" << this << ": Aufruf des Konstruktors." << CLogFile::endl();
    }
    #endif
    Window = window->Get_Window_as_Pointer();
    ScreenX = 0;
    ScreenY = 0;
    Local_X = 0;
    Local_Y = 0;
    sf::Rect<float> Rect;
    Rect.Bottom = 1000 + Window->GetHeight();
    Rect.Left = 1000;
    Rect.Right = 1000 + Window->GetWidth();
    Rect.Top = 1000;
    Camera.SetFromRect(Rect);
    Window->SetView(Camera);
    Rect.Bottom = 0 + Window->GetHeight();
    Rect.Left = 0;
    Rect.Right = 0 + Window->GetWidth();
    Rect.Top = 0;
    UI_Camera.SetFromRect(Rect);
    Mouse = 0;
    Map = 0;
    Button = 0;
    GameState = 0;
    #ifdef LOGFILE
    if(LogFile)
    {
        *LogFile << LFF_GREEN;
        *LogFile << "CSceneGraph" << this << ": Verlassen des Konstruktors." << CLogFile::endl();
    }
    #endif
}
CSceneGraph::~CSceneGraph()
{
    Window = 0;
    Map = 0;
    Mouse = 0;
    Button = 0;
}
void CSceneGraph::Add_to_Scene(CMapIso* map)
{
    Map = map;
}
void CSceneGraph::Render_Scene()
{
    if(Map)
    {
        if(Map->Get_GlobalLight())
        {
            // Rendern für Globales Licht
            for(unsigned int i = 0;i<Window->GetWidth()/8 ;i++)
            {
                for(unsigned int j = 0;j<Window->GetHeight()/8;j++)
                {
                    ScreenX = (i)*16.0f+(25-j)*16.0f+1000;
                    ScreenY = (j)*8.0f+(i)*8.0f+1000;
                    Window->SetView(Camera);
                    if(ScreenX < Camera.GetRect().Left-32 || ScreenX > Camera.GetRect().Right || ScreenY < Camera.GetRect().Top-80 || ScreenY > Camera.GetRect().Bottom || i-Local_X < 0|| j-Local_Y < 0 || i-Local_X >= Map->Get_X_Size() || j-Local_Y >= Map->Get_Y_Size())
                    {
                        // Hier nichts machen da Ausserhalb des Bildschirms liegt
                    }
                    else
                    {
                        // Hier wird alles Gerendert was auf dem Bildschirm liegt
                        //if(Map->Tile_in_LOS(Local_X,Local_Y,i-Local_X,j-Local_Y))
                        //{
                            // Hier wird Gerendert wenn Tile in line of sight ist
                            Layer1 = Map->Get_Sprite_Layer_1(i-Local_X,j-Local_Y);
                            Layer2 = Map->Get_Sprite_Layer_2(i-Local_X,j-Local_Y);
                            Layer3 = Map->Get_Sprite_Layer_3(i-Local_X,j-Local_Y);
                            Layer1.SetPosition(ScreenX,ScreenY);
                            Layer2.SetPosition(ScreenX,ScreenY);
                            Layer3.SetPosition(ScreenX,ScreenY);
                            Window->Draw(Layer1);
                            Window->Draw(Layer2);
                            Window->Draw(Layer3);
                        /*}
                        else
                        {
                            // Hier wird nur die Silouete Gerendert
                            Layer1 = Map->Get_Sprite_Layer_1(i-Local_X,j-Local_Y);
                            Layer2 = Map->Get_Sprite_Layer_2(i-Local_X,j-Local_Y);
                            Layer3 = Map->Get_Sprite_Layer_3(i-Local_X,j-Local_Y);
                            Layer2.SetColor(sf::Color(0,0,0));
                            Layer1.SetColor(sf::Color(0,0,0));
                            Layer3.SetColor(sf::Color(0,0,0));
                            Layer1.SetPosition(ScreenX,ScreenY);
                            Layer2.SetPosition(ScreenX,ScreenY);
                            Layer3.SetPosition(ScreenX,ScreenY);
                            Window->Draw(Layer1);
                            Window->Draw(Layer2);
                            Window->Draw(Layer3);
                        }*/
                    }
                }
            }
        }
        else
        {
            for(unsigned int i = 0;i<Window->GetWidth()/8 ;i++)
            {
                for(unsigned int j = 0;j<Window->GetHeight()/8;j++)
                {
                    ScreenX = (i)*16.0f+(25-j)*16.0f+1000;
                    ScreenY = (j)*8.0f+(i)*8.0f+1000;
                    Window->SetView(Camera);
                    if(ScreenX < Camera.GetRect().Left-32 || ScreenX > Camera.GetRect().Right || ScreenY < Camera.GetRect().Top-80 || ScreenY > Camera.GetRect().Bottom || i-Local_X < 0|| j-Local_Y < 0 || i-Local_X >= Map->Get_X_Size() || j-Local_Y >= Map->Get_Y_Size())
                    {
                        // Hier nichts machen da Ausserhalb des Bildschirms liegt
                    }
                    else
                    {
                        // Hier wird alles Gerendert was auf dem Bildschirm liegt
                       // if(Map->Tile_in_LOS(Local_X,Local_Y,i-Local_X,j-Local_Y))
                       // {
                            // Hier wird Gerendert wenn Tile in line of sight ist
                            Shadow = Map->Get_LightSourceIndex(i-Local_X,j-Local_Y);
                            Layer1 = Map->Get_Sprite_Layer_1(i-Local_X,j-Local_Y);
                            Layer2 = Map->Get_Sprite_Layer_2(i-Local_X,j-Local_Y);
                            Layer3 = Map->Get_Sprite_Layer_3(i-Local_X,j-Local_Y);
                            Layer2.SetColor(sf::Color(Shadow,Shadow,Shadow));
                            Layer1.SetColor(sf::Color(Shadow,Shadow,Shadow));
                            Layer3.SetColor(sf::Color(Shadow,Shadow,Shadow));
                            Layer1.SetPosition(ScreenX,ScreenY);
                            Layer2.SetPosition(ScreenX,ScreenY);
                            Layer3.SetPosition(ScreenX,ScreenY);
                            Window->Draw(Layer1);
                            Window->Draw(Layer2);
                            Window->Draw(Layer3);
                        /*}
                        else
                        {
                            // Hier wird nur die Silouete Gerendert
                            Layer1 = Map->Get_Sprite_Layer_1(i-Local_X,j-Local_Y);
                            Layer2 = Map->Get_Sprite_Layer_2(i-Local_X,j-Local_Y);
                            Layer3 = Map->Get_Sprite_Layer_3(i-Local_X,j-Local_Y);
                            //Layer2.SetColor(sf::Color(0,0,0));
                            //Layer1.SetColor(sf::Color(0,0,0));
                            //Layer3.SetColor(sf::Color(0,0,0));
                            Layer1.SetPosition(ScreenX,ScreenY);
                            Layer2.SetPosition(ScreenX,ScreenY);
                            Layer3.SetPosition(ScreenX,ScreenY);
                            Window->Draw(Layer1);
                            Window->Draw(Layer2);
                            Window->Draw(Layer3);
                        } */
                    }
                }
            }
            // Hier wird gerendert wenn kein Globales Licht an ist
            /*for(int i = 0;i<50;i++)
            {
                for(int j = 0;j<50;j++)
                {
                    Shadow = Map->Get_LightSourceIndex(i,j);
                    Layer1 = Map->Get_Sprite_Layer_1(i,j);
                    Layer2 = Map->Get_Sprite_Layer_2(i,j);
                    Layer3 = Map->Get_Sprite_Layer_3(i,j);
                    Layer2.SetColor(sf::Color(Shadow,Shadow,Shadow));
                    Layer1.SetColor(sf::Color(Shadow,Shadow,Shadow));
                    Layer3.SetColor(sf::Color(Shadow,Shadow,Shadow));
                    Layer1.SetPosition(i*16.0f+(Window->GetWidth() / 16-j)*16.0f,j*8.0f+i*8.0f);
                    Layer2.SetPosition(i*16.0f+(Window->GetWidth() / 16-j)*16.0f,j*8.0f+i*8.0f);
                    Layer3.SetPosition(i*16.0f+(Window->GetWidth() / 16-j)*16.0f,j*8.0f+i*8.0f);
                    Window->Draw(Layer1);
                    Window->Draw(Layer2);
                    Window->Draw(Layer3);
                }
            }*/
        }
    }
    /*if(Button)
    {
        Window->SetView(UI_Camera);
        Window->Draw(*Button->Render_Element());
    } */
    if(Surface)
    {
        Window->SetView(UI_Camera);
        // Immer vom ersten Elment zum Letzten Rendern
        Surface->First_Element();
        if(Surface->Get_Surface_Element()->Next == 0)
        {
            do
            {
                Window->Draw(*Surface->Render_Element());
            }
            while(Surface->Prev_Element());
        }
        else if (Surface->Get_Surface_Element()->Prev == 0)
        {
            do
            {
                Window->Draw(*Surface->Render_Element());
            }
            while(Surface->Next_Element());
        }
        else if (Surface->Get_Surface_Element()->Prev && Surface->Get_Surface_Element()->Next)
        {
            while(Surface->Prev_Element());
            do
            {
                Window->Draw(*Surface->Render_Element());
            }
            while(Surface->Next_Element());
        }
    }
    // Rendern der Mouse
    if(Mouse)
    {

        Window->SetView(UI_Camera);
        //Window->Draw(Mouse->Mouse_Update(UI_Camera.GetRect().Left,UI_Camera.GetRect().Top));
        Window->Draw(Mouse->Mouse_Update());
        //Window->Draw(sf::String("Test"));
    }
}
#ifdef LOGFILE
void CSceneGraph::Set_LogFile(CLogFile* logfile)
{
    LogFile = logfile;
    *LogFile << "Setzen des LogFiles (" << LogFile << ") für die SceneGraph Klasse." << CLogFile::endl();
}
#endif
