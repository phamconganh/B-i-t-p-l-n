#include <SDL_ttf.h>
#include "number.h"
#include "check and init.h"


RightBackGround::RightBackGround(SDL_Renderer* ren_):renderer(ren_)
{
}
int RightBackGround::createRightBackGround(const int& posiY,const int& heightNumber,const int& number)
{
    // init ttf
    if (TTF_Init() < 0)
    {
        logError(std::cout,"TTF_Init Error: ",TTF_GetError(),false);
        return -1;
    }

    // check font
    if (TTF_OpenFont(fontnumber.c_str(), sizeFont) == nullptr)
    {
        logError(std::cout,"TTF_Init Error: ",TTF_GetError(),false);
        return -1;
    }

    // number to string
    std::string s = genericToString(number);

    // load font
    TTF_Font* font = TTF_OpenFont(fontnumber.c_str(), sizeFont);

    // ttf
    SDL_Surface* surFace = TTF_RenderText_Solid(font, s.c_str(), Color);
    SDL_Texture* texTure = SDL_CreateTextureFromSurface(renderer, surFace);
	SDL_FreeSurface(surFace);

	SDL_RenderCopy(renderer, texTure, NULL,new SDL_Rect{ posiX, posiY, lengthRight, heightNumber });

	// destroy
	TTF_CloseFont(font);
	font = NULL;
	SDL_DestroyTexture(texTure);
    TTF_Quit();
    return 1;
}

std::string RightBackGround::genericToString(const int& number)
{
    std::ostringstream stringNumber;
    stringNumber << number;
    return stringNumber.str();
}
