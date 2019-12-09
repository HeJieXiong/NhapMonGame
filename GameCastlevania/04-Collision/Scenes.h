#pragma once
#include <d3dx9.h>
#include <iostream>
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#include "Simon.h"
#include "Brick.h"
#include "BackGround.h"
#include "Goomba.h"
#include "Fire.h"
#include "Morningstar.h"
#include "HeaderBar.h"
#include "Item.h"
#include "TileMap.h"
#include "Knife.h"
#include "Light_die.h"
#include "Candle.h"
#include "Ghost.h"
#include "Stair.h"
#include "Grid.h"
#include "Panther.h"
#include "Bat.h"
#include "Fish.h"
#include "Boss.h"
#include "Door.h"
#include "Scenes.h"
using namespace std;

class Scenes
{
private:
	
public:	
	CTextures * textures = CTextures::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	LPANIMATION ani;
	int columntex, rowtex, columsprite, colani, rowsprite, rowani;
	int level;
	string **maptex;
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

