
#include <SDL.h>
#include <stdbool.h>
#include "gamefuncs.h"
#include "common.h"
#include "state_gethighscorename.h"

void GetHighScoreName(char NameIn[21],int Place, long PScore)
{
	char Name[21];
	char Msg[500];
	bool End=false,SubmitChanges=false;
	int Teller,MaxSelection=0, Selection = 0,asci=97;
	SDL_Event Event;
	SDL_Color TextColor = {102,115,152,255}, TextColor1 = {255,115,152,255};;
    memset(&Name[0], 0, 21 * sizeof(char));
	SDL_PollEvent(&Event);
	sprintf(Name,"%s",NameIn);
	MaxSelection = strlen(NameIn);
	Name[Selection+1]='\0';
	if (MaxSelection == 0)
		Name[MaxSelection]=chr(asci);
	char Tekst[100];
	while (!End)
	{
        if(MusicCount > 0)
        {
            if(GlobalSoundEnabled)
            {
                if(!Mix_PlayingMusic())
                {
                    SelectedMusic = 0;
                    Mix_PlayMusic(Music[SelectedMusic],0);
                    SetVolume(Volume);
                }
            }
        }
		while (SDL_PollEvent(&Event))
		{
			if(Event.type == SDL_QUIT)
            {
				End = true;
				SubmitChanges = false;
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
						if (Selection > 0)
						{	Selection--;
							asci = ord(Name[Selection]);
						}
						break;
					case 2: //right
						if (Selection < 16)
						{
							Selection++;
							if (Selection > MaxSelection)
							{
								Name[Selection] = chr(97);
								Name[Selection+1] = '\0';
								MaxSelection=Selection;
							}
							asci = ord(Name[Selection]);
						}
						break;
					case 1: // up
						asci++;
						if (asci==123)
                        {
							asci=32;
                        }
						if (asci==33)
                        {
							(asci=48);
                        }
						if (asci==58)
                        {
							asci=97;
                        }
						Name[Selection] = chr(asci);
						break;
					case 4: //down
						asci--;
						if(asci==96)
                        {
						    asci=57;
                        }
						if(asci==47)
                        {
							asci=32;
                        }
						if(asci==31)
                        {
							asci=122;
                        }
						Name[Selection] = chr(asci);
						break;
                    default:
                        break;            
                }
            }

			if (Event.type == SDL_JOYBUTTONDOWN)
			{
				switch(Event.jbutton.button)
				{					
					case GP2X_BUTTON_A:
						if (GlobalSoundEnabled)
							Mix_PlayChannel(-1,Sounds[SND_SELECT],0);
						End = true;
						SubmitChanges=true;
						break;
                    case GP2X_BUTTON_B:
						End=true;
						SubmitChanges=false;
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
				switch(Event.key.keysym.sym)
				{	
					case SDLK_q:
						End = true;
						SubmitChanges = false;
						GameState = GSQuit;
						Mix_HaltMusic();
						if (GlobalSoundEnabled)
						Mix_PlayChannel(-1,Sounds[SND_GOODBYE],0);
						SDL_Delay(750);
						break;
					case SDLK_a:
						if (GlobalSoundEnabled)
							Mix_PlayChannel(-1,Sounds[SND_SELECT],0);
						End = true;
						SubmitChanges=true;
						break;
                    case SDLK_b:
						End=true;
						SubmitChanges=false;
						break;
                    case SDLK_n:
						IncVolume();
						break;
					case SDLK_m:
						DecVolume();
						break;
					case SDLK_l: //left
						if (Selection > 0)
						{	Selection--;
							asci = ord(Name[Selection]);
						}
						break;
					case SDLK_r: //right
						if (Selection < 16)
						{
							Selection++;
							if (Selection > MaxSelection)
							{
								Name[Selection] = chr(97);
								Name[Selection+1] = '\0';
								MaxSelection=Selection;
							}
							asci = ord(Name[Selection]);
						}
						break;
					case SDLK_u: // up
						asci++;
						if (asci==123)
                        {
							asci=32;
                        }
						if (asci==33)
                        {
							(asci=48);
                        }
						if (asci==58)
                        {
							asci=97;
                        }
						Name[Selection] = chr(asci);
						break;
					case SDLK_d: //down
						asci--;
						if(asci==96)
                        {
						    asci=57;
                        }
						if(asci==47)
                        {
							asci=32;
                        }
						if(asci==31)
                        {
							asci=122;
                        }
						Name[Selection] = chr(asci);
						break;
                    default:
                        break;
				}
			}
		}
        SDL_BlitSurface(IMGHighScores,NULL,Screen,NULL);

        for(Teller = 0;Teller<9;Teller++)
        {
            if(Teller < Place)
            {
                sprintf(Msg,"%2d.%s",Teller+1,HighScores[GameType][Teller].PName);
                WriteText(Screen,MonoFont,Msg,strlen(Msg),3*SCALE,(62+Teller*16)*SCALE,0,TextColor);
                sprintf(Msg,"%7ld",HighScores[GameType][Teller].PScore);
                WriteText(Screen,MonoFont,Msg,strlen(Msg),180*SCALE,(62+Teller*16)*SCALE,0,TextColor);
            }
            else
            {
                sprintf(Msg,"%2d.%s",Teller+2,HighScores[GameType][Teller].PName);
                WriteText(Screen,MonoFont,Msg,strlen(Msg),3*SCALE,(62+(Teller+1)*16)* SCALE,0,TextColor);
                sprintf(Msg,"%7ld",HighScores[GameType][Teller].PScore);
                WriteText(Screen,MonoFont,Msg,strlen(Msg),180*SCALE,(62+(Teller+1)*16)*SCALE,0,TextColor);
            }
        }
		sprintf(Msg,"%2d.%s",Place+1,Name);
		WriteText(Screen,MonoFont,Msg,strlen(Msg),3*SCALE,(62+Place*16)*SCALE,0,TextColor1);
		sprintf(Msg,"%7ld",PScore);
        WriteText(Screen,MonoFont,Msg,strlen(Msg),180*SCALE,(62+Place*16)*SCALE,0,TextColor1);
		if (Selection > 0)
		{
			sprintf(Tekst,"    ");
			for (Teller=1;Teller<Selection;Teller++)
				strcat(Tekst," ");
			strcat(Tekst,"_");
		}
		else
			sprintf(Tekst,"   _");
		WriteText(Screen,MonoFont,Tekst,strlen(Tekst),3*SCALE,(62+(Place)*16)*SCALE,2,TextColor1);
		sprintf(Tekst,"Use Up,Down,Left,right A=Ok B=Cancel" );
		WriteText(Screen,font,Tekst,strlen(Tekst),1*SCALE,226*SCALE,0,TextColor);
        SDL_Flip(Screen);
	}
	Name[MaxSelection+1] = '\0';
	while ((Name[0] == ' ') && (MaxSelection>-1))
	{
		for (Teller=0;Teller<MaxSelection;Teller++)
			Name[Teller] = Name[Teller+1];
		MaxSelection--;
	}
	if (MaxSelection>-1)
		while ((Name[MaxSelection] == ' ') && (MaxSelection>0))
		{
			Name[MaxSelection] = '\0';
			MaxSelection--;
		}
	if (!SubmitChanges)
		sprintf(NameIn,"%s"," ");
    else
        sprintf(NameIn,"%s",Name);
}
