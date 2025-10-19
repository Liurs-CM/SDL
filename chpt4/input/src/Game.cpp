#include <iostream>
#include "Game.h"
#include "TextureManager.h"
#include "SDL_image.h"
#include "InputHandler.h"

Game* Game::s_pInstance = 0;

bool Game::init(const char* title, int x_pos, int y_pos, int width,
        int height, int flags)
{
    //initialize SDL
    if( SDL_Init(SDL_INIT_EVERYTHING) >= 0 )
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
                //SDL_SetRenderDrawColor(m_pRenderer, 128,128,128,255);
                SDL_SetRenderDrawColor(m_pRenderer, 255,0,255,255);
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

	TheInputHandler::Instance()->initialiseJoysticks();

    std::cout << "init success\n";
    m_bRunning = true;

    init_obj();

    return true;
}

void Game::init_obj()
{
    if(!TheTextureManager::Instance()->load("assets/animate.png", "animate", m_pRenderer))
    {
        std::cout << "load img to texture fail\n";
    }
    m_gameObjects.push_back(new Player(new LoaderParams(100, 100, 128, 82, "animate")));
    m_gameObjects.push_back(new Enemy(new LoaderParams(300, 300, 128, 82, "animate")));
}

void Game::render()
{
    //clear the renderer to the draw color on the screen
    SDL_RenderClear(m_pRenderer);

    //loop move texture to render
    for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->draw();
    }

    //draw to the screen
    SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
    for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->update();
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

