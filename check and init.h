#ifndef CHECK_AND_INIT_H_INCLUDED
#define CHECK_AND_INIT_H_INCLUDED

#include <iostream>
#include <SDL.h>
#pragma once


const int   SCREEN_WIDTH = 700;
const int   SCREEN_HEIGHT = 700;
const std::string WINDOW_TITLE = "collecting heart";


void logError(std::ostream& os, const std::string &msg, const std::string& msgErr,bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();

#endif // CHECK_AND_INIT_H_INCLUDED
