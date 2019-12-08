#include "Scenes.h"
#include <fstream>
#include "Define.h"
 
// Read data of sprites and animations from file.
void Scenes::LoadTextureAndSprite(int id, LPCWSTR tex, LPDIRECT3DTEXTURE9 texname)
{
	ifstream FILE;
	ifstream FILESPRITE;
	FILE.open("texture.txt");
	FILESPRITE.open("sprite.txt");
	string sLinetex;
	string sLinesprite;
	columntex = 6;
	columsprite = 6;
	if (FILE.good())
	{
		getline(FILE, sLinetex);
	}
	rowtex = stoi(sLinetex);
	maptex = new float *[rowtex];
	for (int i = 0; i < rowtex; i++) {
		maptex[i] = new float[columntex];
	}
	for (int i = 0; i < rowtex; i++) {
		for (int j = 0; j < columntex; j++) {
			FILE >> maptex[i][j];
		}
	}	
	for (int i = 1; i < rowtex; i++) {
		if (maptex[i][0] == id) {
			textures->Add(maptex[i][0], tex, D3DCOLOR_XRGB(0, 0, 0));
		}
	}
	LPDIRECT3DTEXTURE9 texname = textures->Get(id);
	if (FILESPRITE.good()) {
		getline(FILESPRITE, sLinesprite);
	}
	rowsprite = stoi(sLinesprite);
	mapspr = new float *[rowsprite];
	for (int i = 0; i < rowsprite; i++) {
		mapspr[i] = new float[columsprite];
	}
	for (int i = 0; i < rowsprite; i++) {
		for (int j = 0; j < columsprite; j++) {
			FILE >> mapspr[i][j];
		}
	}
	for (int i = 1; i < rowsprite; i++) {
		if (mapspr[i][0] == id) {
			sprites->Add(mapspr[i][1], mapspr[i][2], mapspr[i][3], mapspr[i][4], mapspr[i][5], texname);
		}
	}
}
void Scenes::LoadAnimation(int timeperframe, int aniid, string filelocation, int id) {
	ifstream FILE;
	FILE.open(filelocation);
	string sLineAni;
	int columnani = 6;
	if (FILE.good()) {
		getline(FILE, sLineAni);
	}
	rowani = stoi(sLineAni);
	mapani = new float *[columnani];
	for (int i = 0; i < rowani; i++) {
		mapani[i] = new float[columnani];
	}
	for (int i = 0; i < rowani; i++) {
		for (int j = 0; j < columsprite; j++) {
			FILE >> mapspr[i][j];
		}
	}
	ani = new CAnimation(timeperframe);
	for (int i = 1; i < rowani; i++) {
		if (mapani[i][0] == aniid) {
			ani->Add(mapani[i][1]);
		}
	}
	animations->Add(id, ani);
}