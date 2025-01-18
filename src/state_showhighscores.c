
#include <SDL.h>
#include "gamefuncs.h"
#include "common.h"
#include "state_showhighscores.h"

void ShowHighScores()
{
    SDL_Event Event;
    SDL_Color TextColor = {102,115,152,255};
    int Teller = 0;
    char Text[250];
    int ScoreType = GameType;
    while (GameState == GSShowHighScores)
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
                    case GP2X_BUTTON_START:
                    case GP2X_BUTTON_X:
                    case GP2X_BUTTON_Y:
                        if (ScoreType == Fixed)
                            ScoreType = Relative;
                        else
                            GameState = GSTitleScreen;
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
                    case SDLK_n:
						IncVolume();
						break;
					case SDLK_m:
						DecVolume();
						break;
                    case SDLK_a:
                    case SDLK_s:
                    case SDLK_x:
                    case SDLK_y:
                        if (ScoreType == Fixed)
                            ScoreType = Relative;
                        else
                            GameState = GSTitleScreen;
                        break;                    
                    case SDLK_b:
                        GameState = GSTitleScreen;
                        break;
                    default:
                        break;
                }
            }
        }
        SDL_BlitSurface(IMGHighScores,NULL,Screen,NULL);
        switch(ScoreType)
        {
            case Fixed :
                sprintf(Text,"Gametype: Fixed Timer" );
                break;
            case Relative :
                sprintf(Text,"Gametype: Relative Timer" );
                break;
        }

		WriteText(Screen,font,Text,strlen(Text),45*SCALE,226*SCALE,0,TextColor);
        for(Teller = 0;Teller<10;Teller++)
        {
            sprintf(Text,"%2d.%s",Teller+1,HighScores[ScoreType][Teller].PName);
            WriteText(Screen,MonoFont,Text,strlen(Text),3*SCALE,(62+Teller*16)*SCALE,0,TextColor);
            sprintf(Text,"%7ld",HighScores[ScoreType][Teller].PScore);
            WriteText(Screen,MonoFont,Text,strlen(Text),180*SCALE,(62+Teller*16)*SCALE,0,TextColor);
        }
        SDL_Flip(Screen);


    }
}
