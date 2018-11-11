#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

class CBrick : public CGameObject
{
public:
	virtual void Render(float &xcam, float &ycam, float &x_simon, float &y_simon);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	//virtual bool check();
};