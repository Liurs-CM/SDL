#ifndef __Game__
#define __Game__
#include "SDL.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>

class Game
{
    public:
        ~Game() {}

        bool init(const char* title, int x_pos, int y_pos, int width, int height, int flags);
        void init_obj();
        void render();
        void update();
        void handleEvents();
        void clean(); 

        bool running() { return m_bRunning; }
        SDL_Renderer* getRenderer() const { return m_pRenderer; }
        // create the public instance function
        static Game* Instance()
        {
            if(s_pInstance == 0)
            {
                s_pInstance = new Game();
                return s_pInstance;
            }
            return s_pInstance;
        }

    private:
        Game() {}

        SDL_Window* m_pWindow;
        SDL_Renderer* m_pRenderer;

        int m_currentFrame;
        std::vector<GameObject*> m_gameObjects;

        bool m_bRunning;

        // create the s_pInstance member variable
        static Game* s_pInstance;
};

// create the typedef
typedef Game TheGame;

#endif /* defined(__Game__) */
