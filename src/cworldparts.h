#ifndef CWORLDPARTS_H
#define CWORLDPARTS_H

#include <SDL.h>
#include "common.h"
#include "defines.h"

struct CBlock
{
    int Color,AnimCounter,AnimBase,AnimDelay,AnimDelayCounter,AnimPhases,AnimPhase,PlayFieldX,PlayFieldY;
    bool bNeedToKill,bSelected;
};

typedef struct CBlock CBlock;

CBlock* CBlock_Create(int PlayFieldXin,int PlayFieldYin,int ColorIn);
void CBlock_Select(CBlock* Block);
void CBlock_DeSelect(CBlock* Block);
void CBlock_Kill(CBlock* Block);
void CBlock_Draw(CBlock* Block, SDL_Surface *Surface);
int CBlock_GetColor(CBlock* Block);
bool CBlock_IsSelected(CBlock* Block);
bool CBlock_NeedToKill(CBlock* Block);
void CBlock_Destroy(CBlock* Block);

struct CWorldParts
{
    CBlock *Items[NrOfCols][NrOfRows];
    SPoint Selects [4];
    int NumSelected,SelectedColor;
    Uint32 Time;
    bool NeedToKillBlocks,NeedToAddBlocks;
};
typedef struct CWorldParts CWorldParts;


CWorldParts* CWorldParts_Create();
void CWorldParts_Destroy(CWorldParts* WorldParts);
void CWorldParts_KillBlocks(CWorldParts* WorldParts);
void CWorldParts_AddBlocks(CWorldParts* WorldParts);
void CWorldParts_NewGame(CWorldParts* WorldParts);
void CWorldParts_Draw(CWorldParts* WorldParts, SDL_Surface * Surface);
void CWorldParts_DeSelect(CWorldParts* WorldParts, bool PlaySound);
long CWorldParts_Select(CWorldParts* WorldParts, int PlayFieldX,int PlayFieldY);

extern CWorldParts *World;

#endif