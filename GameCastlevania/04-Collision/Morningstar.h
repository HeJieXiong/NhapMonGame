#pragma once
#include "GameObject.h"
#define MORNINGSTAR_STATE	100
#define MORNINGSTAR_ANI		0
#define MORNINGSTAR_BOX_WIDTH	50
#define MORNINGSTAR_BOX_HEIGHT	20
class CMorningstar : public CGameObject {
	int x_simon;
	int y_simon;
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(float &x_simon, float  &y_simon);
	//virtual bool check();
public:
	virtual void SetState(int state);
	
};

