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
		
================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#include "Simon.h"
#include "Brick.h"
#include "BackGround.h"
#include "Camera.h"
#include "Goomba.h"
#include "Fire.h"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0,0,0)


#define MAX_FRAME_RATE 100

#define ID_TEX_SIMON 0
#define ID_TEX_MISC 10
#define ID_TEX_BACK_GROUND 20
#define ID_TEX_FIRE 30

CGame *game;

CSimon *Simon;
CBackGround *background;
CFire *fire;
//CGoomba *goomba;

vector<LPGAMEOBJECT> objects;

class CSampleKeyHander: public CKeyEventHandler
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
		Simon->SetSpeed(0, 0);
		break;
	case DIK_Z:
		Simon->SetState(SIMON_STATE_ATTACK);
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
	if (game->IsKeyDown(DIK_RIGHT))
		Simon->SetState(SIMON_STATE_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))
		Simon->SetState(SIMON_STATE_WALKING_LEFT);
	else if (game->IsKeyDown(DIK_DOWN)) {
		if (game->IsKeyDown(DIK_X))
			Simon->SetState(SIMON_STATE_SIT_DOWN);
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
	CTextures * textures = CTextures::GetInstance();
	
	textures->Add(ID_TEX_SIMON, L"textures\\simon2.png",D3DCOLOR_XRGB(0, 0, 0));
	textures->Add(ID_TEX_MISC, L"textures\\ground\\2.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_BACK_GROUND, L"textures\\back_ground.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_FIRE, L"textures\\fire.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));


	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	
	LPDIRECT3DTEXTURE9 texBACKGROUND = textures->Get(ID_TEX_BACK_GROUND);
	sprites->Add(30001, 0, 0, 770, 145, texBACKGROUND);

	

	LPDIRECT3DTEXTURE9 texSIMON = textures->Get(ID_TEX_SIMON);

	// big
	int top = 0;
	int bottom = 33;
	int id = 10001;
	for (int i=0;i <4; i++){
		int left = 0;
		int right = 30;
		for (int j = 0; j < 16; j++) {
			sprites->Add(id, left, top, right, bottom, texSIMON);
			id++;
			left += 30;
			right += 30;
		}
		top += 33;
		bottom += 33;
	}

	LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_MISC);
	sprites->Add(20001, 0, 0, 31, 31, texMisc);
	
	LPDIRECT3DTEXTURE9 textFire = textures->Get(ID_TEX_FIRE);
	sprites->Add(4001, 0, 0, 17, 31, textFire);
	sprites->Add(4002, 27, 0, 44, 31, textFire);

	LPANIMATION ani;

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
	ani->Add(10033);
	animations->Add(408, ani);

	ani = new CAnimation(100);	// idle sit down right
	ani->Add(10048);
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

	ani = new CAnimation(70);	// idle attack sit left
	ani->Add(10049);
	ani->Add(10033);
	ani->Add(10034);
	animations->Add(412, ani);

	ani = new CAnimation(70);	// idle attack sit right
	ani->Add(10050);
	ani->Add(10048);
	ani->Add(10047);
	animations->Add(413, ani);


	ani = new CAnimation(100);		// brick
	ani->Add(20001);
	animations->Add(601, ani);


	ani = new CAnimation(100);		//background
	ani->Add(30001);
	animations->Add(602, ani);

	ani = new CAnimation(100);		//fire
	ani->Add(4001);
	ani->Add(4002);
	animations->Add(603, ani);

	background = new CBackGround();
	background->AddAnimation(602);
	background->SetPosition(0, 0);
	objects.push_back(background);

	//for (int i = 0; i < 5; i++) {
	//	fire = new CFire();
	//	fire->AddAnimation(603);
	//	fire->SetPosition(i*130+88, 110);
	//	objects.push_back(fire);
	//}
	

	Simon = new CSimon();
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


	Simon->SetPosition(40.0f, 0);
	objects.push_back(Simon);

	
	for (int i = 0; i < 50; i++) //Tạo nền đứng
	{
		CBrick *brick = new CBrick();
		brick->AddAnimation(601);
		brick->SetPosition(0 + i*16.0f, 140);
		objects.push_back(brick);
	}

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
	for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt,&coObjects);
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

		for (int i = 0; i < objects.size(); i++) {
			float x = Simon->x;
			float y = 0;
			if (x <= SCREEN_WIDTH / 2) {
				x = 0;
			}
			else
			x = Simon->x - SCREEN_WIDTH / 2;
			objects[i]->Render(x,y);
		}

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

			game->ProcessKeyboard();
			
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
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);


	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH*2, SCREEN_HEIGHT*2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}