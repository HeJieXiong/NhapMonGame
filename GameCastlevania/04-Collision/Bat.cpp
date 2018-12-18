#include "Bat.h"
#include "GameObject.h"
#include <math.h>
#include "Debug.h""


void CBat::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + BAT_BBOX_WIDTH;
	bottom = y + BAT_BBOX_HEIGHT;
}

void CBat::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);

	/*if (is_active == true) {*/
	if (abs(simon->x - this->x) <= 400 && simon->x - this->x<0)
	{
		is_active = true;
	}
	if (is_active == true) {
		if (vx < 0) {
			if (x < 0) {
				SetState(BAT_STATE_FLY_RIGHT);
			}
			else {
				SetState(BAT_STATE_FLY_LEFT);
			}
		}
	

		if (vx > 0 ) {
			if (x > 450) {
				SetState(BAT_STATE_FLY_LEFT);
			}
			else SetState(BAT_STATE_FLY_RIGHT);
		}
		
		
		y = 10 * sin(flying_coordinate* PI / 180) + bat_x;
		x += dx;
		flying_coordinate += 5;
	}

	DebugOut(L"Bat_y %d\n", this->y);
	DebugOut(L"Bat_x %d\n", this->x);
	DebugOut(L"Bat_f %d\n", this->flying_coordinate);
}

void CBat::Render(float &xcam, float &ycam, float &x_simon, float &y_simon)
{
	int ani = 0;
	if (nx == 1) {
		ani = BAT_ANI_FLY_RIGHT;
	}
	else
		ani = BAT_ANI_FLY_LEFT;
	animations[ani]->Render(x - xcam, y - ycam);
	RenderBoundingBox(xcam, ycam);
	//RenderBoundingBox();
}

void CBat::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BAT_STATE_FLY_LEFT:
		nx = -1;
		vx = -BAT_SPEED;
		break;
	case BAT_STATE_FLY_RIGHT:
		nx = 1;
		vx = BAT_SPEED;
		break;
	}
}
