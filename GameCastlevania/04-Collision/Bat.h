#pragma once
#include "GameObject.h"
#include <math.h>

#define BAT_BBOX_WIDTH 16
#define BAT_BBOX_HEIGHT 16

#define BAT_STATE_FLY 100
#define BAT_STATE_DIE 200
#define BAT_SPEED 0.03f
#define BAT_ANI_FLY 0
#define PI 3.14
class CBat : public CGameObject
{
	int point;
	float flying_coordinate;//tọa độ được cộng thêm của dơi
	
	int startPoint;
public:
	float bat_x;
	CBat();
	~CBat();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(float &xcam, float &ycam, float &x_simon, float &y_simon);
};