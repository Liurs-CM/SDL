#include "SDL.h"
#include "defs.h"
#include "struct.h"
#include <iostream>

int main()
{
    if( SDL_INIT_VIDEO < 0 )
    {
        std::cout << "SDL init fail!\nSDL ERROR: " << SDL_GetError();
        return 0;
    }
    memset(&app, 0, sizeof(App));
    app.window = SDL_CreateWindow("SDL2_Window", SCREEN_POS_X, SCREEN_POS_Y, SCREEN_WIDTH, SCREEN_HEIGHT, false);
    if( !app.window )
    {
        std::cout << "SDL create window fail!\nSDL ERROR: " << SDL_GetError();
        SDL_Quit();
        return 0;
    }
    SDL_Delay(2000);
    SDL_DestroyWindow(app.window);
    SDL_Quit();
    return 1;
}
