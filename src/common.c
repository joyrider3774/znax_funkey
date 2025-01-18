#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include "defines.h"


struct CWorldParts;

SDL_Surface *IMGBackground=NULL,*IMGBlocks=NULL,*IMGCursor=NULL,*IMGReady=NULL,*IMGGo=NULL,*IMGTimeOver=NULL,*IMGIntro1=NULL, *IMGIntro2=NULL,*IMGIntro3=NULL,
            *IMGTitleScreen=NULL,*IMGQuit1=NULL,*IMGQuit2=NULL,*IMGPlay1=NULL,*IMGPlay2=NULL,*IMGHighScores1=NULL,*IMGHighScores2=NULL,*IMGCredits1=NULL,*IMGCredits2=NULL,
            *IMGCredits=NULL,*IMGSelectGame=NULL,*IMGFixedTimer1=NULL,*IMGFixedTimer2=NULL,*IMGRelativeTimer1=NULL,*IMGRelativeTimer2=NULL,*IMGHighScores;



Mix_Chunk *Sounds[NrOfSounds];
Mix_Music *Music[MaxMusicFiles];

bool GlobalSoundEnabled = true;
int Timer = 150, AddToScore = 0;
SDL_Surface *Screen;
TTF_Font* font,*BigFont,*MonoFont;
SDL_Joystick *Joystick;
int GameState = GSIntro;
int MusicCount=0,SelectedMusic=0,Volume = 96,Score=0;
int GameType = Fixed;
SHighScore HighScores[2][10];