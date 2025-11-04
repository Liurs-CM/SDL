#include "Bullet.h"
#include "InputHandler.h"

Bullet::Bullet() : SDLGameObject() {}

void Bullet::draw()
{
    SDLGameObject::draw();
}

void Bullet::update()
{
    m_position += Vector2D(2,0);
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
