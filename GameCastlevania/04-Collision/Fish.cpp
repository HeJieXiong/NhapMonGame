#include "Fish.h"

void CFish::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	float a = abs(simon->x - this->x);
	if (is_active == false) {
		if (abs(simon->x - this->x) <= 50 && simon->x - this->x < 0)
		{
			SetState(FISH_STATE_JUMP_LEFT);		
			start_jump = GetTickCount();
			is_jump = 1;
			is_active = true;
		}
	}
	if (is_active == true) {
		if (GetTickCount() - start_jump <= FISH_TIME_JUMP_DOWN) {
			vy = -FISH_JUMP_SPEED;
		}
		else {
			vy = FISH_JUMP_SPEED;
			is_standing = 1;
			
			if (can_count == 1 && is_jump==1) {
				can_count = 0;
				is_jump = 0;
				fire_countdown = GetTickCount();
			}
		}
		if (is_standing == 1) {
			start_jump = 0;
		}
	}

	if (can_count == 0) {	
		if (GetTickCount() - fire_countdown <= 2000) {
			state = FISH_STATE_WALKING_LEFT;
		}
		if (GetTickCount() - fire_countdown  > 2000 && GetTickCount()- fire_countdown < 4000) {
			vx = 0;
			if (nx < 0) {
				state = FISH_STATE_ATK_LEFT;
			}
			if (nx > 0) {
				state = FISH_STATE_ATK_RIGHT;
			}
			can_fire = 1;
		}
		if (GetTickCount() - fire_countdown >= 4000) {
			state = FISH_STATE_WALKING_LEFT; 
			fire_countdown = 0;
			can_count = 1;
			can_fire = 0;
		}
	}
	if (state == FISH_STATE_WALKING_LEFT) {
		vx = -FISH_WALKING_SPEED;
		x += dx;
	}
	if (can_count == 1 && is_standing == 1) {
		fire_countdown = GetTickCount();
		can_count = 0;
	}
	
	vector<LPCOLLISIONEVENT> coEventsResult;
	vector<LPCOLLISIONEVENT> coEvents;
	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);
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
			if (dynamic_cast<CBrick *>(e->obj))
			{
				CBrick *ground = dynamic_cast<CBrick *>(e->obj);
				if (is_standing == 0) {
					SetState(FISH_STATE_JUMP_LEFT);
					y +=dy;
					
				}
				
			}
			if (dynamic_cast<CBrick *>(e->obj)) {
				CStair *stair = dynamic_cast<CStair *>(e->obj);
				
			}
		}
	}
	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];
	}
	DebugOut(L"abs %d\n", a);
}

void CFish::Render(float &xcam, float &ycam, float &x_simon, float &y_simon)
{
	int ani = 0;
	if (state == FISH_STATE_HIDE) {
		ani = FISH_ANI_HIDE;
	}
	if (state == FISH_STATE_JUMP_LEFT) {
		ani = FISH_ANI_JUMP_LEFT;
	}
	if (state == FISH_STATE_WALKING_LEFT) {
		ani = FISH_ANI_WALKING_LEFT;
	}
	if (state == FISH_STATE_WALKING_RIGHT) {
		ani = FISH_ANI_WALKING_RIGHT;
	}
	if (state == FISH_STATE_ATK_LEFT) {
		ani = FISH_ANI_ATK_LEFT;
	}
	animations[ani]->Render(x - xcam, y - ycam);
	RenderBoundingBox(xcam, ycam);
}

void CFish::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FISH_STATE_ATK_LEFT:
		vx = 0;
		isAttacking = true;
		break;
	case FISH_STATE_ATK_RIGHT:
		vx = 0;
		isAttacking = true;
		break;
	case FISH_STATE_JUMP_LEFT:
		vy = -FISH_JUMP_SPEED;
		vx = 0;
		nx = -1;
		break;
	case FISH_STATE_JUMP_RIGHT:
		vy = -FISH_JUMP_SPEED;
		nx = 1;
		break;
	case FISH_STATE_WALKING_LEFT:
		vx = -FISH_WALKING_SPEED;
		nx = -1;
		break;
	case FISH_STATE_WALKING_RIGHT:
		vx = FISH_WALKING_SPEED;
		nx = 1;
		break;
	case FISH_STATE_HIDE:
		vx = 0;
		vy = 0;
		hitWater = 0;
		break;
	}
}

void CFish::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + FISH_BBOX_WIDTH;
	bottom = y + FISH_BBOX_HEIGHT;
}

void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	x += dx;
}

void CBullet::Render()
{
	animations[0]->Render(x, y);
}

void CBullet::GetBoundingBox(float &left, float &top, float &right, float &bottom){
	left = x;
	top = y;
	right = x + BULLET_BBOX_WIDTH;
	bottom = y + BULLET_BBOX_HEIGHT;
}
