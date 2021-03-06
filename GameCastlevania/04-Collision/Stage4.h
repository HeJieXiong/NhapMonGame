#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#include "Simon.h"
#include "Brick.h"
#include "BackGround.h"
#include "Goomba.h"
#include "Fire.h"
#include "Morningstar.h"
#include "HeaderBar.h"
#include "Item.h"
#include "TileMap.h"
#include "Knife.h"
#include "Candle.h"
#include "Ghost.h"
#include "Stair.h"
#include "Grid.h"
#include "Bat.h"
#include "Fish.h"
#define BACKGROUND_COLOR D3DCOLOR_XRGB(0,0,0)


#define MAX_FRAME_RATE 100

#define ID_TEX_SIMON 0
#define ID_TEX_MISC 10
#define ID_TEX_FIRE 30
#define ID_TEX_MORNINGSTAR 40
#define ID_TEX_HEADERBAR 50
#define ID_ITEM			60
#define ID_TEX_KNIFE		70
#define	ID_TEX_CANDLE		80
#define ID_TEX_GHOST	90
#define ID_TEX_BAT	100
#define ID_TEX_BIG_BRICK 110
#define ID_TEX_FISH 120
#define MAP_LENGTH	4608

class  CStage4 {

	CGame		*game;
	CMorningstar*morningstar;
	CSimon		*Simon;
	CFire		*fire;
	CHeaderBar	*headerbar;
	CHeaderBar	*health;
	CHeaderBar	*enemy;
	CKnife		*knife;
	CCandle		*candle;
	CGhost		*ghost;
	CStair		*stair;
	CBat		*bat;
	CFish		*fish;
	TileMap		*map;
	CGrids		*gridsSys;
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> objects_morningstar;
	vector<LPGAMEOBJECT> obejects_item;
	vector<LPGAMEOBJECT> objects_weapons;
	vector<LPGAMEOBJECT> objects_bat;
	vector<LPGAMEOBJECT> objects_fish;
	vector<LPGAMEOBJECT> objects_stair_1;
	vector<LPGAMEOBJECT> objects_stair_2;
	vector<LPGAMEOBJECT> objects_stair_3;
	int **stagemap;
public:
	int stage_id = 4;
	bool is_running;
	CStage4(CSimon *a, CMorningstar *b, CKnife *d, int e) {
		Simon = a;
		morningstar = b;
	};
	void LoadStage4();
	void Update(DWORD dt);
	void Render();
	void SetGame(CGame *g) {
		game = CGame::GetInstance();
		game = g;
	}
	int column, row;
	float **location3;
	~CStage4();
};