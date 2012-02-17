//==============================================================================
#include "CApp.h"
#include "CMap.h"
#include "CArea.h"

//==============================================================================
void CApp::OnEvent(SDL_Event* Event)
{
    CEvent::OnEvent(Event);
}

//==============================================================================
void CApp::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    switch(sym)
    {
    case SDLK_UP:
        CCamera::CameraControl.OnMove( 0,  CAMERA_SPEED);
        break;
    case SDLK_DOWN:
        CCamera::CameraControl.OnMove( 0, -CAMERA_SPEED);
        break;
    case SDLK_LEFT:
        CCamera::CameraControl.OnMove( CAMERA_SPEED,  0);
        break;
    case SDLK_RIGHT:
        CCamera::CameraControl.OnMove(-CAMERA_SPEED,  0);
        break;
    case SDLK_ESCAPE:
        CArea::AreaControl.OnSave("./mapsave/savearea.area", "./tilesets/game_tiles_1.png");
        CApp::OnCleanup();
        break;

    default:
    {
    }
    }
}

void CApp::OnLButtonDown(int mX, int mY)
{
    CTile* tile;


    if((mX < 32 && mY < 128))
    {
        newTileID = TileWindow.GetTileID(mX, mY, newTypeID);
    }
    if(!(mX < 32 && mY < 128))
    {
        if(InBounds(mX, mY))
        {
            tile = CArea::AreaControl.GetTile((mX - CCamera::CameraControl.GetX()), (mY - CCamera::CameraControl.GetY()));

            CMap* Map;

            Map->SetTile(tile, newTileID, newTypeID);
        }
    }
}

void CApp::OnRButtonDown(int mX, int mY)
{
    if((mX < 32 && mY < 128))
    {
        newTileID = TileWindow.GetTileID(mX, mY, newTypeID);
    }
    if((!(mX < 32 && mY < 128)))
    {
        down = true;
        mXold = mX;
        mYold = mY;
        if(InBounds(mX, mY))
        {
            CTile* tile;
            tile = CArea::AreaControl.GetTile((mX - CCamera::CameraControl.GetX()), (mY - CCamera::CameraControl.GetY()));

            CMap* Map;


            Map->SetTile(tile, newTileID, newTypeID);
        }
    }
}


void CApp::OnRButtonUp(int mX, int mY)
{
    if(down)
    {
        if(InBounds(mX,mY))
        {

            CTile * tile;

            if(mX < mXold)
            {
                if(mY < mYold)
                {
                    for(int Y = mY; Y < mYold; Y++)
                        for(int X = mX; X < mXold; X++)
                        {
                            if(InBounds(X,Y))
                            {
                                tile = CArea::AreaControl.GetTile((X - CCamera::CameraControl.GetX()), (Y - CCamera::CameraControl.GetY()));

                                CMap* Map;

                                Map->SetTile(tile, newTileID, newTypeID);
                            }
                        }

                }
                if(mY > mYold)
                {
                    for(int Y = mY; Y > mYold; Y--)
                        for(int X = mX; X < mXold; X++)
                        {
                            if(InBounds(X,Y))
                            {
                                tile = CArea::AreaControl.GetTile((X - CCamera::CameraControl.GetX()), (Y - CCamera::CameraControl.GetY()));

                                CMap* Map;

                                Map->SetTile(tile, newTileID, newTypeID);
                            }
                        }

                }
            }
            if(mX > mXold)
            {
                if(mY < mYold)
                {
                    for(int Y = mY; Y < mYold; Y++)
                        for(int X = mX; X > mXold; X--)
                        {
                            if(InBounds(X,Y))
                            {
                                tile = CArea::AreaControl.GetTile((X - CCamera::CameraControl.GetX()), (Y - CCamera::CameraControl.GetY()));

                                CMap* Map;

                                Map->SetTile(tile, newTileID, newTypeID);
                            }
                        }

                }
                if(mY > mYold)
                {
                    for(int Y = mY; Y > mYold; Y--)
                        for(int X = mX; X > mXold; X--)
                        {
                            if(InBounds(X, Y))
                            {
                                tile = CArea::AreaControl.GetTile((X - CCamera::CameraControl.GetX()), (Y - CCamera::CameraControl.GetY()));

                                CMap* Map;

                                Map->SetTile(tile, newTileID, newTypeID);
                            }
                        }

                }
            }

            down = false;
        }
    }

}

void CApp::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{
    CTile* tile;
    CMap* Map;
    if (Left)
    {
        if(!(mX < 32 && mY < 128))
        {
            if(InBounds(mX, mY))
            {
                tile = CArea::AreaControl.GetTile((mX - CCamera::CameraControl.GetX()), (mY - CCamera::CameraControl.GetY()));

                Map->SetTile(tile, newTileID, newTypeID);
            }
        }
    }
    if (Right)
    {
        if(!(mX < 32 && mY < 128))
        {
            if(InBounds(mX, mY))
            {
                if( ((mX - CCamera::CameraControl.GetX()) < MAP_WIDTH*TILE_SIZE*CArea::AreaControl.AreaSize) &&
                        ((mY - CCamera::CameraControl.GetY()) < MAP_HEIGHT*TILE_SIZE*CArea::AreaControl.AreaSize) &&
                        ((mYold - CCamera::CameraControl.GetY()) < MAP_HEIGHT*TILE_SIZE*CArea::AreaControl.AreaSize) &&
                        ((mXold - CCamera::CameraControl.GetX()) < MAP_WIDTH*TILE_SIZE*CArea::AreaControl.AreaSize)
                  )
                {

                    // draws tiles but doesn't erase when you go too far
                    tile = CArea::AreaControl.GetTile((mX - CCamera::CameraControl.GetX()), mYold - CCamera::CameraControl.GetY());

                    Map->SetTile(tile, newTileID, newTypeID);


                    tile = CArea::AreaControl.GetTile(mXold - CCamera::CameraControl.GetX(), mY - CCamera::CameraControl.GetY());

                    Map->SetTile(tile, newTileID, newTypeID);

                }
            }
        }
    }
}

bool CApp::InBounds(int mX, int mY)
{

    if((mX - CCamera::CameraControl.GetX()) >= 0 && (mY - CCamera::CameraControl.GetY()) >= 0 &&
            ((mX - CCamera::CameraControl.GetX()) <= MAP_WIDTH*TILE_SIZE*CArea::AreaControl.AreaSize) &&
            ((mY - CCamera::CameraControl.GetY()) <= MAP_HEIGHT*TILE_SIZE*CArea::AreaControl.AreaSize))
        return true;
    return false;
}
//------------------------------------------------------------------------------
void CApp::OnExit()
{
    Running = false;
}

//==============================================================================
