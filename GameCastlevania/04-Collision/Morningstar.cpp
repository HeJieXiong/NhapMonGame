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
	x = x_simon-xcam;
	y = y_simon-ycam+10;
	int ani = 0;
	animations[ani]->Render(x_simon - xcam-5, y_simon - ycam+6);
	RenderBoundingBox_MoringStar(x, y);
}

void CMorningstar::LoadResource() {
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_MORNINGSTAR, L"textures\\whip.png", D3DCOLOR_XRGB(255,0, 255));
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	LPDIRECT3DTEXTURE9 textmorningstar = textures->Get(ID_TEX_MORNINGSTAR);
	sprites->Add(5001, 51, 5, 67, 25, textmorningstar);
	sprites->Add(5002, 80, 5, 132, 25, textmorningstar);
	sprites->Add(5003, 150, 5, 160, 25, textmorningstar);
	LPANIMATION ani;
	ani = new CAnimation(100);
	ani->Add(5003);
	ani->Add(5001);
	ani->Add(5002);
	animations->Add(701, ani);	
	this->AddAnimation(701);
}


void CMorningstar::SetType(int type) {
	type_morningstar = type;
}