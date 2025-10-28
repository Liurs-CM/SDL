#include "TextureManager.h"
#include "SDL_image.h"
#include <iostream>

TextureManager* TextureManager::s_pInstance = 0;

bool TextureManager::load(
        std::string fileName, 
        std::string id, 
        SDL_Renderer* pRenderer)
{
    //1. create surface temporary from image file
    SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
    if(pTempSurface == 0)
    {
        std::cout << "Error can't load img: " << fileName;
        return false;
    }
    //2. create texture from temporary surface
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
    //3. free temporary surface
    SDL_FreeSurface(pTempSurface);
    //4. map id and texture to dict
    if(pTexture != 0)
    {
        m_textureMap[id] = pTexture;
        return true;
    }
    return false;
}

void TextureManager::draw(
        std::string id, 
        int x, 
        int y, 
        int width, 
        int height, 
        SDL_Renderer* pRenderer, 
        SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect dstRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = width;
    srcRect.h = height;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = width;
    dstRect.h = height;
    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &dstRect, 0, 0, flip);
}

void TextureManager::clearFromTextureMap(std::string id)
{
    m_textureMap.erase(id);
}
