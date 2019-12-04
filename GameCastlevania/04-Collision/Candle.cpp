#include "Candle.h"

void CCandle::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	if (state == CANDLE_STATE) {
		right = x + CANDLE_BOX_WIDTH;
		bottom = y + CANDLE_BOX_HEIGHT;
	}
	if (state == FIRE_STATE) {
		right = x + FIRE_BOX_WIDTH;
		bottom = y + FIRE_BOX_HEIGHT;
	}
}

void CCandle::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);
	

}

void CCandle::Render(float &xcam, float &ycam, float &x_simon, float &y_simon)
{

	if (state == CANDLE_STATE) {
		int ani = ANI;
		animations[ani]->Render(x - xcam, y - ycam);
	}
	if (state == FIRE_STATE) {
		int ani = ANI;
		animations[ani]->Render(x - xcam, y - ycam);
	}
	RenderBoundingBox(xcam,ycam);
}

void CCandle::SetState(int state)
{
	CGameObject::SetState(state);

	
}
