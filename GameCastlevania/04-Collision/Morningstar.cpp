#include "Morningstar.h"
#include "Simon.h"

void CMorningstar::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + MORNINGSTAR_BOX_WIDTH;
	bottom = y + MORNINGSTAR_BOX_HEIGHT;
}

void CMorningstar::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);
}

void CMorningstar::Render(float &xcam, float &ycam)
{

	int ani = MORNINGSTAR_ANI;
	int alpha = 255;
	animations[ani]->Render(x_simon, y_simon, alpha);
	RenderBoundingBox(xcam, ycam);
}

void CMorningstar::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MORNINGSTAR_STATE:
		x += 100;
		y = 100;
		vx = 0;
		vy = 0;
		break;
	}
}
//bool CMorningstar::check() {
//	return TRUE;
//}