#include "defs.h"
#include "Enemy.h"
#include "Game.h"
#include "InputHandler.h"

Enemy::Enemy() : SDLGameObject() {}

void Enemy::draw()
{
    //SDLGameObject::draw();
    TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(), SDL_FLIP_HORIZONTAL);
}

void Enemy::update()
{
    m_position -= Vector2D(0.2,0);
	handleInput();
    SDLGameObject::update();
}

void Enemy::clean() { }

void Enemy::handleInput()
{
}

void Enemy::load(const LoaderParams *pParams)
{
    SDLGameObject::load(pParams);
}

void Enemy::SetPosition(Vector2D pos) 
{ 
    m_position = pos; 
    //m_position = pos + Vector2D(24, 24); 
}

bool Enemy::isDead()
{
    if (m_position.getX() > SCR_W ||
            m_position.getX() < 0 ||
            m_position.getY() > SCR_H ||
            m_position.getY() < 0)
    {
        return true;
    }
    else if(collision_state)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::unique_ptr<SDLGameObject> Enemy::clone()
{
    // 返回当前对象的完整副本（包括纹理、宽高等）
    return std::make_unique<Enemy>(*this);  // 调用拷贝构造
}
