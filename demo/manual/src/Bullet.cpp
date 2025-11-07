#include "Bullet.h"
#include "InputHandler.h"

Bullet::Bullet() : SDLGameObject() {}

void Bullet::draw()
{
    SDLGameObject::draw();
}

void Bullet::update()
{
    m_position += Vector2D(1,0);
	handleInput();
    SDLGameObject::update();
}

void Bullet::clean() { }

void Bullet::handleInput()
{
}

void Bullet::load(const LoaderParams *pParams)
{
    SDLGameObject::load(pParams);
}

void Bullet::SetPosition(Vector2D pos) 
{ 
    //m_position = pos; 
    m_position = pos + Vector2D(24, 24); 
}
