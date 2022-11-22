#include "SplitStage.h"


SplitStage g_spritStage;

void InitSplitStage()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			g_spritStage.Split3[i][j] = D3DXVECTOR2( 100.0f +180.0f * (i + 1), 180.0f * (j + 1));

		}

	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			g_spritStage.Split4[i][j] = D3DXVECTOR2(180.0f * (i + 1), 180.0f * (j + 1));

		}

	}


}

void UninitSplitStage()
{
}

void UpdateSplitStage()
{
}

void DrawSplitStage()
{
}

SplitStage* GetSplitStage()
{
	return &g_spritStage;
}
