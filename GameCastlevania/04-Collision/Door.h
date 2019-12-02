#pragma once
#include "GameObject.h"
#include "Item.h"

#define DOOR_STATE_CLOSE 200
#define DOOR_STATE_OPEN 300

#define DOOR_CLOSE_ANI 1
#define DOOR_OPEN_ANI 2
#define DOOR_OPENED_ANI 3

#define DOOR_BOX_WIDTH 5
#define DOOR_BOX_HEIGHT 5

class CDoor : public CGameObject
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(float &xcam, float &ycam, float &x_simon, float &y_simon);

public:
	DWORD open_start;
	int opened = 0;
	int state = 0;
	virtual void SetState(int state);
};