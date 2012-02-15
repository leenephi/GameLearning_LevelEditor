//==============================================================================
#include "CApp.h"

//==============================================================================
bool CApp::OnInit()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }

    if((Surf_Display = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
    {
        return false;
    }

    if(CArea::AreaControl.OnLoad("./maps/area.area") == false)
    {
        return false;
    }

    if(TileWindow.OnLoad("./tilesets/game_tiles_1.png", 32, 128) == false)
    {
        return false;
    }

    SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

    newTileID = 10;
    newTypeID = 1;

    return true;
}

//==============================================================================
