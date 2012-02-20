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
    case SDLK_n:
        CArea::AreaControl.OnCreateNew(5, 10);

    default:
    {
    }
    }
}

void CApp::OnLButtonDown(int mX, int mY)
{



    if((mX < 32 && mY < 256))
    {
        newTileID = TileWindow.GetTileID(mX, mY, newTypeID);
    }
    if(!(mX < 32 && mY < 256))
    {
        if(InBounds(mX, mY))
        {
            GetTile(mX,mY);
            Map->SetTile(tile, newTileID, newTypeID);
        }
    }
}

void CApp::OnRButtonDown(int mX, int mY)
{
    if((mX < 32 && mY < 256))
    {
        newTileID = TileWindow.GetTileID(mX, mY, newTypeID);
    }
    if((!(mX < 32 && mY < 256)))
    {
        down = true;
        mXold = mX;
        mYold = mY;
        if(InBounds(mX, mY))
        {
            GetTile( mX, mY);
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
            if(mX < mXold)
            {
                if(mY < mYold)
                {
                    for(int Y = mY; Y < mYold; Y++)
                        for(int X = mX; X < mXold; X++)
                        {
                            if(InBounds(X,Y))
                            {
                                GetTile( X, Y);
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
                                GetTile( X, Y);
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
                                GetTile( X, Y);
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
                                GetTile( X, Y);
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
    if (Left)
    {
        if(!(mX < 32 && mY < 256))
        {
            if(InBounds(mX, mY))
            {
                GetTile( mX, mY);
                Map->SetTile(tile, newTileID, newTypeID);
            }
        }
    }
    if (Right)
    {
        if(!(mX < 32 && mY < 256))
        {
            if(InBounds(mX, mY))
            {
                if( ((mX - CCamera::CameraControl.GetX()) < MAP_WIDTH*TILE_SIZE*CArea::AreaControl.areaWidth) &&
                        ((mY - CCamera::CameraControl.GetY()) < MAP_HEIGHT*TILE_SIZE*CArea::AreaControl.areaHeight) &&
                        ((mYold - CCamera::CameraControl.GetY()) < MAP_HEIGHT*TILE_SIZE*CArea::AreaControl.areaHeight) &&
                        ((mXold - CCamera::CameraControl.GetX()) < MAP_WIDTH*TILE_SIZE*CArea::AreaControl.areaWidth))
                {
                    // draws tiles but doesn't erase when you go too far
                    GetTile( mX, mYold);
                    Map->SetTile(tile, newTileID, newTypeID);
                    GetTile(mXold, mY);
                    Map->SetTile(tile, newTileID, newTypeID);
                }
            }
        }
    }
}

bool CApp::InBounds(int mX, int mY)
{

    if((mX - CCamera::CameraControl.GetX()) >= 0 && (mY - CCamera::CameraControl.GetY()) >= 0 &&
            ((mX - CCamera::CameraControl.GetX()) <= MAP_WIDTH*TILE_SIZE*CArea::AreaControl.areaWidth) &&
            ((mY - CCamera::CameraControl.GetY()) <= MAP_HEIGHT*TILE_SIZE*CArea::AreaControl.areaHeight))
        return true;
    return false;
}

void CApp::GetTile(int mX, int mY)
{
    tile = CArea::AreaControl.GetTile((mX - CCamera::CameraControl.GetX()), (mY - CCamera::CameraControl.GetY()));
}
//------------------------------------------------------------------------------
void CApp::OnExit()
{
    Running = false;
}

//==============================================================================
