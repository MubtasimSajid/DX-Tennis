#include "iGraphics.h"
#include <bits/stdc++.h>
using namespace std;
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ScreenWidth 1000
#define ScreenHeight 600
#define player1Margin 150
#define player2Margin 750
#define totalBricks 36
#define noOfPowerUps 4
#define powerupSize 72
#define showTime 400
#define activationPeriod 500

typedef struct brickStructure
{
    int x;
    int y;
    int dx = 18;
    int dy = 98;
    bool show = false;
    int lives = 1;
} brickStructure;

typedef struct boardStructure
{
    int x;
    int y;
    int dx = 20;
    int dy = 130;
    int movement;
    bool show = true;
} boardStructure;

typedef struct powerup
{
    int x;
    int y;
    bool show = false;
    bool active = false;
    int type;
    int displayTime = showTime;
    int activeTime = activationPeriod;
} powerup;

brickStructure bricksPlayer1[totalBricks / 2], bricksPlayer2[totalBricks / 2];
boardStructure boards[2];
powerup PowerUps;

int doubleLives[6] = {6, 7, 8, 9, 10, 11};
int tripleLives[6] = {12, 13, 14, 15, 16, 17};

int ballMovementSeconds = 1;
int xBall = (int)ScreenWidth / 2;
int yBall = (int)ScreenHeight / 2;
int radiusBall = 10;
int dx = 80;
int dy = 40;
int mposx, mposy, mouseButton = NULL, mouseState = GLUT_UP;
bool isStartedPlayer1 = false;
bool isStartedPlayer2 = false;
int firstWallLeft = 0;
int secondWallLeft = 0;
int ballMovementX;
int ballMovementY;
int multiplierX = 0;
int multiplierY = 0;
int lastPlayerTouch = 0;
int powerUpActivatedFor = 0;
int background = 0;
int slowDown = 200;
int fireBallAnimation = 1;
int brickRegenrationTimedown = 10;

int playButtonClick = 0;
int instructionsButtonClick = 0;
int aboutButtonClick = 0;
int backButtonClick = 0;
int soundOnButtonClick = 0;
int soundOffButtonClick = 0;

int homePage = 1;
int playPage = 0;
int aboutPage = 0;
int instructionsPage = 0;
int soundOn = 1;
int soundOnPage = 0;
int soundOffPage = 0;
int gameoverPage = 0;
int difficultyPage = 0;
int easyMode = 0;
int mediumMode = 0;
int difficultMode = 0;
int pausePage = 0;

void boardInitialize();
void ballChange();
void defineBricks();
void powerupRandomizer();

void drawHomePage();
void drawAboutPage();
void drawInstructionsPage();
void drawSoundOnPage();
void drawSoundOffPage();
void drawDifficultyPage();
void player1WinPage();
void player2WinPage();
void batCollisionSound();
void brickCollisionSound();

void playButtonClickHandler();
void soundOnButtonClickHandler();
void soundOffButtonClickHandler();
void instructionsButtonClickHandler();
void aboutButtonClickHandler();
void backButtonClickHandler();
void homePageButtonClickHandler();
void difficultyButtonClickHandler();
void pauseButtonClickHandler();
void playFromPause();

void iDraw() 
{
    iClear();

    if(homePage == 1)
    {
        drawHomePage();
    }
    else if(aboutPage == 1)
    {
        drawAboutPage();
    }
    else if(instructionsPage == 1)
    {
        drawInstructionsPage();
    }
    else if(soundOnPage == 1 && soundOn == 1)
    {
        drawSoundOnPage();
    }
    else if(soundOffPage == 1 && soundOn == 0)
    {
        drawSoundOffPage();
    }
    else if (difficultyPage == 1)
    {
        drawDifficultyPage();
    }
    else if(playPage == 1)
    {
        if (slowDown > 0)
            slowDown--;

        if (boards[0].y < 0)
            boards[0].y = 0;
        if (boards[1].y < 0)
            boards[1].y = 0;
        if (boards[0].y > (ScreenHeight - boards[0].dy))
            boards[0].y = ScreenHeight - boards[0].dy;
        if (boards[1].y > (ScreenHeight - boards[1].dy))
            boards[1].y = ScreenHeight - boards[1].dy;

        iMouse(mouseButton, mouseState, mposx, mposy);
        if (!background)
            iShowBMP(0, 0, "Images\\bg.bmp");
        else if (background == 1)
            iShowBMP(0, 0, "Images\\newbg.bmp");
        else if (background == 2)
            iShowBMP(0, 0, "Images\\black_bg.bmp");
        else if (background == 3)
            iShowBMP(0, 0, "Images\\calmBG.bmp");

        iSetColor(0, 0, 0);
        iFilledCircle(xBall, yBall, radiusBall, 1000);

        if (easyMode && background == 0)
            iShowBMP2(xBall - radiusBall, yBall - radiusBall, "Images\\ballGreen.bmp", 0);
        else if (easyMode && background == 1)
            iShowBMP2(xBall - radiusBall, yBall - radiusBall, "Images\\ballPink.bmp", 0);
        else if (easyMode && background == 2)
            iShowBMP2(xBall - radiusBall, yBall - radiusBall, "Images\\ballLightBlue.bmp", 0);
        else if (easyMode && background == 3)
            iShowBMP2(xBall - radiusBall, yBall - radiusBall, "Images\\ballBlue.bmp", 0);
        else if (mediumMode && background == 0)
            iShowBMP2(xBall - radiusBall, yBall - radiusBall, "Images\\ballGreen.bmp", 0);
        else if (mediumMode && background == 1)
            iShowBMP2(xBall - radiusBall, yBall - radiusBall, "Images\\ballPink.bmp", 0);
        else if (mediumMode && background == 2)
            iShowBMP2(xBall - radiusBall, yBall - radiusBall, "Images\\ballBlue.bmp", 0);
        else if (mediumMode && background == 3)
            iShowBMP2(xBall - radiusBall, yBall - radiusBall, "Images\\ballLightBlue.bmp", 0);
        else if (difficultMode)
            iShowBMP2(xBall - radiusBall, yBall - radiusBall, "Images\\ballGrey.bmp", 0);

        if (PowerUps.active && PowerUps.type == 2)
        {
            iShowBMP2(xBall - radiusBall, yBall - radiusBall, "Images\\fireBall.bmp", 0);
        }

        if (easyMode)
        {
            if (PowerUps.active && PowerUps.type == 0 && powerUpActivatedFor == 1)
            {
                iShowBMP2(boards[0].x, boards[0].y, "Images\\batEasyLong.bmp", 0);
            }
            else if (!PowerUps.active || PowerUps.type != 3 || powerUpActivatedFor != 1)
                iShowBMP2(boards[0].x, boards[0].y, "Images\\batEasy.bmp", 0);
        }
        else if (mediumMode)
        {
            if (PowerUps.active && PowerUps.type == 0 && powerUpActivatedFor == 1)
            {
                iShowBMP2(boards[0].x, boards[0].y, "Images\\batMediumLong.bmp", 0);
            }
            else if (!PowerUps.active || PowerUps.type != 3 || powerUpActivatedFor != 1)
                iShowBMP2(boards[0].x, boards[0].y, "Images\\batMedium.bmp", 0);
        }
        else if (difficultMode)
        {
            if (PowerUps.active && PowerUps.type == 0 && powerUpActivatedFor == 1)
            {
                iShowBMP2(boards[0].x, boards[0].y, "Images\\batHardLong.bmp", 0);
            }
            else if (!PowerUps.active || PowerUps.type != 3 || powerUpActivatedFor != 1)
                iShowBMP2(boards[0].x, boards[0].y, "Images\\batHard.bmp", 0);
        }

        if (easyMode)
        {
            if (PowerUps.active && PowerUps.type == 0 && powerUpActivatedFor == 2)
            {
                iShowBMP2(boards[1].x, boards[1].y, "Images\\batEasyLong.bmp", 0);
            }
            else if (!PowerUps.active || PowerUps.type != 3 || powerUpActivatedFor != 2)
                iShowBMP2(boards[1].x, boards[1].y, "Images\\batEasy.bmp", 0);
        }
        else if (mediumMode)
        {
            if (PowerUps.active && PowerUps.type == 0 && powerUpActivatedFor == 2)
            {
                iShowBMP2(boards[1].x, boards[1].y, "Images\\batMediumLong.bmp", 0);
            }
            else if (!PowerUps.active || PowerUps.type != 3 || powerUpActivatedFor != 2)
                iShowBMP2(boards[1].x, boards[1].y, "Images\\batMedium.bmp", 0);
        }
        else if (difficultMode)
        {
            if (PowerUps.active && PowerUps.type == 0 && powerUpActivatedFor == 2)
            {
                iShowBMP2(boards[1].x, boards[1].y, "Images\\batHardLong.bmp", 0);
            }
            else if (!PowerUps.active || PowerUps.type != 3 || powerUpActivatedFor != 2)
                iShowBMP2(boards[1].x, boards[1].y, "Images\\batHard.bmp", 0);
        }

        if (!isStartedPlayer1)
        {
            if (!background || background == 2)
                iSetColor(255, 255, 255);
            else
                iSetColor(0, 0, 0);
            iText((ScreenWidth / 2) - 150, (ScreenHeight / 2) + 50, "Press space if player-1 is ready", GLUT_BITMAP_TIMES_ROMAN_24);
        }
        if (!isStartedPlayer2)
        {
            if (!background || background == 2)
                iSetColor(255, 255, 255);
            else
                iSetColor(0, 0, 0);
            iText((ScreenWidth / 2) - 220, (ScreenHeight / 2) - 50, "Press the middle mouse button if player-2 is ready", GLUT_BITMAP_TIMES_ROMAN_24);
        }

        firstWallLeft = 0;
        for (int i = 0; i < totalBricks / 2; i++)
        {
            if (bricksPlayer1[i].show)
            {
                iFilledRectangle(bricksPlayer1[i].x, bricksPlayer1[i].y, bricksPlayer1[i].dx, bricksPlayer1[i].dy);
                if (bricksPlayer1[i].lives == 1)
                    iShowBMP2(bricksPlayer1[i].x, bricksPlayer1[i].y, "Images\\brick1.bmp", 0);
                else if (bricksPlayer1[i].lives == 2)
                    iShowBMP2(bricksPlayer1[i].x, bricksPlayer1[i].y, "Images\\brick2.bmp", 0);
                else if (bricksPlayer1[i].lives == 3)
                    iShowBMP2(bricksPlayer1[i].x, bricksPlayer1[i].y, "Images\\brick3.bmp", 0);
                firstWallLeft++;
            }
        }

        if (!firstWallLeft && playPage)
        {
            player1WinPage();
            playPage = 0;
            gameoverPage = 1;
            isStartedPlayer1 = false;
            isStartedPlayer2 = false;
            if (soundOn)
                PlaySound(TEXT("Sounds\\gameOver.wav"), NULL, SND_FILENAME | SND_ASYNC);
        }

        secondWallLeft = 0;
        for (int i = 0; i < totalBricks / 2; i++)
        {
            if (bricksPlayer2[i].show)
            {
                iFilledRectangle(bricksPlayer2[i].x, bricksPlayer2[i].y, bricksPlayer2[i].dx, bricksPlayer2[i].dy);
                if (bricksPlayer2[i].lives == 1)
                    iShowBMP2(bricksPlayer2[i].x, bricksPlayer2[i].y, "Images\\brick1.bmp", 0);
                else if (bricksPlayer2[i].lives == 2)
                    iShowBMP2(bricksPlayer2[i].x, bricksPlayer2[i].y, "Images\\brick2.bmp", 0);
                else if (bricksPlayer2[i].lives == 3)
                    iShowBMP2(bricksPlayer2[i].x, bricksPlayer2[i].y, "Images\\brick3.bmp", 0);
                secondWallLeft++;
            }
        }
        if (!secondWallLeft && playPage)
        {
            player2WinPage();
            playPage = 0;
            gameoverPage = 1;
            isStartedPlayer1 = false;
            isStartedPlayer2 = false;
            if (soundOn)
                PlaySound(TEXT("Sounds\\gameOver.wav"), NULL, SND_FILENAME | SND_ASYNC);
        }
        powerupRandomizer();
    }
    else if (gameoverPage == 1)
    {
        if (!firstWallLeft)
            player2WinPage();
        else if (!secondWallLeft)
            player1WinPage();
        xBall = ScreenWidth / 2;
        yBall = ScreenHeight / 2;
    }
}

void iMouseMove(int mx, int my) 
{

}

void iMouse(int button, int state, int mx, int my) 
{
    mouseButton = button;
    mouseState = state;

    if (state == GLUT_DOWN)
    {
        if(homePage == 1 && (mx >= 767 && mx <= 982) && (my >= 356 && my <= 403))
        {
            difficultyButtonClickHandler();
        }
        else if(homePage == 1 && (mx >= 767 && mx <= 982) && (my >= 103 && my <= 150))
        {
            aboutButtonClickHandler();
        }
        else if(homePage == 1 && (mx >= 767 && mx <= 982) && (my >= 274 && my <= 319))
        {
            instructionsButtonClickHandler();
        }
        else if(homePage == 1 && (mx >= 767 && mx <= 982) && (my >= 191 && my <= 235))
        {
            if (soundOn)
                soundOnButtonClickHandler();
            else
                soundOffButtonClickHandler();
        }
        else if(homePage == 1 && (mx >= 767 && mx <= 982) && (my >= 21 && my <= 66))
        {
            exit(1);
        }
        else if((homePage == 1 && soundOn==1) && (mx >= 767 && mx <= 982) && (my >= 191 && my <= 235))
        {
            soundOnButtonClickHandler();
        }
        else if((homePage == 1 && soundOn == 0) && (mx >= 767 && mx <= 982) && (my >= 191 && my <= 235))
        {
            soundOffButtonClickHandler();
        }
        else if((soundOffPage == 1 && soundOn == 0) && (mx >= 466 && mx <= 637) && (my >= 303 && my <= 339))
        {
            soundOnButtonClickHandler();
        }
        else if ((soundOnPage == 1 && soundOn == 1) && (mx >= 658 && mx <= 823) && (my >= 303 && my <= 339))
        {
            soundOffButtonClickHandler(); 
        }
        else if((aboutPage == 1 || instructionsPage == 1 || soundOnPage == 1 || soundOffPage == 1 || difficultyPage == 1) && (mx >= 19 && mx <= 53) && (my >= 542 && my <= 575))
        {
            backButtonClickHandler();
        }
        else if (difficultyPage)
        {
            if ((mx >= 310) && (mx <= 700) && (my >= 305 && my <= 385))
            {
                easyMode = 1;
                mediumMode = 0;
                difficultMode = 0;
                background = 3;
                dx = 50;
                dy = 25;
                ballMovementX = dx;
                ballMovementY = dy;
                radiusBall = 10;

                for (int i = 0; i < 2; i++)
                {
                    boards[i].dx = 25;
                    boards[i].dy = 135;
                }
                boards[0].movement = 63;
                boards[1].movement = 13;

                playButtonClickHandler();
            }
            else if ((mx >= 310) && (mx <= 700) && (my >= 185 && my <= 267))
            {
                easyMode = 0;
                mediumMode = 1;
                difficultMode = 0;
                background = 1;
                dx = 60;
                dy = 30;
                ballMovementX = dx;
                ballMovementY = dy;
                radiusBall = 10;

                for (int i = 0; i < 2; i++)
                {
                    boards[i].dx = 25;
                    boards[i].dy = 135;   
                }
                boards[0].movement = 62;
                boards[1].movement = 12;

                playButtonClickHandler();
            }
            else if ((mx >= 310) && (mx <= 700) && (my >= 68 && my <= 150))
            {
                easyMode = 0;
                mediumMode = 0;
                difficultMode = 1;
                dx = 70;
                dy = 35;
                ballMovementX = dx;
                ballMovementY = dy;
                radiusBall = 10;
                for (int i = 0; i < 2; i++)
                {
                    boards[i].dx = 25;
                    boards[i].dy = 135;
                }
                boards[0].movement = 61;
                boards[1].movement = 11;

                playButtonClickHandler();
            }

            time_t t;
            srand((unsigned) time(&t));

            while (!multiplierX)
            {
                multiplierX = (rand() % 3) - 1;
            }

            while (!multiplierY)
            {
                multiplierY = (rand() % 3) - 1;
            }

            dx *= multiplierX;
            dy *= multiplierY;
        }
        else if (gameoverPage)
        {
            dx = 10;
            dy = 5;
            if (mx >= 308 && mx <= 696 && my >= 309 && my <= 384)
                difficultyButtonClickHandler();
            else if (mx >= 308 && mx <= 696 && my>= 189 && my<=265)
                drawHomePage();
            else if (mx >= 313 && mx <= 696 && my >= 79 && my <= 142)
                exit(1);
        }
    }

    if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN && !isStartedPlayer2 && playPage)
        isStartedPlayer2 = true;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && isStartedPlayer1 && isStartedPlayer2) 
    {
        if (boards[1].y < ScreenHeight - boards[1].dy)
        {
            boards[1].y += boards[1].movement;
        }
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && isStartedPlayer1 && isStartedPlayer2) 
    {
        if (boards[1].y > 0)
        {
            boards[1].y -= boards[1].movement;
        }
    }
}

void iKeyboard(unsigned char key) 
{
    if (key == ' ' && playPage)
    {
        if (!isStartedPlayer1)
            isStartedPlayer1 = true;
    }

    if ((key == 'w' || key == 'W') && isStartedPlayer1 && isStartedPlayer2)
    {
        if (boards[0].y < ScreenHeight - boards[0].dy)
        {
            boards[0].y += boards[0].movement;
        }
    }
    else if ((key == 's' || key == 'S') && isStartedPlayer1 && isStartedPlayer2)
    {
        if (boards[0].y >= 0)
        {
            boards[0].y -= boards[0].movement;
        }
    }

    if (playPage && (key == 'q' || key == 'Q'))
        homePageButtonClickHandler();

    if (playPage && (key == 'p' || key == 'P'))
        pauseButtonClickHandler();

    if (pausePage && (key == 'p' || key == 'P'))
        playFromPause();

    if (key == 'b' || key == 'B')
    {
        if (!background)
            background = 1;
        else if (background == 1)
            background = 2;
        else if (background == 2)
            background = 3;
        else
            background = 0;
    }
}

void iSpecialKeyboard(unsigned char key) 
{
    if (key == GLUT_KEY_END)
        exit(1);
}

void boardInitialize()
{
    boards[0].x = player1Margin - 20;
    boards[0].y = (int)(ScreenHeight / 2) - (int)(boards[0].dy / 2);
    boards[1].x = ScreenWidth - player1Margin;
    boards[1].y = (int)(ScreenHeight / 2) - (int)(boards[1].dy / 2);
}

void ballChange()
{
    if (isStartedPlayer1 && isStartedPlayer2)
    {
        xBall += dx;
        yBall += dy;

        if (xBall >= ScreenWidth - radiusBall || xBall <= radiusBall)
        {
            dx *= (-1);
            if (xBall - radiusBall < 0)
                xBall = radiusBall;
            ballMovementX = dx;
            ballMovementY = dy;
        }

        if (yBall >= ScreenHeight - radiusBall || yBall <= radiusBall)
        {
            if (yBall - radiusBall < 0)
                yBall = radiusBall;
            dy *= (-1);
            ballMovementX = dx;
            ballMovementY = dy;
        }

        for (int i = 0; i < totalBricks / 2; i++)
        {
            if (bricksPlayer1[i].show)
            {
                if (xBall >= bricksPlayer1[i].x && xBall <= bricksPlayer1[i].x + bricksPlayer1[i].dx)
                {
                    if (yBall >= bricksPlayer1[i].y && yBall <= bricksPlayer1[i].y + bricksPlayer1[i].dy)
                    {
                        if (!PowerUps.active || PowerUps.type != 2)
                        {
                            dx *= (-1);
                            if (xBall - radiusBall < bricksPlayer1[i].x + bricksPlayer1[i].dx && difficultMode)
                                xBall = radiusBall + bricksPlayer1[i].x + bricksPlayer1[i].dx;
                            else if (xBall + radiusBall > bricksPlayer1[i].x && difficultMode)
                                xBall = bricksPlayer1[i].x - radiusBall;
                        }
                        ballMovementX = dx;
                        ballMovementY = dy;
                        if (bricksPlayer1[i].lives)
                        {
                            bricksPlayer1[i].lives--;

                            if (!bricksPlayer1[i].lives || (PowerUps.type == 2 && PowerUps.active))
                            {
                                bricksPlayer1[i].show = false;
                                bricksPlayer1[i].lives = 0;
                            }
                            else if (bricksPlayer1[i].lives == 2)
                            {
                                iShowBMP2(bricksPlayer1[i].x, bricksPlayer1[i].y, "Images\\brick2.bmp", 0);
                            }
                            else if (bricksPlayer1[i].lives == 1)
                            {
                                iShowBMP2(bricksPlayer1[i].x, bricksPlayer1[i].y, "Images\\brick1.bmp", 0);
                            }
                        }
                        if (soundOn)
                            brickCollisionSound();
                    }
                }
                else if (yBall >= bricksPlayer1[i].y && yBall <= bricksPlayer1[i].y + bricksPlayer1[i].dy)
                {
                    if (xBall >= bricksPlayer1[i].x && xBall <= bricksPlayer1[i].x + bricksPlayer1[i].dx)
                    {
                        if (!PowerUps.active || PowerUps.type != 2)
                        {
                            dy *= (-1);
                            if (yBall - radiusBall > bricksPlayer1[i].y + bricksPlayer1[i].dy && difficultMode)
                                yBall = radiusBall + bricksPlayer1[i].y + bricksPlayer1[i].dy;
                            else if (yBall + radiusBall > bricksPlayer1[i].y && difficultMode)
                                yBall = (abs)(bricksPlayer1[i].y - radiusBall);
                        }
                        ballMovementX = dx;
                        ballMovementY = dy;
                        if (bricksPlayer1[i].lives)
                        {
                            bricksPlayer1[i].lives--;

                            if (!bricksPlayer1[i].lives || (PowerUps.type == 2 && PowerUps.active))
                            {
                                bricksPlayer1[i].show = false;
                                bricksPlayer1[i].lives = 0;
                            }
                            else if (bricksPlayer1[i].lives == 2)
                            {
                                iShowBMP2(bricksPlayer2[i].x, bricksPlayer2[i].y, "Images\\brick2.bmp", 0);
                            }
                            else if (bricksPlayer1[i].lives == 1)
                            {
                                iShowBMP2(bricksPlayer2[i].x, bricksPlayer2[i].y, "Images\\brick1.bmp", 0);
                            }
                        }
                        if (soundOn)
                            brickCollisionSound();
                    }
                }
            }

            if (bricksPlayer2[i].show)
            {
                if (xBall >= bricksPlayer2[i].x && xBall <= bricksPlayer2[i].x + bricksPlayer2[i].dx)
                {
                    if (yBall >= bricksPlayer2[i].y && yBall <= bricksPlayer2[i].y + bricksPlayer2[i].dy)
                    {
                        if (!PowerUps.active || PowerUps.type != 2)
                        {
                            dx *= (-1);
                            if (xBall - radiusBall < bricksPlayer2[i].x + bricksPlayer2[i].dx && difficultMode)
                                xBall = bricksPlayer2[i].x - radiusBall;
                            else if (xBall + radiusBall > bricksPlayer2[i].x && difficultMode)
                                xBall = radiusBall + bricksPlayer2[i].x + bricksPlayer2[i].dx;
                        }
                        ballMovementX = dx;
                        ballMovementY = dy;
                        if (bricksPlayer2[i].lives)
                        {
                            bricksPlayer2[i].lives--;

                            if (!bricksPlayer2[i].lives || (PowerUps.type == 2 && PowerUps.active))
                            {
                                bricksPlayer2[i].show = false;
                                bricksPlayer2[i].lives = 0;
                            }
                            else if (bricksPlayer2[i].lives == 2)
                            {
                                if (bricksPlayer2[i].show)
                                    iShowBMP2(bricksPlayer2[i].x, bricksPlayer2[i].y, "Images\\brick2.bmp", 0);
                            }
                            else if (bricksPlayer2[i].lives == 1)
                            {
                                if (bricksPlayer2[i].show)
                                    iShowBMP2(bricksPlayer2[i].x, bricksPlayer2[i].y, "Images\\brick1.bmp", 0);
                            }
                        }
                        if (soundOn)
                            brickCollisionSound();
                    }
                }
                else if (yBall >= bricksPlayer2[i].y && yBall <= bricksPlayer2[i].y + bricksPlayer2[i].dy)
                {
                    if (xBall >= bricksPlayer2[i].x && xBall <= bricksPlayer2[i].x + bricksPlayer2[i].dx)
                    {
                        if (!PowerUps.active || PowerUps.type != 2)
                        {
                            dy *= (-1);
                            if (yBall - radiusBall > bricksPlayer2[i].y + bricksPlayer2[i].dy && difficultMode)
                                yBall = (abs)(bricksPlayer2[i].y - radiusBall);
                            else if (yBall + radiusBall > bricksPlayer2[i].y && difficultMode)
                                yBall = radiusBall + bricksPlayer2[i].y + bricksPlayer2[i].dy;
                        }
                        ballMovementX = dx;
                        ballMovementY = dy;
                        if (bricksPlayer2[i].lives)
                        {
                            bricksPlayer2[i].lives--;

                            if (!bricksPlayer2[i].lives || (PowerUps.type == 2 && PowerUps.active))
                            {
                                bricksPlayer2[i].show = false;
                                bricksPlayer2[i].lives = 0;
                            }
                            else if (bricksPlayer2[i].lives == 2)
                            {
                                if (bricksPlayer2[i].show)
                                    iShowBMP2(bricksPlayer2[i].x, bricksPlayer2[i].y, "Images\\brick2.bmp", 0);
                            }
                            else if (bricksPlayer2[i].lives == 1)
                            {
                                if (bricksPlayer2[i].show)
                                    iShowBMP2(bricksPlayer2[i].x, bricksPlayer2[i].y, "Images\\brick1.bmp", 0);
                            }
                        }
                        if (soundOn)
                            brickCollisionSound();
                    }
                }
            }
        }

        for (int i = 0; i < 2; i++)
        {
            if (xBall >= boards[i].x && xBall <= boards[i].x + boards[i].dx && yBall >= boards[i].y && yBall <= boards[i].y + boards[i].dy)
            {
                if (!i && difficultMode)
                {
                    if (xBall + radiusBall > boards[i].x)
                        xBall = boards[i].x + radiusBall;
                    else if (xBall - radiusBall < boards[i].x + boards[i].dx)
                        xBall = radiusBall + boards[i].x + boards[i].dx;
                }
                else if (i && difficultMode)
                {
                    if (xBall - radiusBall < boards[i].x + boards[i].dx)
                        xBall = boards[i].x + radiusBall;
                    else if (xBall + radiusBall > boards[i].x)
                        xBall = radiusBall + boards[i].x + boards[i].dx;
                }
                else if (easyMode || mediumMode)
                {
                    if (!i)
                    {
                        if (xBall + radiusBall > boards[i].x && dx > 0)
                            xBall = boards[i].x + radiusBall;
                        else if (xBall - radiusBall < boards[i].x + boards[i].dx && dx < 0)
                            xBall = radiusBall + boards[i].x + boards[i].dx;
                    }
                    else if (i)
                    {
                        if (xBall - radiusBall < boards[i].x + boards[i].dx && dx > 0)
                            xBall = boards[i].x + radiusBall;
                        else if (xBall + radiusBall > boards[i].x && dx < 0)
                            xBall = radiusBall + boards[i].x + boards[i].dx;
                    }
                }

                dx *= (-1);
                ballMovementX = dx;
                ballMovementY = dy;
                batCollisionSound();
                lastPlayerTouch = i + 1;
            }
        }

        if (PowerUps.show)
        {
            if (xBall >= PowerUps.x && xBall <= (PowerUps.x + powerupSize) && yBall >= PowerUps.y && yBall <= (PowerUps.y + powerupSize))
            {
                PowerUps.show = false;
                PowerUps.active = true;

                if (PowerUps.type == 0 && PowerUps.active)
                {
                    powerUpActivatedFor = lastPlayerTouch;
                    boards[lastPlayerTouch - 1].dy = (boards[lastPlayerTouch - 1].dx * 10);
                }
                else if (PowerUps.type == 1 && PowerUps.active)
                {
                    time_t timeVariable;
                    srand((unsigned)time(&timeVariable));

                    int index = rand() % 18;

                    if (lastPlayerTouch == 1)
                    {
                        while (bricksPlayer1[index].lives == 3)
                            int index = rand() % 18;

                        if (!bricksPlayer1[index].show)
                        {
                            bricksPlayer1[index].show = true;
                            bricksPlayer1[index].lives = 1;
                            iShowBMP2(bricksPlayer1[index].x, bricksPlayer1[index].y, "Images\\brick1.bmp", 0);
                        }
                        else if (bricksPlayer1[index].lives < 3 && bricksPlayer1[index].show)
                        {
                            bricksPlayer1[index].lives++;

                            if (bricksPlayer1[index].lives == 3)
                                iShowBMP2(bricksPlayer1[index].x, bricksPlayer1[index].y, "Images\\brick3.bmp", 0);
                            else if (bricksPlayer1[index].lives == 2)
                                iShowBMP2(bricksPlayer1[index].x, bricksPlayer1[index].y, "Images\\brick2.bmp", 0);
                            else if (bricksPlayer1[index].lives == 1)
                                iShowBMP2(bricksPlayer1[index].x, bricksPlayer1[index].y, "Images\\brick1.bmp", 0);
                        }
                    }
                    else if (lastPlayerTouch == 2)
                    {
                        while (bricksPlayer2[index].lives == 3)
                            int index = rand() % 18;

                        if (!bricksPlayer2[index].show)
                        {
                            bricksPlayer2[index].show = true;
                            bricksPlayer2[index].lives = 1;
                            iShowBMP2(bricksPlayer2[index].x, bricksPlayer2[index].y, "Images\\brick1.bmp", 0);
                        }
                        else if (bricksPlayer2[index].lives < 3 && bricksPlayer2[index].show)
                        {
                            bricksPlayer2[index].lives++;

                            if (bricksPlayer2[index].lives == 3)
                                iShowBMP2(bricksPlayer2[index].x, bricksPlayer2[index].y, "Images\\brick3.bmp", 0);
                            else if (bricksPlayer2[index].lives == 2)
                                iShowBMP2(bricksPlayer2[index].x, bricksPlayer2[index].y, "Images\\brick2.bmp", 0);
                            else if (bricksPlayer2[index].lives == 1)
                                iShowBMP2(bricksPlayer2[index].x, bricksPlayer2[index].y, "Images\\brick1.bmp", 0);
                        }
                    }

                    if (brickRegenrationTimedown)
                        brickRegenrationTimedown--;
                    else
                    {
                        brickRegenrationTimedown = 10;
                        PowerUps.active = false;
                    }
                }
                else if (PowerUps.type == 3 && PowerUps.active)
                {
                    powerUpActivatedFor = lastPlayerTouch;
                }
            }
        }
    }
}

void defineBricks()
{
    int sumx = 0;
    int sumy = 0;
    int limit = totalBricks / 2;

    if (easyMode)
        limit -= 12;
    else if (mediumMode)
        limit -= 6;

    for (int i = 0; i < totalBricks / 2; i++)
    {
        bricksPlayer1[i].x = sumx;
        bricksPlayer1[i].y = sumy;

        if (i < limit)
        {
            bricksPlayer1[i].show = true;
            bricksPlayer1[i].lives = 1;
        }
        else
        {
            bricksPlayer1[i].show = false;
            bricksPlayer1[i].lives = 0;
        }

        sumy += 100;

        if (sumy >= ScreenHeight)
        {
            sumy = 0;
            sumx += 20;
        }
    }

    if (mediumMode || difficultMode)
    {
        for (int i = 0; i < 6; i++)
        {
            bricksPlayer1[doubleLives[i]].lives = 2;
        }

        if (difficultMode)
        {
            for (int i = 0; i < 6; i++)
            {
                bricksPlayer1[tripleLives[i]].lives = 3;
            }
        }
    }

    sumx = ScreenWidth - 20;
    sumy = 0;

    for (int i = 0; i < totalBricks / 2; i++)
    {
        bricksPlayer2[i].x = sumx;
        bricksPlayer2[i].y = sumy;

        if (i < limit)
        {
            bricksPlayer2[i].show = true;
            bricksPlayer2[i].lives = 1;
        }
        else
        {
            bricksPlayer2[i].show = false;
            bricksPlayer2[i].lives = 0;
        }

        sumy += 100;

        if (sumy >= ScreenHeight)
        {
            sumy = 0;
            sumx -= 20;
        }
    }

    if (mediumMode || difficultMode)
    {
        for (int i = 0; i < 6; i++)
        {
            bricksPlayer2[doubleLives[i]].lives = 2;
        }

        if (difficultMode)
        {
            for (int i = 0; i < 6; i++)
            {
                bricksPlayer2[tripleLives[i]].lives = 3;
            }
        }
    }
}

void drawHomePage()
{
    iSetColor(0, 0, 0);
    iFilledRectangle(0, 0, ScreenWidth, ScreenHeight);
    iShowBMP2(0, 0, "Images\\Homepage.bmp", 0);
    homePage = 1;
    playPage = 0;
    aboutPage = 0;
    instructionsPage = 0;
    gameoverPage = 0;
    soundOnPage = 0;
    soundOffPage = 0;
    difficultyPage = 0;
    pausePage = 0;

    if (easyMode)
    {
        dx = 12;
        dy = 6;
    }
    else if (mediumMode)
    {
        dx = 14;
        dy = 7;
    }
    else if (difficultMode)
    {
        dx = 18;
        dy = 9;
    }
}

void drawSoundOnPage()
{
    iSetColor(0, 0, 0);
    iFilledRectangle(0, 0, ScreenWidth, ScreenHeight);
    iShowBMP2(0, 0, "Images\\soundon.bmp", 0);
}

void drawSoundOffPage()
{
    iSetColor(0, 0, 0);
    iFilledRectangle(0, 0, ScreenWidth, ScreenHeight);
    iShowBMP2(0, 0, "Images\\soundoff.bmp", 0);
}

void drawSettingsPage()
{
    iSetColor(0, 0, 0);
    iFilledRectangle(0, 0, ScreenWidth, ScreenHeight);
    iShowBMP2(0, 0, "Images\\Settings.bmp", 0);
}

void drawInstructionsPage()
{
    iSetColor(0, 0, 0);
    iFilledRectangle(0, 0, ScreenWidth, ScreenHeight);
    iShowBMP2(0, 0, "Images\\Instructions.bmp", 0);
}

void drawAboutPage()
{
    iSetColor(0, 0, 0);
    iFilledRectangle(0, 0, ScreenWidth, ScreenHeight);
    iShowBMP2(0, 0, "Images\\AboutUs.bmp", 0);
}

void drawDifficultyPage()
{
    iSetColor(0, 0, 0);
    iFilledRectangle(0, 0, ScreenWidth, ScreenHeight);
    iShowBMP2(0, 0, "Images\\difficulty.bmp", 0);
}

void player1WinPage()
{
    homePage = 0;
    playPage = 0;
    aboutPage = 0;
    soundOnPage = 0;
    soundOffPage = 0;
    instructionsPage = 0;
    gameoverPage = 1;
    difficultyPage = 0;
    pausePage = 0;
    iSetColor(0, 0, 0);
    iFilledRectangle(0, 0, ScreenWidth, ScreenHeight);
    iShowBMP2(0, 0, "Images\\Player-1.bmp", 0);
}

void player2WinPage()
{
    homePage = 0;
    playPage = 0;
    aboutPage = 0;
    soundOnPage = 0;
    soundOffPage = 0;
    instructionsPage = 0;
    gameoverPage = 1;
    difficultyPage = 0;
    pausePage = 0;
    iSetColor(0, 0, 0);
    iFilledRectangle(0, 0, ScreenWidth, ScreenHeight);
    iShowBMP2(0, 0, "Images\\Player-2.bmp", 0);
}

void playButtonClickHandler()
{
    homePage = 0;
    playPage = 1;
    aboutPage = 0;
    soundOnPage = 0;
    soundOffPage = 0;
    instructionsPage = 0;
    gameoverPage = 0;
    difficultyPage = 0;
    pausePage = 0;
    boardInitialize();
    defineBricks();

    if (easyMode)
    {
        dx = 12;
        dy = 6;
    }
    else if (mediumMode)
    {
        dx = 14;
        dy = 7;
    }
    else if (difficultMode)
    {
        dx = 18;
        dy = 9;
    }

    iSetTimer(ballMovementSeconds, ballChange);
    iSetTimer(ballMovementSeconds, powerupRandomizer);

    ballMovementSeconds += 50;

    if (ballMovementSeconds >= 1000)
        ballMovementSeconds = 1;
}

void aboutButtonClickHandler()
{
    homePage = 0;
    playPage = 0;
    aboutPage = 1;
    soundOnPage = 0;
    soundOffPage = 0;
    instructionsPage = 0;
    gameoverPage = 0;
    difficultyPage = 0;
    pausePage = 0;
}

void backButtonClickHandler()
{
    homePage = 1;
    playPage = 0;
    aboutPage = 0;
    instructionsPage = 0;
    soundOnPage = 0;
    soundOffPage = 0;
    gameoverPage = 0;
    difficultyPage = 0;
    pausePage = 0;
}

void instructionsButtonClickHandler()
{
    homePage = 0;
    playPage = 0;
    aboutPage = 0;
    instructionsPage = 1;
    soundOnPage = 0;
    soundOffPage = 0;
    gameoverPage = 0;
    difficultyPage = 0;
    pausePage = 0;
}

void soundOnButtonClickHandler()
{
    homePage = 0;
    playPage = 0;
    aboutPage = 0;
    instructionsPage = 0;
    soundOnPage = 1;
    soundOn = 1;
    soundOffPage = 0;
    gameoverPage = 0;
    difficultyPage = 0;
    pausePage = 0;
}

void soundOffButtonClickHandler()
{
    homePage = 0;
    playPage = 0;
    aboutPage = 0;
    instructionsPage = 0;
    soundOffPage = 1;
    soundOn = 0;
    soundOnPage = 0;
    gameoverPage = 0;
    difficultyPage = 0;
    pausePage = 0;
}

void batCollisionSound()
{
    if (soundOn)
        PlaySound(TEXT("Sounds\\batCollision.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void brickCollisionSound()
{
    if (soundOn)
        PlaySound(TEXT("Sounds\\brickCollision.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void homePageButtonClickHandler()
{
    homePage = 1;
    playPage = 0;
    aboutPage = 0;
    instructionsPage = 0;
    gameoverPage = 0;
    soundOnPage = 0;
    soundOffPage = 0;
    difficultyPage = 0;
    pausePage = 0;

    lastPlayerTouch = 0;
    PowerUps.show = false;
    PowerUps.active = false;
    powerUpActivatedFor = 0;

    for (int i = 0; i < (totalBricks / 2); i++)
    {
        bricksPlayer1[i].show = false;
        bricksPlayer2[i].show = false;
    }

    isStartedPlayer1 = false;
    isStartedPlayer2 = false;

    xBall = ScreenWidth / 2;
    yBall = ScreenHeight / 2;

    boards[0].x = ScreenWidth / 2;
    boards[1].x = ScreenWidth / 2;
}

void difficultyButtonClickHandler()
{
    homePage = 0;
    playPage = 0;
    aboutPage = 0;
    instructionsPage = 0;
    gameoverPage = 0;
    soundOnPage = 0;
    soundOffPage = 0;
    difficultyPage = 1;
    pausePage = 0;

    lastPlayerTouch = 0;
    PowerUps.show = false;
    PowerUps.active = false;
    powerUpActivatedFor = 0;

    slowDown = 200;

    for (int i = 0; i < (totalBricks / 2); i++)
    {
        bricksPlayer1[i].show = false;
        bricksPlayer2[i].show = false;
    }

    isStartedPlayer1 = false;
    isStartedPlayer2 = false;

    xBall = ScreenWidth / 2;
    yBall = ScreenHeight / 2;

    boards[0].x = ScreenWidth / 2;
    boards[1].x = ScreenWidth / 2;
}

void pauseButtonClickHandler()
{
    homePage = 0;
    playPage = 0;
    aboutPage = 0;
    instructionsPage = 0;
    gameoverPage = 0;
    soundOnPage = 0;
    soundOffPage = 0;
    difficultyPage = 0;
    pausePage = 1;

    dx = 0;
    dy = 0;

    for (int i = 0; i < 2; i++)
    {
        boards[i].movement = 0;
    }

    isStartedPlayer1 = false;
    isStartedPlayer2 = false;
}

void playFromPause()
{
    homePage = 0;
    playPage = 1;
    aboutPage = 0;
    instructionsPage = 0;
    gameoverPage = 0;
    soundOnPage = 0;
    soundOffPage = 0;
    difficultyPage = 0;
    pausePage = 0;

    dx = ballMovementX;
    dy = ballMovementY;

    radiusBall = 10;

    for (int i = 0; i < 2; i++)
    {
        boards[i].dx = 25;
        boards[i].dy = 135;
    }

    if (easyMode)
    {
        boards[0].movement = 63;
        boards[1].movement = 13;
    }
    else if (mediumMode)
    {
        boards[0].movement = 62;
        boards[1].movement = 12;
    }
    else if (difficultMode)
    {
        boards[0].movement = 61;
        boards[1].movement = 11;
    }
}

void powerupRandomizer()
{
    time_t timeVar;
    srand((unsigned)time(&timeVar));
    int axisX = 0, axisY = 0;
    int shouldItBeActivated = rand() % 5;

    if (!isStartedPlayer1 || !isStartedPlayer2)
        PowerUps.show = false;

    if (lastPlayerTouch && !slowDown && !PowerUps.show && !shouldItBeActivated && !PowerUps.active && isStartedPlayer1 && isStartedPlayer2)
    {
        PowerUps.type = rand() % noOfPowerUps;
        PowerUps.show = true;
        axisX = rand() % (ScreenWidth - (4 * player1Margin)) - 100;
        axisX += ((ScreenWidth - (2 * player1Margin)) / 2);
        axisY = (rand() % (ScreenHeight - 100));
        PowerUps.x = axisX;
        PowerUps.y = axisY;
    }

    if (PowerUps.show)
    {
        if (isStartedPlayer1 && isStartedPlayer2)
            PowerUps.displayTime--;

        if (PowerUps.active)
        {
            PowerUps.displayTime = 0;
            PowerUps.show = false;
        }

        if (PowerUps.displayTime)
        {
            if (PowerUps.type == 0 && !PowerUps.active)
            {
                iShowBMP2(PowerUps.x, PowerUps.y, "Images\\doubler.bmp", 0);
            }
            else if (PowerUps.type == 1 && !PowerUps.active)
            {
                iShowBMP2(PowerUps.x, PowerUps.y, "Images\\brickRegeneration.bmp", 0);
            }
            else if (PowerUps.type == 2 && !PowerUps.active)
            {
                if (fireBallAnimation == 1)
                {
                    iShowBMP2(PowerUps.x, PowerUps.y, "Images\\fireBall1.bmp", 0);
                    fireBallAnimation++;
                }
                else if (fireBallAnimation == 2)
                {
                    iShowBMP2(PowerUps.x, PowerUps.y, "Images\\fireBall2.bmp", 0);
                    fireBallAnimation++;
                }
                else if (fireBallAnimation == 3)
                {
                    iShowBMP2(PowerUps.x, PowerUps.y, "Images\\fireBall3.bmp", 0);
                    fireBallAnimation++;
                }
                else if (fireBallAnimation == 4)
                {
                    iShowBMP2(PowerUps.x, PowerUps.y, "Images\\fireBall4.bmp", 0);
                    fireBallAnimation = 1;
                }
            }
            else if (PowerUps.type == 3 && !PowerUps.active)
            {
                iShowBMP2(PowerUps.x, PowerUps.y, "Images\\invisibility.bmp", 0);
            }
        }

        if (!PowerUps.displayTime)
        {
            PowerUps.displayTime = showTime;
            PowerUps.show = false;
        }
    }

    if (PowerUps.active)
    {
        PowerUps.show = false;

        if (PowerUps.type == 0 || PowerUps.type == 2 || PowerUps.type == 3)
        {
            if (isStartedPlayer1 && isStartedPlayer2)
                PowerUps.activeTime--;

            if (PowerUps.active && !PowerUps.activeTime)
            {
                PowerUps.active = false;
                PowerUps.activeTime = activationPeriod;

                if (PowerUps.type == 0)
                {
                    boards[powerUpActivatedFor - 1].dy = 135;
                }
            }
        }
    }
}

int main()
{
    iInitialize(ScreenWidth, ScreenHeight, "DX Tennis");
    return 0;
}