#pragma once
#include "GameObject.h"
#define BACK_GROUND_STATE 100
#define BACK_GROUND_ANI 0
#define BACK_GROUND_BBOX_WIDTH  400
#define BACK_GROUND_BBOX_HEIGHT 600
class CBackGround : public CGameObject
{
public:
	virtual void Render(float &xcam, float &ycam, float &x_simon, float &y_simon);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	//virtual bool check();
};
