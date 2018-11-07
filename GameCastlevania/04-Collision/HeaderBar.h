#pragma once
#include "GameObject.h"
#include "Camera.h"
#define HEADER_BAR_STATE 100
#define HEADER_BAR_ANI 0
#define HEADER_BAR_BBOX_WIDTH  20
#define HEADER_BAR_BBOX_HEIGHT 20
class CHeaderBar : public CGameObject
{
public:
	virtual void Render(float &xcam, float  &ycam);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};
