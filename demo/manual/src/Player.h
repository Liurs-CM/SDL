#ifndef __Player__
#define __Player__
#include "SDLGameObject.h"
#include "GameObjectFactory.h"
#include "Bullet.h"

class Player : public SDLGameObject
{
    public:
        Player();
        void draw();
        void update();
        void clean();
        void shoot();
        void load(const LoaderParams* pParams);
    private:
        Bullet* m_bullet;
        void handleInput();
};

class PlayerCreator : public BaseCreator
{
    public:	
        GameObject* createGameObject() const
        {
            return new Player();
        }
};

#endif /* defined(__Player__) */
