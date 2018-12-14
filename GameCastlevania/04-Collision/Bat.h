#pragma once
#include "GameObject.h"
#include <math.h>
#define BAT_STATE_FLY 0.05f;

#define BAT_BBOX_WIDTH 16
#define BAT_BBOX_HEIGHT 31

#define BAT_STATE_FLY 100
#define BAT_STATE_DIE 200
#define BAT_SPEED 0.1f
#define BAT_ANI_FLY 0
#define PI 3.14159265
class CBat : public CGameObject
{
	int point;
	double a=45.0;
	double val = PI / 180;
	double ret;
	float flying_coordinate;//tọa độ được cộng thêm của dơi
	int startPoint;
public:
	CBat();
	~CBat();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(float &xcam, float &ycam, float &x_simon, float &y_simon);
};