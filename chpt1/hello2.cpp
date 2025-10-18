#include<SDL.h>
SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;

//create a loop
bool g_bRunning = false;

bool init(const char* title, int x_pos, int y_pos, int height, int width, int flags)
{
    //initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        //create window
        g_pWindow = SDL_CreateWindow(title, x_pos, y_pos, height, width, flags);
        //creation succeeded create our renderer if window creation 
        if(g_pWindow != 0)
        {
            g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
        }
    }
    else
    {
        //sdl could not initialize
        return false;
    }

    return true;
}

void render()
{
    //set to black
    SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);

    //clear the window to black
    SDL_RenderClear(g_pRenderer);

    //show the window
    SDL_RenderPresent(g_pRenderer);
}

int main(int argc, char* argv[])
{
    if( init("Chapter 1: Setting up SDL", 
                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                640, 480, SDL_WINDOW_SHOWN))
    {
        g_bRunning = true;
    }
    else
    {
        return 1;
    }

    while(g_bRunning)
    {
        render();
    }

    //clean up SDL
    SDL_Quit();

    return 0;
}

