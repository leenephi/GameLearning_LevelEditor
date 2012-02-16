//==============================================================================
// SDL Tutorial 1
//==============================================================================
#ifndef _CAPP_H_
#define _CAPP_H_

#include <SDL.h>

#include "Define.h"

#include "CArea.h"
#include "CCamera.h"
#include "CEvent.h"
#include "CSurface.h"
#include "CTileWindow.h"

//==============================================================================
class CApp : public CEvent
{
private:
    bool            Running;

    SDL_Surface*    Surf_Display;

public:
    CApp();

    CTileWindow TileWindow;

    int newTileID;
    int newTypeID;

    bool down;

    int mXold;
    int mYold;

    int OnExecute();

public:
    bool OnInit();

    void OnEvent(SDL_Event* Event);

    void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);

    void OnLButtonDown(int mX, int mY);

    void OnRButtonDown(int mX, int mY);

    void OnRButtonUp(int mX, int mY);

    void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);

    void OnExit();

    void OnLoop();

    void OnRender();

    bool OnCleanup();
};

//==============================================================================

#endif
