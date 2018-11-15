#pragma once
#include <d3dx9.h>
#include <string.h>
#include "Sprites.h"
#include "Textures.h"
#define TILE_WIDTH = 60;
#define TILE_HEIGHT = 60;
#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 240
class TileMap {
private:
	

public:
	TileMap();
	TileMap(int _cols, int _rows, int _tileWidth, int _tileHeight);
	~TileMap();
	void InitTileSet(CSprite * _tileSet);
	void LoadMatrixMap(LPCSTR fileSource);
	void LoadRescoure();
	void Draw(float &xcam, float &ycam);
};
