#include "spawnpoint.h"
#include"MapChip.h"
#include"player.h"


SpawnPoint g_SpawnPoint[SPAWN_POINT_MAX];


void InitSpawnPoint()
{
	for (int i = 0; i < SPAWN_POINT_MAX; i++)
	{
		g_SpawnPoint[i].Position = D3DXVECTOR2(0.0f, 0.0f);
		g_SpawnPoint[i].Size = D3DXVECTOR2(0.0f, 0.0f);
		g_SpawnPoint[i].PieceIndex = -1;
		g_SpawnPoint[i].UseFlag = false;
	}


}

void UninitSpawnPoint()
{
}

void UpdateSpawnPoint()
{


}

void SetSpawnPoint(D3DXVECTOR2 p, D3DXVECTOR2 s, int index)
{

	for (int i = 0; i < SPAWN_POINT_MAX; i++)
	{
		if (!g_SpawnPoint[i].UseFlag)
		{

			g_SpawnPoint[i].Position = p;
			g_SpawnPoint[i].Size = s;
			g_SpawnPoint[i].PieceIndex = index;
			g_SpawnPoint[i].UseFlag = true;

			break;

		}

	}


}

void DeleteSpawnPoint(int index)
{
	for (int i = 0; i < SPAWN_POINT_MAX; i++)
	{
		if (g_SpawnPoint[i].UseFlag)
		{
			if (g_SpawnPoint[i].PieceIndex == index)
			{
				g_SpawnPoint[i].UseFlag = false;
			}

		}
	}


}

SpawnPoint* GetSpawnPoint()
{
	return g_SpawnPoint;
}
