#include <string>
#include <iostream>
#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameObject.h"
#include "InputHandler.h"
#include "LoaderParams.h"
#include "StateParser.h"
//#include "LevelParser.h"
//#include "Level.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
    {
        //TheGame::Instance()->getStateMachine()->pushState(new PauseState());
        std::cout << "exit PlayState" << std::endl;
    }
    else if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
    {
        if (bullet && player) 
        {
            Vector2D ppos = player->getPosition();
            bullet->SetPosition(ppos);
        }
    }
    for(auto* obj : m_gameObjects)
    {
        obj->update();
    }
    //pLevel->update();
}

void PlayState::render()
{
    for(auto* obj : m_gameObjects)
    {
        obj->draw();
    }
    //pLevel->render();
}

bool PlayState::onEnter()
{
	StateParser stateParser;
	stateParser.parseState("assets/test.xml", s_playID, &m_gameObjects, &m_textureIDList);
    for(auto* obj : m_gameObjects)
    {
        if(dynamic_cast<Player*>(obj) != nullptr)
        {
            player = static_cast<Player*>(obj);
        }
        else if(dynamic_cast<Bullet*>(obj) != nullptr)
        {
            bullet = static_cast<Bullet*>(obj);
        }
    }
    if (bullet && player) 
    {
        std::cout << "get player bullet" << std::endl;
    }
    std::cout << "entering PlayState" << std::endl;
    //LevelParser levelParser;
    //pLevel = levelParser.parseLevel("assets/map1.tmx");
    return true;
}

bool PlayState::onExit()
{
    for(auto* obj :  m_gameObjects)
    {
        obj->clean();
    }
    m_gameObjects.clear();
    TheTextureManager::Instance()->clearFromTextureMap("pilot");
    TheTextureManager::Instance()->clearFromTextureMap("bullet");
    std::cout << "exiting PlayState" << std::endl;
    return true;
}

bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{	
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = p1->getPosition().getX();
    rightA = p1->getPosition().getX() + p1->getWidth();
    topA = p1->getPosition().getY();
    bottomA = p1->getPosition().getY() + p1->getHeight();

    // Calculate the sides of rect B
    leftB = p2->getPosition().getX();
    rightB = p2->getPosition().getX() + p2->getWidth();
    topB = p2->getPosition().getY();
    bottomB = p2->getPosition().getY() + p2->getHeight();

    // If any of the sides from A are outside of B
    if(bottomA <= topB) { return false; }
    if(topA >= bottomB) { return false; }
    if(rightA <= leftB) { return false; }
    if(leftA >= rightB) { return false; }

    return true;
}
