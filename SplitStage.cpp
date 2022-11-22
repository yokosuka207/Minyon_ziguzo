#include "SplitStage.h"


SplitStage g_spritStage;

void InitSplitStage()
{

	g_spritStage.pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	g_spritStage.size = D3DXVECTOR2(SPLIT_SIZE, SPLIT_SIZE);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			g_spritStage.Split3[i][j] = D3DXVECTOR2(g_spritStage.pos.x + SPLIT_SIZE * (i - 1), g_spritStage.pos.y+ SPLIT_SIZE * (j - 1));

		}

	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			g_spritStage.Split4[i][j] = D3DXVECTOR2(g_spritStage.pos.x + SPLIT_SIZE * (i - 2), g_spritStage.pos.y + SPLIT_SIZE * (j - 2));

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
