#ifndef MUSIC_H_INCLUDED
#define MUSIC_H_INCLUDED

#undef main
#include <iostream>
#include <SDL_mixer.h>

const std::string redHeart = "./sounds/red heart.wav";
const std::string blackHeart = "./sounds/black heart.wav";
const std::string gameOver = "./sounds/gameover.wav";
const std::string levelUp = "./sounds/levelup.wav";
const std::string level1 = "./sounds/level1.wav";
const std::string level2 = "./sounds/level2.wav";
const std::string level3 = "./sounds/level3.wav";
const std::string level4 = "./sounds/level4.wav";
const std::string startscreen = "./sounds/startscreen.wav";

struct Music
{
    int sound(const std::string& nameSound,const int& t);
};

#endif // MUSIC_H_INCLUDED
