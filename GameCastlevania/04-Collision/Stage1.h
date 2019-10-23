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


#define BACKGROUND_COLOR D3DCOLOR_XRGB(0,0,0)


#define MAX_FRAME_RATE 100

#define ID_TEX_SIMON 0
#define ID_TEX_MISC 10
#define ID_TEX_FIRE 30
#define ID_TEX_MORNINGSTAR 40
#define ID_TEX_HEADERBAR 50
#define ID_ITEM			60
#define ID_TEX_KNIFE		70
#define ID_TEX_LIGHT		80

class  CStage1 {

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

	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> objects_morningstar;
	vector<LPGAMEOBJECT> obejects_item;
	vector<LPGAMEOBJECT> objects_weapons;
	int count1;
	int **stagemap;
public:
	int stage_id = 1;
	bool is_running;
	CStage1(CSimon *a,CMorningstar *b, CKnife *d, int e) {
		Simon = a;
		morningstar = b;
	};
	void LoadStage1();
	void Update(DWORD dt);
	void Render();
	void SetGame(CGame *g) { game = CGame::GetInstance();
	game = g;
	}
	~CStage1();
};