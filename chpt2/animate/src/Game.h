#include "SDL.h"
#ifndef __Game__
#define __Game__
class Game
{
    public:
        Game() {}
        ~Game() {}

        bool init(const char* title, int x_pos, int y_pos, int width,
        int height, int flags);
        void init_fig();

        void render();
        void update();
        void handleEvents();
        void clean(); 

        //function to access the private running variable
        bool running() { return m_bRunning; }

    private:

        SDL_Window* m_pWindow;
        SDL_Renderer* m_pRenderer;

        SDL_Texture* m_pTexture;
        SDL_Rect m_sourceRectangle;
        SDL_Rect m_destinationRectangle;

        bool m_bRunning;
};
#endif /* defined(__Game__) */
