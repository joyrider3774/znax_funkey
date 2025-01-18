#include <SDL.h>
#include <SDL_mixer.h>
#include <stdbool.h>
#include "cworldparts.h"
#include "common.h"
#include "defines.h"

CWorldParts *World;

CBlock* CBlock_Create(int PlayFieldXin,int PlayFieldYin,int ColorIn)
{
    CBlock* Result = (CBlock *) malloc(sizeof(CBlock));
    Result->AnimBase = 0;
    Result->AnimPhase = 0;
    Result->AnimCounter = 0;
    Result->AnimDelayCounter = 0;
    Result->AnimPhases = 1;
    Result->AnimDelay = 2;
    Result->PlayFieldX = PlayFieldXin;
    Result->PlayFieldY = PlayFieldYin;
    Result->Color = ColorIn;
    Result->bNeedToKill = false;
    Result->bSelected = false;
    return Result;
}

void CBlock_Select(CBlock* Block)
{
    Block->AnimBase = 0;
    Block->AnimCounter = 0;
    Block->AnimPhases = 6;
    Block->bSelected = true;
}

void CBlock_DeSelect(CBlock* Block)
{
    Block->AnimBase = 0;
    Block->AnimCounter = 0;
    Block->AnimPhases = 1;
    Block->bSelected=false;
}

void CBlock_Kill(CBlock* Block)
{
    Block->AnimBase = 6;
    Block->AnimCounter = 0;
    Block->AnimPhases = 1;
    Block->bNeedToKill = true;
}

void CBlock_Draw(CBlock* Block, SDL_Surface *Surface)
{
    SDL_Rect Dst,Src;

    Src.x = Block->AnimPhase *TileWidth;
    Src.y = Block->Color *TileHeight;
    Src.w = TileWidth;
    Src.h = TileHeight;

    Dst.x = Block->PlayFieldX * TileWidth+5 + Block->PlayFieldX;
    Dst.y = Block->PlayFieldY * TileHeight+17;
    Dst.w = TileWidth;
    Dst.h = TileHeight;

    SDL_BlitSurface(IMGBlocks,&Src,Surface,&Dst);

    Block->AnimPhase = Block->AnimBase + Block->AnimCounter;
    if(Block->AnimPhase != Block->AnimBase + Block->AnimPhases - 1)
    {
        Block->AnimDelayCounter++;
        if (Block->AnimDelayCounter >= Block->AnimDelay)
        {
            Block->AnimDelayCounter = 0;
            Block->AnimCounter++;
            if (Block->AnimCounter == Block->AnimPhases)
                Block->AnimCounter = 0;
        }
    }
}

void CBlock_Destroy(CBlock* Block)
{
    free(Block);
    Block = NULL;
}

CWorldParts* CWorldParts_Create()
{
    CWorldParts* Result = (CWorldParts*) malloc(sizeof(CWorldParts));
    int X,Y;
    Result->NeedToKillBlocks = false;
    Result->NeedToAddBlocks = false;
    Result->NumSelected = 0;
    Result->SelectedColor = -1;
    for(Y=0;Y<NrOfRows;Y++)
        for(X=0;X<NrOfCols;X++)
            Result->Items[X][Y] = NULL;
    return Result;
}

void CWorldParts_KillBlocks(CWorldParts* WorldParts)
{
    int X,Y,Teller=0,StartX=NrOfCols,StartY=NrOfRows,EndX=-1,EndY=-1;
    for(Teller=0;Teller<WorldParts->NumSelected;Teller++)
    {
        if(WorldParts->Selects[Teller].X > EndX)
            EndX = WorldParts->Selects[Teller].X;
        if(WorldParts->Selects[Teller].X < StartX)
            StartX = WorldParts->Selects[Teller].X;
        if(WorldParts->Selects[Teller].Y > EndY)
            EndY = WorldParts->Selects[Teller].Y;
        if(WorldParts->Selects[Teller].Y < StartY)
            StartY = WorldParts->Selects[Teller].Y;
    }
    for(Y = StartY;Y<=EndY;Y++)
        for(X=StartX;X<=EndX;X++)
            CBlock_Kill(WorldParts->Items[X][Y]);
}

void CWorldParts_AddBlocks(CWorldParts* WorldParts)
{
    int X,Y;
    for(Y=0;Y<NrOfRows;Y++)
        for(X=0;X<NrOfCols;X++)
            if(WorldParts->Items[X][Y]->bNeedToKill)
            {
                CBlock_Destroy(WorldParts->Items[X][Y]);
                WorldParts->Items[X][Y] = CBlock_Create(X,Y,rand()%NrOfBlockColors);
            }
}


void CWorldParts_NewGame(CWorldParts* WorldParts)
{
    int X,Y;
    for(Y=0;Y<NrOfRows;Y++)
        for(X=0;X<NrOfCols;X++)
        {
            if (WorldParts->Items[X][Y])
                CBlock_Destroy(WorldParts->Items[X][Y]);
            WorldParts->Items[X][Y] = CBlock_Create(X,Y,rand()%NrOfBlockColors);
        }
    WorldParts->NeedToKillBlocks = false;
    WorldParts->NeedToAddBlocks = false;
    WorldParts->NumSelected = 0;
    WorldParts->SelectedColor = -1;
}

void CWorldParts_Destroy(CWorldParts* WorldParts)
{
    printf("Freed\n");
    int X,Y;
    for(Y=0;Y<NrOfRows;Y++)
        for(X=0;X<NrOfCols;X++)
            if(WorldParts->Items[X][Y])
                CBlock_Destroy(WorldParts->Items[X][Y]);
}

void CWorldParts_Draw(CWorldParts* WorldParts, SDL_Surface * Surface)
{
    if(WorldParts->NeedToKillBlocks && (WorldParts->Time < SDL_GetTicks()))
    {
        CWorldParts_KillBlocks(WorldParts);
        WorldParts->NeedToKillBlocks = false;
        WorldParts->NeedToAddBlocks = true;
        WorldParts->Time = SDL_GetTicks() + 350;
        Mix_PlayChannel(-1,Sounds[SND_DELETE],0);
    }

    if (WorldParts->NeedToAddBlocks && (WorldParts->Time < SDL_GetTicks()))
    {
        CWorldParts_AddBlocks(WorldParts);
        WorldParts->NeedToAddBlocks = false;
        WorldParts->NumSelected = 0;
    }

    SDL_BlitSurface(IMGBackground,NULL,Surface,NULL);
    int X,Y;
    for(Y=0;Y<NrOfRows;Y++)
        for(X=0;X<NrOfCols;X++)
            CBlock_Draw(WorldParts->Items[X][Y], Surface);
}

void CWorldParts_DeSelect(CWorldParts* WorldParts, bool PlaySound)
{
    if(GlobalSoundEnabled)
        if(PlaySound)
            Mix_PlayChannel(-1,Sounds[SND_ERROR],0);
    int Teller = 0;
    for(Teller = 0;Teller<WorldParts->NumSelected;Teller++)
        CBlock_DeSelect(WorldParts->Items[WorldParts->Selects[Teller].X][WorldParts->Selects[Teller].Y]);
    WorldParts->NumSelected = 0;
    WorldParts->SelectedColor = -1;
}

long CWorldParts_Select(CWorldParts* WorldParts, int PlayFieldX,int PlayFieldY)
{

    int Score = 0,NumEqualY=0,NumEqualX = 0,Teller1=0,Teller2=0,StartX=NrOfCols,StartY=NrOfRows,EndX=-1,EndY=-1;;
    if(!WorldParts->NeedToKillBlocks && !WorldParts->NeedToAddBlocks)
    {
        if(!WorldParts->Items[PlayFieldX][PlayFieldY]->bSelected)
        {

            if (WorldParts->NumSelected == 0)
            {
                CBlock_Select(WorldParts->Items[PlayFieldX][PlayFieldY]);
                WorldParts->SelectedColor = WorldParts->Items[PlayFieldX][PlayFieldY]->Color;
                WorldParts->Selects[WorldParts->NumSelected].X = PlayFieldX;
                WorldParts->Selects[WorldParts->NumSelected].Y = PlayFieldY;
                WorldParts->NumSelected++;
                Mix_PlayChannel(-1,Sounds[SND_BLOCKSELECT],0);

            }
            else
            {
                if(WorldParts->Items[PlayFieldX][PlayFieldY]->Color == WorldParts->SelectedColor)
                {
                    CBlock_Select(WorldParts->Items[PlayFieldX][PlayFieldY]);
                    WorldParts->Selects[WorldParts->NumSelected].X = PlayFieldX;
                    WorldParts->Selects[WorldParts->NumSelected].Y = PlayFieldY;
                    WorldParts->NumSelected++;
                    if(WorldParts->NumSelected > 2)
                    {
                        for(Teller1=0;Teller1 < WorldParts->NumSelected;Teller1++)
                        {
                            for(Teller2=0;Teller2<WorldParts->NumSelected;Teller2++)
                            if(Teller1 != Teller2)
                            {
                                if(WorldParts->Selects[Teller1].X == WorldParts->Selects[Teller2].X)
                                    NumEqualX++;
                                if(WorldParts->Selects[Teller1].Y == WorldParts->Selects[Teller2].Y)
                                    NumEqualY++;
                            }
                        }
                        if((NumEqualX > 4) || (NumEqualY > 4))
                            CWorldParts_DeSelect(WorldParts, true);
                    }


                    if(WorldParts->NumSelected == 3)
                        if (!(((NumEqualX == 2) && (NumEqualY == 2)) ))
                            CWorldParts_DeSelect(WorldParts, true);

                    if(WorldParts->NumSelected == 4)
                    {
                        if((NumEqualX == 4) && (NumEqualY == 4))
                        {
                            for(Teller1=0;Teller1<WorldParts->NumSelected;Teller1++)
                            {
                                if(WorldParts->Selects[Teller1].X > EndX)
                                    EndX = WorldParts->Selects[Teller1].X;
                                if(WorldParts->Selects[Teller1].X < StartX)
                                    StartX = WorldParts->Selects[Teller1].X;
                                if(WorldParts->Selects[Teller1].Y > EndY)
                                    EndY = WorldParts->Selects[Teller1].Y;
                                if(WorldParts->Selects[Teller1].Y < StartY)
                                    StartY = WorldParts->Selects[Teller1].Y;
                            }
                            Score = (EndY-StartY+1) * (EndX-StartX +1) * 100;
                            WorldParts->NeedToKillBlocks = true;
                            WorldParts->Time = SDL_GetTicks() + 350;
                        }
                        else
                            CWorldParts_DeSelect(WorldParts, true);
                    }

                    if(((WorldParts->NumSelected <= 4) && (WorldParts->NumSelected > 0)) )
                        Mix_PlayChannel(-1,Sounds[SND_BLOCKSELECT],0);
                }
                else
                    CWorldParts_DeSelect(WorldParts, true);
            }

        }
        else
            CWorldParts_DeSelect(WorldParts, true);
    }
    return Score;
}
