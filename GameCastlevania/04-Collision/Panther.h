#pragma once
#include "GameObject.h"
#include "Simon.h"

#define PANTHER_WALKING_SPEED_X 0.11f
#define PANTHER_WALKING_SPEED_Y 0.07f
#define PANTHER_GRAVITY 0.002f

#define PANTHER_BBOX_WIDTH 32
#define PANTHER_BBOX_HEIGHT 15

#define PANTHER_STATE_WALKING_LEFT 100
#define PANTHER_STATE_WALKING_RIGHT 200
#define PANTHER_STATE_JUMP 300
#define PANTHER_STATE_SLEEP			500
#define PANTHER_Y_DIS -9850
#define PANTHER_ANI_WALKING_LEFT 0
#define PANTHER_ANI_WALKING_RIGHT 1
#define PANTHER_ANI_JUMP_LEFT			2
#define PANTHER_ANI_JUMP_RIGHT			3
#define PANTHER_ANI_SLEEP				4
class CPanther : public CGameObject
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(float &xcam, float &ycam, float &x_simon, float &y_simon);
	int is_standing;
	int is_jump;
	
	CSimon *simon;
public:
	int code;
	CPanther(CSimon *a) : CGameObject()
	{
		simon = a;
		is_standing = 0;
		is_jump = 0;
		point = 100;
	}
	virtual void SetState(int state);
};