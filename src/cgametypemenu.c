#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "SDL_mixer.h"
#include "common.h"
#include "defines.h"
#include "cgametypemenu.h"


// constructor of main menu will Load the graphics and set the current selection to 1 (io newgame)
CGameTypeMenu* CGameTypeMenu_Create()
{
    CGameTypeMenu* Result = (CGameTypeMenu*) malloc(sizeof(CGameTypeMenu));
    Result->Selection = Fixed;
    return Result;
}

// return the current selection
int CGameTypeMenu_GetSelection(CGameTypeMenu* GameTypeMenu) 
{
    return GameTypeMenu->Selection;
}

// Destructor will free the surface images
void CGameTypeMenu_Destroy(CGameTypeMenu* GameTypeMenu)
{
    free(GameTypeMenu);
    GameTypeMenu = NULL;
}

// Increase the selection if it goes to far set i to the first selection
void CGameTypeMenu_NextItem(CGameTypeMenu* GameTypeMenu)
{
    GameTypeMenu->Selection++;
    if (GameTypeMenu->Selection == 2)
        GameTypeMenu->Selection = 0;
    if (GlobalSoundEnabled)
        Mix_PlayChannel(-1,Sounds[SND_MENU],0);
}

// decrease the selection if it goes to low set it to the last selection
void CGameTypeMenu_PreviousItem(CGameTypeMenu* GameTypeMenu)
{
    GameTypeMenu->Selection--;
    if (GameTypeMenu->Selection == -1)
        GameTypeMenu->Selection = 1;
    if (GlobalSoundEnabled)
        Mix_PlayChannel(-1,Sounds[SND_MENU],0);
}

// Draw the main menu
void CGameTypeMenu_Draw(CGameTypeMenu* GameTypeMenu, SDL_Surface *Surface)
{
    SDL_Rect Dest;

    // draw the title screen background
    SDL_BlitSurface(IMGTitleScreen,NULL,Surface,NULL);
    Dest.x = (WINDOW_WIDTH - IMGSelectGame->w) / 2;
    Dest.y = 77*SCALE;
    Dest.w = IMGSelectGame->w;
    Dest.h = IMGSelectGame->h;
    SDL_BlitSurface(IMGSelectGame,NULL,Surface,&Dest);

    if (GameTypeMenu->Selection == Fixed)
    {
        Dest.x = (WINDOW_WIDTH - IMGFixedTimer2->w) / 2;
        Dest.y = 114*SCALE;
        Dest.w = IMGFixedTimer2->w;
        Dest.h = IMGFixedTimer2->h;
        SDL_BlitSurface(IMGFixedTimer2,NULL,Surface,&Dest);
    }
    else
    {
        Dest.x = (WINDOW_WIDTH - IMGFixedTimer1->w) / 2;
        Dest.y = 114 *SCALE;
        Dest.w = IMGFixedTimer1->w;
        Dest.h = IMGFixedTimer1->h;
        SDL_BlitSurface(IMGFixedTimer1,NULL,Surface,&Dest);
    }

    if (GameTypeMenu->Selection == Relative)
    {
        Dest.x = (WINDOW_WIDTH - IMGRelativeTimer2->w) / 2;
        Dest.y = 151*SCALE;
        Dest.w = IMGRelativeTimer2->w;
        Dest.h = IMGRelativeTimer2->h;
        SDL_BlitSurface(IMGRelativeTimer2,NULL,Surface,&Dest);
    }
    else
    {
        Dest.x = (WINDOW_WIDTH - IMGRelativeTimer1->w) / 2;
        Dest.y = 151 *SCALE;
        Dest.w = IMGRelativeTimer1->w;
        Dest.h = IMGRelativeTimer1->h;
        SDL_BlitSurface(IMGRelativeTimer1,NULL,Surface,&Dest);
    }
}
