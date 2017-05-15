#ifndef PAINTER_H_INCLUDED
#define PAINTER_H_INCLUDED

#pragma once

#include <iostream>
#include <SDL.h>


const SDL_Color BLUE_COLOR = {0, 0, 255};
const SDL_Color WHITE_COLOR = {255, 255, 255};
const SDL_Color DEFAULT_COLOR = WHITE_COLOR;
const std::string BackGround = "image\\background.png";
const std::string RedHeart = "./image/red heart.bmp";
const std::string BlackHeart = "./image/black heart.bmp";
const std::string BreakHeart = "./image/break heart.bmp";
const std::string StartScreen = "./image/start screen.png";

enum PictureID {
    PIC_NULL = 0 ,PIC_RED_HEART , PIC_BLACK_HEART,
    PIC_BREAK_HEART,
};

class Painter
{
    float x;
    float y;
    int width;
    int height;
    SDL_Color color;
    SDL_Renderer* renderer;
public:
    Painter(SDL_Window* window, SDL_Renderer* renderer);

    void setPosition(float x, float y);
    void setColor(SDL_Color color);
    SDL_Renderer* getRenderer() const { return renderer; }
    void clearWithBgColor(SDL_Color color);

    SDL_Texture* loadTexture(const std::string& photo );
    bool createImage( SDL_Texture* texture,
        SDL_Rect* srcrect = nullptr, SDL_Rect* dstrect = nullptr );
    void DrawImage(const int& x,const int& y,const int& length,const std::string& s);
};

#endif // PAINTER_H_INCLUDED
