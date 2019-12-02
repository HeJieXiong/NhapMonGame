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
	
	if (state == DOOR_STATE_CLOSE) {
		int ani = DOOR_CLOSE_ANI;
		animations[ani]->Render(x - xcam, y - ycam);
	}
	else if (state == DOOR_STATE_OPEN ) {
		if (opened == 0) {
			int ani = DOOR_OPEN_ANI;
			animations[ani]->Render(x - xcam, y - ycam);
			
		}
		if (opened == 1) {
			int ani = DOOR_OPENED_ANI;
			animations[ani]->Render(x - xcam, y - ycam);
		}
		opened = 1;
	}
	else{
		int ani = CANDLE_ANI;
		animations[ani]->Render(x - xcam, y - ycam);
	}
	RenderBoundingBox(xcam,ycam);
}

void CCandle::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case DOOR_STATE_CLOSE:

	{
		state = DOOR_STATE_CLOSE;
		break;
	}
	case CANDLE_ANI:

	{
		state = CANDLE_ANI;
		break;
	}
	case DOOR_STATE_OPEN:

	{
		state = DOOR_STATE_OPEN;
		break;
	}
	}

}
