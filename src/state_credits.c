
#include <SDL.h>
#include "gamefuncs.h"
#include "common.h"
#include "state_credits.h"

void Credits()
{
    SDL_Rect Rect1;
    SDL_Event Event;
    Rect1.x = 33;
    Rect1.y = 85;
    Rect1.w = IMGCredits->w;
    Rect1.h = IMGCredits->h;
    while (GameState == GSCredits)
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

            if (Event.type == SDL_JOYBUTTONDOWN)
                switch (Event.jbutton.button)
                {
                    case GP2X_BUTTON_VOLUP:
						IncVolume();
						break;
					case GP2X_BUTTON_VOLDOWN:
						DecVolume();
						break;
                    default :
                        GameState = GSTitleScreen;
                        break;
                }
            
            if (Event.type == SDL_KEYDOWN)
                switch (Event.key.keysym.sym)
                {
                    case SDLK_q:
                        GameState = GSQuit;
                        Mix_HaltMusic();
                        if (GlobalSoundEnabled)
                            Mix_PlayChannel(-1,Sounds[SND_GOODBYE],0);
                        SDL_Delay(750);
                        break;
                    case SDLK_n:
						IncVolume();
						break;
					case SDLK_m:
						DecVolume();
						break;
                    default :
                        GameState = GSTitleScreen;
                        break;
                }

        }

        SDL_BlitSurface(IMGTitleScreen,NULL,Screen,NULL);
        SDL_BlitSurface(IMGCredits,NULL,Screen,&Rect1);
        SDL_Flip(Screen);
    }
}
