#pragma once
#include "GameObject.h"
#include "Item.h"
#define CANDLE_STATE 100
#define CANDLE_ANI 0
#define CANDLE_BOX_WIDTH 7
#define CANDLE_BOX_HEIGHT 15
class CCandle : public CGameObject
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(float &xcam, float &ycam, float &x_simon, float &y_simon);

public:
	int state = 0;
	virtual void SetState(int state);
};