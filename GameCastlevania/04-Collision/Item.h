#pragma once
#include "GameObject.h"
#define ITEM_WHIP 0
#define ITEM_HEART 1
#define ITEM_HEART_BIG 2
#define ITEM_KNIFE 3
#define ITEM_AXE 4
#define ITEM_BOOMERANG 5
#define ITEM_BAG_100 6
#define ITEM_BAG_400 7
#define ITEM_BAG_700 8
#define ITEM_GRAVITY 0.0002f
#define WEAPONS_HEIGHT 16
#define WEAPONS_WIDTH 16
#define SMALL_HEART_HEIGHT 8
#define SMALL_HEART_WIDTH 10
#define HEART_HEIGHT 10
#define HEART_WIDTH 12
class CItem : public CGameObject
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	


public:
	int ani;
	virtual void SetState(int state);
	virtual void Render(float &xcam, float &ycam, float &x_, float &y_);
	void Item_setting(CItem *Item, float &x, float &y, int a);
	int check_taken;
};