#ifndef GAMEFUNCS_H
#define GAMEFUNCS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdbool.h>

void DrawStatusBar(SDL_Surface* Target);

void UnloadSounds();

void LoadSounds();

void SaveHighScores();

void LoadHighScores();

bool FileExists(char * FileName);

void UnloadMusic();

void SearchForMusic();

void UnLoadGraphics();

void LoadGraphics();

// set the volume of the music and both channels (left/right)
void SetVolume(const int VolumeIn);

// increase the volume with 8
void IncVolume();

// decrease the volume with 8
void DecVolume();

void LoadSettings();

void SaveSettings();

void WriteText(SDL_Surface* Surface,TTF_Font* FontIn,char* Tekst,int NrOfChars,int X,int Y,int YSpacing,SDL_Color ColorIn);

char chr(int ascii);
int ord(char chr);

#endif