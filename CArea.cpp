//=============================================================================
#include "CArea.h"

//=============================================================================
CArea CArea::AreaControl;

//=============================================================================
CArea::CArea()
{
    AreaSize = 0;
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

    fscanf(FileHandle, "%d\n", &AreaSize);

    for(int X = 0; X < AreaSize; X++)
    {
        for(int Y = 0; Y < AreaSize; Y++)
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
    int MapWidth  = MAP_WIDTH * TILE_SIZE;
    int MapHeight = MAP_HEIGHT * TILE_SIZE;

    int FirstID = -CameraX / MapWidth;
    FirstID = FirstID + ((-CameraY / MapHeight) * AreaSize);

    for(int i = 0; i < 4; i++)
    {
        int ID = FirstID + ((i / 2) * AreaSize) + (i % 2);

        if(ID < 0 || ID >= MapList.size()) continue;

        int X = ((ID % AreaSize) * MapWidth) + CameraX;
        int Y = ((ID / AreaSize) * MapHeight) + CameraY;

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

    int AreaSize = 3;

    FILE* FileHandle = fopen(File, "w");

    if(FileHandle == NULL)
    {
        return false;
    }

    char tilesetbuff[] = {*tilesetFile, '\n'};
    fwrite(tilesetbuff, 1, sizeof(tilesetbuff), FileHandle);

    int areasizebuff[] = {AreaSize, '\n'};
    fwrite(areasizebuff, 1, sizeof(areasizebuff), FileHandle);

    int mapSaveCount = 1;

    for(int X = 0; X < AreaSize; X++)
    {
        for(int Y = 0; Y < AreaSize; Y++)
        {

            CMap tempMap;
            tempMap = MapList.front();

            // later we'll base this off of user input
            char* mapName = "./maps/level_map_%d.map", mapSaveCount;

            if(tempMap.OnSave(mapName) == false)
            {
                fclose(FileHandle);
                return false;
            }

            char* mapnamebuff[] = {mapName, " "};
            fwrite(mapnamebuff, 1, sizeof(mapnamebuff), FileHandle);

            MapList.erase(MapList.begin());

            mapSaveCount++;
        }
        char newline[] = {'\n'};
        fwrite(newline, 1 , sizeof(newline), FileHandle);
    }

    fclose(FileHandle);

    return true;
}
