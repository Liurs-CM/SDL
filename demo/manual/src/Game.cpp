#include "defs.h"
#include "Game.h"
#include "SDL_image.h"
#include "TextureManager.h"
#include "InputHandler.h"
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

    pos = Vector2D(100,100);
    TheInputHandler::Instance()->initialiseJoysticks();
    std::cout << "init success\n";
    m_bRunning = true;

    if(!TheTextureManager::Instance()->load("assets/pilot.png", "pilot", m_pRenderer))
    {
        std::cout << "load img to texture fail\n";
        return false;
    }
    if(!TheTextureManager::Instance()->load("assets/bullet.png", "bullet", m_pRenderer))
    {
        std::cout << "load img to texture fail\n";
        return false;
    }

    return true;
}

void Game::render()
{
    SDL_RenderClear(m_pRenderer);
    TheTextureManager::Instance()->draw("pilot", pos.getX(), pos.getY(), 64, 64, m_pRenderer);
    TheTextureManager::Instance()->draw("bullet", bulletPos.getX()-7, bulletPos.getY()-7, 16, 16, m_pRenderer);
    SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
    TheInputHandler::Instance()->update();
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_W))
    {
        pos += Vector2D(0,-1);
        //std::cout << pos << "move up\n";
    }
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_S))
    {
        pos += Vector2D(0,1);
        //std::cout << pos << "move down\n";
    }
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_A))
    {
        pos += Vector2D(-1,0);
        //std::cout << pos << "move left\n";
    }
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D))
    {
        pos += Vector2D(1,0);
        //std::cout << pos << "move right\n";
    }
    bulletPos += Vector2D(2,0);
    if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
    {
        bulletPos = pos;
        bulletPos += Vector2D(32, 32);
        //std::cout << pos << "move up\n";
    }
}

void Game::handleEvents()
{
    TheInputHandler::Instance()->update();
}

void Game::clean()
{
    std::cout << "cleaning game\n";
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    TheInputHandler::Instance()->clean();
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
