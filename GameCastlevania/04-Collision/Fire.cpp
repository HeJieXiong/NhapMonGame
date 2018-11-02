#include "Fire.h"

void CFire::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + FIRE_BOX_WIDTH;
	bottom = y + FIRE_BOX_HEIGHT;
}

void CFire::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);
}

void CFire::Render(float &xcam, float &ycam)
{
	int ani = FIRE_ANI;
	animations[ani]->Render(x-xcam, y-ycam);
	RenderBoundingBox(xcam,ycam);
}

void CFire::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FIRE_STATE:
		x += 100;
		y = 100;
		vx = 0;
		vy = 0;
		break;
	}
}