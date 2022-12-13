#include "SplitStage.h"
#include "sprite.h"
#include "texture.h"


SplitStage g_splitStage;

// テクスチャの名前
static char* g_splitStageTextureName = (char*)"data\\texture\\split.png";

void InitSplitStage()
{

	int texNo = LoadTexture(g_splitStageTextureName);			// テクスチャ読み込み

	g_splitStage.pos = D3DXVECTOR2(0.0f, 0.0f);
	g_splitStage.size = D3DXVECTOR2(SPLIT_SIZE, SPLIT_SIZE);
	g_splitStage.texNo = texNo;		// テクスチャ番号

	//ステージの分割座標格納
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			g_splitStage.Split3[i][j] = D3DXVECTOR2(g_splitStage.pos.x - SPLIT_SIZE +(SPLIT_SIZE * i), g_splitStage.pos.y + SPLIT_SIZE - (SPLIT_SIZE * j));

		}

	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			g_splitStage.Split4[i][j] = D3DXVECTOR2(g_splitStage.pos.x + SPLIT_SIZE * (i - 2), g_splitStage.pos.y + SPLIT_SIZE * (j - 2));

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
		// テクスチャの設定
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_splitStage.texNo));
		// 四角形の描画
		SpriteDrawColorRotation(g_splitStage.pos.x, g_splitStage.pos.y,0.1f, (g_splitStage.size.x * 3), (g_splitStage.size.y * 3), 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 1.0f, 1.0f, 1);
}

SplitStage* GetSplitStage()
{
	return &g_splitStage;
}
