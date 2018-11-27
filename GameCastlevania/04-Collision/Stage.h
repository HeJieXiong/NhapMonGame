#pragma once
#include "Tilemap.h"
#include "Simon.h"
#include "Brick.h"
#include "Fire.h"
#include "Morningstar.h"
#include "HeaderBar.h"
#include "Item.h"
#include "TileMap.h"
#include "Knife.h"
#include "Stage.h"
class  CStage {
private:
	int stage;
public:
	CSimon *simon;
	CMorningstar *morningstar;
	CItem *item;
	TileMap *map;
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> objects_morningstar;
	vector<LPGAMEOBJECT> obejects_item;
	vector<LPGAMEOBJECT> objects_weapons;
	
	
	CStage(int s, CSimon *a, TileMap *b, CMorningstar *c)
	{
		simon = a;
		map = b;
		stage = s;
	}
	void SetStage(float x,float y);
};