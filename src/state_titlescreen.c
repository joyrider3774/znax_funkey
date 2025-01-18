
#include <SDL.h>
#include "gamefuncs.h"
#include "common.h"
#include "cmainmenu.h"
#include "state_titlescreen.h"

void TitleScreen()
{
    SDL_Event Event;
    CMainMenu *Menu = CMainMenu_Create();
    while (GameState == GSTitleScreen)
    {
       if(MusicCount > 0)
            if(GlobalSoundEnabled)
                if(!Mix_PlayingMusic())
                {
                    SelectedMusic = 0;
                    Mix_PlayMusic(Music[SelectedMusic],0);
                    SetVolume(Volume);
                }
        while (SDL_PollEvent(&Event))
		{
            if(Event.type == SDL_QUIT)
            {
                GameState = GSQuit;
                Mix_HaltMusic();
                if (GlobalSoundEnabled)
                   Mix_PlayChannel(-1,Sounds[SND_GOODBYE],0);
                SDL_Delay(750);
            }

            if (Event.type == SDL_JOYHATMOTION)
            {
                switch (Event.jhat.value)
                {
                    case 1: //up
                        CMainMenu_PreviousItem(Menu);
                        break;
                    case 4: //down
                        CMainMenu_NextItem(Menu);
                        break;
                    case 8: //left
                    case 2: //right
                    default:
                        break;            
                }
            }
            else
		    if (Event.type == SDL_KEYDOWN)
            {
                switch (Event.key.keysym.sym)
                {   
                    case SDLK_q:
                        GameState = GSQuit;
                        Mix_HaltMusic();
                        if (GlobalSoundEnabled)
                            Mix_PlayChannel(-1,Sounds[SND_GOODBYE],0);
                        SDL_Delay(750);
                        break;
                    case SDLK_u: //up
                        CMainMenu_PreviousItem(Menu);
                        break;
                    case SDLK_d: //down
                        CMainMenu_NextItem(Menu);
                        break;          
                    case SDLK_n:
						IncVolume();
						break;
					case SDLK_m:
						DecVolume();
						break;
                    case SDLK_x:
                    case SDLK_y:
                    case SDLK_a:
                    case SDLK_s:
                        if(CMainMenu_GetSelection(Menu) != 4)
                            if (GlobalSoundEnabled)
                                Mix_PlayChannel(-1,Sounds[SND_SELECT],0);
                        switch(CMainMenu_GetSelection(Menu))
                        {
                            case 1:
                                GameState = GSGameTypeMenu;
                                break;
                            case 2:
                                GameType = Fixed;
                                GameState = GSShowHighScores;
                                break;
                            case 3:
                                GameState = GSCredits;
                                break;
                            case 4:
                                GameState = GSQuit;
                                Mix_HaltMusic();
                                if (GlobalSoundEnabled)
                                    Mix_PlayChannel(-1,Sounds[SND_GOODBYE],0);
                                SDL_Delay(750);
                                break;
                        }
                        break;
                    case SDLK_b:
                        GameState = GSQuit;
                        Mix_HaltMusic();
                        if (GlobalSoundEnabled)
                            Mix_PlayChannel(-1,Sounds[SND_GOODBYE],0);
                        SDL_Delay(750);
                        break;
                    default:
                        break;
                }
            }

            if (Event.type == SDL_JOYBUTTONDOWN)
                switch (Event.jbutton.button)
                {                    
                    case GP2X_BUTTON_VOLUP:
						IncVolume();
						break;
					case GP2X_BUTTON_VOLDOWN:
						DecVolume();
						break;
                    case GP2X_BUTTON_X:
                    case GP2X_BUTTON_Y:
                    case GP2X_BUTTON_A:
                    case GP2X_BUTTON_START:
                        if(CMainMenu_GetSelection(Menu) != 4)
                            if (GlobalSoundEnabled)
                                Mix_PlayChannel(-1,Sounds[SND_SELECT],0);
                        switch(CMainMenu_GetSelection(Menu))
                        {
                            case 1:
                                GameState = GSGameTypeMenu;
                                break;
                            case 2:
                                GameType = Fixed;
                                GameState = GSShowHighScores;
                                break;
                            case 3:
                                GameState = GSCredits;
                                break;
                            case 4:
                                GameState = GSQuit;
                                Mix_HaltMusic();
                                if (GlobalSoundEnabled)
                                    Mix_PlayChannel(-1,Sounds[SND_GOODBYE],0);
                                SDL_Delay(750);
                                break;
                        }
                        break;
                    case GP2X_BUTTON_B:
                        GameState = GSQuit;
                        Mix_HaltMusic();
                        if (GlobalSoundEnabled)
                            Mix_PlayChannel(-1,Sounds[SND_GOODBYE],0);
                        SDL_Delay(750);
                        break;
                }
        }
        CMainMenu_Draw( Menu, Screen);
        SDL_Flip(Screen);
    }
    CMainMenu_Destroy(Menu);
}
