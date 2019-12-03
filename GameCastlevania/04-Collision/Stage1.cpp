#include "Stage1.h"
#include <fstream>
void CStage1::LoadStage()
{
	
	CTextures * textures = CTextures::GetInstance();
	LPANIMATION ani;
	textures->Add(ID_TEX_SIMON, L"textures\\simon2.png", D3DCOLOR_XRGB(0, 0, 0));
	textures->Add(ID_TEX_MISC_1, L"textures\\ground\\2.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_MISC_2, L"textures\\ground\\2-4.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_FIRE, L"textures\\fire.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_MORNINGSTAR, L"textures\\whip.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_HEADERBAR, L"textures\\ItemBoard.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_ITEM, L"textures\\item\\item.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_KNIFE, L"textures\\item\\item.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_LIGHT, L"textures\\other\\light_die_1.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_SIMON_EXTRA, L"textures\\Simon_extra.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_CANDLE, L"textures\\ground\\1.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_GHOST, L"textures\\enemy\\1.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_PANTHER, L"textures\\enemy\\10.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_DOOR, L"textures\\ground\\Gate1.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_BAT, L"textures\\enemy\\11.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_BIG_BRICK, L"textures\\ground\\16.png", D3DCOLOR_XRGB(255, 0, 255));
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
	ani = new CAnimation(100); //KNIFE
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
	//BRICK1-START
	LPDIRECT3DTEXTURE9 texMisc_1 = textures->Get(ID_TEX_MISC_1);
	sprites->Add(20001, 0, 0, 31, 31, texMisc_1);
	ani = new CAnimation(100);		// brick
	ani->Add(20001);
	animations->Add(601, ani);
	//BRICK2-START
	LPDIRECT3DTEXTURE9 texMisc_2 = textures->Get(ID_TEX_MISC_2);
	sprites->Add(20002, 0, 0, 16, 2, texMisc_2);
	ani = new CAnimation(100);		// brick
	ani->Add(20002);
	animations->Add(602, ani);
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
	//LIGHT_DIE-START
	LPDIRECT3DTEXTURE9 texLightDie = textures->Get(ID_TEX_LIGHT);
	sprites->Add(15001, 0, 0, 8, 19, texLightDie);
	sprites->Add(15002, 12, 0, 23, 23, texLightDie);
	ani = new CAnimation(100);
	ani->Add(15001);
	ani->Add(15002);
	animations->Add(15001, ani);

	//LIGHT_DIE-END

	//CANLDE-START
	LPDIRECT3DTEXTURE9 textCandle = textures->Get(ID_TEX_CANDLE);
	sprites->Add(9001, 0, 0, 8, 15, textCandle);
	sprites->Add(9002, 8, 0, 16, 15, textCandle);
	ani = new CAnimation(100);		//fire
	ani->Add(9001);
	ani->Add(9002);
	animations->Add(903, ani);
	//GHOST-START
	LPDIRECT3DTEXTURE9 textGhost = textures->Get(ID_TEX_GHOST);
	sprites->Add(11001, 0, 0, 17, 31, textGhost);
	sprites->Add(11002, 17, 0, 34, 31, textGhost);
	sprites->Add(11003, 33, 0, 50, 31, textGhost);
	sprites->Add(11004, 53, 0, 68, 31, textGhost);
	ani = new CAnimation(100);
	ani->Add(11001);
	ani->Add(11002);
	animations->Add(1103, ani);
	ani = new CAnimation(100);
	ani->Add(11003);
	ani->Add(11004);
	animations->Add(1104, ani);
	//CANLDE-START
	LPDIRECT3DTEXTURE9 textDoor = textures->Get(ID_TEX_DOOR);
	sprites->Add(13001, 0, 0, 10, 48, textDoor);
	sprites->Add(13002, 22, 0, 40, 48, textDoor);
	sprites->Add(13003, 48, 0, 88, 48, textDoor);
	ani = new CAnimation(1000);		//door close	
	ani->Add(13001);
	animations->Add(1301, ani);
	ani = new CAnimation(1000);		//door opening
	ani->Add(13002);
	ani->Add(13003);
	animations->Add(1302, ani);
	ani = new CAnimation(1000);		//door opened
	ani->Add(13003);
	animations->Add(1303, ani);
	//SIMON_EXTRA
	LPDIRECT3DTEXTURE9 texSIMON_EXTRA = textures->Get(ID_TEX_SIMON_EXTRA);
	sprites->Add(16001, 0, 130, 30, 160, texSIMON_EXTRA);
	sprites->Add(16002, 30, 130, 60, 160, texSIMON_EXTRA);
	sprites->Add(16003, 60, 130, 90, 160, texSIMON_EXTRA);
	sprites->Add(16004, 0, 165, 30, 195, texSIMON_EXTRA);
	sprites->Add(16005, 30, 165, 60, 195, texSIMON_EXTRA);
	sprites->Add(16006, 60, 165, 90, 195, texSIMON_EXTRA);
	ani = new CAnimation(200); //EXTRA LEFT
	ani->Add(16003);
	ani->Add(16002);
	ani->Add(16001);
	animations->Add(16001, ani);
	ani = new CAnimation(200); //EXTRA RIGHT
	ani->Add(16004);
	ani->Add(16005);
	ani->Add(16006);
	animations->Add(16002, ani);
	//SIMON_EXTRA-END



	//SIMON-START
	LPDIRECT3DTEXTURE9 texSIMON = textures->Get(ID_TEX_SIMON);
	int top_simon = 0;
	int bottom_simon = 33;
	int id_simon = 10001;
	for (int i = 0; i < 4; i++) {
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
	ani->Add(10055);
	animations->Add(406, ani);

	ani = new CAnimation(100);	// idle jump left
	ani->Add(10056);
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
	ani->Add(10027);
	ani->Add(10028);
	animations->Add(415, ani);

	ani = new CAnimation(150);	// idle on stair right
	ani->Add(10020);
	ani->Add(10021);
	animations->Add(416, ani);

	ani = new CAnimation(150);	// idle down stair left
	ani->Add(10020);
	ani->Add(10019);
	animations->Add(417, ani);

	ani = new CAnimation(150);	// idle down stair right
	ani->Add(10029);
	ani->Add(10030);
	animations->Add(418, ani);

	ani = new CAnimation(150);	// idle stay stair left down
	ani->Add(10019);
	animations->Add(419, ani);

	ani = new CAnimation(150);	// idle stay stair left up
	ani->Add(10028);
	animations->Add(420, ani);

	ani = new CAnimation(150);	// idle stay stair right down
	ani->Add(10030);
	animations->Add(421, ani);

	ani = new CAnimation(150);	// idle stay stair right up
	ani->Add(10021);
	animations->Add(422, ani);

	ani = new CAnimation(150);	// idle attack stair right up
	ani->Add(10043);
	ani->Add(10042);
	ani->Add(10041);
	animations->Add(423, ani);


	ani = new CAnimation(150);	// idle stay stair left up
	ani->Add(10038);
	ani->Add(10039);
	ani->Add(10040);
	animations->Add(424, ani);


	ani = new CAnimation(150);	// idle stay stair right down
	ani->Add(10035);
	ani->Add(10036);
	ani->Add(10037);
	animations->Add(425, ani);

	ani = new CAnimation(150);	// idle stay stair right down
	ani->Add(10046);
	ani->Add(10045);
	ani->Add(10044);
	animations->Add(426, ani);

	ani = new CAnimation(150);	// idle stay heart right 
	ani->Add(10032);
	animations->Add(427, ani);

	ani = new CAnimation(150);	// idle stay heart left 
	ani->Add(10017);
	animations->Add(428, ani);

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
	Simon->AddAnimation(419);		// idle stay stair left down
	Simon->AddAnimation(420);		// idle stay stair left up
	Simon->AddAnimation(421);		// idle stay stair right down
	Simon->AddAnimation(422);		// idle stay stair right up
	Simon->AddAnimation(16001);		// idle stay extra left
	Simon->AddAnimation(16002);		// idle stay extra right
	Simon->AddAnimation(423);		// idle attack stair right up
	Simon->AddAnimation(424);		// idle stay stair left up
	Simon->AddAnimation(425);		// idle attack stair right down
	Simon->AddAnimation(426);		// idle stay stair left down
	Simon->AddAnimation(427);		// idle stay heart right 
	Simon->AddAnimation(428);		// idle stay heart left
	Simon->SetPosition(640.0f, 0);
	//PANTHER-STAR
	LPDIRECT3DTEXTURE9 texPan = textures->Get(ID_TEX_PANTHER);
	sprites->Add(12001, 0, 0, 32, 16, texPan);//STANDING
	sprites->Add(12002, 32, 0, 64, 16, texPan);//WALKING_LEFT
	sprites->Add(12003, 64, 0, 96, 16, texPan);
	sprites->Add(12004, 96, 0, 128, 16, texPan);
	sprites->Add(12005, 128, 0, 160, 16, texPan);//WALKING_RIGHT
	sprites->Add(12006, 160, 0, 192, 16, texPan);
	sprites->Add(12007, 192, 0, 224, 16, texPan);
	ani = new CAnimation(100);		//PANTHER SLEEP
	ani->Add(12001);
	animations->Add(1201, ani);
	ani = new CAnimation(100);		//PANTHER WALKING LEFT
	ani->Add(12004);
	ani->Add(12002);
	ani->Add(12003);
	animations->Add(1202, ani);
	ani = new CAnimation(100);		//PANTHER JUMP (LEFT)
	ani->Add(12004);
	animations->Add(1203, ani);

	ani = new CAnimation(100);		//PANTHER WALKING RIGHT
	ani->Add(12005);
	ani->Add(12007);
	ani->Add(12006);
	animations->Add(1204, ani);
	ani = new CAnimation(100);		//PANTHER JUMP (RIGHT)
	ani->Add(12005);
	animations->Add(1205, ani);
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
	objects.push_back(Simon);
	//BIG_BRICK_STAR
	LPDIRECT3DTEXTURE9 texMisc_big = textures->Get(ID_TEX_BIG_BRICK);
	sprites->Add(170001, 0, 0, 62, 94, texMisc_big);
	ani = new CAnimation(100);		// brick
	ani->Add(170001);
	animations->Add(1701, ani);
	//BIG-BRICK-END
	//BAT-STAR
	LPDIRECT3DTEXTURE9 texBAT = textures->Get(ID_TEX_BAT);
	sprites->Add(18001, 48, 0, 64, 16, texBAT);
	sprites->Add(18002, 32, 0, 48, 16, texBAT);
	sprites->Add(18003, 16, 0, 32, 16, texBAT);
	sprites->Add(18004, 64, 0, 80, 16, texBAT);
	sprites->Add(18005, 80, 0, 96, 16, texBAT);
	sprites->Add(18006, 96, 0, 112, 16, texBAT);
	ani = new CAnimation(100);//FLY_LEFT
	ani->Add(18001);
	ani->Add(18002);
	ani->Add(18003);
	animations->Add(1803, ani);
	ani = new CAnimation(100);//FLY_RIGHT
	ani->Add(18004);
	ani->Add(18005);
	ani->Add(18006);
	animations->Add(1804, ani);
	
	//BAT-END
	if (stage_id == 1) {
		map = new TileMap();

		for (int i = 0; i < 48; i++)
		{
			CBrick *brick = new CBrick();
			brick->AddAnimation(601);
			brick->SetPosition(0 + i * 16.0f, 186);
			brick->tag = 1;
			brick->type = 0;
			objects.push_back(brick);
			obejects_item.push_back(brick);
		}
		//BRICK-END
		
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
		
		//SIMON-END


		//LOAD-MAP
		map->LoadMap(stagemap, 1);
	}
	if (stage_id == 2) {
		map = new TileMap();
		column = 5;
		row;
		ifstream FILE;
		string sLine;
		FILE.open("location2.txt");


		if (FILE.good())
		{
			getline(FILE, sLine);
		}
		row = stoi(sLine);
		location2 = new float *[row];
		for (int i = 0; i < row; i++) {
			location2[i] = new float[column];
		}

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				FILE >> location2[i][j];
			}
		}
		
		//ITEM-START
	
		//ITEM-END
		//MORNING-STAR-START
		
		//STAIR-1-STAR
		for (int i = 0; i < row; i++) {
			if (location2[i][0] == 100003) {
				stair = new CStair();
				stair->id = location2[i][1];
				stair->SetPosition(location2[i][2], location2[i][3]);
				stair->stair_direction = location2[i][4];
				stair->tag = 1;
				stair->type_stair = 1;
				objects.push_back(stair);
				objects_stair_1.push_back(stair);
			}
		}

		//STAIR-1-END
		//STAIR-2-STAR
		for (int i = 0; i < row; i++) {
			if (location2[i][0] == 100004) {
				stair = new CStair();
				stair->id = location2[i][1];
				stair->SetPosition(location2[i][2], location2[i][3]);
				stair->stair_direction = location2[i][4];
				stair->tag = 1;
				stair->type_stair = 2;
				objects.push_back(stair);
				objects_stair_2.push_back(stair);
			}
		}

		//STAIR-2-END
		//STAIR-3-STAR
		for (int i = 0; i < row; i++) {
			if (location2[i][0] == 100005) {
				stair = new CStair();
				stair->id = location2[i][1];
				stair->SetPosition(location2[i][2], location2[i][3]);
				stair->stair_direction = location2[i][4];
				stair->tag = 1;
				stair->type_stair = 3;
				objects.push_back(stair);
				objects_stair_2.push_back(stair);
			}
		}

		//STAIR-3-END
		//BRICK-START
		
		for (int i = 0; i < 100; i++)
		{
			CBrick *brick = new CBrick();
			brick->AddAnimation(602);
			brick->SetPosition(i * 15.5f, 203);
			brick->tag = 1;
			brick->type = 0;
			objects.push_back(brick);
			obejects_item.push_back(brick);
			objects_panther.push_back(brick);
		}

		for (int i = 0; i < 3; i++)
		{
			CBrick *brick = new CBrick();
			brick->AddAnimation(602);
			brick->SetPosition(i * 15.5f + 667, 141);
			brick->tag = 1;
			brick->type = 0;
			objects.push_back(brick);
			obejects_item.push_back(brick);
			objects_panther.push_back(brick);
		}
		for (int i = 0; i < 10; i++)
		{
			CBrick *brick = new CBrick();
			brick->AddAnimation(602);
			brick->SetPosition(i * 15.5f + 730, 110);
			brick->tag = 1;
			brick->type = 0;
			objects.push_back(brick);
			obejects_item.push_back(brick);
			objects_panther.push_back(brick);
		}

		for (int i = 0; i < 6; i++)
		{
			CBrick *brick = new CBrick();
			brick->AddAnimation(602);
			brick->SetPosition(i * 15.5f + 900, 141);
			brick->tag = 1;
			brick->type = 0;
			objects.push_back(brick);
			obejects_item.push_back(brick);
			objects_panther.push_back(brick);
		}

		for (int i = 0; i < 9; i++)
		{
			CBrick *brick = new CBrick();
			brick->AddAnimation(602);
			brick->SetPosition(i * 15.5f + 1350, 110);
			brick->tag = 1;
			brick->type = 0;
			objects.push_back(brick);
			obejects_item.push_back(brick);
			objects_panther.push_back(brick);
		}
		//BRICK-END
		//KNIFE-STAR
		

		//KNIFE-END
		//FIRE-START
		
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
		
		for (int i = 0; i < row; i++) {
			if (location2[i][0] == 100001) {
				candle = new CCandle();
				candle->AddAnimation(903);
				candle->SetPosition(location2[i][1], location2[i][2]);
				
				candle->tag = location2[i][3];
				objects.push_back(candle);
				objects_morningstar.push_back(candle);
				objects_weapons.push_back(candle);
			}
		}
		//CANLDE-END

		//GHOST-START
		
		for (int i = 0; i < row; i++) {
			if (location2[i][0] == 100002) {
				ghost = new CGhost();
				ghost->AddAnimation(1103);
				ghost->AddAnimation(1104);
				ghost->SetPosition(location2[i][1], location2[i][2]);
				ghost->tag = location2[i][3];
				ghost->SetState(GHOST_STATE_WALKING);
				objects.push_back(ghost);
				objects_morningstar.push_back(ghost);
				objects_weapons.push_back(ghost);
			}
		}
		//GHOST-END
		//DOOR-START

		for (int i = 0; i < row; i++) {
			if (location2[i][0] == 100007) {
				door = new CDoor();
				door->AddAnimation(1301);
				door->AddAnimation(1301);
				door->AddAnimation(1302);
				door->SetPosition(location2[i][2], location2[i][3]);
				door->tag = location2[i][4];
				door->opened = 0;
				door->state= DOOR_STATE_CLOSE;
				objects.push_back(door);
				/*objects_morningstar.push_back(ghost);
				objects_weapons.push_back(ghost);*/
			}
		}
		//DOOR-END

		//SIMON-START
		for (int i = 0; i < row; i++) {
			if (location2[i][0] == 100006) {
				panther = new CPanther(Simon);
				panther->AddAnimation(1202);
				panther->AddAnimation(1204);
				panther->AddAnimation(1203);
				panther->AddAnimation(1205);
				panther->AddAnimation(1201);
				/*panther->SetPosition(670, 124);*/
				panther->SetPosition(location2[i][2], location2[i][3]);
				//panther->SetPosition(50, 50);
				panther->SetState(PANTHER_STATE_SLEEP);
				//objects.push_back(panther);
				objects.push_back(panther);
				objects_morningstar.push_back(panther);
				//objects_weapons.push_back(panther); -- Hiện đang lỗi tự động chạy ở chỗ này
				objects_panther.push_back(panther);
			}
		}
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
		map->LoadMap(stagemap, 2);
	}
	if (stage_id == 3) {
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
		LPDIRECT3DTEXTURE9 texMisc_big = textures->Get(ID_TEX_BIG_BRICK);
		sprites->Add(130001, 0, 0, 62, 94, texMisc_big);
		ani = new CAnimation(100);		// brick
		ani->Add(130001);
		animations->Add(1301, ani);
		for (int i = 0; i < row; i++)
		{
			if (location3[i][0] == 100007) {
				CBrick *big_brick = new CBrick();
				big_brick->AddAnimation(1301);
				big_brick->SetPosition(location3[i][2], location3[i][3]);
				big_brick->tag = 1;
				big_brick->type = 1;
				objects.push_back(big_brick);
				obejects_item.push_back(big_brick);
			}
		}
		//BIG_BRICK_END
		//BRICK-START
	
		
		for (int i = 0; i < 3; i++)
		{
			CBrick *brick = new CBrick();
			brick->AddAnimation(602);
			brick->SetPosition(i * 15.5f, 203);
			brick->tag = 1;
			brick->type = 0;
			objects.push_back(brick);
			obejects_item.push_back(brick);
		}
		for (int i = 0; i < 97; i++)
		{
			CBrick *brick = new CBrick();
			brick->AddAnimation(602);
			brick->SetPosition(i * 15.5f + 63, 203);
			brick->tag = 1;
			brick->type = 0;
			objects.push_back(brick);
			obejects_item.push_back(brick);
		}

		for (int i = 0; i < 8; i++)
		{
			CBrick *brick = new CBrick();
			brick->AddAnimation(602);
			brick->SetPosition(i * 15.5f, 110);
			brick->tag = 1;
			brick->type = 0;
			objects.push_back(brick);
			obejects_item.push_back(brick);
		}
		for (int i = 0; i < 3; i++)
		{
			CBrick *brick = new CBrick();
			brick->AddAnimation(602);
			brick->SetPosition(i * 15.5f + 124, 141);
			brick->tag = 1;
			brick->type = 0;
			objects.push_back(brick);
			obejects_item.push_back(brick);
		}
		for (int i = 0; i < 2; i++)
		{
			CBrick *brick = new CBrick();
			brick->AddAnimation(602);
			brick->SetPosition(i * 15.5f + 310, 125);
			brick->tag = 1;
			brick->type = 0;
			objects.push_back(brick);
			obejects_item.push_back(brick);
		}
		for (int i = 0; i < 3; i++)
		{
			CBrick *brick = new CBrick();
			brick->AddAnimation(602);
			brick->SetPosition(i * 15.5f + 341, 141);
			brick->tag = 1;
			brick->type = 0;
			objects.push_back(brick);
			obejects_item.push_back(brick);
		}

		for (int i = 0; i < 6; i++)
		{
			CBrick *brick = new CBrick();
			brick->AddAnimation(602);
			brick->SetPosition(i * 15.5f + 403, 110);
			brick->tag = 1;
			brick->type = 0;
			objects.push_back(brick);
			obejects_item.push_back(brick);
		}
		//BRICK-END
		//FIRE-START
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

		//CANLDE-START
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
		//BAT-START
		for (int i = 0; i < row; i++) {
			if (location3[i][0] == 100006) {
				bat = new CBat(Simon);
				bat->AddAnimation(1803);
				bat->AddAnimation(1804);
				bat->SetPosition(location3[i][2], location3[i][3]);
				bat->bat_x = location3[i][4];
				bat->SetState(BAT_STATE_FLY_LEFT);
				objects.push_back(bat);
				objects_bat.push_back(bat);
				//objects_weapons.push_back(ghost);
			}
		}

		//BAT-END
		map->LoadMap(stagemap, 3);
	}

}

void CStage1::Update(DWORD dt)
{
	// We know that SIMON is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	count1 = dt;
	vector<LPGAMEOBJECT> coObjects;
	vector<LPGAMEOBJECT> coObjects_morningstar;
	vector<LPGAMEOBJECT> coObjects_item;
	vector<LPGAMEOBJECT> coObjects_weapons;
	vector<LPGAMEOBJECT> coObjects_panther;
	if (Simon->next_stage == 2) {
		
		for (int i = 0; i < objects.size(); i++) {
			if (objects[i]->tag == 10 && objects[i]->x != 1000) {
				objects[i]->x = 1000;
				CDoor		*door_open;
				door_open = new CDoor();
				door_open->AddAnimation(1301);
				door_open->AddAnimation(1301);
				door_open->AddAnimation(1302);
				door_open->AddAnimation(1303);
				door_open->SetPosition(1480, 62);
				door_open->open_start = GetTickCount();
				door_open->opened = 0;
				door_open->state = DOOR_STATE_OPEN;
				Simon->next_stage == 3;
				objects.push_back(door_open);
				
				//[i]->x = 10000;
			}
		}
	}
	for (int i = 0; i < objects.size(); i++)
	{
		
		if (objects[i]->tag == 1 || objects[i]->tag == 5 || objects[i]->tag==10)
			coObjects.push_back(objects[i]);
	}
	for (int i = 0; i < objects_panther.size(); i++)
	{
		coObjects_panther.push_back(objects_panther[i]);
	}
	for (int i = 0; i < obejects_item.size(); i++)
	{
		if (obejects_item[i]->tag == 1 || obejects_item[i]->tag == 5)
			coObjects_item.push_back(obejects_item[i]);
	}
	for (int i = 0; i < objects_morningstar.size(); i++)
	{
		coObjects_morningstar.push_back(objects_morningstar[i]);
	}
	for (int i = 0; i < objects_weapons.size(); i++)
	{
		coObjects_weapons.push_back(objects_weapons[i]);
	}
	if (Simon->combine_array == 1) {
		
			objects_weapons.push_back(Simon->objects_weapons[Simon->objects_weapons.size()-1]);
		
		Simon->combine_array = 0;
	}
	morningstar->Update(dt,&coObjects_morningstar);
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
	for (int i = 0; i < objects_weapons.size(); i++)
	{
		objects_weapons[i]->Update(dt, &coObjects_weapons);
		if (objects_weapons[i]->y == -9850 && objects_weapons[i]->tag == 0) {
			light = new CLight();
			light->AddAnimation(15001);
			light->Light_setting(light, objects_weapons[i]->x, objects_weapons[i]->y);
			light->tag = 10;
			objects.push_back(light);
			
				CItem		*item;
				item = new CItem();
				int rand_no;
				rand_no = rand() % 4 + 900;
				item->Item_setting(item, objects_weapons[i]->x, objects_weapons[i]->y, 900);
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
	for (int i = 0; i < objects_panther.size(); i++)
	{
		objects_panther[i]->Update(dt, &coObjects_panther);
	}
	headerbar->UpdateTime();
}

void CStage1::Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();
	if (d3ddv->BeginScene()) {
		if (stage_id == 1) {

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
			int a = 1;
			map->DrawMap(stagemap, x, y);
			for (int i = 0; i < objects.size(); i++) {

				if (objects[i]->tag != 3)
					objects[i]->Render(x, y, Simon->x, Simon->y);
			}
			for (int i = 0; i < objects_weapons.size(); i++) {
				objects_weapons[i]->Render(x, y, Simon->x, Simon->y);
			}

			float i = objects_weapons.size();
			int v = Simon->nx;
			//float i = count1;
			headerbar->score_ = Simon->isLastFrame;
			headerbar->DrawHeaderbar();

		}
		if (stage_id == 2) {
			d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

			spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
			float x = Simon->x;
			float y = 0;

			if (x <= SCREEN_WIDTH / 2) {
				x = 0;
			}
			else
				x = Simon->x - SCREEN_WIDTH / 2;
			map->DrawMap(stagemap, x, y); //vẽ background
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
			for (int i = 0; i < objects_panther.size(); i++) {
				objects_panther[i]->Render(x, y, Simon->x, Simon->y);
			}
			headerbar->score_ = Simon->state_direction_on_stair;

			headerbar->stage_ = Simon->state_direction_on_stair;
			headerbar->score_ = Simon->vx;
			headerbar->DrawHeaderbar();
			//float i = count1;




		}
		if (stage_id == 3) {
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

				headerbar->DrawHeaderbar();

			}


		}
		spriteHandler->End();
		d3ddv->EndScene();
		// Display back buffer content to the screen
		d3ddv->Present(NULL, NULL, NULL, NULL);

	}
}
	
	



