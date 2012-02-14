#ifndef CTILEWINDOW_H_INCLUDED
#define CTILEWINDOW_H_INCLUDED

#include "CArea.h"
#include "CCamera.h"
#include "CSurface.h"

//==============================================================================
class CTileWindow
{

protected:

    SDL_Surface*    Surf_TileWindow;

public:
    float	X;
    float	Y;

    int		Width;
    int		Height;

public:
    int		Type;
    int		Flags;

public:
    CTileWindow();

public:
    virtual bool OnLoad(char* File, int Width, int Height);

    virtual void OnLoop();

    virtual void OnRender(SDL_Surface* Surf_Display);

    virtual void OnCleanup();
};

#endif // CTILEWINDOW_H_INCLUDED
