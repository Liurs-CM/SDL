#include <iostream>
#include "Game.h"

int main(int argc, char* argv[])
{
    std::cout << "game initing...\n";
    if(TheGame::Instance()->init("Chapter 3", 1000, 500, 640, 480, false))
    {
        std::cout << "game init success!\n";
        while(TheGame::Instance()->running())
        {
            TheGame::Instance()->handleEvents();
            TheGame::Instance()->update();
            TheGame::Instance()->render();
            SDL_Delay(10);
        }
    }
    else
    {
        std::cout << "game init failure - " << SDL_GetError() << "\n";
        return -1;
    }
    std::cout << "game closing...\n";
    TheGame::Instance()->clean();

    return 0;
}
