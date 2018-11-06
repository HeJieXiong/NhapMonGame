#pragma once
#include "GameObject.h"
#define MORNINGSTAR_STATE	100
#define MORNINGSTAR_ANI		0
#define MORNINGSTAR_BOX_WIDTH	50
#define MORNINGSTAR_BOX_HEIGHT	20
class CMorningstar : public CGameObject {
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(float &xcam, float  &ycam);
public:
	virtual void SetState(int state);
};

