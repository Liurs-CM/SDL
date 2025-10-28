#include "defs.h"
#include "Game.h"
#include <iostream>

Game* Game::s_pInstance = 0;

bool Game::init(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen)
{
    if( SDL_Init(SDL_INIT_EVERYTHING) >= 0 )
    {
        int flags = 0;
        if(fullscreen)
        { 
            flags = SDL_WINDOW_FULLSCREEN; 
        }
        std::cout << "SDL init success\n";
        m_pWindow = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);
        if(m_pWindow != 0)
        {
            std::cout << "window creation success\n";
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
            if(m_pRenderer != 0)
            {
                std::cout << "renderer creation success\n";
                SDL_SetRenderDrawColor(m_pRenderer, 128, 128, 128, 255);
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
        std::cout << "SDL init fail!\nSDL ERROR: " << SDL_GetError();
        return false;
    }

    std::cout << "init success\n";
    m_bRunning = true;

    return true;
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer);
    SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
}

void Game::handleEvents()
{
    SDL_Event event;
    if(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
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

void Game::syncFPS()
{
    frameTime = SDL_GetTicks() - frameStart;
    if(frameTime < DELAY_TIME)
    {
        SDL_Delay((int)(DELAY_TIME - frameTime));
    }
    frameStart = SDL_GetTicks();
}
