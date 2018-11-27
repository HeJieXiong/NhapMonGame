/* =============================================================
INTRODUCTION TO GAME PROGRAMMING SE102

SAMPLE 04 - COLLISION

This sample illustrates how to:

1/ Implement SweptAABB algorithm between moving objects
2/ Implement a simple (yet effective) collision frame work

Key functions:
CGame::SweptAABB
CGameObject::SweptAABBEx
CGameObject::CalcPotentialCollisions
CGameObject::FilterCollision

CGameObject::GetBoundingBox

NOTE: Ý tưởng cho việc Tạo item và nhặt item của Simon , va chạm giữa roi và vật tĩnh
Tạo 1 mảng để chứa các vật thể mà roi có thể va chạm rớt item (A1),  nếu roi va chạm với thì set vị trí x=9999
Dùng vòng for để kiểm tra mảng vật thể (A1) nếu thỏa x==9999 và tag vật thể  =0 thì sẽ tạo 1 item mới và set tag vật thể về 4
Sau khi tạo item thì item sẽ được lưu vào mảng (A2), tại đây sẽ có hàm xét va chạm giữa item và nền đất , Simon

================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <string.h>
#include "debug.h"
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
#include "Stage.h"
#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255,255,255)


#define MAX_FRAME_RATE 100

#define ID_TEX_SIMON 0
#define ID_TEX_MISC 10
#define ID_TEX_FIRE 30
#define ID_TEX_MORNINGSTAR 40
#define ID_TEX_HEADERBAR 50
#define ID_ITEM			60
#define ID_TEX_KNIFE		70
CGame		*game;
CMorningstar*morningstar;
CSimon		*Simon;
CFire		*fire;
CHeaderBar	*headerbar;
CHeaderBar	*health;
CHeaderBar	*enemy;
CKnife		*knife;
TileMap		*map;
CStage		*stage;

vector<LPGAMEOBJECT> objects;
vector<LPGAMEOBJECT> objects_morningstar;
vector<LPGAMEOBJECT> obejects_item;
vector<LPGAMEOBJECT> objects_weapons;
class CSampleKeyHander : public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler;

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_X:
		Simon->SetState(SIMON_STATE_JUMP);
		break;
	case DIK_A: // reset
		Simon->SetState(SIMON_STATE_IDLE);
		Simon->SetPosition(50.0f, 0.0f);
		break;
	case DIK_Z:
		Simon->attack_wp = 0;
		Simon->Attack(morningstar,Simon->x,Simon->y);
		break;
	case DIK_C:
		Simon->attack_wp = 1;
		Simon->Attack_Weapons(&objects_weapons);
		break;
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSampleKeyHander::KeyState(BYTE *states)
{
	// disable control key when SIMON die 
	if (Simon->GetState() == SIMON_STATE_DIE) return;
	if (game->IsKeyDown(DIK_RIGHT)) {
		if (game->IsKeyDown(DIK_Z))
			Simon->vx = 0;
		else
		Simon->SetState(SIMON_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT)) {
		if (game->IsKeyDown(DIK_Z)|| game->IsKeyDown(DIK_C))
			Simon->vx = 0;
		else Simon->SetState(SIMON_STATE_WALKING_LEFT);
	}
	else if (game->IsKeyDown(DIK_DOWN)) {
		if (game->IsKeyDown(DIK_X)) {
			Simon->vy = 0;
			Simon->y = 149.9999;
			Simon->SetState(SIMON_STATE_SIT_DOWN);
		}
		else
			Simon->SetState(SIMON_STATE_SIT_DOWN);
	}
	else
		Simon->SetState(SIMON_STATE_IDLE);
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
Load all game resources
In this example: load textures, sprites, animations and SIMON object

TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/
void LoadResources()
{
	map = new TileMap();
	
	CTextures * textures = CTextures::GetInstance();
	LPANIMATION ani;
	textures->Add(ID_TEX_SIMON, L"textures\\simon2.png", D3DCOLOR_XRGB(0, 0, 0));
	textures->Add(ID_TEX_MISC, L"textures\\ground\\2.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_FIRE, L"textures\\fire.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_MORNINGSTAR, L"textures\\whip.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_HEADERBAR, L"textures\\ItemBoard.png",D3DCOLOR_XRGB(255,0,255));
	textures->Add(ID_ITEM, L"textures\\item\\item.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_KNIFE, L"textures\\item\\item.png", D3DCOLOR_XRGB(255, 0, 255));

	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	//ITEM-START
	LPDIRECT3DTEXTURE9 textItem = textures->Get(ID_ITEM);
	sprites->Add(9000, 43, 43, 61, 59, textItem);//WHIP UPGRAGDE
	sprites->Add(9001, 125, 39, 134, 47, textItem);//HEART
	sprites->Add(9002, 124, 59, 136, 69, textItem);//HEART BIG
	sprites->Add(9003, 176, 40, 194, 49, textItem);//KNIFE
	sprites->Add(9004, 225, 40, 240, 53, textItem);//AXE_1
	sprites->Add(9005, 225, 62, 240, 77, textItem);//AXE_2
	sprites->Add(9006, 225, 89, 240, 103, textItem);//AXE_3
	sprites->Add(9007, 225, 113, 240, 127, textItem);//AXE_4
	sprites->Add(9008, 264, 39, 280, 53, textItem);//BOOMERANG_1
	sprites->Add(9009, 290, 39, 305, 53, textItem);//BOOMERANG_2
	sprites->Add(9010, 316, 39, 330, 53, textItem);//BOOMERANG_3
	sprites->Add(9011, 379, 43, 392, 58, textItem);//BAG_100
	sprites->Add(9012, 379, 68, 392, 83, textItem);//BAG_400
	sprites->Add(9013, 379, 92, 392, 107, textItem);//BAG_700
	ani = new CAnimation(100); //WHIP UPGRADE
	ani->Add(9000);
	animations->Add(900, ani);
	ani = new CAnimation(100); //HEART
	ani->Add(9001);
	animations->Add(901, ani);

	ani = new CAnimation(100); //HEART BIG
	ani->Add(9002);
	animations->Add(902, ani);
	ani = new CAnimation(100); //HEART BIG
	ani->Add(9003);
	animations->Add(903, ani);
	ani = new CAnimation(100); //AXE
	ani->Add(9004);
	ani->Add(9005);
	ani->Add(9006);
	ani->Add(9007);
	animations->Add(904, ani);
	ani = new CAnimation(100); //BOOMERANG
	ani->Add(9010);
	ani->Add(9009);
	ani->Add(9008);
	animations->Add(905, ani);
	ani = new CAnimation(100); //BAG_100
	ani->Add(9011);
	animations->Add(906, ani);
	ani = new CAnimation(100); //BAG_400
	ani->Add(9012);
	animations->Add(907, ani);
	ani = new CAnimation(100); //BAG_700
	ani->Add(9013);
	animations->Add(908, ani);
	//ITEM-END
	//MORNING-STAR-START
	LPDIRECT3DTEXTURE9 textmorningstar = textures->Get(ID_TEX_MORNINGSTAR);
	sprites->Add(5001, 4, 6, 68, 38, textmorningstar);//NORMAL ATTACK LEFT
	sprites->Add(5002, 88, 6, 151, 38, textmorningstar);
	sprites->Add(5003, 175, 6, 239, 38, textmorningstar);
	sprites->Add(5004, 431, 6, 495, 38, textmorningstar);//NORMAL ATTACK RIGHT
	sprites->Add(5005, 348, 6, 411, 38, textmorningstar);
	sprites->Add(5006, 260, 6, 324, 38, textmorningstar);
	sprites->Add(5007, 431, 93, 495, 121, textmorningstar);//TYPE_1 ATTACK RIGHT
	sprites->Add(5008, 348, 93, 411, 121, textmorningstar);
	sprites->Add(5009, 260, 93, 336, 121, textmorningstar);
	sprites->Add(5010, 4, 93, 82, 121, textmorningstar);//TYPE_1 ATTACK LEFT
	sprites->Add(5011, 88, 93, 165, 121, textmorningstar);
	sprites->Add(5012, 178, 93, 242, 121, textmorningstar);
	ani = new CAnimation(150); //NORMAL ATTACK LEFT
	ani->Add(5001);
	ani->Add(5002);
	ani->Add(5003);
	animations->Add(701, ani);
	ani = new CAnimation(150); //NORMAL ATTACK RIGHT
	ani->Add(5004);
	ani->Add(5005);
	ani->Add(5006);
	animations->Add(702, ani);
	ani = new CAnimation(150); //TYPE_1 ATTACK LEFT
	ani->Add(5010);
	ani->Add(5011);
	ani->Add(5012);
	animations->Add(703, ani);
	
	ani = new CAnimation(150); //TYPE_1 ATTACK RIGHT
	ani->Add(5007);
	ani->Add(5008);
	ani->Add(5009);
	animations->Add(704, ani);
	morningstar = new CMorningstar();
	morningstar->AddAnimation(701);
	morningstar->AddAnimation(702);
	morningstar->AddAnimation(703);
	morningstar->AddAnimation(704);
	//objects.push_back(morningstar);
	//MORNING-STAR-END
	//BRICK-START
	LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_MISC);
	sprites->Add(20001, 0, 0, 31, 31, texMisc);
	ani = new CAnimation(100);		// brick
	ani->Add(20001);
	animations->Add(601, ani);
	for (int i = 0; i < 48; i++)
	{
		CBrick *brick = new CBrick();
		brick->AddAnimation(601);
		brick->SetPosition(0 + i * 16.0f, 186);
		brick->tag = 1;
		objects.push_back(brick);
		obejects_item.push_back(brick);
	}
	//BRICK-END
	//KNIFE-STAR
	LPDIRECT3DTEXTURE9 textKnife = textures->Get(ID_TEX_KNIFE);
	sprites->Add(11000, 177, 40, 194, 48, textKnife);
	sprites->Add(11001, 177, 60, 194, 69, textKnife);
	ani = new CAnimation(100);
	ani->Add(11000);
	animations->Add(1100, ani);
	ani = new CAnimation(100);
	ani->Add(11001);
	animations->Add(1101, ani);

	//KNIFE-END
	//FIRE-START
	LPDIRECT3DTEXTURE9 textFire = textures->Get(ID_TEX_FIRE);
	sprites->Add(4001, 0, 0, 17, 31, textFire);
	sprites->Add(4002, 27, 0, 44, 31, textFire);
	ani = new CAnimation(100);		//fire
	ani->Add(4001);
	ani->Add(4002);
	animations->Add(603, ani);
	for (int i = 0; i < 5; i++) {  //fire
		fire = new CFire();
		fire->AddAnimation(603);
		fire->SetPosition(i * 130 + 88, 156);
		fire->tag = 0;
		objects.push_back(fire);
		objects_morningstar.push_back(fire);
		objects_weapons.push_back(fire);
	}
	//FIRE-END

	
	

	//HEAD-BAR-START
	LPDIRECT3DTEXTURE9 texHeaderBar = textures->Get(ID_TEX_HEADERBAR);
	sprites->Add(8001, 0, 0, 49, 26, texHeaderBar); //heart,p bar
	sprites->Add(8002, 50, 0, 54, 8, texHeaderBar); //health
	sprites->Add(8003, 61, 0, 65, 8, texHeaderBar); //enemy
	ani = new CAnimation(100);//heart&pbar
	ani->Add(8001);
	animations->Add(801, ani);

	ani = new CAnimation(100);//health
	ani->Add(8002);
	animations->Add(802, ani);

	ani = new CAnimation(100);//enemy
	ani->Add(8003);
	animations->Add(803, ani);
	headerbar = new CHeaderBar(game->GetDirect3DDevice());
	headerbar->AddAnimation(801);
	headerbar->tag = 3;
	headerbar->SetPosition(200, 15);
	objects.push_back(headerbar);
	for (int i = 0; i < 15; i++) { //healthbar
		health = new CHeaderBar(game->GetDirect3DDevice());
		health->AddAnimation(802);
		health->SetPosition(i * 5 + 80, 16);
		health->tag = 0;
		objects.push_back(health);
	}
	for (int i = 0; i < 14; i++) {//enemybar
		enemy = new CHeaderBar(game->GetDirect3DDevice());
		enemy->AddAnimation(803);
		enemy->SetPosition(i * 5 + 80, 26);
		objects.push_back(enemy);
	}
	//HEAD-BAR-END
	

	


	//SIMON-START
	LPDIRECT3DTEXTURE9 texSIMON = textures->Get(ID_TEX_SIMON);
	int top_simon = 0;
	int bottom_simon = 33;
	int id_simon = 10001;
	for (int i = 0; i <4; i++) {
		int left = 0;
		int right = 30;
		for (int j = 0; j < 16; j++) {
			sprites->Add(id_simon, left, top_simon, right, bottom_simon, texSIMON);
			id_simon++;
			left += 30;
			right += 30;
		}
		top_simon += 33;
		bottom_simon += 33;
	}
	ani = new CAnimation(100);	// idle big right
	ani->Add(10014);
	animations->Add(400, ani);

	ani = new CAnimation(100);	// idle big left
	ani->Add(10003);
	animations->Add(401, ani);

	ani = new CAnimation(100);	// walk right big
	ani->Add(10013);
	ani->Add(10014);
	ani->Add(10015);
	ani->Add(10016);
	animations->Add(404, ani);

	ani = new CAnimation(100);	// // walk left big
	ani->Add(10004);
	ani->Add(10003);
	ani->Add(10002);
	ani->Add(10001);
	animations->Add(405, ani);

	ani = new CAnimation(100);	// idle jump right
	ani->Add(10012);
	animations->Add(406, ani);

	ani = new CAnimation(100);	// idle jump left
	ani->Add(10005);
	animations->Add(407, ani);

	ani = new CAnimation(100);	// idle sit down left
	ani->Add(10005);
	animations->Add(408, ani);

	ani = new CAnimation(100);	// idle sit down right
	ani->Add(10012);
	animations->Add(409, ani);

	ani = new CAnimation(150);	// idle attack left
	ani->Add(10006);
	ani->Add(10007);
	ani->Add(10008);
	animations->Add(410, ani);

	ani = new CAnimation(150);	// idle attack right
	ani->Add(10011);
	ani->Add(10010);
	ani->Add(10009);
	animations->Add(411, ani);

	ani = new CAnimation(150);	// idle attack sit left
	ani->Add(10049);
	ani->Add(10033);
	ani->Add(10034);
	animations->Add(412, ani);

	ani = new CAnimation(150);	// idle attack sit right
	ani->Add(10050);
	ani->Add(10048);
	ani->Add(10047);
	animations->Add(413, ani);


	ani = new CAnimation(150);	// idle disappear
	ani->Add(10051);
	ani->Add(10052);
	ani->Add(10053);
	ani->Add(10054);
	ani->Add(10055);
	animations->Add(414, ani);

	Simon = new CSimon(morningstar,headerbar,knife );
	Simon->AddAnimation(400);		// idle right big
	Simon->AddAnimation(401);		// idle left big
	Simon->AddAnimation(402);		// idle right small
	Simon->AddAnimation(403);		// idle left small
	Simon->AddAnimation(404);		// walk right big
	Simon->AddAnimation(405);		// walk left big
	Simon->AddAnimation(406);		// jump right
	Simon->AddAnimation(407);		// jump left
	Simon->AddAnimation(408);		// sit down left
	Simon->AddAnimation(409);		// sit down right
	Simon->AddAnimation(410);		// attack left
	Simon->AddAnimation(411);		// attack right
	Simon->AddAnimation(412);		// attack sit left
	Simon->AddAnimation(413);		// attack sit right
	Simon->AddAnimation(414);		// attack disappear
	Simon->SetPosition(40.0f, 0);
	objects.push_back(Simon);
	//SIMON-END
	
	
	stage = new CStage(1,Simon,map,morningstar);
	
}

/*
Update world status for this frame
dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	// We know that SIMON is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	vector<LPGAMEOBJECT> coObjects;
	vector<LPGAMEOBJECT> coObjects_morningstar;
	vector<LPGAMEOBJECT> coObjects_item;
	vector<LPGAMEOBJECT> coObjects_weapons;
	for (int i = 0; i < objects.size(); i++)
	{
		if(objects[i]->tag==1|| objects[i]->tag == 5)
		coObjects.push_back(objects[i]);
	}
	
	for (int i = 0; i < obejects_item.size(); i++)
	{
		if (obejects_item[i]->tag == 1|| obejects_item[i]->tag == 5)
			coObjects_item.push_back(obejects_item[i]);
	}
	for (int i = 0; i < objects_weapons.size(); i++)
	{
		coObjects_weapons.push_back(objects_weapons[i]);
	}

	for (int i = 0; i < objects_morningstar.size(); i++)
	{
			coObjects_morningstar.push_back(objects_morningstar[i]);
			if (objects_morningstar[i]->state == 100 && objects_morningstar[i]->tag==0) {				
						CItem		*item;
						item = new CItem();
						int rand_no;
						rand_no = rand() % 2 + 900;
						item->Item_setting(item, objects_morningstar[i]->x, objects_morningstar[i]->y, rand_no);
						objects.push_back(item);
						obejects_item.push_back(item);
						objects_morningstar[i]->tag = 5;
				}
	}
	morningstar->Update_colison(&coObjects_morningstar);
	for (int i = 0; i < objects_weapons.size(); i++)
	{
		objects_weapons[i]->Update(dt, &coObjects_weapons);
		if (objects_weapons[i]->y==-9850 && objects_weapons[i]->tag == 0) {
			CItem		*item;
			item = new CItem();
			int rand_no;
			rand_no = rand() % 2 + 900;
			item->Item_setting(item, objects_weapons[i]->x, objects_weapons[i]->y, rand_no);
			objects.push_back(item);
			obejects_item.push_back(item);
			objects_weapons[i]->tag = 5;
		}
	}
	for (int i = 0; i < obejects_item.size(); i++)
	{
		coObjects_item.push_back(obejects_item[i]);
	}
	for (int i = 0; i < obejects_item.size(); i++)
	{
		obejects_item[i]->Update(dt, &coObjects_item);
	}
	
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}
	

	
}

/*
Render a frame
*/
void Render()
{
	
	
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();
	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		float x = Simon->x;
		float y = 0;
		
		if (x <= SCREEN_WIDTH / 2) {
			x = 0;
		}
		else if (x > 550) {
			x = 350;
		}
		else
			x = Simon->x - SCREEN_WIDTH / 2;
		stage->SetStage(x, y);
		for (int i = 0; i < objects.size(); i++) {
			
				if(objects[i]->tag!=3)
					objects[i]->Render(x, y,Simon->x,Simon->y);
		}
		for (int i = 0; i < objects_weapons.size(); i++) {
				objects_weapons[i]->Render(x, y, Simon->x, Simon->y);
		}
		float i = objects_weapons[1]->x;
			headerbar->DrawHeaderbar(i, headerbar->time_, headerbar->heart_, headerbar->p_);
		
		
		spriteHandler->End();
		d3ddv->EndScene();
		
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			
			if ((Simon->x < 650) &&( game->unablekeyboard == 0)) {
				
				game->ProcessKeyboard();
			}
			else {
				if (Simon->GetState() != SIMON_STATE_IDLE && Simon->is_walking!=1) {
					Simon->SetState(SIMON_STATE_WALKING_LEFT);
					Simon->vx = -0.02;
				}
				if (Simon->x <= 610) {
					Simon->vx = 0;
					Simon->nx = 1;
					Simon->SetState(SIMON_STATE_IDLE);
				}
				if (Simon->x <= 630 && Simon->GetState() != SIMON_STATE_WALKING_LEFT) {
						Simon->SetState(SIMON_STATE_WALKING_RIGHT);
						Simon->vx = 0.02;
						Simon->is_walking = 1;
				}
				if (Simon->x >= 660 && Simon->GetState() == SIMON_STATE_WALKING_RIGHT) {
					Simon->SetState(SIMON_STATE_DISAPPEAR);
					Simon->vx = 0;
				}
				
				
				game->unablekeyboard = 1;
			}
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/*std::string a="dcm";
	std::string b="game";*/
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);
	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);
	

	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}