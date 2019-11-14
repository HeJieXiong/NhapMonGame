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
#include "Light_die.h"
#include "Candle.h"
#include "Ghost.h"
#include "Stair.h"
#include "Grid.h"
#include "Panther.h"
#include "Bat.h"
#include "Fish.h"
#include "Boss.h"
#define BACKGROUND_COLOR D3DCOLOR_XRGB(0,0,0)


#define MAX_FRAME_RATE 100

#define ID_TEX_SIMON 0
#define ID_TEX_MISC_1 10
#define ID_TEX_MISC_2 10
#define ID_TEX_FIRE 30
#define ID_TEX_MORNINGSTAR 40
#define ID_TEX_HEADERBAR 50
#define ID_ITEM			60
#define ID_TEX_KNIFE		70
#define ID_TEX_LIGHT		80
#define ID_TEX_SIMON_EXTRA		90
#define	ID_TEX_CANDLE		80
#define ID_TEX_GHOST	90
#define ID_TEX_PANTHER	100
#define ID_TEX_BAT	100
#define ID_TEX_BIG_BRICK 110
#define ID_TEX_FISH 120
#define ID_TEX_BOSS	160
#define MAP_LENGTH	4608
class  CStage1 {
	//Stage 1
	CGame		*game;
	CMorningstar*morningstar;
	CSimon		*Simon;
	CFire		*fire;
	CHeaderBar	*headerbar;
	CHeaderBar	*health;
	CHeaderBar	*enemy;
	CKnife		*knife;
	CLight		*light;
	TileMap		*map;

	//Stage 2
	CCandle		*candle;
	CGhost		*ghost;
	CStair		*stair;
	CGrids		*gridsSys;
	CPanther	*panther;
	


	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> objects_morningstar;
	vector<LPGAMEOBJECT> obejects_item;
	vector<LPGAMEOBJECT> objects_weapons;
	vector<LPGAMEOBJECT> objects_panther;
	vector<LPGAMEOBJECT> objects_stair_1;
	vector<LPGAMEOBJECT> objects_stair_2;
	vector<LPGAMEOBJECT> objects_stair_3;
	int count1;
	int **stagemap;
public:
	int stage_id = 1;
	bool is_running;
	CStage1(CSimon *a,CMorningstar *b, CKnife *d, int e) {
		Simon = a;
		morningstar = b;
	};
	void LoadStage();
	void Update(DWORD dt);
	void Render();
	void SetGame(CGame *g) { game = CGame::GetInstance();
	game = g;
	}
	int column, row;
	float **location2;
	~CStage1();
};