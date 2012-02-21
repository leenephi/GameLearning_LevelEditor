//==============================================================================
// SDL Tutorial 1
//==============================================================================
#ifndef _CAPP_H_
#define _CAPP_H_

#include <SDL.h>

#include "Define.h"
#include "CText.h"
#include "CArea.h"
#include "CCamera.h"
#include "CEvent.h"
#include "CSurface.h"
#include "CTileWindow.h"
#include "CText.h"
#include "string"
#include "CApp.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "CSurface.h"

//==============================================================================
class StringInput
{
private:
    std::string str;

    SDL_Surface* text;

public:
    static StringInput input;

    StringInput();

    ~StringInput();

    void handle_input(std::string&);

    void OnRender(SDL_Surface* Surf_Display);

};


class CApp : public CEvent
{
private:
    bool            Running;
    SDL_Surface*    Surf_Display;
    SDL_Surface*    Surf_Overlay;

    CTile*          tile;

    CMap*           Map;

    void GetTile(int mX, int mY);

public:


    CApp();

    CTileWindow TileWindow;



    int newTileID;
    int newTypeID;

    bool down;

    int mXold;
    int mYold;

    SDL_Rect overlay;

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

    bool InBounds(int mX, int mY);
};

//==============================================================================

#endif
