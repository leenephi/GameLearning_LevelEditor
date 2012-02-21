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
CTileWindow::~CTileWindow()
{
    OnCleanup();
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
    CSurface::OnDraw(Surf_Display, Surf_TileWindow, 0, 0);
    //CSurface::OnDraw(Surf_Display, Surf_Entity, X - CCamera::CameraControl.GetX(), Y - CCamera::CameraControl.GetY() + 2, CurrentFrameCol * Width, (CurrentFrameRow + 5) * Height, Width, Height);
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

//------------------------------------------------------------------------------
int CTileWindow::GetTileID(int mX, int mY, int &TileType)
{

    int TilesetWidth  = Width;
    int TilesetHeight = Height;

    int ID = 0;

    for(int Y = 0; Y < TilesetHeight; Y += TILE_SIZE)
    {
        for(int X = 0; X < TilesetWidth; X += TILE_SIZE)
        {

            int tileX = X;
            int tileY = Y;

            // if the mouse click was within the bounds of this tile...
            if(mX > tileX && mX < tileX + TILE_SIZE &&
               mY > tileY && mY < tileY + TILE_SIZE)
               {
                   // then return the tile's ID!

            char switcher;

            if (ID >= 0 && ID <= 5)
                switcher = 'a';
            else if (ID >= 6 && ID <= 11)
                switcher = 'b';
            else if (ID >= 12 && ID <= 15)
                switcher = 'c';

            switch(switcher)
            {
                case 'a':
                {
                    TileType = 1;
                    break;
                }
                case 'b':
                {
                    TileType = 2;
                    break;
                }
                case 'c':
                {
                    TileType = 3;
                    ID = 5;
                    break;
                }
                default:
                {
                    TileType = 1;
                    break;
                }
            }



                   return ID;
               }
            ID++;
        }
    }
}
