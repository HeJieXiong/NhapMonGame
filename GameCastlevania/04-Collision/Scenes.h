#pragma once
#include <d3dx9.h>
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
	CTextures * textures;
	CSprites *sprites;
	CTextures * textures = CTextures::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	LPANIMATION ani;
public:	
	int columntex, rowtex, columsprite, rowsprite, rowani;
	int level;
	float **maptex;
	float **mapspr;
	float **mapani;
	Scenes();
	void LoadTextureAndSprite(int id,LPCWSTR tex, LPDIRECT3DTEXTURE9 texname);
	void LoadAnimation(int timeperframe, int aniamount, string filelocation, int id);
	CSprite *GETTILE(int ID) { return sprites->Get(ID); };
	~Scenes();

};

