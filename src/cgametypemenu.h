#ifndef CGAMETYPEMENU_H
#define CGAMETYPEMENU_H

#include <SDL.h>

struct CGameTypeMenu
{
    int Selection; //Holds what we currently selected in the main menu, 1 = new game, 2= credits, 3 = quit
};
typedef struct CGameTypeMenu CGameTypeMenu;

CGameTypeMenu* CGameTypeMenu_Create(); // constructor
void CGameTypeMenu_Draw(CGameTypeMenu* GameTypeMenu, SDL_Surface *Surface); //draw to a certain surface
void CGameTypeMenu_NextItem(CGameTypeMenu* GameTypeMenu); //Select the next menuitem
void CGameTypeMenu_PreviousItem(CGameTypeMenu* GameTypeMenu); //select the previous menuitem
int CGameTypeMenu_GetSelection(CGameTypeMenu* GameTypeMenu); // return the current selection
void CGameTypeMenu_Destroy(CGameTypeMenu* GameTypeMenu); // destructor

#endif