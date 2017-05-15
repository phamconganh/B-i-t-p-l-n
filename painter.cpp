
#include <SDL_image.h>
#include "painter.h"
#include "check and init.h"

Painter::Painter(SDL_Window* window, SDL_Renderer* renderer_)
    : renderer(renderer_)
{
    SDL_RenderGetLogicalSize(renderer, &width, &height); // default width anh height
    if (width == 0 && height == 0)  SDL_GetWindowSize(window, &width, &height);

    // default
    setPosition(width/2, height/2);
    setColor(WHITE_COLOR);
    clearWithBgColor(BLUE_COLOR);
}

void Painter::setPosition(float x, float y)
{
    this->x = x;
    this->y = y;
}


void Painter::setColor(SDL_Color color)
{
    this->color = color;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0);
}

void Painter::clearWithBgColor(SDL_Color bgColor)
{
    SDL_Color curColor = color;
    setColor(bgColor);
    SDL_RenderClear(renderer);
    setColor(curColor);
}

// load image
SDL_Texture* Painter::loadTexture(const std::string& photo)
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( photo.c_str() );
    if ( loadedSurface == NULL )
        logError(std::cout,"Unable to load image: ",SDL_GetError(),false);
    else {
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
            logError(std::cout,"Unable to create texture from: ", SDL_GetError(),false);
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}

bool Painter::createImage( SDL_Texture* texTure,
        SDL_Rect* srcrect, SDL_Rect* dstrect)
{
    if( texTure == NULL ) return false;
    SDL_RenderCopy( renderer, texTure, srcrect, dstrect );
    return true;
}

void Painter::DrawImage(const int& x,const int& y,const int& length,const std::string& s)
{
    SDL_Texture* texTure = loadTexture(s.c_str());
    SDL_Rect miniheart{x,y,length,length};
    createImage(texTure,NULL,&miniheart);
    SDL_DestroyTexture(texTure);
}
