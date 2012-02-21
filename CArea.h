//=============================================================================
#ifndef _CAREA_H_
#define _CAREA_H_

#include "CMap.h"

//=============================================================================
class CArea
{
public:
    static CArea            AreaControl;

public:
    std::vector<CMap>       MapList;

private:
    SDL_Surface*			Surf_Tileset_Passables;

    SDL_Surface*            Surf_Tileset_Impassables;

public:
    int                     AreaSize;

    int                     areaWidth;

    int                     areaHeight;

    char                    PassablesFile[255];

    char                    ImpassablesFile[255];

    CArea();

    void    OnCreateNew(int nareaWidth, int nareaHeight);

    bool    OnLoad(char* File);

    void    OnRender(SDL_Surface* Surf_Display, int CameraX, int CameraY);

    void    OnCleanup();


public:

    CMap*	GetMap(int X, int Y);

    CTile*	GetTile(int X, int Y);

    bool    OnSave(char* File, char*, char*);
};

//=============================================================================

#endif

