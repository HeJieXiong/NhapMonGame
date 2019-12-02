#include "Door.h"

void CDoor::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + DOOR_BOX_WIDTH;
	bottom = y + DOOR_BOX_HEIGHT;
}

void CDoor::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);
	if (state == DOOR_STATE_OPEN) {
		if (GetTickCount() - open_start <= 1000) {
			state = DOOR_STATE_OPEN;
			opened = 0;
		}
		if (GetTickCount() - open_start > 1000) {
			state = DOOR_STATE_OPEN;
			opened = 1;
		}
	}
}

void CDoor::Render(float &xcam, float &ycam, float &x_simon, float &y_simon)
{

	if (state == DOOR_STATE_CLOSE) {
		int ani = DOOR_CLOSE_ANI;
		animations[ani]->Render(x - xcam, y - ycam);
	}
	else if (state == DOOR_STATE_OPEN) {
		if (opened == 0) {
			int ani = DOOR_OPEN_ANI;
			animations[ani]->Render(x - xcam, y - ycam);

		}
		if (opened == 1) {
			int ani = DOOR_OPENED_ANI;
			animations[ani]->Render(x - xcam, y - ycam);
		}
		//opened = 1;
	}
	RenderBoundingBox(xcam, ycam);
}

void CDoor::SetState(int state)
{
	CGameObject::SetState(state);
	

}
