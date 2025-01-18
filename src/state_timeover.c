
#include <SDL.h>
#include <stdbool.h>
#include "gamefuncs.h"
#include "common.h"
#include "state_timeover.h"
#include "cworldparts.h"
#include "state_gethighscorename.h"

void TimeOver()
{
    char Name[21];
    int Teller1,Teller2;
    SDL_Rect Dst;
    SDL_Event Event;
    Uint32 Time2 = SDL_GetTicks() + 1250;
    int Counter=0;
    Timer = 0;
    memset(&Name[0], 0, 21 * sizeof(char));
    CWorldParts_DeSelect(World, false);

    while (GameState == GSTimeOver)
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
		    case 0 :
                Dst.x = (WINDOW_WIDTH - IMGTimeOver->w) / 2;
                Dst.y = (WINDOW_HEIGHT - IMGTimeOver->h) / 2;                
                Dst.w = IMGTimeOver->w;
                Dst.h = IMGTimeOver->h;
                SDL_BlitSurface(IMGTimeOver,NULL,Screen,&Dst);
                break;
		}
        DrawStatusBar(Screen);
        SDL_Flip(Screen);
        if (Time2 < SDL_GetTicks())
        {
            GameState = GSShowHighScores;
        }

    }
    for(Teller1 =0;Teller1<10;Teller1++)
        if(HighScores[GameType][Teller1].PScore < Score)
        {
            GetHighScoreName(Name,Teller1,Score);
            for(Teller2=8;Teller2>=Teller1;Teller2--)
                HighScores[GameType][Teller2+1] = HighScores[GameType][Teller2];
            if((strcmp(Name," ") == 0))
                sprintf(HighScores[GameType][Teller1].PName,"%s","player");
            else
                sprintf(HighScores[GameType][Teller1].PName,"%s",Name);
            HighScores[GameType][Teller1].PScore = Score;
            break;
        }
}
