#include "Boss.h"

void CBoss::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BOSS_STATE_STANDING:
		vx = vy = 0;
		break;
	case BOSS_STATE_DIE:
		vx = vy = 0;
		break;
	case BOSS_STATE_FLY:
		vx = BOSS_SPEED_X;
		break;
	}
}

void CBoss::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BOSS_BBOX_WIDTH;
	bottom = y + BOSS_BBOX_HEIGHT;
}

void CBoss::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	/*if (is_active == true) {*/
	if (is_active == false) {
		if (abs(simon->x - this->x) <= 150 && simon->x - this->x > 0)
		{
			is_active = true;
			check_fly = 3;
			vx = -BOSS_SPEED_X;
			
		}
	}
	if (is_active == true ) {
		if (check_fly == 3) {
			if (y < 100) {
				vy = BOSS_SPEED_Y;
				y += dy;
			}
			else {
				check_fly = 1;
				vy = 0;
			}
		}
		
		if (check_fly == 0) {
			
			if (vx < 0) {
				if (x < 450) {
					vx = -vx;
					check_fly = 1;
				}
				else vx = BOSS_SPEED_X;
			}
			if (vx > 0) {
				if (x > 650) {
					vx = -vx;
					check_fly = 1;
				}
				else vx = BOSS_SPEED_X;
			}
			y += dy;
			x += dx;
		}
		if (check_fly == 1) {
			if (vx < 0) {
				if (x < 450) {
					vx = -vx;
					check_fly = 0;
				}
			}


			if (vx > 0) {
				if (x > 650) {
					vx = -vx;
					check_fly = 0;
				}
			}
			y = 20 * sin(flying_coordinate* PI / 180) + 110;
			x += dx;
			flying_coordinate += 5;
		}
	}
}

void CBoss::Render(float & xcam, float & ycam, float & x_simon, float & y_simon)
{
	int ani = 0;
	if (check_fly == 2)
		ani = BOSS_ANI_STANDING;
	else 
		ani = BOSS_ANI_FLY;
	
	
	animations[ani]->Render(x - xcam, y - ycam);
	RenderBoundingBox(xcam, ycam);
	//RenderBoundingBox();
}
