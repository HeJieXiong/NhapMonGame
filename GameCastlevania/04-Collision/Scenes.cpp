#include "Scenes.h"
#include <fstream>
#include "Define.h"
#include <atlbase.h>
#include <atlconv.h>
// Read data of sprites and animations from file.
//Convert string to LPWSTR
wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

void Scenes::LoadTextureAndSprite(int texid, LPCWSTR link, string texName)
{
	ifstream FILE;
	ifstream FILESPRITE;
	ifstream FILEANI;
	FILE.open("texture.txt");
	FILESPRITE.open("sprite.txt");
	FILEANI.open("animtion.txt");
	string sLinetex;
	string sLinesprite;
	string sLineAni;
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
			FILESPRITE >> mapspr[i][j];
		}
	}
	if (FILEANI.good()) {
		getline(FILEANI, sLineAni);
	}
	rowani = stoi(sLineAni);
	mapani = new float *[rowani];
	for (int i = 0; i < rowani; i++) {
		mapani[i] = new float[columsprite];
	}
	for (int i = 0; i < rowsprite; i++) {
		for (int j = 0; j < columsprite; j++) {
			FILEANI >> mapani[i][j];
		}
	}
	for (int i = 1; i < rowtex; i++) { //LoadTexture and Sprite
		if (texid == maptex[i][0]) {
			textures->Add(maptex[i][0], link, D3DCOLOR_XRGB(0, 0, 0));
		}
		LPDIRECT3DTEXTURE9 texName = textures->Get(maptex[i][0]);
		for (int i = 1; i < rowsprite; i++) {
			if (texid == mapspr[i][0]) {
				sprites->Add(mapspr[i][1], mapspr[i][2], mapspr[i][3], mapspr[i][4], mapspr[i][5], texName);
			}
		}
	}
	for (int i = 1; i < rowani; i++) { //LoadAni
		if (texid == mapani[i][0]) {
			int curRow = i;
			for (int j = curRow; j < rowani; j++) {
				if (mapani[j][5] == 0) { //Head
					ani = new CAnimation(mapani[i][2]);
					ani->Add(mapani[i][1]);
				}
				if (mapani[j][5] == 1) { //Body
					ani->Add(mapani[i][1]);
				}
				if (mapani[j][5] == 2) { //Tail
					ani->Add(mapani[i][1]);
					animations->Add(mapani[i][4], ani);
				}
				if (mapani[j][5] == 3) {//only 1
					ani = new CAnimation(mapani[i][2]);
					ani->Add(mapani[i][1]);
					animations->Add(mapani[i][4], ani);
				}
			}
		}
	}
}
	/*LPDIRECT3DTEXTURE9 texname = textures->Get(id);
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
	}*/
}
//void Scenes::LoadAnimation(int timeperframe, int aniid, string filelocation, int id) {
//	ifstream FILE;
//	FILE.open(filelocation);
//	string sLineAni;
//	int columnani = 6;
//	if (FILE.good()) {
//		getline(FILE, sLineAni);
//	}
//	rowani = stoi(sLineAni);
//	mapani = new float *[columnani];
//	for (int i = 0; i < rowani; i++) {
//		mapani[i] = new float[columnani];
//	}
//	for (int i = 0; i < rowani; i++) {
//		for (int j = 0; j < columsprite; j++) {
//			FILE >> mapspr[i][j];
//		}
//	}
//	ani = new CAnimation(timeperframe);
//	for (int i = 1; i < rowani; i++) {
//		if (mapani[i][0] == aniid) {
//			ani->Add(mapani[i][1]);
//		}
//	}
//	animations->Add(id, ani);
//}
void Scenes::LoadPerTex(int texid, LPCWSTR link, LPDIRECT3DTEXTURE9 texName) {
	LoadTextureAndSprite();
}