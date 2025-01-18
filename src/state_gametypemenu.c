
#include <SDL.h>
#include "cgametypemenu.h"
#include "gamefuncs.h"
#include "common.h"
#include "state_gametypemenu.h"

void GameTypeMenu()
{
    SDL_Event Event;
    CGameTypeMenu *Menu = CGameTypeMenu_Create();
    GameType = Fixed;
    while (GameState == GSGameTypeMenu)
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

            if(Event.type == SDL_JOYHATMOTION)
                switch (Event.jhat.value)
                {                   
                    case 1: //up
                        CGameTypeMenu_NextItem(Menu);
                        break;
                    case 4: //down
                        CGameTypeMenu_PreviousItem(Menu);
                        break;
                    default:
                        break;
                }
            
            if (Event.type == SDL_JOYBUTTONDOWN)
            {
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
                        if (GlobalSoundEnabled)
                            Mix_PlayChannel(-1,Sounds[SND_SELECT],0);
                        switch(CGameTypeMenu_GetSelection(Menu))
                        {
                            case Fixed:
                                GameType = Fixed;
                                break;
                            case Relative:
                                GameType = Relative;
                                break;
                        }
                        GameState = GSReadyGo;
                        break;
                    case GP2X_BUTTON_B:
                        GameState = GSTitleScreen;
                        break;
                }
            }

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
                        CGameTypeMenu_NextItem(Menu);
                        break;
                    case SDLK_d: //down
                        CGameTypeMenu_PreviousItem(Menu);
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
                        if (GlobalSoundEnabled)
                            Mix_PlayChannel(-1,Sounds[SND_SELECT],0);
                        switch(CGameTypeMenu_GetSelection(Menu))
                        {
                            case Fixed:
                                GameType = Fixed;
                                break;
                            case Relative:
                                GameType = Relative;
                                break;
                        }
                        GameState = GSReadyGo;
                        break;
                    case SDLK_b:
                        GameState = GSTitleScreen;
                        break;
                    default:
                        break;
                }
            }
        }
        CGameTypeMenu_Draw(Menu, Screen);
        SDL_Flip(Screen);
    }
    CGameTypeMenu_Destroy(Menu);
}

