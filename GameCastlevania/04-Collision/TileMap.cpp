#include "Textures.h"
#include "TileMap.h"
#include "Game.h"
#include <fstream>
TileMap::TileMap()
{
	tileWidth = 16;
	tileHeight = 16;
}

TileMap::TileMap(int col, int row, int tilewidth, int tileheight)
{
	columns = col;
	rows = row;
	tileWidth = tilewidth;
	tileHeight = tileheight;

	matrix = new int *[rows];
	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new int[columns];
	}
}

TileMap::~TileMap()
{
	if (matrix)
	{
		for (int i = 0; i < rows; i++)
		{
			delete matrix[i];
		}
		delete matrix;
		matrix = nullptr;
	}
}

void TileMap::InitTileSet(CSprite * tileset)
{
	tileSet = tileset;
}

void TileMap::LoadMatrixMap(LPCSTR fileSource)
{
	fstream pFile;
	pFile.open(fileSource, fstream::in);

	string lineString;
	int * posSpace = NULL;
	string subString;
	int countLine = 0;
	int i = 0;

	while (pFile.good())
	{
		getline(pFile, lineString);
		if (countLine == 0)
		{
			columns = atoi(lineString.c_str());
		}
		else if (countLine == 1)
		{
			rows = atoi(lineString.c_str());

			matrix = new int *[rows];
			for (int row = 0; row < rows; row++)
			{
				matrix[row] = new int[columns];
			}
		}
		else
		{
			posSpace = new int[columns];
			for (int j = 0; j < columns; j++)
			{
				if (j == 0)
				{
					posSpace[0] = lineString.find(" ", 0);
					subString = lineString.substr(0, posSpace[0]);
					int id = atoi(subString.c_str());
					matrix[i][j] = id;
				}
				else
				{
					posSpace[j] = lineString.find(" ", posSpace[j - 1] + 1);
					subString = lineString.substr(posSpace[j - 1] + 1, posSpace[j] - (posSpace[j - 1] + 1));
					int id = atoi(subString.c_str());
					matrix[i][j] = id;
				}
			}
			i++;
		}
		countLine++;
	}
}
void TileMap::Draw(float &xcam, float &ycam)
{
	RECT tileRect;
	D3DXVECTOR3 tilePos;

	int colStart = xcam / tileWidth;
	int colEnd = (xcam) / tileWidth < columns - 1 ? (xcam + SCREEN_WIDTH) / tileWidth : columns - 1;
	int rowStart = ycam / tileHeight;
	int rowEnd = (ycam) / tileHeight < rows - 1 ? (ycam + SCREEN_HEIGHT) / tileHeight : rows - 1;

	for (int i = rowStart; i <= rowEnd; i++)
	{
		for (int j = colStart; j <= colEnd; j++)
		{
			tileRect.left = (matrix[i][j] % 16) * 16;
			tileRect.top = (matrix[i][j] / 16) * 16;
			tileRect.right = tileRect.left + 16;
			tileRect.bottom = tileRect.top + 16;

			tilePos = D3DXVECTOR3(j * 16, i * 16 + 40, 0);
			tileSet->Draw(tilePos.x, tilePos.y);

		}
	}
}