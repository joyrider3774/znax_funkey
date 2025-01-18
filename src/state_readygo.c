
#include <SDL.h>
#include "gamefuncs.h"
#include "common.h"
#include "cworldparts.h"
#include "state_readygo.h"

void ReadyGo()
{
    SDL_Rect Dst;
    SDL_Event Event;
    CWorldParts_NewGame(World);
    Score = 0;
    Uint32 Time2 = SDL_GetTicks();
    int Counter=0;
    if(GameType == Relative)
        Timer = 150;
    else
        Timer = 300;
    if (MusicCount > 1)
    {
        SelectedMusic =	1+rand()%(MusicCount-1);
        Mix_PlayMusic(Music[SelectedMusic],0);
        SetVolume(Volume);
    }
    else
        if(MusicCount ==1)
        {
            if(!Mix_PlayingMusic())
            {
                SelectedMusic =	0;
                Mix_PlayMusic(Music[SelectedMusic],0);
                SetVolume(Volume);
            }
        }
    while (GameState == GSReadyGo)
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

			if (Event.type == SDL_JOYBUTTONDOWN)
			{
				switch (Event.jbutton.button)
				{
					case GP2X_BUTTON_B:
						GameState = GSTitleScreen;
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
                    case SDLK_n:
						IncVolume();
						break;
					case SDLK_m:
						DecVolume();
						break;
                    default:
                        break;
				}
			}
		}
		CWorldParts_Draw(World, Screen);
		switch(Counter)
		{
		    case 1 :
                Dst.x = (WINDOW_WIDTH - IMGReady->w) / 2;
                Dst.y = (WINDOW_HEIGHT - IMGReady->h) / 2;
                Dst.w = IMGReady->w;
                Dst.h = IMGReady->h;
                SDL_BlitSurface(IMGReady,NULL,Screen,&Dst);
                break;
            case 2 :
                Dst.x = (WINDOW_WIDTH - IMGGo->w) / 2;
                Dst.y = (WINDOW_HEIGHT - IMGGo->h) / 2;
                Dst.w = IMGGo->w;
                Dst.h = IMGGo->h;
                SDL_BlitSurface(IMGGo,NULL,Screen,&Dst);
                break;
            case 3 :
                GameState = GSGame;
                break;
		}
        DrawStatusBar(Screen);
        SDL_Flip(Screen);
        if (Time2 < SDL_GetTicks())
        {
            Counter++;
            if(Counter == 1)
                if(GlobalSoundEnabled)
                    Mix_PlayChannel(-1,Sounds[SND_READYGO],0);
            if (Counter == 2)
            {
                Time2 = SDL_GetTicks() + 400;
            }
            else
                Time2 = SDL_GetTicks() + 900;
        }

    }
}
