#ifndef CMAINMENU_H
#define CMAINMENU_H

#include <SDL.h>

struct CMainMenu
{
    int Selection; //Holds what we currently selected in the main menu, 1 = new game, 2= credits, 3 = quit
};
typedef struct CMainMenu CMainMenu;

CMainMenu* CMainMenu_Create(); // constructor
void CMainMenu_Draw(CMainMenu* MainMenu, SDL_Surface *Surface); //draw to a certain surface
void CMainMenu_NextItem(CMainMenu* MainMenu); //Select the next menuitem
void CMainMenu_PreviousItem(CMainMenu* MainMenu); //select the previous menuitem
int CMainMenu_GetSelection(CMainMenu* MainMenu); // return the current selection
void CMainMenu_Destroy(CMainMenu* MainMenu); // destructor

#endif