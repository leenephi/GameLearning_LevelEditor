//==============================================================================
#include "CTileWindow.h"


CTileWindow::CTileWindow()
{
    Surf_TileWindow = NULL;

    X = 0;
    Y = 0;

    Width 	= 0;
    Height 	= 0;
}

//==============================================================================
bool CTileWindow::OnLoad(char* File, int Width, int Height)
{
    if((Surf_TileWindow = CSurface::OnLoad(File)) == NULL)
    {
        return false;
    }

    CSurface::Transparent(Surf_TileWindow, 255, 0, 255);

    this->Width = Width;
    this->Height = Height;

    return true;
}

//------------------------------------------------------------------------------
void CTileWindow::OnLoop()
{

}

//------------------------------------------------------------------------------
void CTileWindow::OnRender(SDL_Surface* Surf_Display)
{
    CSurface::OnDraw(Surf_Display, Surf_TileWindow, CCamera::CameraControl.GetX() + X, CCamera::CameraControl.GetY() + Y);
}

//------------------------------------------------------------------------------
void CTileWindow::OnCleanup()
{
    if(Surf_TileWindow)
    {
        SDL_FreeSurface(Surf_TileWindow);
    }

    Surf_TileWindow = NULL;
}
