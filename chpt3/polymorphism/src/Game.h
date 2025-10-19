#ifndef __Game__
#define __Game__
#include "SDL.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>

class Game
{
    public:
        Game() {}
        ~Game() {}

        bool init(const char* title, int x_pos, int y_pos, int width, int height, int flags);
        void init_obj();
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
        std::vector<GameObject*> m_gameObjects;
        GameObject* m_go;
        GameObject* m_player;
        GameObject* m_enemy;
        GameObject* m_enemy2;
        GameObject* m_enemy3;

        bool m_bRunning;
};
#endif /* defined(__Game__) */
