#include "Item.h"
#include <cstdlib> 
#include <ctime> 

void CItem::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	if (ani == 901)//SMALL_HEART
	{
		right = x + SMALL_HEART_WIDTH;
		bottom = y + SMALL_HEART_HEIGHT;
	}
	else if (ani == 902)//HEART
	{
		right = x + HEART_WIDTH;
		bottom = y + HEART_HEIGHT;
	}
	else if (ani == 903)//HEART
	{
		right = x + HEART_WIDTH;
		bottom = y + HEART_HEIGHT;
	}
	else//WEAPONS
	{
		right = x + WEAPONS_WIDTH;
		bottom = y + WEAPONS_HEIGHT;
	}
}

void CItem::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);
	if (check_taken == 0) {
		// Simple fall down
		vy += ITEM_GRAVITY * dt;

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

			/*if (nx != 0) vx = 0;
			if (ny != 0) vy = 0;*/
		}

		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void CItem::Render(float &xcam, float &ycam, float &x_, float &y_)
{
	int ani = 0;
	animations[ani]->Render(x - xcam, y - ycam);
	//RenderBoundingBox(xcam, ycam);
}

void CItem::Item_setting(CItem * Item, float & x, float & y,int a)
{
		
		ani = a;
		Item->x = x;
		Item->y = y+10010;
		Item->AddAnimation(ani);
		Item->tag = 5;
	
}

void CItem::SetState(int state)
{
	CGameObject::SetState(state);

}