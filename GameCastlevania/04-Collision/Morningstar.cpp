#include "Morningstar.h"
#include "Textures.h"
#include "Sprites.h"


CMorningstar::CMorningstar() {
	type_morningstar = MORNINGSTAR_NORMAL;
}

CMorningstar::~CMorningstar() {
	
}

CMorningstar * CMorningstar::_instance = NULL;

CMorningstar *CMorningstar::GetInstance()
{
	if (_instance == NULL) _instance = new CMorningstar();
	return _instance;
}

void CMorningstar::Update_colison( vector<LPGAMEOBJECT> *coObjects) {
	float top = y;
	float left = x;
	float bottom = y + MORNINGSTAR_BOX_HEIGHT;
	float right = x + MORNINGSTAR_BOX_WIDTH;
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		coObjects->at(i);
		float top_co;
		float left_co;
		float bottom_co;
		float right_co;
		coObjects->at(i)->GetBoundingBox(left_co, top, right_co, bottom_co);
		coObjects->at(i)->y = 100;
	}
}
void CMorningstar::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
	left = x;
	top = y;
	right = x + MORNINGSTAR_BOX_WIDTH;
	bottom = y + MORNINGSTAR_BOX_HEIGHT;
}

void CMorningstar::Render(float &xcam, float &ycam, float &x_simon, float &y_simon)
{
	if (state == 0) {
		x = x_simon - xcam - 22;
		y = y_simon - ycam + 15;
		int ani = 0;
		animations[ani]->Render(x_simon - xcam - 26, y_simon - ycam + 5);
		RenderBoundingBox_MoringStar(x, y);
	}
	if (state == 1) {
		x = x_simon - xcam;
		y = y_simon - ycam + 15;
		int ani = 1;
		animations[ani]->Render(x_simon - xcam - 8, y_simon - ycam + 5);
		RenderBoundingBox_MoringStar(x, y);
	}
	if (state == 2) {
		int ani = 0;
		x = x_simon - xcam - 22;
		y = y_simon - ycam + 10;
		animations[ani]->Render(x_simon - xcam - 26, y_simon - ycam);
		RenderBoundingBox_MoringStar(x, y);
	}
	if (state == 3) {
		x = x_simon - xcam;
		y = y_simon - ycam + 10;
		int ani = 1;
		animations[ani]->Render(x_simon - xcam - 8, y_simon - ycam);
		RenderBoundingBox_MoringStar(x, y);
	}
	
}

//void CMorningstar::LoadResource() {
//	CTextures * textures = CTextures::GetInstance();
//
//	CSprites * sprites = CSprites::GetInstance();
//	CAnimations * animations = CAnimations::GetInstance();
//	
//	LPANIMATION ani;
//	
//
//}


void CMorningstar::SetType(int type) {
	type_morningstar = type;
}