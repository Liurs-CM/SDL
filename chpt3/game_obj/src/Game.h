#include "SDL.h"
#include "Player.h"
#ifndef __Game__
#define __Game__

class Game
{
    public:
        Game() {}
        ~Game() {}

        bool init(const char* title, int x_pos, int y_pos, int width, int height, int flags);
        void render();
        void update();
        void handleEvents();
        void clean(); 

        //function to access the private running variable
        bool running() { return m_bRunning; }

    private:

        SDL_Window* m_pWindow;
        SDL_Renderer* m_pRenderer;

        int m_currentFrame;
        GameObject m_go;
        Player m_player;

        bool m_bRunning;
};
#endif /* defined(__Game__) */
