#pragma once
#include <d3dx9.h>
#include "Game.h"
#include "Grid.h"
#include "GameObject.h"
#include "TileMap.h"
#include "Candle.h"
#include "Morningstar.h"
#include "Knife.h"
#include "Simon.h"
#include "Item.h"
#include "Door.h"
#include "Stair.h"
#include "Ghost.h"
#include "Panther.h"
#include "Bat.h"
#include "Fish.h"
using namespace std;

class Scenes
{
	int IDScene;
	CGame * game;
	vector<LPGAMEOBJECT> listObjects;
	vector<LPGAMEOBJECT> listItems;
	vector<LPGAMEOBJECT> listDoors;
	vector<LPGAMEOBJECT> listStairs;
	vector<LPGAMEOBJECT> listZombie;
	CSimon *simon;
	CMorningstar * morningstar;
	CKnife *knife;
	vector<CKnife*> knifelist;
public:
	CTextures * textures = CTextures::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	void LoadSprites(int id, LPCWSTR tex, LPCWSTR sprite_data, LPCWSTR animation_data, int time_ani));
	void LoadSpritesFromFile(LPCWSTR FilePath);
	void LoadResources();
	Scenes(CGame * game);
	~Scenes();
	void Init(int idScene);						
	void LoadObjectsFromFileToGrid(LPCWSTR FilePath);	
	// Update
	void ChangeScene();							
	void Update(DWORD dt);
	void Simon_Update(DWORD dt);
	void Whip_Update(DWORD dt);
	void Weapon_Update(DWORD dt, int index);
	void UpdateGrid();
	// Render
	void Render();
	// Set
	void SetInactivationByPosition();			
	void SetDropItems();	
	void SetGameState(int state);	
	void SetEnemiesSpawnPositon();	

	// Get
	CSimon * GetSimon() { return this->simon; }
	vector<CKnife*> * GetWeaponList() { return &knifelist; }
	void GetObjectFromGrid();
	void GetColliableObjects(LPGAMEOBJECT curObj, vector<LPGAMEOBJECT>&coObjects);
	vector<LPGAMEOBJECT> * GetListStairs() { return &(listStairs); }
	int GetRandomItem();
};

