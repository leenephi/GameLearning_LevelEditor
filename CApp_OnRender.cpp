//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnRender()
{
    SDL_Rect Rect;
    Rect.x = 0;
    Rect.y = 0;
    Rect.w = WWIDTH;
    Rect.h = WHEIGHT;

    SDL_FillRect(Surf_Display, &Rect, 0);

    CArea::AreaControl.OnRender(Surf_Display, CCamera::CameraControl.GetX(), CCamera::CameraControl.GetY());

    TileWindow.OnRender(Surf_Display);



    SDL_Flip(Surf_Display);
}

//==============================================================================
