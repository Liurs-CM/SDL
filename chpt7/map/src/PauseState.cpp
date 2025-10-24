#include <iostream>
#include "PauseState.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "Game.h"
#include "GameStateMachine.h"
#include "MenuButton.h"
#include "MainMenuState.h"
#include "StateParser.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::update()
{
    for(auto* obj :  m_gameObjects)
    {
        obj->update();
    }
}

void PauseState::render()
{
    for(auto* obj :  m_gameObjects)
    {
        obj->draw();
    }
}

bool PauseState::onEnter()
{
    StateParser stateParser;
    stateParser.parseState("assets/test.xml", s_pauseID, &m_gameObjects, &m_textureIDList);
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_pauseToMain);
    m_callbacks.push_back(s_resumePlay);
    setCallbacks(m_callbacks);
    std::cout << "entering PauseState\n" << std::endl;
    return true;
}

bool PauseState::onExit()
{
    for(auto* obj :  m_gameObjects)
    {
        obj->clean();
    }
    m_gameObjects.clear();
	for(std::string tid : m_textureIDList)
	{
		TheTextureManager::Instance()->clearFromTextureMap(tid);
	}
    // reset the mouse button states to false
    TheInputHandler::Instance()->reset();
    std::cout << "exiting PauseState\n" << std::endl;
    return true;
}

void PauseState::s_pauseToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
}

void PauseState::s_resumePlay()
{
    TheGame::Instance()->getStateMachine()->popState();
}

void PauseState::setCallbacks(const std::vector<Callback>& callbacks)
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

