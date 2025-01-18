
#include <SDL.h>
#include "gamefuncs.h"
#include "common.h"
#include "cworldparts.h"
#include "cselector.h"
#include "state_game.h"

void Game()
{
    SDL_Event Event;
    Uint32 Time = SDL_GetTicks();
    Uint32 ScoreTimer = 0;
    CSelector* Selector = CSelector_Create(NrOfCols / 2, NrOfRows / 2);
    AddToScore = 0;
    if(GameType == Relative)
        Timer = 150;
    else
        Timer = 300;
    while (GameState == GSGame)
    {
        if(!Mix_PlayingMusic())
        if(GlobalSoundEnabled)
        {
            if (MusicCount > 1)
            {
                SelectedMusic =	1+rand()%(MusicCount-1);
                Mix_PlayMusic(Music[SelectedMusic],0);
                SetVolume(Volume);
            }
            else
                if(MusicCount ==1)
                {
                    SelectedMusic =	0;
                    Mix_PlayMusic(Music[SelectedMusic],0);
                    SetVolume(Volume);
                }

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
                    case 8: //left
                        CSelector_SetPosition(Selector, Selector->CurrentPoint.X -1,Selector->CurrentPoint.Y);
                        break;
                    case 2: //right
                        CSelector_SetPosition(Selector, Selector->CurrentPoint.X +1,Selector->CurrentPoint.Y);
                        break;
                    case 1: //up
                        CSelector_SetPosition(Selector, Selector->CurrentPoint.X,Selector->CurrentPoint.Y-1);
                        break;
                    case 4: //down
                        CSelector_SetPosition(Selector, Selector->CurrentPoint.X,Selector->CurrentPoint.Y+1);
                        break;
                    default:
                        break;
                }
            }  

			if (Event.type == SDL_JOYBUTTONDOWN)
			{
				switch (Event.jbutton.button)
				{
					case GP2X_BUTTON_B:
						GameState = GSTitleScreen;
						break;
                    case GP2X_BUTTON_A :
                    case GP2X_BUTTON_X :
                    case GP2X_BUTTON_Y :
                        AddToScore+= CWorldParts_Select(World, Selector->CurrentPoint.X,Selector->CurrentPoint.Y);
                        if(AddToScore != 0)
                        {
                            ScoreTimer = SDL_GetTicks() + 700;
                        }
                        break;                    
                    case GP2X_BUTTON_VOLUP:
						IncVolume();
						break;
					case GP2X_BUTTON_VOLDOWN:
						DecVolume();
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
					case SDLK_b:
						GameState = GSTitleScreen;
						break;
                    case SDLK_a :
                    case SDLK_x :
                    case SDLK_y :
                        AddToScore+= CWorldParts_Select(World, Selector->CurrentPoint.X,Selector->CurrentPoint.Y);
                        if(AddToScore != 0)
                        {
                            ScoreTimer = SDL_GetTicks() + 700;
                        }
                        break;                    
                    case SDLK_n:
						IncVolume();
						break;
					case SDLK_m:
						DecVolume();
						break;
                    case SDLK_l: //left
                        CSelector_SetPosition(Selector, Selector->CurrentPoint.X -1,Selector->CurrentPoint.Y);
                        break;
                    case SDLK_r: //right
                        CSelector_SetPosition(Selector, Selector->CurrentPoint.X +1,Selector->CurrentPoint.Y);
                        break;
                    case SDLK_u: //up
                        CSelector_SetPosition(Selector, Selector->CurrentPoint.X,Selector->CurrentPoint.Y-1);
                        break;
                    case SDLK_d: //down
                        CSelector_SetPosition(Selector, Selector->CurrentPoint.X,Selector->CurrentPoint.Y+1);
                        break;
                    default:
                        break;
				}                
			}
		}
		CWorldParts_Draw(World, Screen);
        CSelector_Draw(Selector, Screen);
        if(AddToScore !=0)
        {
            if(ScoreTimer <= SDL_GetTicks())
            {
                ScoreTimer = 0;
                Score +=AddToScore;
                if (GameType == Relative)
                    Timer += AddToScore / 400;
                AddToScore = 0;
            }
        }
        DrawStatusBar(Screen);
        SDL_Flip(Screen);
        if (Time +1000 < SDL_GetTicks())
        {
            Timer-= 1;
            switch (Timer)
            {
                case 300 :
                    if (GlobalSoundEnabled)
                        Mix_PlayChannel(-1,Sounds[SND_5MINUTE],0);
                    break;
                case 60:
                    if (GlobalSoundEnabled)
                        Mix_PlayChannel(-1,Sounds[SND_1MINUTE],0);
                    break;
                case 3 :
                    if (GlobalSoundEnabled)
                        Mix_PlayChannel(-1,Sounds[SND_3],0);
                    break;
                case 2 :
                    if (GlobalSoundEnabled)
                        Mix_PlayChannel(-1,Sounds[SND_2],0);
                    break;
                case 1 :
                    if (GlobalSoundEnabled)
                        Mix_PlayChannel(-1,Sounds[SND_1],0);
                    break;
                case 0 :
                    if(ScoreTimer != 0)
                    {
                        Score += AddToScore;
                        if(GameType == Relative)
                            Timer += AddToScore / 200;
                    }
                    if(Timer == 0)
                    {
                        if (GlobalSoundEnabled)
                            Mix_PlayChannel(-1,Sounds[SND_TIMEOVER],0);
                        GameState = GSTimeOver;
                    }
                    break;
            }
            Time = SDL_GetTicks();
        }

    }
    CSelector_Destroy(Selector);
}
