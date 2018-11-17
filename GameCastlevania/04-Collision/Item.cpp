#include "Item.h"
#include <cstdlib> 
#include <ctime> 

void CItem::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x+ITEM_WIDTH ;
	bottom = y+ITEM_HEIGHT;
}

void CItem::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += ITEM_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	/*if ( GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
	untouchable_start = 0;
	untouchable = 0;
	}*/
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

void CItem::Render(float &xcam, float &ycam, float &x_, float &y_)
{
	int ani = 0;
	animations[ani]->Render(x - xcam, y - ycam);
	RenderBoundingBox(xcam, ycam);

}

void CItem::Item_setting(CItem * Item, float & x, float & y,int ani)
{

		
		Item->x = x;
		Item->y = y;
		Item->AddAnimation(ani);
		Item->check = 0;
		/*Item->vy += 500;
		Item->vx += 400;*/
	
}

void CItem::SetState(int state)
{
	CGameObject::SetState(state);
	//switch (state)
	//{
	//case FIRE_STATE:
	//	x += 100;
	//	y = 100;
	//	vx = 0;
	//	vy = 0;
	//	break;
	//}
}