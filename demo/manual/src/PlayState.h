#ifndef __PlayState__
#define __PlayState__
#include "GameState.h"
#include "Bullet.h"
#include "Player.h"
#include <vector>
//#include "Level.h"

class GameObject;
class SDLGameObject;

class PlayState : public GameState
{
    public:
        virtual void update();
        virtual void render();
        virtual bool onEnter();
        virtual bool onExit();
        virtual std::string getStateID() const { return s_playID; }
        void createBullet();
        void removeBullet(Bullet* bullet);
        int dbg_num = 0;
    private:
        static const std::string s_playID;
        std::vector<GameObject*> m_gameObjects;
        Player* player = nullptr;
        Bullet* bullet = nullptr;
        std::vector<std::unique_ptr<Bullet>> m_bullets;
        //std::vector<Bullet*> m_bullets;
        //Level* pLevel;
        bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);
};

#endif // __PlayState__
