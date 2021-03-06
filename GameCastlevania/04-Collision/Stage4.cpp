#include "Stage4.h"
#include <fstream>
void CStage4::LoadStage4()
{
	map = new TileMap();
	column = 5;
	row;
	ifstream FILE;
	string sLine;
	FILE.open("location3.txt");


	if (FILE.good())
	{
		getline(FILE, sLine);
	}
	row = stoi(sLine);
	location3 = new float *[row];
	for (int i = 0; i < row; i++) {
		location3[i] = new float[column];
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			FILE >> location3[i][j];
		}
	}
	CTextures * textures = CTextures::GetInstance();
	LPANIMATION ani;
	textures->Add(ID_TEX_SIMON, L"textures\\simon2.png", D3DCOLOR_XRGB(0, 0, 0));
	textures->Add(ID_TEX_MISC, L"textures\\ground\\2-4.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_FIRE, L"textures\\fire.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_MORNINGSTAR, L"textures\\whip.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_HEADERBAR, L"textures\\ItemBoard.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_ITEM, L"textures\\item\\item.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_KNIFE, L"textures\\item\\item.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_CANDLE, L"textures\\ground\\1.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_GHOST, L"textures\\enemy\\1.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_BAT, L"textures\\enemy\\11.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_BIG_BRICK, L"textures\\ground\\16.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_FISH, L"textures\\enemy\\12.png", D3DCOLOR_XRGB(255, 0, 255));
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
	//morningstar = new CMorningstar();
	morningstar->AddAnimation(701);
	morningstar->AddAnimation(702);
	morningstar->AddAnimation(703);
	morningstar->AddAnimation(704);
	//objects.push_back(morningstar);
	//MORNING-STAR-END
	//STAIR-1-STAR
	for (int i = 0; i < row; i++) {
		if (location3[i][0] == 100003) {
			stair = new CStair();
			stair->id = location3[i][1];
			stair->SetPosition(location3[i][2], location3[i][3]);
			stair->stair_direction = location3[i][4];
			stair->tag = 1;
			stair->type_stair = 1;
			objects.push_back(stair);
			objects_stair_1.push_back(stair);
		}
	}

	//STAIR-1-END
	//STAIR-2-STAR
	for (int i = 0; i < row; i++) {
		if (location3[i][0] == 100004) {
			stair = new CStair();
			stair->id = location3[i][1];
			stair->SetPosition(location3[i][2], location3[i][3]);
			stair->stair_direction = location3[i][4];
			stair->tag = 1;
			stair->type_stair = 2;
			objects.push_back(stair);
			objects_stair_2.push_back(stair);
		}
	}

	//STAIR-2-END
	//STAIR-3-STAR
	for (int i = 0; i < row; i++) {
		if (location3[i][0] == 100005) {
			stair = new CStair();
			stair->id = location3[i][1];
			stair->SetPosition(location3[i][2], location3[i][3]);
			stair->stair_direction = location3[i][4];
			stair->tag = 1;
			stair->type_stair = 3;
			objects.push_back(stair);
			objects_stair_2.push_back(stair);
		}
	}

	//STAIR-3-END
	//BIG_BRICK_STAR
	//LPDIRECT3DTEXTURE9 texMisc_big = textures->Get(ID_TEX_BIG_BRICK);
	//sprites->Add(130001, 0, 0, 62, 94, texMisc_big);
	//ani = new CAnimation(100);		// brick
	//ani->Add(130001);
	//animations->Add(1301, ani);
	//for (int i = 0; i < row; i++)
	//{
	//	if (location3[i][0] == 100007) {
	//		CBrick *big_brick = new CBrick();
	//		big_brick->AddAnimation(1301);
	//		big_brick->SetPosition(location3[i][2], location3[i][3]);
	//		big_brick->tag = 1;
	//		big_brick->type = 1;
	//		objects.push_back(big_brick);
	//		obejects_item.push_back(big_brick);
	//	}
	//}
	//BIG_BRICK_END
	//BRICK-START
	LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_MISC);
	sprites->Add(20001, 0, 0, 16, 14, texMisc);
	ani = new CAnimation(100);		// brick
	ani->Add(20001);
	animations->Add(601, ani);



	for (int i = 0; i < 14; i++)
	{
		CBrick *brick = new CBrick();
		brick->AddAnimation(601);
		brick->SetPosition(i * 15.5f, 125);
		brick->tag = 1;
		brick->type = 0;
		objects.push_back(brick);
		obejects_item.push_back(brick);
		objects_fish.push_back(brick);
	}
	for (int i = 0; i < 2; i++)
	{
		CBrick *brick = new CBrick();
		brick->AddAnimation(601);
		brick->SetPosition(i * 15.5f +93, 94);
		brick->tag = 1;
		brick->type = 0;
		objects.push_back(brick);
		obejects_item.push_back(brick);
	}
	for (int i = 0; i < 2; i++)
	{
		CBrick *brick = new CBrick();
		brick->AddAnimation(601);
		brick->SetPosition(i * 15.5f + 249, 125);
		brick->tag = 1;
		brick->type = 0;
		objects.push_back(brick);
		obejects_item.push_back(brick);
		objects_fish.push_back(brick);
	}
	for (int i = 0; i < 9; i++)
	{
		CBrick *brick = new CBrick();
		brick->AddAnimation(601);
		brick->SetPosition(i * 15.5f + 310, 125);
		brick->tag = 1;
		brick->type = 0;
		objects.push_back(brick);
		obejects_item.push_back(brick);
		objects_fish.push_back(brick);
	}

	for (int i = 0; i < 2; i++)
	{
		CBrick *brick = new CBrick();
		brick->AddAnimation(601);
		brick->SetPosition(i * 15.5f + 466, 156);
		brick->tag = 1;
		brick->type = 0;
		objects.push_back(brick);
		obejects_item.push_back(brick);
		objects_fish.push_back(brick);
	}

	for (int i = 0; i < 2; i++)
	{
		CBrick *brick = new CBrick();
		brick->AddAnimation(601);
		brick->SetPosition(i * 15.5f + 435, 187);
		brick->tag = 1;
		brick->type = 0;
		objects.push_back(brick);
		obejects_item.push_back(brick);
		//objects_fish.push_back(brick);
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
		/*objects.push_back(fire);
		objects_morningstar.push_back(fire);
		objects_weapons.push_back(fire);*/
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


	//CANLDE-START
	LPDIRECT3DTEXTURE9 textCandle = textures->Get(ID_TEX_CANDLE);
	sprites->Add(9001, 0, 0, 8, 15, textCandle);
	sprites->Add(9002, 8, 0, 16, 15, textCandle);
	ani = new CAnimation(100);		//fire
	ani->Add(9001);
	ani->Add(9002);
	animations->Add(903, ani);
	for (int i = 0; i < row; i++) {
		if (location3[i][0] == 100001) {
			candle = new CCandle();
			candle->AddAnimation(903);
			candle->SetPosition(location3[i][1], location3[i][2]);
			candle->tag = location3[i][3];
			/*objects.push_back(candle);
			objects_morningstar.push_back(candle);
			objects_weapons.push_back(candle);*/
		}
	}
	//CANLDE-END

	//GHOST-START
	LPDIRECT3DTEXTURE9 textGhost = textures->Get(ID_TEX_GHOST);
	sprites->Add(11001, 0, 0, 17, 31, textGhost);
	sprites->Add(11002, 17, 0, 34, 31, textGhost);
	ani = new CAnimation(100);
	ani->Add(11001);
	ani->Add(11002);
	animations->Add(1103, ani);
	//for (int i = 0; i < row; i++) {
	//	if (location3[i][0] == 100002) {
	//		ghost = new CGhost();
	//		ghost->AddAnimation(1103);
	//		ghost->SetPosition(location3[i][1], location3[i][2]);
	//		ghost->tag = location3[i][3];
	//		ghost->SetState(GHOST_STATE_WALKING);
	//		//objects.push_back(ghost);
	//		//objects_morningstar.push_back(ghost);
	//		//objects_weapons.push_back(ghost);
	//	}
	//}
	//GHOST-END



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

	ani = new CAnimation(150);	// idle on stair left
	ani->Add(10020);
	ani->Add(10021);
	animations->Add(415, ani);

	ani = new CAnimation(150);	// idle on stair right
	ani->Add(10027);
	ani->Add(10028);
	animations->Add(416, ani);

	ani = new CAnimation(150);	// idle down stair left
	ani->Add(10020);
	ani->Add(10019);
	animations->Add(417, ani);

	ani = new CAnimation(150);	// idle down stair right
	ani->Add(10029);
	ani->Add(10030);
	animations->Add(418, ani);

	//Simon = new CSimon(morningstar, headerbar, knife);
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
	Simon->AddAnimation(415);		// on stair left
	Simon->AddAnimation(416);		// on stair right
	Simon->AddAnimation(417);		// down stair left
	Simon->AddAnimation(418);		// down stair right
	Simon->SetPosition(100.0f, 0);
	objects.push_back(Simon);
	//SIMON-END
	//BAT-STAR
	//LPDIRECT3DTEXTURE9 texBAT = textures->Get(ID_TEX_BAT);
	//sprites->Add(12001, 48, 0, 64, 16, texBAT);
	//sprites->Add(12002, 32, 0, 48, 16, texBAT);
	//sprites->Add(12003, 16, 0, 32, 16, texBAT);
	//sprites->Add(12004, 64, 0, 80, 16, texBAT);
	//sprites->Add(12005, 80, 0, 96, 16, texBAT);
	//sprites->Add(12006, 96, 0, 112, 16, texBAT);
	//ani = new CAnimation(100);//FLY_LEFT
	//ani->Add(12001);
	//ani->Add(12002);
	//ani->Add(12003);
	//animations->Add(1203, ani);
	//ani = new CAnimation(100);//FLY_RIGHT
	//ani->Add(12004);
	//ani->Add(12005);
	//ani->Add(12006);
	//animations->Add(1204, ani);
	//for (int i = 0; i < row; i++) {
	//	if (location3[i][0] == 100006) {
	//		bat = new CBat(Simon);
	//		bat->AddAnimation(1203);
	//		bat->AddAnimation(1204);
	//		bat->SetPosition(location3[i][2], location3[i][3]);
	//		bat->bat_x = location3[i][4];
	//		bat->SetState(BAT_STATE_FLY_LEFT);
	//		objects.push_back(bat);
	//		objects_bat.push_back(bat);
	//		//objects_weapons.push_back(ghost);
	//	}
	//}

	//BAT-END
	//FISH-STAR
	LPDIRECT3DTEXTURE9 texFISH = textures->Get(ID_TEX_FISH);
	sprites->Add(15001, 0, 0, 16, 32, texFISH);
	sprites->Add(15002, 16, 0, 32, 32, texFISH);
	sprites->Add(15003, 32, 0, 48, 32, texFISH);
	sprites->Add(15004, 48, 0, 64, 32, texFISH);
	sprites->Add(15005, 64, 0, 80, 32, texFISH);
	sprites->Add(15006, 80, 0, 96,32, texFISH);
	ani = new CAnimation(100);//WALKING_LEFT
	ani->Add(15003);
	ani->Add(15002);
	animations->Add(1503, ani);
	ani = new CAnimation(100);//WALKING_RIGHT
	ani->Add(15004);
	ani->Add(15005);
	animations->Add(1504, ani);
	ani = new CAnimation(100);//JUMP_LEFT
	ani->Add(15003);
	animations->Add(1505, ani);
	ani = new CAnimation(100);//JUMP_RIGHT
	ani->Add(15004);
	animations->Add(1506, ani);
	ani = new CAnimation(100);//ATTACK_LEFT
	ani->Add(15001);
	animations->Add(1507, ani);
	ani = new CAnimation(100);//ATTACK_RIGHT
	ani->Add(15006);
	animations->Add(1508, ani);
	//for (int i = 0; i < row; i++) {
	//	if (location3[i][0] == 100008) {
	//		fish = new CFish(Simon);
	//		fish->AddAnimation(1503);
	//		fish->AddAnimation(1504);
	//		fish->AddAnimation(1505);
	//		fish->AddAnimation(1506);
	//		fish->AddAnimation(1507);
	//		fish->AddAnimation(1508);
	//		//fish->SetPosition(location3[i][2], location3[i][3]);
	//		//fish->bat_x = location3[i][4];
	//		fish->SetPosition(50, 50);
	//		fish->SetState(FISH_STATE_WALKING_LEFT);
	//		objects.push_back(bat);
	//		objects_bat.push_back(bat);
	//		//objects_weapons.push_back(ghost);
	//	}
	//}
	for (int i = 0; i < 2; i++) {
		fish = new CFish(Simon);
		fish->AddAnimation(1503);
		fish->AddAnimation(1504);
		fish->AddAnimation(1505);
		fish->AddAnimation(1506);
		fish->AddAnimation(1507);
		fish->AddAnimation(1508);
		fish->AddAnimation(1507);
		//fish->SetPosition(location3[i][2], location3[i][3]);
		//fish->bat_x = location3[i][4];
		fish->SetPosition(180+i*50, 250);
		fish->SetState(FISH_STATE_HIDE);
		//objects.push_back(fish);
		objects_fish.push_back(fish);
		//objects_weapons.push_back(fish);
	}
	//FISH-END
	//GRID-STAR
	/*gridsSys = new CGrids();
	int numOfCell = MAP_LENGTH / SCREEN_WIDTH;
	float posX, posY, cellX, cellY;
	for (int i = 0; i < numOfCell; i++)
	{
	gridsSys->Add(i, i*SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	for (int k = 0; k < objects.size(); k++)
	{
	objects.at(k)->GetPosition(posX, posY);
	gridsSys->GetGrid(i)->GetPosition(cellX, cellY);
	if (posX >= cellX && posX <= cellX + SCREEN_WIDTH)
	gridsSys->GetGrid(i)->AddGrid(objects.at(k));
	}
	}*/
	//GRID-END
	map->LoadMap(stagemap, 4);
}

void CStage4::Update(DWORD dt)
{
	// We know that SIMON is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	vector<LPGAMEOBJECT> coObjects;
	vector<LPGAMEOBJECT> coObjects_morningstar;
	vector<LPGAMEOBJECT> coObjects_item;
	vector<LPGAMEOBJECT> coObjects_weapons;
	vector<LPGAMEOBJECT> coObjects_bat;
	vector<LPGAMEOBJECT> coObjects_fish;
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->tag == 1 || objects[i]->tag == 5)
			coObjects.push_back(objects[i]);
	}
	for (int i = 0; i < objects_bat.size(); i++)
	{
		coObjects_bat.push_back(objects_bat[i]);
	}
	for (int i = 0; i < objects_fish.size(); i++)
	{
		coObjects_fish.push_back(objects_fish[i]);
	}
	for (int i = 0; i < obejects_item.size(); i++)
	{
		if (obejects_item[i]->tag == 1 || obejects_item[i]->tag == 5)
			coObjects_item.push_back(obejects_item[i]);
	}
	for (int i = 0; i < objects_weapons.size(); i++)
	{
		coObjects_weapons.push_back(objects_weapons[i]);
	}
	if (Simon->combine_array == 1) {

		objects_weapons.push_back(Simon->objects_weapons[Simon->objects_weapons.size() - 1]);

		Simon->combine_array = 0;
	}
	for (int i = 0; i < objects_morningstar.size(); i++)
	{
		coObjects_morningstar.push_back(objects_morningstar[i]);
		if (objects_morningstar[i]->state == 100 && objects_morningstar[i]->tag == 0) {
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
	//morningstar->Update_colison(&coObjects_morningstar);
	for (int i = 0; i < objects_weapons.size(); i++)
	{
		objects_weapons[i]->Update(dt, &coObjects_weapons);
		if (objects_weapons[i]->y == -9850 && objects_weapons[i]->tag == 0) {
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

	for (int i = 0; i < objects_bat.size(); i++)
	{
		objects_bat[i]->Update(dt, &coObjects_bat);
	}
	for (int i = 0; i < objects_fish.size(); i++)
	{
		objects_fish[i]->Update(dt, &coObjects_fish);
	}
	/*DebugOut(L"size %d\n", objects_fish.size());*/
}

void CStage4::Render()
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
		else
			x = Simon->x - SCREEN_WIDTH / 2;
		map->DrawMap(stagemap, x, y);
		float i = Simon->state_direction_on_stair;
		int v = Simon->is_on_stair;
		int k = Simon->has_g;

		for (int i = 0; i < objects.size(); i++) {

			if (objects[i]->tag != 3)
				objects[i]->Render(x, y, Simon->x, Simon->y);
		}
		for (int i = 0; i < objects_weapons.size(); i++) {
			objects_weapons[i]->Render(x, y, Simon->x, Simon->y);
		}
		for (int i = 0; i < objects_fish.size(); i++) {
			objects_fish[i]->Render(x, y, Simon->x, Simon->y);
		}
		headerbar->DrawHeaderbar();
		//float i = count1;




		spriteHandler->End();
		d3ddv->EndScene();

	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}


