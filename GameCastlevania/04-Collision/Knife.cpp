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

		// turn off collision when die 
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
		//if (state == 0) {//SIMON_ANI_SIT_ATTACK_LEFT
		//	x = x_simon - 25;
		//	y = y_simon + 15;
		//	int ani = 0;

		//	animations[ani]->Render(x - xcam - 2, y - ycam - 10);
		//	//RenderBoundingBox_MoringStar(x, y);
		//	RenderBoundingBox_MoringStar(xcam, ycam);
		//}
		//if (state == 1) {//SIMON_ANI_SIT_ATTACK_RIGHT
		//	x = x_simon;
		//	y = y_simon + 15;
		//	int ani = 0;
		//	animations[ani]->Render(x - xcam - 15, y - ycam - 10);
		//	//RenderBoundingBox_MoringStar(x, y);
		//	RenderBoundingBox_MoringStar(xcam, ycam);
		//}
		//if (state == 2) {//SIMON_ANI_ATTACK_LEFT
		//	int ani = 0;
		//	x = x_simon - 26;
		//	y = y_simon + 10;
		//	animations[ani]->Render(x - xcam - 4, y - ycam - 10);
		//	//RenderBoundingBox_MoringStar(x, y);
		//	RenderBoundingBox_MoringStar(xcam, ycam);
		//}
		//if (state == 3) {//SIMON_ANI_ATTACK_RIGHT
		//	x = x_simon;
		//	y = y_simon + 10;
		//	int ani = 0;
		//	animations[ani]->Render(x - xcam - 15, y - ycam - 10);
		//	RenderBoundingBox_MoringStar(xcam, ycam);
		//}
	
}


