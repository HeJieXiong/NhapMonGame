#include "Light_die.h"

void CLight::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + LIGHT_BOX_WIDTH;
	bottom = y + LIGHT_BOX_HEIGHT;
}

void CLight::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);
	if (GetTickCount() - time_start < 200) {
		vy += LIGHT_GRAVITY * dt;
		time_disappear += dt;
	}
	if (time_disappear > dt*8) {
		y = -99999;		
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() == 0)//new code
	{

		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
	}
	
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CLight::Render(float &xcam, float &ycam, float &x_simon, float &y_simon)
{
	int ani = LIGHT_ANI;
	animations[ani]->Render(x - xcam, y - ycam);
	//RenderBoundingBox(xcam,ycam);
}

void CLight::SetState(int state)
{
	CGameObject::SetState(state);
}

void CLight::Light_setting(CLight * Light, float & x, float & y)
{

	int ani = LIGHT_ANI;
	Light->x = x;
	Light->y = y + 10000;
	Light->AddAnimation(ani);
	//Light->tag = 5;
	time_start = GetTickCount();
}
