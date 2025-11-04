#ifndef __Bullet__
#define __Bullet__
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
        void SetOwner(Player* player){ owner = player; }
        void SetPosition(Vector2D pos) { this->m_position = pos + Vector2D(32, 32); }
    private:
        Player* owner;
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
