#include "Ghost.h"
#include "GameObject.h"

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

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	x += dx;
	y += dy;

	if (vx < 0 && x < 0) {
		x = 0; vx = -vx;
	}

	if (vx > 0 && x > 290) {
		x = 290; vx = -vx;
	}
}

void CGhost::Render(float &xcam, float &ycam, float &x_simon, float &y_simon)
{
	int ani = GHOST_ANI_WALKING;
	animations[ani]->Render(x - xcam, y - ycam);
	RenderBoundingBox(xcam, ycam);
	//RenderBoundingBox();
}

void CGhost::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GHOST_STATE_WALKING:
		vx = -GHOST_WALKING_SPEED;
	}

}
