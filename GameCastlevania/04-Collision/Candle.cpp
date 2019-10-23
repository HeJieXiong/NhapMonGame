#include "Candle.h"

void CCandle::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + CANDLE_BOX_WIDTH;
	bottom = y + CANDLE_BOX_HEIGHT;
}

void CCandle::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);
}

void CCandle::Render(float &xcam, float &ycam, float &x_simon, float &y_simon)
{
	int ani = CANDLE_ANI;
	animations[ani]->Render(x - xcam, y - ycam);
	//RenderBoundingBox(xcam,ycam);
}

void CCandle::SetState(int state)
{
	CGameObject::SetState(state);
}
