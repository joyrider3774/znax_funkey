
#include <SDL.h>
#include "gamefuncs.h"
#include "common.h"
#include "state_intro.h"

void Intro()
{
    SDL_Event Event;
    Uint32 Time=0;
    int IntroScreenNr = 1;
    Time = SDL_GetTicks();
    while (GameState == GSIntro)
    {
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
                   case GP2X_BUTTON_VOLUP:
						IncVolume();
						break;
					case GP2X_BUTTON_VOLDOWN:
						DecVolume();
						break;
                    case GP2X_BUTTON_A:
                    case GP2X_BUTTON_B:
                    case GP2X_BUTTON_X:
                    case GP2X_BUTTON_Y:
                    case GP2X_BUTTON_START:
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
                    case SDLK_n:
						IncVolume();
						break;
					case SDLK_m:
						DecVolume();
						break;
                    case SDLK_a:
                    case SDLK_b:
                    case SDLK_x:
                    case SDLK_y:
                    case SDLK_s:
                        GameState = GSTitleScreen;
                        break;
                    default:
                        break;
                }
            }
        }

        switch(IntroScreenNr)
        {
            case 1 :
                SDL_BlitSurface(IMGIntro1,NULL,Screen,NULL);
                break;
            case 2 :
                SDL_BlitSurface(IMGIntro2,NULL,Screen,NULL);
                break;
            case 3 :
                SDL_BlitSurface(IMGIntro3,NULL,Screen,NULL);
                break;
        }
        SDL_Flip(Screen);

        if(Time + 3700 < SDL_GetTicks())
        {
            IntroScreenNr++;
            if(IntroScreenNr > 3)
                GameState = GSTitleScreen;
            Time = SDL_GetTicks();
        }

    }
    if (GlobalSoundEnabled)
        Mix_PlayChannel(-1,Sounds[SND_WELCOME],0);
}
