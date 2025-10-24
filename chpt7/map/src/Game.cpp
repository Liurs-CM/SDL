#include <iostream>
#include <vector>
#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "GameStateMachine.h"
#include "GameObjectFactory.h"
#include "MainMenuState.h"
#include "MenuButton.h"
#include "AnimatedGraphic.h"

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
        std::cout << "SDL init success";
        //init the window
        m_pWindow = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);
        if( m_pWindow != 0)
        {
            std::cout << "window creation success";
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
            if( m_pRenderer != 0)
            {
                std::cout << "renderer creation success";
                //SDL_SetRenderDrawColor(m_pRenderer, 128,128,128,255);
                SDL_SetRenderDrawColor(m_pRenderer, 128, 128, 255, 255);
            }
            else
            {
                std::cout << "renderer init fail";
                return false;
            }
        }
        else
        {
            std::cout << "window init fail";
            return false;
        }
    }
    else
    {
        std::cout << "SDL init fail";
        return false;
    }

	TheInputHandler::Instance()->initialiseJoysticks();

    std::cout << "init success";
    m_bRunning = true;
	TheGameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
	TheGameObjectFactory::Instance()->registerType("Enemy", new EnemyCreator());
	TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
	TheGameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());

	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(new MainMenuState());

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
    std::cout << "cleaning game";
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
	TheInputHandler::Instance()->clean();
    SDL_Quit();
}

