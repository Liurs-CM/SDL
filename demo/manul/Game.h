#ifndef __Game__
#define __Game__
#include "SDL.h"

class Game
{
    public:
        ~Game() {}
        bool init(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen);
        void render();
        void update();
        void handleEvents();
        void clean();
        bool running() { frameStart = SDL_GetTicks(); return m_bRunning; }
        void syncFPS();
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
        int m_gameWidth;
        int m_gameHeight;
        Uint32 frameStart;
        Uint32 frameTime;
        bool m_bRunning;
        SDL_Window* m_pWindow;
        SDL_Renderer* m_pRenderer;
        static Game* s_pInstance;
};

typedef Game TheGame;

#endif /* defind(__Game__) */
