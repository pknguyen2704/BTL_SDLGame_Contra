#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include "CommonFunc.h"
#include "BaseObject.h"

#define MAX_TILES 20

class TileMat : public BaseObject
{
    public:
        TileMat() {;}
        ~TileMat() {;}
};

class GameMap 
{
    public:
        GameMap() {;}
        ~GameMap() {;}
        void LoadMap(char* filename);
        void LoadTiles(SDL_Renderer* screen);
        void DrawMap(SDL_Renderer* screen);
        Map GetMap() const {return game_map;};
        void SetMap(Map& mapData) {game_map = mapData;} 
    private:
        Map game_map;
        TileMat tile_mat[MAX_TILES];
};

#endif