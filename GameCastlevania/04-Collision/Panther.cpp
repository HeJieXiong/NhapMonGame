#include "Panther.h"
#include "Simon.h"

CPanther::CPanther()
{
	is_standing = 1;
	is_jump = false;
	point = 100;
}
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
	if (abs(simon->x - this->x) <= 200)
	{
		is_standing = false;
	}
	if (is_standing == false)
	{
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();
		if (state != DOG_STATE_DIE)
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
			for (UINT i = 0; i < coEventsResult.size(); i++)
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
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}
}

void CPanther::Render(float & xcam, float & ycam, float & x_simon, float & y_simon)
{
	int ani = PANTHER_ANI_WALKING;
	animations[ani]->Render(x - xcam, y - ycam);
	RenderBoundingBox(xcam, ycam);
}

void CPanther::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PANTHER_STATE_WALKING:
		vx = -PANTHER_WALKING_SPEED_X;
	}
}

void CPanther::Jump()
{
}

void CPanther::Move()
{
}
