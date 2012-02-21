//=============================================================================
#include "CMap.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

//=============================================================================
CMap::CMap()
{
    Surf_Tileset_Passables = NULL;
    Surf_Tileset_Impassables = NULL;
}

//=============================================================================

void CMap::OnCreateNew()
{
    TileList.clear();
    for(int Y = 0; Y < MAP_HEIGHT; Y++)
    {
        for(int X = 0; X < MAP_WIDTH; X++)
        {
            CTile tempTile;
            tempTile.TileID = 5;
            tempTile.TypeID = 1;
            TileList.push_back(tempTile);
        }
    }
}

//============================================================================
bool CMap::OnLoad(char* File)
{
    TileList.clear();

    FILE* FileHandle = fopen(File, "r");

    if(FileHandle == NULL)
    {
        return false;
    }

    for(int Y = 0; Y < MAP_HEIGHT; Y++)
    {
        for(int X = 0; X < MAP_WIDTH; X++)
        {
            CTile tempTile;

            fscanf(FileHandle, "%d:%d ", &tempTile.TileID, &tempTile.TypeID);

            TileList.push_back(tempTile);
        }
        fscanf(FileHandle, "\n");
    }

    fclose(FileHandle);

    return true;
}

//-----------------------------------------------------------------------------
void CMap::OnRender(SDL_Surface* Surf_Display, int MapX, int MapY)
{
    if(Surf_Tileset_Passables == NULL || Surf_Tileset_Impassables == NULL) return;

    int TilesetWidth;
    int TilesetHeight;

    int ID = 0;

    for(int Y = 0; Y < MAP_HEIGHT; Y++)
    {
        for(int X = 0; X < MAP_WIDTH; X++)
        {
            if(TileList[ID].TypeID == TILE_TYPE_NONE)
            {
                ID++;
                continue;
            }

            int tX = MapX + (X * TILE_SIZE);
            int tY = MapY + (Y * TILE_SIZE);

            if(TileList[ID].TypeID == TILE_TYPE_PASSABLE)
            {
                TilesetWidth  = Surf_Tileset_Passables->w / TILE_SIZE;
                TilesetHeight = Surf_Tileset_Passables->h / TILE_SIZE;

                int TilesetX = (TileList[ID].TileID % TilesetWidth) * TILE_SIZE;
                int TilesetY = (TileList[ID].TileID / TilesetWidth) * TILE_SIZE;

                CSurface::OnDraw(Surf_Display, Surf_Tileset_Passables, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);
            }

            else if(TileList[ID].TypeID == TILE_TYPE_IMPASSABLE)
            {
                TilesetWidth  = Surf_Tileset_Impassables->w / TILE_SIZE;
                TilesetHeight = Surf_Tileset_Impassables->h / TILE_SIZE;

                int TilesetX = (TileList[ID].TileID % TilesetWidth) * TILE_SIZE;
                int TilesetY = (TileList[ID].TileID / TilesetWidth) * TILE_SIZE;

                CSurface::OnDraw(Surf_Display, Surf_Tileset_Impassables, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);
            }
            ID++;
        }
    }
}

//=============================================================================
CTile* CMap::GetTile(int X, int Y)
{
    int ID = 0;

    ID = X / TILE_SIZE;
    ID = ID + (MAP_WIDTH * (Y / TILE_SIZE));

    if(ID < 0 || ID >= TileList.size())
    {
        return NULL;
    }

    return &TileList[ID];
}

//=============================================================================

void CMap::SetTile(CTile* tile, int newTile, int newType)
{
    tile->TileID = newTile;
    tile->TypeID = newType;
}


    /*
    int main () {
        ofstream myfile;
        myfile.open ("example.txt");
        myfile << "Writing this to a file.\n";
        myfile.close();
        return 0;
    }
    */


bool CMap::OnSave(char* File)
{
    ofstream mapfile(File);
    if(mapfile.is_open())
    {
        for(int Y = 0; Y < MAP_HEIGHT; Y++)
        {
            for(int X = 0; X < MAP_WIDTH; X++)
            {

                CTile tempTile;
                tempTile = TileList.front();

                mapfile << tempTile.TileID;
                mapfile << ":";
                mapfile << tempTile.TypeID;
                mapfile << " ";

                TileList.erase(TileList.begin());

            }
            mapfile << "\n";
        }

        mapfile.close();

        return true;
    }
}
