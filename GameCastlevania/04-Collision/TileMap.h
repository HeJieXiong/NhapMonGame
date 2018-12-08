#pragma once
#include <d3dx9.h>
#include "Sprites.h"
#include "Textures.h"
class TileMap:public CSprites {
private:
	
	CTextures * textures;
	CSprites *sprites;
	
public:
	int column, row;
	
	int level;
	TileMap();
	void LoadMap(int **&map, int level);
	void DrawMap(int **map,float &xcam, float &ycam);
	CSprite *GETTILE(int ID) { return sprites->Get(ID); };
	~TileMap();
};
