#include "Scenes.h"
#include <fstream>
#include "Define.h"
#include  <sstream> 
// Read data of sprites and animations from file.
void Scenes::LoadSprites(int id, LPCWSTR tex, LPCWSTR sprite_data, LPCWSTR animation_data, int time_ani)
{
	textures->Add(id, tex);
	LPDIRECT3DTEXTURE9 texture = textures->Get(id);

	ifstream spriteReader, animationReader;

	spriteReader.open(sprite_data);
	animationReader.open(animation_data);

	



	// Load sprite data

	int spriteid;
	int left, top, right, bottom;

	while (spriteReader >> spriteid >> left >> top >> right >> bottom)
		sprites->Add(spriteid, left, top, right, bottom, texture);

	spriteReader.close();

	// Load animation data

	int  animationId;
	string line;
	int spriteId;
	int frameTime;

	while (getline(animationReader, line))
	{
		LPANIMATION ani = new CAnimation(time_ani);

		istringstream iss(line, istringstream::in);
		iss >> animationId;

		while (iss >> spriteId >> frameTime)
			ani->Add(spriteId, frameTime);

		animations->Add(animationId, ani);
	}

	animationReader.close();
}
