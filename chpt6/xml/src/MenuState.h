#ifndef __MenuState__
#define __MenuState__
#include "GameState.h"
#include "GameObject.h"
#include <vector>

class MenuState : public GameState
{
    public:
        typedef void(*Callback)();
        virtual void setCallbacks(const std::vector<Callback>& callbacks) = 0;
        std::vector<Callback> m_callbacks;
};

#endif // __MenuState__
