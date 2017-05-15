#ifndef NUMBER_H_INCLUDED
#define NUMBER_H_INCLUDED

#pragma once
#include <sstream>

const int positionScore = 100,positionLevel = 260,positionLife = 425;
const std::string fontnumber="./fonts/charecter.ttf";
const int sizeFont = 1000;
const int posiX = 520;
const int lengthRight = 150;
const SDL_Color Color{ 0, 98, 65, 0 };

class RightBackGround
{
    SDL_Renderer* renderer;
public:
    RightBackGround(SDL_Renderer* ren_);
    int createRightBackGround(const int& posiY,const int& heightNumber,const int& number);
    std::string genericToString(const int& number);
};

/*template <typename T>
std::string genericToString(const T& t)
{
    std::ostringstream oss;
    oss << t;
    return oss.str();
}*/

#endif // NUMBER_H_INCLUDED
