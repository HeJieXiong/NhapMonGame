#include "Morningstar.h"
#include "Textures.h"
#include "Sprites.h"


CMorningstar::CMorningstar() {
	type_morningstar = MORNINGSTAR_NORMAL;
	LoadResource();
}

CMorningstar::~CMorningstar() {

}

CMorningstar * CMorningstar::_instance = NULL;

CMorningstar *CMorningstar::GetInstance()
{
	if (_instance == NULL) _instance = new CMorningstar();
	return _instance;
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

void CMorningstar::LoadResource() {
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_MORNINGSTAR, L"textures\\whip.png", D3DCOLOR_XRGB(255,0, 255));
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	LPDIRECT3DTEXTURE9 textmorningstar = textures->Get(ID_TEX_MORNINGSTAR);

	sprites->Add(5001, 4, 6, 68, 38, textmorningstar);//NORMAL ATTACK LEFT
	sprites->Add(5002, 88, 6, 151, 38, textmorningstar);
	sprites->Add(5003, 175, 6, 239, 38, textmorningstar);

	sprites->Add(5004, 431, 6, 495, 38, textmorningstar);//NORMAL ATTACK RIGHT
	sprites->Add(5005, 348, 6, 411, 38, textmorningstar);
	sprites->Add(5006, 260, 6, 324, 38, textmorningstar);
	LPANIMATION ani;
	ani = new CAnimation(100); //NORMAL ATTACK LEFT
	ani->Add(5001);
	ani->Add(5002);
	ani->Add(5003);
	animations->Add(701, ani);	
	this->AddAnimation(701);

	ani = new CAnimation(101); //NORMAL ATTACK RIGHT
	ani->Add(5004);
	ani->Add(5005);
	ani->Add(5006);
	animations->Add(702, ani);
	this->AddAnimation(702);

}


void CMorningstar::SetType(int type) {
	type_morningstar = type;
}