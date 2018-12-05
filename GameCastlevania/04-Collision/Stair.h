#pragma once
#include "GameObject.h"
#define STAIR_HEIGHT 30;
#define STAIR_WIDTH	 20;
class CStair : public CGameObject
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);



public:
	bool check_stair;
	virtual void Render(float &xcam, float &ycam, float &x_, float &y_);
};