#pragma once
#include "GameObject.h"
#inclue "Simon.h"

#define PANTHER_WALKING_SPEED_X 0.05f
#define PANTHER_WALKING_SPEED_Y 0.05f
#define PANTHER_GRAVITY 0.05f

#define PANTHER_BBOX_WIDTH 16
#define PANTHER_BBOX_HEIGHT 31

#define PANTHER_STATE_WALKING 100
#define PANTHER_STATE_JUMP 200
#define PANTHER_STATE_DIE 300

#define PANTHER_ANI_WALKING 0
#define PANTHER_ANI_JUMP 1
class CPanther : public CGameObject
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(float &xcam, float &ycam, float &x_simon, float &y_simon);
	int is_standing;
	int is_jump;
	CSimon *simon;
public:
	CPanther();
	~CPanther();
	CPanther(CSimon *a) : CGameObject()
	{
		simon = a;
	}
	virtual void SetState(int state);
	void Jump();
	void Move();
};