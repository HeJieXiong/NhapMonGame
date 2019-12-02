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

#include "Stage3.h"
#include "Stage4.h"
#include "Stage5.h"
#include "Simon.h"
#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"
#define TIME_CHANGE_STATE_2 20000


CGame		*game;

CSimon		*Simon;

CStage1		*stage1;
CStage1		*stage2;
CStage1		*stage3;
CStage4		*stage4;
CStage5		*stage5;
CMorningstar*morningstar;


CHeaderBar	*headerbar;

CKnife		*knife;
vector<LPGAMEOBJECT> objects_weapons;
int i;
int current_stage;
DWORD time_start;
int is_start = 0;
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
		if (Simon->has_g != 0 && Simon->state != SIMON_STATE_SIT_DOWN && Simon->between_stair != 1 && Simon->touch_stair_jump == 0 || Simon->is_heart == 0) {
			Simon->SetState(SIMON_STATE_JUMP);
			Simon->isFalling = 1;
			break;
		}

		if (Simon->state == SIMON_STATE_SIT_DOWN || Simon->between_stair == 1) {
			Simon->vy = 0;
			break;
		}
		break;
	case DIK_A: // reset
		if (Simon->is_heart == 0){
			Simon->SetState(SIMON_STATE_IDLE);
			Simon->SetPosition(500.0f, 0.0f);
			break;
		}
		break;
	case DIK_Z:
		if (Simon->is_heart == 0) {
			Simon->attack_wp = 0;
			Simon->attack_start = GetTickCount();
			morningstar->attack_start = GetTickCount();
			Simon->Attack(morningstar, Simon->x, Simon->y);
			break;
		}
		break;
	case DIK_C:
		if (Simon->is_heart == 0) {
			if (Simon->has_wp == 1) {
				Simon->attack_wp = 1;
				Simon->Attack_Weapons();
				break;
			}
		}
	}
	/*case DIK_LEFT:
		if (Simon->on_jump == 1) {
			Simon->vx = 0;

			break;
		}

	}*/
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_UP:
		
		if (Simon->is_on_stair == 1 && Simon->has_g == 0) {
			Simon->vy = 0;
			//Simon->walking_up = 1;
			break;
		}
	case DIK_DOWN:
		if (Simon->is_on_stair == 1 && Simon->has_g == 0) {
			Simon->vy = 0;
			//Simon->walking_up = 2;
			break;
		}
		/*case DIK_Z:
			break;*/
	}

}


void CSampleKeyHander::KeyState(BYTE *states)
{
	// disable control key when SIMON die 
	if (Simon->GetState() == SIMON_STATE_DIE || Simon->GetState() == SIMON_STATE_JUMP || Simon->GetState() == SIMON_STATE_EXTRA
		|| Simon->on_jump == 1 || Simon->on_jump == 2 || Simon->touch_stair_jump == 1 || Simon->GetState() == SIMON_STATE_HEART) return;
	if (game->IsKeyDown(DIK_RIGHT)) {
		if (Simon->has_g == 1) {
			if (game->IsKeyDown(DIK_Z)) {
				Simon->vx = 0;
				Simon->attack_then_walk = 2;
			}
			else
				Simon->SetState(SIMON_STATE_WALKING_RIGHT);
		}
		if (game->IsKeyDown(DIK_X)) {
			if (Simon->between_stair != 1) {
				Simon->jump_walk = 2;
				Simon->SetState(SIMON_STATE_JUMP);
			}
			else Simon->vy = 0;

		}
	}
	else if (game->IsKeyDown(DIK_LEFT)) {

		if (Simon->has_g == 1) {
			if (game->IsKeyDown(DIK_Z) || game->IsKeyDown(DIK_C)) {
				Simon->vx = 0;
				Simon->attack_then_walk = 1;
			}
			else Simon->SetState(SIMON_STATE_WALKING_LEFT);
		}
		if (game->IsKeyDown(DIK_X)) {
			if (Simon->between_stair != 1) {
				Simon->jump_walk = 1;
				Simon->SetState(SIMON_STATE_JUMP);
			}
			else Simon->vy = 0;
		

		}


	}
	else if (game->IsKeyDown(DIK_DOWN)) {
		if ((Simon->is_on_stair == 1 && (Simon->state_direction_on_stair == 4 || Simon->state_direction_on_stair == 2))) {
			Simon->Walking_down_stair();
			Simon->SetState(SIMON_STATE_ON_STAIR);
			Simon->walking_up = 2;
			if (Simon->state_direction_on_stair == 2)
				Simon->between_stair = 1;
			if (Simon->state_direction_on_stair == 4)
				Simon->between_stair = 2;
		}
		else if ((Simon->is_on_stair == 1 && (Simon->state_direction_on_stair == 1 || Simon->state_direction_on_stair == 3)) && Simon->has_g == 0) {
			Simon->Walking_down_stair();
			Simon->SetState(SIMON_STATE_ON_STAIR);
			Simon->walking_up = 2;
			if (Simon->state_direction_on_stair == 1)
				Simon->between_stair = 1;
			if (Simon->state_direction_on_stair == 3)
				Simon->between_stair = 2;
		}
		else {
			Simon->SetState(SIMON_STATE_SIT_DOWN);
		}
	}
	else if (game->IsKeyDown(DIK_UP)) {
			
			if (Simon->is_on_stair == 1 && (Simon->state_direction_on_stair == 1 || Simon->state_direction_on_stair == 3|| Simon->state_direction_on_stair == 2)){
				Simon->walking_up = 1;
				Simon->SetState(SIMON_STATE_ON_STAIR);
				Simon->Walking_on_stair();
				if (Simon->state_direction_on_stair == 2)
					Simon->between_stair = 1;
				if (Simon->state_direction_on_stair == 4)
					Simon->between_stair = 2;


			}
			else if (Simon->is_on_stair == 1 && (Simon->state_direction_on_stair == 1 || Simon->state_direction_on_stair == 3 || Simon->state_direction_on_stair == 2))  {
				
				Simon->Walking_down_stair();
				Simon->SetState(SIMON_STATE_ON_STAIR);
				Simon->walking_up = 2;
				if (Simon->state_direction_on_stair == 1)
					Simon->between_stair = 1;
				if (Simon->state_direction_on_stair == 3)
					Simon->between_stair = 2;
			}
			else {
				Simon->SetState(SIMON_STATE_IDLE);
			}
		
	}

	else {
		if (Simon->walking_up == 1) {
			if (Simon->state_direction_on_stair == 1 || Simon->state_direction_on_stair == 2)
				Simon->between_stair = 1;
			if (Simon->state_direction_on_stair == 3 || Simon->state_direction_on_stair == 4)
				Simon->between_stair = 2;
			Simon->SetState(SIMON_STATE_IDLE);
		}
		else if (Simon->walking_up == 2) {
			if (Simon->state_direction_on_stair == 1 || Simon->state_direction_on_stair == 2)
				Simon->between_stair = 1;
			if (Simon->state_direction_on_stair == 3 || Simon->state_direction_on_stair == 4)
				Simon->between_stair = 2;
			Simon->SetState(SIMON_STATE_IDLE);
		}
		else {
			Simon->SetState(SIMON_STATE_IDLE);
		}
	}
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

	stage1->LoadStage();
}

void  Updatestage1(DWORD dt) {
	i = objects_weapons.size();
	stage1->Update(dt);
}

void  Renderstage1() {
	stage1->Render();
}

void  LoadStage2() {
	stage2->stage_id = 2;
	stage2->LoadStage();
}

void  Updatestage2(DWORD dt) {
	i = objects_weapons.size();
	stage2->Update(dt);
}

void  Renderstage2() {
	stage2->Render();
}

void  LoadStage3() {
	stage3->stage_id = 3;
	stage3->LoadStage();
}

void  Updatestage3(DWORD dt) {
	i = objects_weapons.size();
	stage3->Update(dt);
}

void  Renderstage3() {
	stage3->Render();
}

void  LoadStage4() {

	stage4->LoadStage4();
}

void  Updatestage4(DWORD dt) {
	i = objects_weapons.size();
	stage4->Update(dt);
}

void  Renderstage4() {
	stage4->Render();
}

void  LoadStage5()
{
	stage5->LoadStage5();
}

void  Updatestage5(DWORD dt) {
	i = objects_weapons.size();
	stage5->Update(dt);
}

void  Renderstage5() {
	stage5->Render();
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

int RunStage5()
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

			Updatestage5(dt);
			Renderstage5();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

int RunStage4()
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

			Updatestage4(dt);
			Renderstage4();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

int RunStage3()
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

			Updatestage3(dt);
			Renderstage3();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
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
			if ((Simon->x < 1450) && (Simon->x > 80 ) && game->unablekeyboard == 0())
			{
				frameStart = now;

				game->ProcessKeyboard();
			}
			else {
				
				is_start = 1;
				
			}
			if (is_start == 1) {
				
				Simon->next_stage = 2;
				game->unablekeyboard = 1;
				if (Simon->is_walking != 3) {
					Simon->is_walking = 2;
				}
			}
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
				if ((Simon->x <= 610 || Simon->x >= 625) && Simon->GetState() != SIMON_STATE_WALKING_LEFT) {
					Simon->SetState(SIMON_STATE_WALKING_RIGHT);
					Simon->vx = 0.02;
					Simon->is_walking = 1;
				}
				if (Simon->x >= 650 && Simon->GetState() == SIMON_STATE_WALKING_RIGHT) {
					Simon->SetState(SIMON_STATE_DISAPPEAR);
					Simon->vx = 0;
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
	stage1 = new CStage1(Simon, morningstar, knife, i);
	stage2 = new CStage1(Simon, morningstar, knife, i);
	stage3 = new CStage1(Simon, morningstar, knife, i);
	stage4 = new CStage4(Simon, morningstar, knife, i);
	stage5 = new CStage5(Simon, morningstar, knife, i);
	//stage1->SetGame(game);
	//LoadStage1();
	//SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	//RunStage1();
	//currentstage(stage1);
	//stage2->SetGame(game);
	//LoadStage2();
	//SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	//RunStage2();
	stage3->SetGame(game);
	LoadStage3();
	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	RunStage3();
	/*stage4->SetGame(game);
	LoadStage4();
	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	RunStage4();*/
	/*stage5->SetGame(game);
	LoadStage5();
	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	RunStage5();*/
	return 0;
}