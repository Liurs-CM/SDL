#include <string>
#include <iostream>
#include "MenuState.h"
#include "MenuButton.h"
#include "TextureManager.h"
#include "Game.h"

const std::string MenuState::s_menuID = "MENU";

void MenuState::update()
{
    for(auto* obj : m_gameObjects)
    {
        obj->update();
    }
}

void MenuState::render()
{
    for(auto* obj : m_gameObjects)
    {
        obj->draw();
    }
}

bool MenuState::onEnter()
{
    if(!TheTextureManager::Instance()->load("assets/button_play.png", "playbutton", TheGame::Instance()->getRenderer()))
    {
        return false;
    }

    if(!TheTextureManager::Instance()->load("assets/button_exit.png", "exitbutton", TheGame::Instance()->getRenderer()))
    {
        return false;
    }

    GameObject* button1 = new MenuButton(new LoaderParams(100, 100, 400, 100, "playbutton"), s_menuToPlay);
    GameObject* button2 = new MenuButton(new LoaderParams(100, 300, 400, 100, "exitbutton"), s_exitFromMenu);

    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);

    std::cout << "entering MenuState\n";
    return true;
}

bool MenuState::onExit()
{
    for(auto* obj : m_gameObjects)
    {
        obj-> clean();
    }
    m_gameObjects.clear();
    TheTextureManager::Instance()->clearFromTextureMap("playbutton");
    TheTextureManager::Instance()->clearFromTextureMap("exitbutton");

    std::cout << "exiting MenuState\n";
    return true;
}

void MenuState::s_menuToPlay()
{
    std::cout << "Play button clicked" << std::endl;
    TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void MenuState::s_exitFromMenu()
{
    std::cout << "Exit button clicked" << std::endl;
    TheGame::Instance()->quit();
}
