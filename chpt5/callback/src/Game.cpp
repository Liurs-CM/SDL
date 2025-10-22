#include <iostream>
#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "GameStateMachine.h"

Game* Game::s_pInstance = 0;

bool Game::init(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen)
{
    //initialize SDL
    if( SDL_Init(SDL_INIT_EVERYTHING) >= 0 )
    {
		int flags = 0;
		if(fullscreen)
		{
			flags = SDL_WINDOW_FULLSCREEN;
		}
        std::cout << "SDL init success\n";
        //init the window
        m_pWindow = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);
        if( m_pWindow != 0)
        {
            std::cout << "window creation success\n";
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
            if( m_pRenderer != 0)
            {
                std::cout << "renderer creation success\n";
                //SDL_SetRenderDrawColor(m_pRenderer, 128,128,128,255);
                SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
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
	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(new MenuState());

    return true;
}


void Game::render()
{
    //clear the renderer to the draw color on the screen
    SDL_RenderClear(m_pRenderer);

    //loop move texture to render
	m_pGameStateMachine->render();

    //draw to the screen
    SDL_RenderPresent(m_pRenderer);
}

void Game::update()
{
	m_pGameStateMachine->update();
} 

void Game::handleEvents()
{
	TheInputHandler::Instance()->update();
	if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
	{
		m_pGameStateMachine->changeState(new PlayState());
	}
}

void Game::clean()
{
    std::cout << "cleaning game\n";
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
	TheInputHandler::Instance()->clean();
    SDL_Quit();
}

