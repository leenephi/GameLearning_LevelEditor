//=============================================================================
#include "CArea.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

//=============================================================================
CArea CArea::AreaControl;

//=============================================================================
CArea::CArea()
{
    AreaSize = 0;
}

//=============================================================================

void CArea::OnCreateNew(int nareaWidth, int nareaHeight)
{
    OnCleanup();

    areaWidth = nareaWidth;

    areaHeight = nareaHeight;

    Surf_Tileset = CSurface::OnLoad("./tilesets/game_tiles_1.png");

    for(int X = 0; X < areaWidth; X++)
    {
        for(int Y = 0; Y < areaHeight; Y++)
        {
            CMap tempMap;
            tempMap.OnCreateNew();
            tempMap.Surf_Tileset = Surf_Tileset;
            MapList.push_back(tempMap);
        }
    }
}

//=============================================================================

bool CArea::OnLoad(char* File)
{
    OnCleanup();

    FILE* FileHandle = fopen(File, "r");

    if(FileHandle == NULL)
    {
        return false;
    }

    char TilesetFile[255];

    fscanf(FileHandle, "%s\n", TilesetFile);

    if((Surf_Tileset = CSurface::OnLoad(TilesetFile)) == false)
    {
        fclose(FileHandle);

        return false;
    }

    fscanf(FileHandle, "%d:%d\n", &areaWidth, &areaHeight);

    cout << areaHeight << areaWidth;

    AreaSize = areaWidth;

    for(int X = 0; X < areaWidth; X++)
    {
        for(int Y = 0; Y < areaHeight; Y++)
        {
            char MapFile[255];

            fscanf(FileHandle, "%s ", MapFile);

            CMap tempMap;
            if(tempMap.OnLoad(MapFile) == false)
            {
                fclose(FileHandle);

                return false;
            }

            tempMap.Surf_Tileset = Surf_Tileset;

            MapList.push_back(tempMap);
        }
        fscanf(FileHandle, "\n");
    }

    fclose(FileHandle);

    return true;
}

//-----------------------------------------------------------------------------
void CArea::OnRender(SDL_Surface* Surf_Display, int CameraX, int CameraY)
{
    /*
    original code
    int MapWidth  = MAP_WIDTH * TILE_SIZE;
    int MapHeight = MAP_HEIGHT * TILE_SIZE;

    int FirstID = -CameraX / MapWidth;    int MapWidth  = MAP_WIDTH * TILE_SIZE;
    int MapHeight = MAP_HEIGHT * TILE_SIZE;

    int FirstID = -CameraX / MapWidth;
    FirstID = FirstID + ((-CameraY / MapHeight) * AreaSize);

    for(int i = 0; i < 16; i++)
    {
        int ID = FirstID + ((i / 2) * AreaSize) + (i % 2);

        if(ID < 0 || ID >= MapList.size()) continue;

        int X = ((ID % AreaSize) * MapWidth) + CameraX;
        int Y = ((ID / AreaSize) * MapHeight) + CameraY;

        MapList[ID].OnRender(Surf_Display, X, Y);
    FirstID = FirstID + ((-CameraY / MapHeight) * AreaSize);

    for(int i = 0; i < 16; i++)
    {
        int ID = FirstID + ((i / 2) * AreaSize) + (i % 2);

        if(ID < 0 || ID >= MapList.size()) continue;

        int X = ((ID % AreaSize) * MapWidth) + CameraX;
        int Y = ((ID / AreaSize) * MapHeight) + CameraY;

        MapList[ID].OnRender(Surf_Display, X, Y);
    original code
    */

    int MapWidth  = MAP_WIDTH * TILE_SIZE;
    int MapHeight = MAP_HEIGHT * TILE_SIZE;

    int FirstID = -CameraX / MapWidth;
    FirstID = FirstID + ((-CameraY / MapHeight) * areaWidth);

    for(int i = 0; i < 6; i++)
    {
        int ID = FirstID + ((i / 2) * areaWidth) + (i % 2);

        if(ID < 0 || ID >= MapList.size()) continue;

        int X = ((ID % areaWidth) * MapWidth) + CameraX;
        int Y = ((ID / areaWidth) * MapHeight) + CameraY;

        MapList[ID].OnRender(Surf_Display, X, Y);

    }
}

//-----------------------------------------------------------------------------
void CArea::OnCleanup()
{


    if(Surf_Tileset)
    {
        SDL_FreeSurface(Surf_Tileset);
    }

    MapList.clear();
}

//=============================================================================
CMap* CArea::GetMap(int X, int Y)
{
    int MapWidth  = MAP_WIDTH * TILE_SIZE;
    int MapHeight = MAP_HEIGHT * TILE_SIZE;

    int ID = X / MapWidth;
    ID = ID + ((Y / MapHeight) * AreaSize);

    if(ID < 0 || ID >= MapList.size())
    {
        return NULL;
    }

    return &MapList[ID];
}

//-----------------------------------------------------------------------------
CTile* CArea::GetTile(int X, int Y)
{
    int MapWidth  = MAP_WIDTH * TILE_SIZE;
    int MapHeight = MAP_HEIGHT * TILE_SIZE;

    CMap* Map = GetMap(X, Y);

    if(Map == NULL) return NULL;

    X = X % MapWidth;
    Y = Y % MapHeight;

    return Map->GetTile(X, Y);
}

//=============================================================================


/*
int main () {
  ofstream myfile;
  myfile.open ("example.txt");
  myfile << "Writing this to a file.\n";
  myfile.close();
  return 0;
}

int buffer[] = {tempTile.TileID, ':', tempTile.TypeID, ' '};
fwrite(buffer, 1, sizeof(buffer), FileHandle);
*/

bool CArea::OnSave(char* File, char* tilesetFile)
{

    int AreaSize = areaWidth*areaHeight;

    ofstream areafile(File);


    if(areafile.is_open())
    {
        areafile << tilesetFile;
        areafile << "\n";
        areafile << areaWidth << ':' << areaHeight;
        areafile << "\n";

        int mapSaveCount = 1;

        for(int X = 0; X < areaWidth; X++)
        {
            for(int Y = 0; Y < areaHeight; Y++)
            {

                CMap tempMap;
                tempMap = MapList.front();

                // later we'll base this off of user input

                char mapName[30];
                sprintf(mapName, "./mapsave/level_map_%d.map", mapSaveCount);

                if(tempMap.OnSave(mapName) == false)
                {
                    areafile.close();
                    return false;
                }

                areafile << mapName;
                areafile << " ";

                MapList.erase(MapList.begin());

                mapSaveCount++;
            }
            areafile << "\n";
        }

        areafile.close();
        return true;
        OnCleanup();
    }
    cout << "fail" << endl;
    return false;
}
