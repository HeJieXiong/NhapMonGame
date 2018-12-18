#include "Bat.h"
#include "GameObject.h"
#include <math.h>
#include "Debug.h""

CBat::CBat()
{
	tag = 15;
	point = 100;
	//flying_coordinate = 0;
	startPoint = 0;
}
void CBat::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + BAT_BBOX_WIDTH;
	bottom = y + BAT_BBOX_HEIGHT;
}

void CBat::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	/*if (is_active == true) {*/
	if(this->x<0){
		x = 450;
	}
	else {
	CGameObject::Update(dt, coObjects);
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
	int ani = BAT_ANI_FLY;
	animations[ani]->Render(x - xcam, y - ycam);
	RenderBoundingBox(xcam, ycam);
	//RenderBoundingBox();
}

void CBat::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BAT_STATE_FLY:
		nx = -1;
		vx = -BAT_SPEED;
		break;
	}
}
