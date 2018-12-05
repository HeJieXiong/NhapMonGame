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
#include "Stage1.h"
#include "Stage2.h"
#include "Simon.h"
#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"



CGame		*game;

CSimon		*Simon;

CStage1		*stage1;
CStage2		*stage2;
CMorningstar*morningstar;


CHeaderBar	*headerbar;

CKnife		*knife;
vector<LPGAMEOBJECT> objects_weapons;
int i ;
int current_stage;
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
		if (Simon->has_wp == 1) {
			Simon->attack_wp = 1;
			Simon->Attack_Weapons();
			break;
		}
		
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


void  LoadStage1() {
	
	stage1->LoadStage1();
}

void  Updatestage1(DWORD dt) {
	i = objects_weapons.size();
	stage1->Update(dt);
}

void  Renderstage1() {
	stage1->Render();
}

void  LoadStage2() {

	stage2->LoadStage2();
}

void  Updatestage2(DWORD dt) {
	i = objects_weapons.size();
	stage2->Update(dt);
}

void  Renderstage2() {
	stage2->Render();
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

int RunStage2()
{
	MSG msg;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;
	int done = 0;
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

			Updatestage2(dt);
			Renderstage2();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}
int RunStage1()
{
	MSG msg;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;
	int done=0;
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
			if ((Simon->x < 650) && (game->unablekeyboard == 0)) {

				game->ProcessKeyboard();
			}
			else {
				if (Simon->GetState() != SIMON_STATE_IDLE && Simon->is_walking != 1) {
					Simon->SetState(SIMON_STATE_WALKING_LEFT);
					Simon->vx = -0.02;
				}
				if (Simon->x <= 610) {
					Simon->vx = 0;
					Simon->nx = 1;
					Simon->SetState(SIMON_STATE_IDLE);
				}
				if (Simon->x <= 610 && Simon->GetState() != SIMON_STATE_WALKING_LEFT) {
					Simon->SetState(SIMON_STATE_WALKING_RIGHT);
					Simon->vx = 0.02;
					Simon->is_walking = 1;
				}
				if (Simon->x >= 650 && Simon->GetState() == SIMON_STATE_WALKING_RIGHT) {
					Simon->SetState(SIMON_STATE_DISAPPEAR);
					Simon->vx = 0;
					stage2->SetGame(game);
					LoadStage2();
					RunStage2();

				}


				game->unablekeyboard = 1;
			}

				Updatestage1(dt);
				Renderstage1();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

int currentstage(CStage1 *a) {
	current_stage = a->stage_id;
	return current_stage;
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
	morningstar = new CMorningstar();
	knife = new CKnife();
	Simon = new CSimon(morningstar, headerbar, knife);
	stage1 = new CStage1(Simon,morningstar, knife,i);
	stage2 = new CStage2(Simon, morningstar, knife, i);
	stage1->SetGame(game);
	LoadStage1();
	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	RunStage1();
	currentstage(stage1);
	

		
	
	
	

	return 0;
}