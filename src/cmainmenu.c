#include <SDL.h>
#include <SDL_mixer.h>
#include "common.h"
#include "cmainmenu.h"

// constructor of main menu will Load the graphics and set the current selection to 1 (io newgame)
CMainMenu* CMainMenu_Create()
{
    CMainMenu* Result = (CMainMenu*) malloc(sizeof(CMainMenu));
    Result->Selection = 1;
    return Result;
}

// destructor
void CMainMenu_Destroy(CMainMenu* MainMenu)
{
    free(MainMenu);
    MainMenu = NULL;
}

// return the current selection
int CMainMenu_GetSelection(CMainMenu* MainMenu) 
{
    return MainMenu->Selection;
}

// Increase the selection if it goes to far set i to the first selection
void CMainMenu_NextItem(CMainMenu* MainMenu)
{
    MainMenu->Selection++;
    if (MainMenu->Selection == 5)
        MainMenu->Selection = 1;
    if (GlobalSoundEnabled)
        Mix_PlayChannel(-1,Sounds[SND_MENU],0);
}

// decrease the selection if it goes to low set it to the last selection
void CMainMenu_PreviousItem(CMainMenu* MainMenu)
{
    MainMenu->Selection--;
    if (MainMenu->Selection == 0)
        MainMenu->Selection = 4;
    if (GlobalSoundEnabled)
        Mix_PlayChannel(-1,Sounds[SND_MENU],0);
}

// Draw the main menu
void CMainMenu_Draw(CMainMenu* MainMenu, SDL_Surface *Surface)
{
    SDL_Rect Dest;


    SDL_BlitSurface(IMGTitleScreen,NULL,Surface,NULL);
    if (MainMenu->Selection == 1)
    {
        Dest.x = (WINDOW_WIDTH - IMGPlay2->w) / 2;
        Dest.y = 73*SCALE;
        Dest.w = IMGPlay2->w;
        Dest.h = IMGPlay2->h;
        SDL_BlitSurface(IMGPlay2,NULL,Surface,&Dest);
    }
    else
    {
        Dest.x = (WINDOW_WIDTH - IMGPlay1->w) / 2;
        Dest.y = 73 *SCALE;
        Dest.w = IMGPlay1->w;
        Dest.h = IMGPlay1->h;
        SDL_BlitSurface(IMGPlay1,NULL,Surface,&Dest);
    }

    if (MainMenu->Selection == 2)
    {
        Dest.x = (WINDOW_WIDTH - IMGHighScores2->w) / 2;
        Dest.y = 105 *SCALE;
        Dest.w = IMGHighScores2->w;
        Dest.h = IMGHighScores2->h;
        SDL_BlitSurface(IMGHighScores2,NULL,Surface,&Dest);
    }
    else
    {
        Dest.x =  (WINDOW_WIDTH - IMGHighScores1->w) / 2;
        Dest.y = 105 *SCALE;
        Dest.w = IMGHighScores1->w;
        Dest.h = IMGHighScores1->h;
        SDL_BlitSurface(IMGHighScores1,NULL,Surface,&Dest);
    }


    if (MainMenu->Selection == 3)
    {
        Dest.x = (WINDOW_WIDTH - IMGCredits2->w) / 2;
        Dest.y = 137 *SCALE;
        Dest.w = IMGCredits2->w;
        Dest.h = IMGCredits2->h;
        SDL_BlitSurface(IMGCredits2,NULL,Surface,&Dest);

    }
    else
    {
        Dest.x = (WINDOW_WIDTH - IMGCredits1->w) / 2;
        Dest.y = 137 *SCALE;
        Dest.w = IMGCredits1->w;
        Dest.h = IMGCredits1->h;
        SDL_BlitSurface(IMGCredits1,NULL,Surface,&Dest);

    }

    if (MainMenu->Selection == 4)
    {
        Dest.x = (WINDOW_WIDTH - IMGQuit2->w) / 2;
        Dest.y = 169 *SCALE;
        Dest.w = IMGQuit2->w;
        Dest.h = IMGQuit2->h;
        SDL_BlitSurface(IMGQuit2,NULL,Surface,&Dest);
    }
    else
    {
        Dest.x = (WINDOW_WIDTH - IMGQuit1->w) / 2;
        Dest.y = 169 *SCALE;
        Dest.w = IMGQuit1->w;
        Dest.h = IMGQuit1->h;
        SDL_BlitSurface(IMGQuit1,NULL,Surface,&Dest);
    }

}
