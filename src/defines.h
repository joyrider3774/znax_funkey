#ifndef DEFINES_H
#define DEFINES_H

#define WINDOW_WIDTH 240
#define WINDOW_HEIGHT 240

#define GP2X_BUTTON_UP              (20)
#define GP2X_BUTTON_DOWN            (21)
#define GP2X_BUTTON_LEFT            (22)
#define GP2X_BUTTON_RIGHT           (23)
#define GP2X_BUTTON_UPLEFT          (24)
#define GP2X_BUTTON_UPRIGHT         (25)
#define GP2X_BUTTON_DOWNLEFT        (26)
#define GP2X_BUTTON_DOWNRIGHT       (27)
#define GP2X_BUTTON_CLICK           (8)
#define GP2X_BUTTON_A               (0)
#define GP2X_BUTTON_B               (1)
#define GP2X_BUTTON_Y               (3)
#define GP2X_BUTTON_X               (2)
#define GP2X_BUTTON_L               (4)
#define GP2X_BUTTON_R               (5)
#define GP2X_BUTTON_START           (6)
#define GP2X_BUTTON_SELECT          (7)
#define GP2X_BUTTON_VOLUP           (28)
#define GP2X_BUTTON_VOLDOWN         (29)


//gamestates
#define GSQuit 0 
#define GSIntro 1 
#define GSGame 2 
#define GSTitleScreen 3 
#define GSTimeOver 4 
#define GSReadyGo 5 
#define GSCredits 6 
#define GSGameTypeMenu 7 
#define GSShowHighScores 8

//gametypes
#define Fixed 0
#define Relative 1

#define NrOfSounds 14
#define NrOfRows 11
#define NrOfCols 11
#define NrOfBlockColors 5
#define BlockBlue 0
#define BlockYellow 1
#define BlockOrange 2
#define BlockGreen 3
#define BlockRed 4
#define MaxMusicFiles 26
#define TileWidth 20
#define TileHeight 20
#define SND_READYGO 0
#define SND_5MINUTE 1
#define SND_1MINUTE 2
#define SND_3 3
#define SND_2 4
#define SND_1 5
#define SND_TIMEOVER 6
#define SND_MENU 7
#define SND_SELECT 8
#define SND_WELCOME 9
#define SND_GOODBYE 10
#define SND_DELETE 11
#define SND_BLOCKSELECT 12
#define SND_ERROR 13

#define SCALE 1.0f


struct SHighScore
{
    char PName[21];
    long PScore;
};
typedef struct SHighScore SHighScore;

struct SPoint
{
    int X,Y;
};

typedef struct SPoint SPoint;

#endif