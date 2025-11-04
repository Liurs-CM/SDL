#include "Level.h"

void Level::render()
{
    for(auto* obj : m_layers)
    {
        obj->render();
    }
}

void Level::update()
{
    for(auto* obj : m_layers)
    {
        obj->update();
    }
}
