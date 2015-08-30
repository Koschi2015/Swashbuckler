#include <SFML/Graphics.hpp>
#include "CGameEngine.h"

int main(int argc, char* argv[])
{
    // ohne Parameter eingabe Spiel Normal Starten
    CGameEngine GameEngine;
    GameEngine.MainLoop();

    return 0;
}
