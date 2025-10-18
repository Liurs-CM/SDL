#include "Game.h"
#include "stdio.h"

bool Game::init(const char* title, int x_pos, int y_pos, int width,
        int height, int flags)
{
    //initialize SDL
    if( SDL_Init(SDL_INIT_EVERYTHING) == )
    {
        std::cout << "SDL init success\n";
        //init the window
        m_pWindow = SDL_CreateWindow(title, x_pos, y_pos,
                width, height, flags);
        if( m_pWindow != 0)
        {
            std::cout << "window creation success\n";
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
            if( m_pRenderer != 0)
            {
                std::cout << "renderer creation success\n";
                SDL_SetRenderDrawColor(m_pRenderer, 
                        255,255,255,255);
            }
            else
            {
                std::cout << "renderer init fail\n";
                return false;
            }
        }
        else
        {
            std::cout << "window init fail\n";
            return false;
        }
    }
    else
    {
        std::cout << "SDL init fail\n";
        return false;
    }

    std::cout << "init success\n";
    m_bRunning = true;

    return true;
}
    
void Game::render()
{
    //clear the renderer to the draw color on the screen
    SDL_RenderClear(m_pRenderer);
    //draw to the screen
    SDL_RenderPresent(m_pRenderer);
}

void Game::handleEvents()
{
    SDL_Event event;
    if( SDL_PollEvent(&event) )
    {
        switch (event.type)
        {
            case SDL_Quit:
                m_bRunning = false;
                break;
            default:
                break;
        }
    }
}

void Game::clean()
{
    std::cout << "cleaning game\n";
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

