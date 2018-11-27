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

void TileMap::DrawMap(float &xcam, float &ycam)
{
	int a = int(xcam);
	int b = int(ycam);
	ifstream FILE;
	if (level == 1) {
		FILE.open("map.txt");
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 24; j++) {
				FILE >> map[i][j];
			}
		}
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 24; j++) {
				CSprite *tile = sprites->Get(map[i][j]);
				int x = j % 24;
				int y = j / 24 + i;
				tile->Draw(x * 31 - a, y * 31 - b);
			}
		}
	}
}

