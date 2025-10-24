#include <iostream>
#include "GameOverState.h"
#include "Game.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "AnimatedGraphic.h"
#include "GameOverState.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "LoaderParams.h"
#include "MenuButton.h"
#include "StateParser.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::update()
{
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
    {
        TheGame::Instance()->getStateMachine()->pushState(new PauseState());
    }
    for(auto* obj : m_gameObjects)
    {
        obj->update();
    }
}

void GameOverState::render()
{
    for(auto* obj : m_gameObjects)
    {
        obj->draw();
    }
}

bool GameOverState::onEnter()
{
    // parse the state
    StateParser stateParser;
    stateParser.parseState("assets/test.xml", s_gameOverID, &m_gameObjects, &m_textureIDList);
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_gameOverToMain);
    m_callbacks.push_back(s_restartPlay);
    // set the callbacks for menu items
    setCallbacks(m_callbacks);
    std::cout << "entering GameOverState\n" << std::endl;
    return true;
}

bool GameOverState::onExit()
{
	for(auto* obj :  m_gameObjects)
	{
		obj->clean();
	}
	m_gameObjects.clear();
	// clear the texture manager
	for(std::string tid :  m_textureIDList)
	{
		TheTextureManager::Instance()->clearFromTextureMap(tid);
	}	
	std::cout << "exiting GameOverState\n" << std::endl;;
	return true;
}

void GameOverState::s_gameOverToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void GameOverState::s_restartPlay()
{
    TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void GameOverState::setCallbacks(const std::vector<Callback>& callbacks)
{
	// go through the game objects
	for(auto* obj :  m_gameObjects)
	{
		// if they are of type MenuButton then assign a callback based on the id passed in from the file
		if(dynamic_cast<MenuButton*>(obj))
		{
			MenuButton* pButton = dynamic_cast<MenuButton*>(obj);
			pButton->setCallback(callbacks[pButton->getCallbackID()]);
		}
	}
}
