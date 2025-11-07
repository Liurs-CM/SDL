#ifndef __Bullet__
#define __Bullet__
//#include "Player.h"
#include "SDLGameObject.h"
#include "GameObjectFactory.h"
class Player;

class Bullet : public SDLGameObject
{
    public:
        Bullet();
        void draw();
        void update();
        void clean();
        void load(const LoaderParams* pParams);
        void SetPosition(Vector2D pos);
    private:
        void handleInput();
};

class BulletCreator : public BaseCreator
{
    public:	
        GameObject* createGameObject() const
        {
            return new Bullet();
        }
};

#endif /* defined(__Bullet__) */
