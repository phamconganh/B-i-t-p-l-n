#ifndef LOADHEART_H_INCLUDED
#define LOADHEART_H_INCLUDED

#include <vector>
#include <SDL.h>
#include "painter.h"

enum PictureID {
    PIC_NULL = 0 ,PIC_RED_HEART , PIC_BLACK_HEART,
    PIC_BREAK_HEART,
};

/*class Heart
{
    std::vector<SDL_Texture*> pictures;
    Painter& painter;
public:
    Heart(Painter& painter_);
    ~Heart();

    void loadGamePictures();
    SDL_Texture* getImage(PictureID id) const { return pictures[id]; }
};
*/

#endif // LOADHEART_H_INCLUDED
