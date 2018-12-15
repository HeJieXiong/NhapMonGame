#include "Panther.h"
#include "Simon.h"

//CPanther::CPanther()
//{
//	
//}
void CPanther::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + PANTHER_BBOX_WIDTH;
	bottom = y + PANTHER_BBOX_HEIGHT;
}

void CPanther::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	vy += PANTHER_GRAVITY * dt;
	float a = abs(simon->x - this->x);
	if (abs(simon->x - this->x) <= 200)
	{
		is_standing = false;
		is_active = true;
	}
	if (is_standing == false)
	{
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();
		if (state != PANTHER_STATE_DIE)
			CalcPotentialCollisions(coObjects, coEvents);
		else
		{
			simon->point += this->point;
		}

		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
			x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
			y += min_ty * dy + ny * 0.4f;

			if (nx != 0) vx = 0;
			if (ny != 0) vy = 0;


			// Collision logic with Goombas
			/*for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<StartPoint *>(e->obj))
				{
					StartPoint *start = dynamic_cast<StartPoint *>(e->obj);
					if (jumped != true)
					{
						SetState(DOG_STATE_JUMP);
						return;
					}
				}
				if (dynamic_cast<CCastleGround *>(e->obj))
				{
					CCastleGround *ground = dynamic_cast<CCastleGround *>(e->obj);
					if (jumped == true)
					{
						SetState(DOG_STATE_WALKING_RIGHT);
					}
					else SetState(DOG_STATE_WALKING_LEFT);
				}
			}
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];*/
		}
	}
	DebugOut(L"Panther_a %f\n", a);
	DebugOut(L"Panther_act %f\n", this->is_active);
}

void CPanther::Render(float & xcam, float & ycam, float & x_simon, float & y_simon)
{
	
	if (is_active == true)
	{
		int ani = 0;
		if (state == PANTHER_STATE_DIE)
		{
			ani = PANTHER_ANI_DIE;
		}
		else
		{
			if (vx == 0)
				ani = PANTHER_ANI_SLEEP;
			if (state == PANTHER_STATE_JUMP)
				ani = PANTHER_ANI_JUMP_LEFT;
			if (vx > 0)
				ani = PANTHER_ANI_WALKING_LEFT;
			if (vx < 0)
				ani = PANTHER_ANI_WALKING_LEFT;
		}

		animations[ani]->Render(x - xcam, y - ycam);
		RenderBoundingBox(xcam, ycam);
	}
}

void CPanther::SetState(int state)
{
	CGameObject::SetState(state);
		switch (state)
		{
		case PANTHER_STATE_DIE:
			is_active = false;
			break;
		case PANTHER_STATE_JUMP:
			vy = -PANTHER_WALKING_SPEED_Y;
			vx = -PANTHER_WALKING_SPEED_X;
			is_jump = true;
			break;
		case PANTHER_STATE_SLEEP:
			nx = -1;
			is_standing = true;
			vx = 0;
			break;
		case PANTHER_STATE_WALKING_LEFT:
			nx = -1;
			vx = -PANTHER_WALKING_SPEED_X;
			break;
		}
	}

void CPanther::Jump()
{
}

void CPanther::Move()
{
}
