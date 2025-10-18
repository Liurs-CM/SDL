#ifndef __Game__
#define __Game__
class Game
{
    public:
        Game() {}
        ~Game() {}

        void init() { m_bRunning = true; }

        void render() {}
        void update() {}
        void handleEvents() {}
        void clean() {}

        //function to access the private running variable
        bool running() { return m_bRunning; }

    private:

        SDL_Window* m_pWindow = 0;
        SDL_Renderer* m_pRenderer = 0;

        bool m_bRunning;
};
#endif /* defined(__Game__) */
