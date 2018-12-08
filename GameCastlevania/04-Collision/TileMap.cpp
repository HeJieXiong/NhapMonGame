#include "TileMap.h"
#include "Background.h"
#include <fstream>

TileMap::TileMap()
{
	
	sprites = new CSprites();
	textures = new CTextures();
	int ID = 0;
		textures->Add(1, L"textures\\maptile1.png", D3DCOLOR_XRGB(0,255,0));
		for (int i = 0; i < 14; i++) {
			sprites->Add(ID++, i * 32, 0, 32 * (i + 1), 32, textures->Get(1));
			sprites->Add(ID++, i * 32, 32 * 1, 32 * (i + 1), 32 * 2, textures->Get(1));
			sprites->Add(ID++, i * 32, 32 * 2, 32 * (i + 1), 32 * 3, textures->Get(1));
			sprites->Add(ID++, i * 32, 32 * 3, 32 * (i + 1), 32 * 4, textures->Get(1));
			sprites->Add(ID++, i * 32, 32 * 4, 32 * (i + 1), 32 * 5, textures->Get(1));
			sprites->Add(ID++, i * 32, 32 * 5, 32 * (i + 1), 32 * 6, textures->Get(1));
			sprites->Add(ID++, i * 32, 32 * 6, 32 * (i + 1), 32 * 7, textures->Get(1));
			sprites->Add(ID++, i * 32, 32 * 7, 32 * (i + 1), 32 * 8, textures->Get(1));
		}
}
void TileMap::LoadMap(int **&map, int level) {
	ifstream FILE;
	if (level == 1) {
		column = 24;
		row = 6;
		map = new int *[row];
		
		for (int i = 0; i < row; i++) {
			map[i] = new int[column];
		}
		FILE.open("map1.txt");
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				FILE >> map[i][j];
			}
		}
	}
	if (level == 2) {
		column = 48;
		row = 7;
		map = new int *[row];
		for (int i = 0; i < row; i++) {
			map[i] = new int[column];
		}
		FILE.open("map2.txt");
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 48; j++) {
				FILE >> map[i][j];
			}
		}
	}
}
void TileMap::DrawMap(int **map, float &xcam, float &ycam)
{
	int a = int(xcam);
	int b = int(ycam);
	
	
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				CSprite *tile = sprites->Get(map[i][j]);
				int x = j % column;
				int y = j / column + i;
				tile->Draw(x * 31 - a, y * 31 - b);
			}
		}
	}


