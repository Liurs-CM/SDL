#ifndef __Game__
#define __Game__
#include "SDL.h"
#include "Player.h"
#include "Enemy.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "PlayState.h"

class Game
{
    public:
        ~Game() {}

        bool init(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen);
        void init_obj();
        void render();
        void update();
        void handleEvents();
        void clean(); 
	    void quit() { m_bRunning = false; }

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
        GameStateMachine* m_pGameStateMachine;
        static Game* s_pInstance;
};

// create the typedef
typedef Game TheGame;

#endif /* defined(__Game__) */
