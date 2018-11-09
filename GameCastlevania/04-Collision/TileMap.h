#pragma once
#include <d3dx9.h>
#include <string.h>
#include "Sprites.h"

class TileMap {
private:
	int **matrix;
	int columns;
	int rows;
	int tileWidth, tileHeight;

	CSprite * tileSet;

public:
	TileMap();
	TileMap(int _cols, int _rows, int _tileWidth, int _tileHeight);
	~TileMap();
	void InitTileSet(CSprite * _tileSet);
	void LoadMatrixMap(LPCSTR fileSource);
	void Draw(float &xcam, float &ycam);
};
