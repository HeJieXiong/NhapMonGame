#include "Fish.h"
CFish::CFish()
{
	bullet = NULL;
}
void CFish::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (is_active == false) {
		if (simon->touch_wake == 1)
		{
			if (code == 1) {
				state = FISH_STATE_JUMP_LEFT;
				start_jump = GetTickCount();
				is_jump = 1;
				is_active = true;
			}
		}
		if (simon->touch_wake == 2)
		{
			if (code == 2) {
				state = FISH_STATE_JUMP_LEFT;
				start_jump = GetTickCount();
				is_jump = 1;
				is_active = true;
			}
		}
		if (simon->touch_wake == 3)
		{
			if (code == 3) {
				state = FISH_STATE_JUMP_LEFT;
				start_jump = GetTickCount();
				is_jump = 1;
				is_active = true;
			}
		}
	}
	if (is_active == true) {
		if (is_jump == 1) {
			if (GetTickCount() - start_jump <= FISH_TIME_JUMP_DOWN) {
				state = FISH_STATE_JUMP_LEFT;
				jump_down = 1;
			}
			else {	
				is_standing = 1;
				is_jump = 0;
				state = FISH_STATE_JUMP_DOWN;
			}

			//if (can_count == 1) {
			//	can_count = 0;
			//	is_jump = 0;
			//	//fire_countdown = GetTickCount();
			//}
		}
		if (is_standing == 1) {
			start_jump = 0;
		}
		
		if (state == FISH_STATE_WALKING_LEFT) {
			nx = -1;
			vx = -FISH_WALKING_SPEED;
			x += dx;
		}
		if (state == FISH_STATE_WALKING_RIGHT) {
			vx = FISH_WALKING_SPEED;
			x += dx;
		}
		if (state == FISH_STATE_ATK_LEFT || state == FISH_STATE_ATK_RIGHT) {
			vx = 0;
		}
		if (state == FISH_STATE_JUMP_LEFT) {
			vy = -FISH_JUMP_SPEED;
		}
		if (state == FISH_STATE_JUMP_DOWN) {
			vy = FISH_JUMP_SPEED;
		}
	}

	
	
	if (can_count == 0) {	
		if (GetTickCount() - fire_countdown  > 2000 && GetTickCount()- fire_countdown < 4000) {
			
			if (vx < 0) {
				vx = 0;
				state = FISH_STATE_ATK_LEFT;
				bullet_way = 1;
			}
			if (vx > 0) {
				vx = 0;
				state = FISH_STATE_ATK_RIGHT;
				bullet_way = 2;
			}
			can_fire = 1;
		}
		if (GetTickCount() - fire_countdown > 4000) {
			if (nx < 0) {
				state = FISH_STATE_WALKING_LEFT;
			}
			if (nx > 0) {
				state = FISH_STATE_WALKING_RIGHT;
			}
			can_count = 1;
			can_fire = 0;
		}
	}
	if (can_fire == 1) {
		if (bullet == NULL) {
			float a, b;
			a = x;
			x_bullet = a;
			b = y;
			bullet = new FishBullet(simon);
			bullet->SetPosition(a,b);
			bullet->way = bullet_way;
			if (this->nx > 0) bullet->vx = FISH_BULLET_SPEED_X;
			else bullet->vx = -FISH_BULLET_SPEED_X;
			
		}
	}
	if (bullet != NULL) bullet->Update(dt, coObjects);
	if (bullet != NULL)
	{
		if(can_fire==0)
			bullet = NULL;
		
		/*else if (bullet->isHit == true)
			bullet = NULL;*/
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

		//if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;


		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrick *>(e->obj))
			{
				CBrick *ground = dynamic_cast<CBrick *>(e->obj);
				if (is_standing == 0) {
					state = FISH_STATE_JUMP_LEFT;
					y += dy;
				}
				if (jump_down == 1 && is_standing == 1) {
					fire_countdown = GetTickCount();
					jump_down = 2;
				}
				if (touch_ground == 0 && is_standing == 1) {
					state = FISH_STATE_WALKING_LEFT;
					touch_ground = 1;
					change_way=1;
				}
			}
			if (dynamic_cast<CStair *>(e->obj))
			{
				CStair *stair = dynamic_cast<CStair *>(e->obj);
				if (e->nx < 0 || e->nx > 0 || e->ny < 0 || e->ny>0) {
					simon->count_panther_code = state;
					if (stair->type_stair != 50) {
						if (is_standing == 1 && first_touch == 0 && jump_down != 2) {
							y += dy;
						}
						if (is_standing == 0) {
							y -= dy;
						}
						x += dx;
					}
				}
			}			
		}			
	}
	if (code != 3) {
		if (change_way == 2) {
			state = FISH_STATE_WALKING_RIGHT;
			change_way = 0;
		}
		simon->count_panther_code = state;
		if (change_way == 1) {
			state = FISH_STATE_WALKING_LEFT;
			change_way = 0;
		}
		if (x - center < -1 * STATE_FOR_CHANGE) {
			change_way = 2;
		}
		if (x - center > STATE_FOR_CHANGE) {
			change_way = 1;
		}
		if (x - center > -2 && x - center < 2) {
			fire_countdown = GetTickCount();
			can_count = 0;
		}
	}
	// Xét va chạm của bat và Simon
	if (nx > 0) {
		if (x + FISH_BBOX_WIDTH >= simon->x &&x <= simon->x && y + FISH_BBOX_HEIGHT >= simon->y && y <= simon->y) {
			if (simon->untouchable == 0 && simon->is_heart == 0) {
				simon->start_heart = GetTickCount();
				simon->is_heart = 1;
				simon->state = SIMON_STATE_HEART;
			}
			else {
				x += dx;
			}
		}
	}
	if (nx < 0) {
		if (x + FISH_BBOX_WIDTH >= simon->x + SIMON_BIG_BBOX_WIDTH && x <= simon->x + SIMON_BIG_BBOX_WIDTH
			&& y <= simon->y + SIMON_BIG_BBOX_WIDTH && y + FISH_BBOX_HEIGHT >= simon->y + SIMON_BIG_BBOX_WIDTH) {
			if (simon->untouchable == 0 && simon->is_heart == 0) {
				simon->start_heart = GetTickCount();
				simon->is_heart = 1;
				simon->state = SIMON_STATE_HEART;
			}
			else {
				x += dx;
			}
		}
	}
	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];
	}
	
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
	if (state == FISH_STATE_ATK_RIGHT) {
		ani = FISH_ANI_ATK_RIGHT;
	}
	if (bullet != NULL)
	{
		bullet->Render(xcam, ycam,x,y);
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
void FishBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
		CGameObject::Update(dt, coObjects);
		if (way == 1) {
			x += dx;
		}
		if (way == 2) {
			x -= dx;
		}
		// Xét va chạm của bat và Simon
		if (vx > 0) {
			if (x + BULLET_BBOX_WIDTH >= simon->x &&x <= simon->x && y + BULLET_BBOX_HEIGHT >= simon->y && y <= simon->y) {
				if (simon->untouchable == 0 && simon->is_heart == 0) {
					simon->start_heart = GetTickCount();
					simon->is_heart = 1;
					simon->state = SIMON_STATE_HEART;
				}
				else {
					x += dx;
				}
			}
		}
		if (vx < 0) {
			if (x + BULLET_BBOX_WIDTH >= simon->x + SIMON_BIG_BBOX_WIDTH && x <= simon->x + SIMON_BIG_BBOX_WIDTH
				&& y <= simon->y + SIMON_BIG_BBOX_WIDTH && y + BULLET_BBOX_HEIGHT >= simon->y + SIMON_BIG_BBOX_WIDTH) {
				if (simon->untouchable == 0 && simon->is_heart == 0) {
					simon->start_heart = GetTickCount();
					simon->is_heart = 1;
					simon->state = SIMON_STATE_HEART;
				}
				else {
					x += dx;
				}
			}
		}
}

void FishBullet::Render(float &xcam, float &ycam, float &x_simon, float &y_simon)
{	
	int ani;
	if (way == 1) {
		ani = 0;
		animations[ani]->Render(x - xcam, y - ycam);
	}
	if (way == 2) {
		ani = 1;
		animations[ani]->Render(x - xcam, y - ycam);
	}
		RenderBoundingBox(xcam, ycam);
}
void FishBullet::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{

	left = x;
	top = y;
	right = x + BULLET_BBOX_WIDTH;
	bottom = y + BULLET_BBOX_HEIGHT;
}
