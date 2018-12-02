#include "Knife.h"
#include "Textures.h"
#include "Sprites.h"
#include <chrono>
#include <thread>


CKnife::CKnife() {
	type_morningstar = 0;
}

CKnife::~CKnife() {

}

CKnife * CKnife::_instance = NULL;

CKnife *CKnife::GetInstance()
{
	if (_instance == NULL) _instance = new CKnife();
	return _instance;
}

void CKnife::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	// Calculate dx, dy 
	CGameObject::Update(dt);
	// Simple fall down
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();
		CalcPotentialCollisions(coObjects, coEvents);
		if (coEvents.size() == 0)//new code
		{

			x += dx;
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
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			
			if (dynamic_cast<CFire *>(e->obj))
			{
				CFire *fire = dynamic_cast<CFire *>(e->obj);

				if (e->nx != 0 || e->ny <0)
				{
					fire->state = 100;
					fire->y = -9850;
					y = -9999;
				}
			}
			if (dynamic_cast<CCandle *>(e->obj))
			{
				CCandle *Candle = dynamic_cast<CCandle *>(e->obj);

				if (e->nx != 0 || e->ny <0)
				{
					Candle->state = 100;
					Candle->y = -9850;
					y = -9999;
				}
			}
		}

		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void CKnife::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	
		top = y;
		left = x;
		bottom = y + KNIFE_BOX_HEIGHT;
		right = x + KNIFE_BOX_WIDTH;
	
	
	attack_time = 0;

}

void CKnife::Render(float &xcam, float &ycam, float &x_simon, float &y_simon)
{
	if (state == 0) {
		x = x_simon;
		y = y_simon;
		state = 1;
	}
		animations[0]->Render(x-xcam,y-ycam);
		RenderBoundingBox(xcam, ycam);
}


