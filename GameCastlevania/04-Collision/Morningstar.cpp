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

void CMorningstar::Render(float &xcam, float &ycam)
{
	int ani = 0;
	animations[ani]->Render(xcam, ycam);
	RenderBoundingBox(xcam, ycam); 
}

void CMorningstar::LoadResource() {
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_MORNINGSTAR, L"textures\\whip.png", D3DCOLOR_XRGB(255, 255, 255));
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	LPDIRECT3DTEXTURE9 textmorningstar = textures->Get(ID_TEX_MORNINGSTAR);
	sprites->Add(5001, 52, 5, 67, 25, textmorningstar);
	sprites->Add(5002, 80, 5, 130, 25, textmorningstar);
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