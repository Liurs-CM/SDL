#include "Player.h"
#include "InputHandler.h"

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams) {}

void Player::draw()
{
    SDLGameObject::draw();
}

void Player::update()
{
    m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
	handleInput();
    SDLGameObject::update();
}

void Player::clean() { }

void Player::handleInput()
{
    Vector2D* target = TheInputHandler::Instance()->getMousePosition();
    m_velocity = *target - m_position;
    m_velocity /= 50;
}
