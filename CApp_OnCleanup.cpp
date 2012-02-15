//==============================================================================
#include "CApp.h"

//==============================================================================
bool CApp::OnCleanup()
{
    CArea::AreaControl.OnCleanup();
    if(CArea::AreaControl.OnSave("./maps/1.area", "./tilesets/game_tiles_1.png") == false)
    {
        return false;
    }
    TileWindow.OnCleanup();
    SDL_FreeSurface(Surf_Display);
    SDL_Quit();
}

//==============================================================================
