#include "spawnpoint_d.h"
#include"MapChip.h"
#include"player.h"


SpawnPointD g_SpawnPointD[SPAWN_POINT_D_MAX];


void InitSpawnPointD()
{
	for (int i = 0; i < SPAWN_POINT_D_MAX; i++)
	{
		g_SpawnPointD[i].Position = D3DXVECTOR2(0.0f, 0.0f);
		g_SpawnPointD[i].Size = D3DXVECTOR2(0.0f, 0.0f);
		g_SpawnPointD[i].PieceIndex = -1;
		g_SpawnPointD[i].UseFlag = false;
	}


}

void UninitSpawnPointD()
{
}

void UpdateSpawnPointD()
{


}

void SetSpawnPointD(D3DXVECTOR2 p, D3DXVECTOR2 s, int index)
{

	for (int i = 0; i < SPAWN_POINT_D_MAX; i++)
	{
		if (!g_SpawnPointD[i].UseFlag)
		{

			g_SpawnPointD[i].Position = p;
			g_SpawnPointD[i].Size = s;
			g_SpawnPointD[i].PieceIndex = index;
			g_SpawnPointD[i].UseFlag = true;

			break;

		}

	}


}

void DeleteSpawnPointD(int index)
{
	for (int i = 0; i < SPAWN_POINT_D_MAX; i++)
	{
		if (g_SpawnPointD[i].UseFlag)
		{
			if (g_SpawnPointD[i].PieceIndex == index)
			{
				g_SpawnPointD[i].UseFlag = false;
			}

		}
	}


}

SpawnPointD* GetSpawnPointD()
{
	return g_SpawnPointD;
}
