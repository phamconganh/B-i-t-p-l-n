// LIBRARY
#include <iostream>
#include <ctime>
#include "painter.h"
#include "number.h"
#include "music.h"
#include "check and init.h"

using namespace std;

// LIST CONST
//--------------------------------------------------------------------------------
const int dlevel = 1, dlife = 5,dscore = 0, djump = 4,dloop = 99,AddJump = 4;
const int scoreLevel2 = 21, scoreLevel3 = 41, scoreLevel4 = 61;
int level = dlevel,life = dlife, score = dscore, jump = djump;

const int widthArray = 3, heightArray = 9;
const int lengthPic = 100,lengthBreakHeat = 600,heighNumber = 50;

const int distanceLeft = 50,distanceRight = 450,distanceStartPointOfTowPic = 150;
const SDL_Rect startRedHeart{50,200,150,300};
const SDL_Rect startBlackHeart{550,200,650,300};
//---------------------------------------------------------------------------------

// LIST TYPE AND FUNTIONS
//---------------------------------------------------------------------------------
typedef struct picture
{
    int x = NULL;
    int y = NULL;
    PictureID arr ;
};

int startScreen(Painter painter, Music music, SDL_Renderer* renderer);
void check(picture Array[][widthArray], Painter painter, Music music, int& counts,
           const bool& checkHeart, const bool& checkHeartAtLast);
void mouse(picture Array[][widthArray], Music music, const int& counts);
void randomPicture(picture Array[][widthArray], const bool& random,const bool& move);
//-------------------------------------------------------------------------------


// MAIN
//*******************************************************************************
int main(int argc,char* argv[]){

    srand(time(0));

    //INITIALIZE
    SDL_Window* window;
    SDL_Renderer* renderer;

    initSDL(window, renderer);
    Painter painter(window, renderer);
    Music music;
    RightBackGround rightBackGround(renderer);

    // PLAY
    while(true)
    {
        int t = 0, counts = 0;
        if(!startScreen(painter, music, renderer))
        {
            quitSDL(window, renderer);
            return 0;
        }

        // init ARRAY
        picture Array[heightArray][widthArray];
        for (int i = 0; i < heightArray; i++)
        {
            for (int j = 0; j < widthArray; j++)
            {
                Array[i][j].arr = PIC_NULL;
                Array[i][j].x = distanceLeft + distanceStartPointOfTowPic*j;
                Array[i][j].y = lengthPic*(i-1);
            }
        }

        for (int a = 0; a < heightArray - 4; a++)
            randomPicture(Array, true, true);


        // START
        while(life > 0)
        {
            // BACKGROUND MUSIC
            if (level == 1 )        music.sound(level1, dloop);
            else if (level == 2)    music.sound(level2, dloop);
            else if (level == 3)    music.sound(level3, dloop);
            else if (level == 4)    music.sound(level4, dloop);
            while(life > 0)
            {
                bool checks = true;
                randomPicture(Array, true, false);

                // RUN
                while(counts <= lengthPic)
                {
                    SDL_RenderClear(renderer);
                    painter.DrawImage(0, 0, SCREEN_WIDTH, BackGround);

                    mouse(Array, music, counts);
                    check(Array, painter, music, counts, true, false);

                    // CONDITION PLAY KIND OF BACKGROUND MUSIC
                    if ((score == scoreLevel2 && t == 0)||(score == scoreLevel3 && t == 1)
                        ||(score == scoreLevel4 && t == 2))
                    {
                        t++;
                        checks = false;
                        break;
                    }

                    // JUMP IMAGE
                    counts = counts + jump;

                    // PRINT SCORE, LIFE, LEVEL AT RIGHT
                    if (life > 0)
                    {
                        rightBackGround.createRightBackGround(positionScore, heighNumber ,score);
                        rightBackGround.createRightBackGround(positionLevel, heighNumber, level);
                        rightBackGround.createRightBackGround(positionLife, heighNumber, life);
                        SDL_RenderPresent(renderer);
                    }
                }

                if (counts >= lengthPic) counts = 0;
                if (checks == false) break;

                // MOVE ARRAY
                randomPicture(Array, false, true);

                // CHECK
                check(Array, painter, music, counts, false, true);

                // CHECK LIFE
                if (life < 1)
                {
                    painter.DrawImage(0, 0, lengthBreakHeat, BreakHeart);
                    rightBackGround.createRightBackGround(positionScore, heighNumber, score);
                    rightBackGround.createRightBackGround(positionLevel, heighNumber, level);
                    rightBackGround.createRightBackGround(positionLife, heighNumber, life);
                    SDL_RenderPresent(renderer);
                }
            }
            Mix_HaltChannel(-1);
            Mix_CloseAudio();
        }

        // FINISH PLAYING
        Mix_HaltChannel(-1);
        music.sound(gameOver,0);
        SDL_Delay(3000);
        Mix_HaltChannel(-1);
        Mix_CloseAudio();

        // init NEW ROUND
        life = dlife;
        score = dscore;
        level = dlevel;
        jump = djump;
    }

    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}
//**********************************************************************************


//----------------------------------------------------------------------------------

int startScreen(Painter painter, Music music, SDL_Renderer* renderer)
{
    SDL_Event es;
    music.sound(startscreen, dloop);
    while (true)
    {

        painter.DrawImage(0, 0, SCREEN_WIDTH, StartScreen);
        if (SDL_WaitEvent(&es) == 0)  break;
        else
        {
            if (es.button.x >= startRedHeart.x && es.button.x <= startRedHeart.w
                && es.button.y >= startRedHeart.y && es.button.y <= startRedHeart.h)
            {
                painter.DrawImage(startRedHeart.x, startRedHeart.y, lengthPic, RedHeart);
                SDL_RenderPresent(renderer);
            }
            if (es.button.x >= startBlackHeart.x && es.button.x <= startBlackHeart.w
                && es.button.y >= startBlackHeart.y && es.button.y <= startBlackHeart.h)
            {
                painter.DrawImage(startBlackHeart.x, startBlackHeart.y, lengthPic, BlackHeart);
                SDL_RenderPresent(renderer);
            }
            if (es.type == SDL_MOUSEBUTTONDOWN && es.button.y >= startRedHeart.y && es.button.y <= startRedHeart.h)
            {
                if(es.button.x >= startRedHeart.x && es.button.x <= startRedHeart.w)
                {
                    music.sound(redHeart, 0);
                    break;
                }
                else if (es.button.x >= startBlackHeart.x && es.button.x <= startBlackHeart.w)
                {
                    music.sound(blackHeart, 0);
                    SDL_Delay(1000);
                    return 0;
                }
            }
        }
        SDL_RenderPresent(renderer);
    }
    SDL_Delay(500);
    Mix_HaltChannel(-1);
    return 1;
}

//-------------------------------------------------------------------------------------------------------

void check(picture Array[][widthArray], Painter painter, Music music, int& counts,
           const bool& checkHeart, const bool& checkHeartAtLast)
{
    if (checkHeart)
    {
        // LOAD IMAGE TO SCREEN
        for (int i = 0; i < heightArray; i++)
        {
            for (int j = 0; j < widthArray; j++)
            {
                if (Array[i][j].arr == PIC_RED_HEART)
                    painter.DrawImage(Array[i][j].x, Array[i][j].y + counts, lengthPic, RedHeart);
                else if (Array[i][j].arr == PIC_BLACK_HEART)
                    painter.DrawImage(Array[i][j].x, Array[i][j].y + counts, lengthPic, BlackHeart);
            }
        }

        // CHECK LEVEL
        if (level == 1 && score >= scoreLevel2)
        {
            //music.sound(levelUp,0);
            level = 2;
            jump += AddJump;
        }
        else if (level == 2 && score >= scoreLevel3)
        {
            //music.sound(levelUp,0);
            level = 3;
            jump += AddJump;
        }
        else if (level == 3 && score >= scoreLevel4)
        {
            //music.sound(levelUp,0);
            level = 4;
            jump += AddJump;
        }
    }
    if (checkHeartAtLast)
    {
        for (int j = 0; j < widthArray; j++)
            if(Array[heightArray-1][j].arr != PIC_NULL)
            {
                if (life > 0)   life --;
                music.sound(blackHeart, 0);
            }
    }
}

//---------------------------------------------------------------------------------------------------------

void mouse(picture Array[][widthArray], Music music, const int& counts)
{
    SDL_Event e;
    while(SDL_PollEvent(&e))
    {
         if ( e.type == SDL_MOUSEBUTTONDOWN && e.button.x >= distanceLeft && e.button.x <= distanceRight)
        {
            int i,j = 4;
            for (int a = 0; a < widthArray; a++)
            {
                if ( e.button.x >= distanceLeft + distanceStartPointOfTowPic*a
                    && e.button.x <= distanceStartPointOfTowPic*(a+1))
                {
                    j = a;
                    break;
                }
            }

            for (int a=-1; a < heightArray-1; a++)
                if ( e.button.y >= lengthPic*a + counts && e.button.y <= lengthPic*(a+1) -1 + counts)    i = a+1;
            if ( counts == 0 && e.button.y % lengthPic == 0 )    i++;
            if ( e.button.button == SDL_BUTTON_LEFT )
            {
                if ( Array[i][j].arr == PIC_RED_HEART )
                {
                    score++;
                    music.sound(redHeart, 0);
                }
                else if ( Array[i][j].arr == PIC_BLACK_HEART )
                {
                    life--;
                    music.sound(blackHeart, 0);
                }
            }
            else
            {
                if ( Array[i][j].arr == PIC_BLACK_HEART )
                {
                    score++;
                    music.sound(redHeart, 0);
                }
                else if ( Array[i][j].arr == PIC_RED_HEART )
                {
                    life--;
                    music.sound(blackHeart, 0);
                }
            }
            Array[i][j].arr = PIC_NULL;
        }
    }
}

//-------------------------------------------------------------------------------------------------------

void randomPicture( picture Array[][widthArray], const bool& random,const bool& move)
{
    if(random)
    {
        int levelHeart = level;
        if ( level > 3 ) levelHeart = widthArray;
        // INIT heart for array
        for (int j=0; j < widthArray; j++)   Array[0][j].arr = PIC_NULL;
        for (int i=0; i < levelHeart; i++)
        {
            int x = rand() % widthArray,y = rand() % 2;
            if (Array[0][x].arr != PIC_BLACK_HEART&&Array[0][x].arr != PIC_RED_HEART)
            {
                if (y)  Array[0][x].arr = PIC_RED_HEART;
                else    Array[0][x].arr = PIC_BLACK_HEART;
            }
            else i--;
        }
    }
    if (move)
    {
        for (int i = heightArray-1; i > 0; i--)
            for (int j = 0; j< widthArray; j++)
                Array[i][j].arr = Array[i-1][j].arr;
    }
}

//**********************************************************************************************************
