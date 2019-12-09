#pragma once
#include <d3dx9.h>
#include <iostream>
#include "Game.h"
#include "Grid.h"
#include "GameObject.h"
#include "TileMap.h"
#include "Candle.h"
#include "Morningstar.h"
#include "Knife.h"
#include "Simon.h"
#include "Item.h"
#include "Door.h"
#include "Stair.h"
#include "Ghost.h"
#include "Panther.h"
#include "Bat.h"
#include "Fish.h"
using namespace std;

class Scenes
{
private:
	CTextures * textures = CTextures::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	LPANIMATION ani;
public:	
	int columntex, rowtex, columsprite, colani, rowsprite, rowani;
	int level;
	float **maptex;
	float **mapspr;
	float **mapani;
	Scenes();
	void LoadTextureAndSprite(int texid, LPCWSTR link, string texName);
	void LoadPerTex(int texid, LPCWSTR link, LPDIRECT3DTEXTURE9 texName);
	void LoadAnimation(int timeperframe, int aniamount, string filelocation, int id);
	wstring s2ws(const std::string& s);//Convert string to LPCWSTR
	CSprite *GETTILE(int ID) { return sprites->Get(ID); };
	~Scenes();

};

