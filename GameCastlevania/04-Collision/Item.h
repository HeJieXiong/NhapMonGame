#pragma once
#include "GameObject.h"
#define ITEM_HEART 0
#define ITEM_HEART_BIG 1
#define ITEM_GRAVITY 0.0002f
#define ITEM_HEIGHT 16
#define ITEM_WIDTH 12
class CItem : public CGameObject
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	


public:
	virtual void SetState(int state);
	virtual void Render(float &xcam, float &ycam, float &x_, float &y_);
	void Item_setting(CItem *Item, float &x, float &y, int ani);
	int check;
};