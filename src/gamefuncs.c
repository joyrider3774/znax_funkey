#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <stdio.h>
#include "common.h"
#include "defines.h"

void LoadSounds()
{
    if(GlobalSoundEnabled)
    {
		Sounds[SND_READYGO] = Mix_LoadWAV("./sound/readygo.wav");
		Sounds[SND_1] = Mix_LoadWAV("./sound/one.wav");
		Sounds[SND_2] = Mix_LoadWAV("./sound/two.wav");
		Sounds[SND_3] = Mix_LoadWAV("./sound/three.wav");
		Sounds[SND_1MINUTE] = Mix_LoadWAV("./sound/oneminute.wav");
		Sounds[SND_5MINUTE] = Mix_LoadWAV("./sound/fiveminute.wav");
		Sounds[SND_TIMEOVER] = Mix_LoadWAV("./sound/timeover.wav");
		Sounds[SND_MENU] = Mix_LoadWAV("./sound/menu.wav");
		Sounds[SND_SELECT] = Mix_LoadWAV("./sound/select.wav");
		Sounds[SND_WELCOME] = Mix_LoadWAV("./sound/welcome.wav");
		Sounds[SND_GOODBYE] = Mix_LoadWAV("./sound/goodbye.wav");
		Sounds[SND_DELETE] = Mix_LoadWAV("./sound/delete.wav");
		Sounds[SND_BLOCKSELECT] = Mix_LoadWAV("./sound/blockselect.wav");
		Sounds[SND_ERROR] = Mix_LoadWAV("./sound/error.wav");
    }
}

void UnloadSounds()
{
    if (GlobalSoundEnabled)
    {
        if (!Mix_PlayingMusic())
            Mix_HaltMusic();

        int Teller;
        for (Teller=0;Teller<NrOfSounds;Teller++)
            if(Sounds[Teller])
                Mix_FreeChunk(Sounds[Teller]);
    }

}

void LoadHighScores()
{
    FILE *FHighScores;
 	char Filename[512];
    sprintf(Filename,"%s/.Znax_highscore.dat", getenv("HOME") == NULL ? ".": getenv("HOME"));
 	FHighScores = fopen(Filename, "rb");
 	int Teller = 0;
 	if(FHighScores)
 	{
        fread(HighScores[Fixed],sizeof(HighScores[Fixed][0]),10,FHighScores);
        fread(HighScores[Relative],sizeof(HighScores[Relative][0]),10,FHighScores);
		fclose(FHighScores);
 	}
 	else
 	{
 	    for (Teller = 0;Teller<10;Teller++)
 	    {
 	        sprintf(HighScores[Fixed][Teller].PName,"%s","joyrider");
 	        sprintf(HighScores[Relative][Teller].PName,"%s","joyrider");
 	        HighScores[Fixed][Teller].PScore = 0;
 	        HighScores[Relative][Teller].PScore = 0;
 	    }
 	}
}

void SaveHighScores()
{
    FILE *FHighScores;
 	char Filename[512];
    sprintf(Filename,"%s/.Znax_highscore.dat", getenv("HOME") == NULL ? ".": getenv("HOME"));
 	FHighScores = fopen(Filename, "wb");
 	if(FHighScores)
 	{
        fwrite(HighScores[Fixed],sizeof(HighScores[Fixed][0]),10,FHighScores);
        fwrite(HighScores[Relative],sizeof(HighScores[Relative][0]),10,FHighScores);
		fclose(FHighScores);
 	}
}


bool FileExists(char * FileName)
{
	FILE *Fp;
	Fp = fopen(FileName,"rb");
	if (Fp)
	{
		fclose(Fp);
		return true;
	}
	else
		return false;
}

void UnloadMusic()
{
	int Teller;
	if (GlobalSoundEnabled)
	{
		Mix_HaltMusic();
		for (Teller=0;Teller < MusicCount;Teller++)
			if (Music[Teller])
				Mix_FreeMusic(Music[Teller]);
	}
}

void SearchForMusic()
{
	MusicCount = 0;
    if (GlobalSoundEnabled)
    {
		Music[0] = Mix_LoadMUS("./music/title.mod");
        MusicCount++;
    }
	
}

void UnLoadGraphics()
{
    if(IMGHighScores)
        SDL_FreeSurface(IMGHighScores);
    if(IMGSelectGame)
        SDL_FreeSurface(IMGSelectGame);
    if(IMGFixedTimer2)
        SDL_FreeSurface(IMGFixedTimer2);
    if(IMGRelativeTimer2)
        SDL_FreeSurface(IMGRelativeTimer2);
    if(IMGFixedTimer1)
        SDL_FreeSurface(IMGFixedTimer1);
    if(IMGRelativeTimer1)
        SDL_FreeSurface(IMGRelativeTimer1);
    if(IMGIntro1)
        SDL_FreeSurface(IMGIntro1);
    if(IMGIntro2)
        SDL_FreeSurface(IMGIntro2);
    if(IMGIntro3)
        SDL_FreeSurface(IMGIntro3);
    if(IMGTimeOver)
        SDL_FreeSurface(IMGTimeOver);
    if(IMGBlocks)
        SDL_FreeSurface(IMGBlocks);
    if(IMGBackground)
        SDL_FreeSurface(IMGBackground);
    if(IMGCursor)
        SDL_FreeSurface(IMGCursor);
    if(IMGReady)
        SDL_FreeSurface(IMGReady);
    if(IMGGo)
        SDL_FreeSurface(IMGGo);
    if(IMGPlay1)
        SDL_FreeSurface(IMGPlay1);
    if(IMGPlay2)
        SDL_FreeSurface(IMGPlay2);
    if(IMGCredits1)
        SDL_FreeSurface(IMGCredits1);
    if(IMGCredits2)
        SDL_FreeSurface(IMGCredits2);
    if(IMGQuit1)
        SDL_FreeSurface(IMGQuit1);
    if(IMGQuit2)
        SDL_FreeSurface(IMGQuit2);
    if(IMGHighScores1)
        SDL_FreeSurface(IMGHighScores1);
    if(IMGHighScores2)
        SDL_FreeSurface(IMGHighScores2);
    if(IMGTitleScreen)
        SDL_FreeSurface(IMGTitleScreen);
    if(IMGCredits)
        SDL_FreeSurface(IMGCredits);
}

void LoadGraphics()
{
    SDL_Surface *Tmp;

    if(IMGHighScores)
        SDL_FreeSurface(IMGHighScores);
    if(IMGSelectGame)
        SDL_FreeSurface(IMGSelectGame);
    if(IMGFixedTimer2)
        SDL_FreeSurface(IMGFixedTimer2);
    if(IMGRelativeTimer2)
        SDL_FreeSurface(IMGRelativeTimer2);
    if(IMGFixedTimer1)
        SDL_FreeSurface(IMGFixedTimer1);
    if(IMGRelativeTimer1)
        SDL_FreeSurface(IMGRelativeTimer1);
    if(IMGIntro1)
        SDL_FreeSurface(IMGIntro1);
    if(IMGIntro2)
        SDL_FreeSurface(IMGIntro2);
    if(IMGIntro3)
        SDL_FreeSurface(IMGIntro3);
    if(IMGTimeOver)
        SDL_FreeSurface(IMGTimeOver);
    if(IMGBlocks)
        SDL_FreeSurface(IMGBlocks);
    if(IMGBackground)
        SDL_FreeSurface(IMGBackground);
    if(IMGCursor)
        SDL_FreeSurface(IMGCursor);
    if(IMGReady)
        SDL_FreeSurface(IMGReady);
    if(IMGGo)
        SDL_FreeSurface(IMGGo);
    if(IMGPlay1)
        SDL_FreeSurface(IMGPlay1);
    if(IMGPlay2)
        SDL_FreeSurface(IMGPlay2);
    if(IMGCredits1)
        SDL_FreeSurface(IMGCredits1);
    if(IMGCredits2)
        SDL_FreeSurface(IMGCredits2);
    if(IMGQuit1)
        SDL_FreeSurface(IMGQuit1);
    if(IMGQuit2)
        SDL_FreeSurface(IMGQuit2);
    if(IMGHighScores1)
        SDL_FreeSurface(IMGHighScores1);
    if(IMGHighScores2)
        SDL_FreeSurface(IMGHighScores2);
    if(IMGTitleScreen)
        SDL_FreeSurface(IMGTitleScreen);
    if(IMGCredits)
        SDL_FreeSurface(IMGCredits);


    Tmp = IMG_Load("./graphics/highscores.png");
    IMGHighScores= SDL_DisplayFormat(Tmp);
    SDL_FreeSurface(Tmp);

    Tmp = IMG_Load("./graphics/fixedtimer1.png");
    IMGFixedTimer1= SDL_DisplayFormatAlpha(Tmp);
    SDL_FreeSurface(Tmp);

    Tmp = IMG_Load("./graphics/relativetimer1.png");
    IMGRelativeTimer1= SDL_DisplayFormatAlpha(Tmp);
    SDL_FreeSurface(Tmp);

    Tmp = IMG_Load("./graphics/fixedtimer2.png");
    IMGFixedTimer2= SDL_DisplayFormatAlpha(Tmp);
    SDL_FreeSurface(Tmp);

    Tmp = IMG_Load("./graphics/relativetimer2.png");
    IMGRelativeTimer2= SDL_DisplayFormatAlpha(Tmp);
    SDL_FreeSurface(Tmp);

    Tmp = IMG_Load("./graphics/selectgame.png");
    IMGSelectGame= SDL_DisplayFormatAlpha(Tmp);
    SDL_FreeSurface(Tmp);

    Tmp = IMG_Load("./graphics/credits.png");
    IMGCredits= SDL_DisplayFormatAlpha(Tmp);
    SDL_FreeSurface(Tmp);

    Tmp = IMG_Load("./graphics/titlescreen.png");
    IMGTitleScreen= SDL_DisplayFormatAlpha(Tmp);
    SDL_FreeSurface(Tmp);

    Tmp = IMG_Load("./graphics/play1.png");
    IMGPlay1 = SDL_DisplayFormatAlpha(Tmp);
    SDL_FreeSurface(Tmp);

    Tmp = IMG_Load("./graphics/play2.png");
    IMGPlay2 = SDL_DisplayFormatAlpha(Tmp);
    SDL_FreeSurface(Tmp);

    Tmp = IMG_Load("./graphics/quit1.png");
    IMGQuit1 = SDL_DisplayFormatAlpha(Tmp);
    SDL_FreeSurface(Tmp);

    Tmp = IMG_Load("./graphics/quit2.png");
    IMGQuit2 = SDL_DisplayFormatAlpha(Tmp);
    SDL_FreeSurface(Tmp);

    Tmp = IMG_Load("./graphics/credits2.png");
    IMGCredits2 = SDL_DisplayFormatAlpha(Tmp);
    SDL_FreeSurface(Tmp);

    Tmp = IMG_Load("./graphics/credits1.png");
    IMGCredits1 = SDL_DisplayFormatAlpha(Tmp);
    SDL_FreeSurface(Tmp);

    Tmp = IMG_Load("./graphics/highscores2.png");
    IMGHighScores2 = SDL_DisplayFormatAlpha(Tmp);
    SDL_FreeSurface(Tmp);

    Tmp = IMG_Load("./graphics/highscores1.png");
    IMGHighScores1 = SDL_DisplayFormatAlpha(Tmp);
    SDL_FreeSurface(Tmp);





    Tmp = IMG_Load("./graphics/intro1.png");
    IMGIntro1 = SDL_DisplayFormat(Tmp);
    SDL_FreeSurface(Tmp);

     Tmp = IMG_Load("./graphics/intro2.png");
    IMGIntro2 = SDL_DisplayFormat(Tmp);
    SDL_FreeSurface(Tmp);

    Tmp = IMG_Load("./graphics/intro3.png");
    IMGIntro3 = SDL_DisplayFormat(Tmp);
    SDL_FreeSurface(Tmp);

    Tmp = IMG_Load("./graphics/timeover.png");
    IMGTimeOver = SDL_DisplayFormatAlpha(Tmp);
    SDL_FreeSurface(Tmp);

    Tmp = IMG_Load("./graphics/ready.png");
    IMGReady = SDL_DisplayFormatAlpha(Tmp);
    SDL_FreeSurface(Tmp);

    Tmp = IMG_Load("./graphics/go.png");
    IMGGo = SDL_DisplayFormatAlpha(Tmp);
    SDL_FreeSurface(Tmp);

    Tmp = IMG_Load("./graphics/cursor.png");
    IMGCursor = SDL_DisplayFormatAlpha(Tmp);
    SDL_FreeSurface(Tmp);

    Tmp = IMG_Load("./graphics/blocks.png");
    IMGBlocks = SDL_DisplayFormatAlpha(Tmp);
    SDL_FreeSurface(Tmp);


    Tmp = IMG_Load("./graphics/background.png");
    IMGBackground = SDL_DisplayFormat(Tmp);
    SDL_FreeSurface(Tmp);
}

// set the volume of the music and both channels (left/right)
void SetVolume(const int VolumeIn)
{
	Mix_Volume(0,VolumeIn);
	Mix_Volume(1,VolumeIn);
	Mix_VolumeMusic(VolumeIn);
}

// increase the volume with 8
void IncVolume()
{
	if (Volume < 128)
	{
		Volume += 8;
		SetVolume(Volume);
	}
}

// decrease the volume with 8
void DecVolume()
{
	if (Volume > 0)
	{
		Volume-= 8;
		SetVolume(Volume);
	}
}

void LoadSettings()
{
 	FILE *SettingsFile;
 	char Filename[512];
    sprintf(Filename,"%s/.Znax_settings.dat", getenv("HOME") == NULL ? ".": getenv("HOME"));
 	SettingsFile = fopen(Filename,"r");
 	if(SettingsFile)
 	{
		fscanf(SettingsFile,"Volume=%d\n",&Volume);
		SetVolume(Volume);		
		fclose(SettingsFile);
 	}
 	else
 	{
        Volume = 96;
		SetVolume(Volume);
	}
}

void SaveSettings()
{
 	FILE *SettingsFile;
    char Filename[512];
    sprintf(Filename,"%s/.Znax_settings.dat", getenv("HOME") == NULL ? ".": getenv("HOME"));
 	SettingsFile = fopen(Filename,"w");
 	if(SettingsFile)
 	{
		fprintf(SettingsFile,"Volume=%d\n",Volume);        
		fclose(SettingsFile);
 	}
}


void WriteText(SDL_Surface* Surface,TTF_Font* FontIn,char* Tekst,int NrOfChars,int X,int Y,int YSpacing,SDL_Color ColorIn)
{
	char List[100][255];
	int Lines,Teller,Chars;
	SDL_Rect DstRect;
	SDL_Surface *TmpSurface1;
	Lines = 0;
	Chars = 0;
	for (Teller=0;Teller<NrOfChars;Teller++)
	{
		if(Lines > 100)
			break;
		if((Tekst[Teller] == '\n') || (Chars==255))
		{
			List[Lines][Chars]='\0';
			Lines++;
			Chars = 0;
		}
		else
		{
		 	List[Lines][Chars]=Tekst[Teller];
		 	Chars++;
		}
	}
	List[Lines][Chars] = '\0';
	for (Teller=0;Teller <= Lines;Teller++)
	{
		if(strlen(List[Teller]) > 0)
		{
			TmpSurface1 = TTF_RenderText_Blended(FontIn,List[Teller],ColorIn);
			if (TmpSurface1)
			{
				DstRect.x = X;
				DstRect.y = Y + (Teller) * TTF_FontLineSkip(FontIn) + (Teller*YSpacing);
				DstRect.w = TmpSurface1->w;
				DstRect.h = TmpSurface1->h;
				SDL_BlitSurface(TmpSurface1,NULL,Surface,&DstRect);
				SDL_FreeSurface(TmpSurface1);
			}
		}
	}
}

void DrawStatusBar(SDL_Surface* Target)
{
    char Text[200];
    SDL_Color TextColor = {255,255,255,255};
    if(AddToScore == 0)
        sprintf(Text,"T:%02d:%02d     S:%d",Timer/60,Timer%60,Score);
    else
    {
        if(GameType == Relative)
            sprintf(Text,"T:%02d:%02d+%03d S:%d+%d",Timer/60,Timer%60,AddToScore/400,Score, AddToScore);
        else
            sprintf(Text,"T:%02d:%02d     S:%d+%d",Timer/60,Timer%60,Score, AddToScore);
    }
    
    WriteText(Target,MonoFont,Text,strlen(Text),3*SCALE,-1*SCALE,0,TextColor);


}

char chr(int ascii)
{
	return((char)ascii);
}

int ord(char chr)
{
	return((int)chr);
}

