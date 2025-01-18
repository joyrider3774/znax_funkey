#ifndef CSELECTOR_H
#define CSELECTOR_H

#include <SDL.h>
#include "common.h"

struct CSelector
{
    SPoint SelectedPoint,CurrentPoint; //variables to hold the current position and the selected position
    bool HasSelection;
};
typedef struct CSelector CSelector;


// constructor, parameters define the starting position
CSelector* CSelector_Create(const int PlayFieldXin,const int PlayFieldYin);

// Select will set the current position as the selected position
void CSelector_Select(CSelector* Selector);

void CSelector_SetPosition(CSelector* Selector, const int PlayFieldXin,const int PlayFieldYin);

// Deselect selection
void CSelector_DeSelect(CSelector* Selector);

// Draw the blue box on the current position, with the offsets in mind
void CSelector_Draw(CSelector* Selector, SDL_Surface *Surface);

//destructor
void CSelector_Destroy(CSelector* Selector);


#endif