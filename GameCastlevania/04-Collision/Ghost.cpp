#include "Ghost.h"
#include "GameObject.h"
#include "Simon.h"

void CGhost::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + GHOST_BBOX_WIDTH;
	bottom = y + GHOST_BBOX_HEIGHT;
}

void CGhost::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);
	vy += GHOST_GRAVITY * dt;
	// Xét va chạm của panther và Simon
	/*if (is_standing == false)
	{*/
	//if(is_jump==1)
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	//simon->point += this->point;
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;
		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			/*if (dynamic_cast<StartPoint *>(e->obj))
			{
				StartPoint *start = dynamic_cast<StartPoint *>(e->obj);
				if (jumped != true)
				{
					SetState(DOG_STATE_JUMP);
					return;
				}
			}*/
			if (dynamic_cast<CStair *>(e->obj))
			{
				CStair *stair = dynamic_cast<CStair *>(e->obj);
				if (e->nx < 0 || e->nx > 0 || e->ny < 0 || e->ny>0) {
					if (stair->type_stair == 50) {
						if (state == GHOST_STATE_WALKING_RIGHT && change_way == 0) {
							change_way = 1;
						}
						if (state == GHOST_STATE_WALKING && change_way == 0) {
							change_way = 2;
						}
					}
				}
			}
			if (dynamic_cast<CCandle *>(e->obj))
			{
				CCandle *candle = dynamic_cast<CCandle *>(e->obj);
				if (e->nx < 0 || e->nx > 0 || e->ny < 0 || e->ny>0) {
					x += dx;
				}
			}
			if (dynamic_cast<CKnife *>(e->obj))
			{
				CKnife *knife = dynamic_cast<CKnife *>(e->obj);	
						y = GHOST_Y_DIS;
						vy = 0;
						knife->y = 1000;
						knife->vx = 0;						
			}
		}
	}
	if (change_way == 1) {
		state = GHOST_STATE_WALKING;
		change_way = 0;
	}
	if (change_way == 2) {
		state = GHOST_STATE_WALKING_RIGHT;
		change_way = 0;
	}
	if (state == GHOST_STATE_WALKING) {	
		nx = -1;
		vx = -1*GHOST_WALKING_SPEED;
	}
	if (state == GHOST_STATE_WALKING_RIGHT) {
		nx = 1;
		vx = GHOST_WALKING_SPEED;
		
	}
	if (y == GHOST_Y_DIS) {
		vy = 0;
	}
	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];

	}

}

void CGhost::Render(float &xcam, float &ycam, float &x_simon, float &y_simon)
{
	int ani;
	if (state== GHOST_STATE_WALKING_RIGHT) {
		ani = GHOST_ANI_WALKING_RIGHT;
	}
	else {
		ani = GHOST_ANI_WALKING;
	};
	animations[ani]->Render(x - xcam, y - ycam);
	RenderBoundingBox(xcam, ycam);
	//RenderBoundingBox();
}

void CGhost::SetState(int state)
{
	CGameObject::SetState(state);

}
