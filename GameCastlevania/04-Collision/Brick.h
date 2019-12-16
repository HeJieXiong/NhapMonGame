#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 1

#define BIG_BRICK_BBOX_WIDTH  62
#define BIG_BRICK_BBOX_HEIGHT 94

class CBrick : public CGameObject
{
public:
	int type; //type=0 brick nhỏ type=1 brick lớn
	virtual void Render(float &xcam, float &ycam, float &x_simon, float &y_simon);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	//virtual bool check();
};