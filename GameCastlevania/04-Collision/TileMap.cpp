#include "TileMap.h"
#include "Background.h"

TileMap::TileMap(int levelmap)
{
	level = levelmap;
	sprites = new CSprites();
	textures = new CTextures();
	int ID = 0;
	switch (level) {
	case 1:
		textures->Add(1, L"textures\\maptile1.png", D3DCOLOR_XRGB(255,255,255));
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
		break;
	default:
		break;
	}
	
}

void TileMap::DrawMap(int level)
{
	if (level == 1) {
		int MAP[25*6] = {
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			100,108,108,108,108,108,100,100,100,108,108,108,108,108,100,100,100,100,100,100,5,13,13,21,
			0,61,61,61,61,61,61,69,69,61,61,61,61,61,61,69,69,69,69,69,69,77,85,85,93,
			0,61,109,61,61,61,61,61,61,61,109,61,61,61,61,61,61,61,61,109,109,6,14,85,21,
			0,109,30,109,109,109,109,109,109,109,30,109,109,109,109,109,109,109,109,30,0,6,14,85,93,
			0,62,70,78,62,62,78,62,78,62,70,78,62,62,78,62,78,78,86,70,94,102,110,7,0
		};
		for (int i = 0; i < 150; i++) {
			CSprite *tile = sprites->Get(MAP[i]);
			int x = i % 25;
			int y = i / 25;
			tile->Draw(x * 32, y * 32);
		}
	}
}
