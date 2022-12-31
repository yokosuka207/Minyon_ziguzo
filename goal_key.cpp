//=============================================================================
//ゴール用鍵
//
//制作者/座間研佑　
//=============================================================================

#include "goal_key.h"
#include "goal.h"
#include "polygon.h"
#include "sprite.h"
#include "texture.h"
#include "input.h"
#include "player.h"
#include "time.h"
#include "scene.h"
#include "puzzle.h"

//=============================================================================
//マクロ定義
//=============================================================================

//=============================================================================
//プロトタイプ宣言
//=============================================================================

//=============================================================================
//グローバル変数
//=============================================================================
static GKey g_GKey[GKEY_MAX];
static ID3D11ShaderResourceView* g_textureGKey;	//画像一枚で一つの変数が必要

static char* g_TextureNameGKey = (char*)"data\\texture\\key-1.png";

HRESULT InitGKey()
{
	g_GKey[0].size = D3DXVECTOR2(GKEY_W, GKEY_H);
	g_GKey[0].pos = D3DXVECTOR2(0, 0);
	g_GKey[0].texno = LoadTexture(g_TextureNameGKey);
	g_GKey[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_GKey[0].UseFlag = false;
	g_GKey[0].GetGKey = false;
	return S_OK;
}

void UninitGKey()
{

}

void UpdateGKey()
{

}

void DrawGKey()
{
	if (g_GKey[0].UseFlag)
	{
		//SetWorldViewProjection2D();

		//テクスチャの設定
		GetDeviceContext()[0].PSSetShaderResources(0, 1, GetTexture(g_GKey[0].texno));
		//スプライトを表示
		D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		SpriteDrawColorRotation(g_GKey[0].pos.x, g_GKey[0].pos.y, -0.1f, g_GKey[0].size.x, g_GKey[0].size.y,
			g_GKey[0].rot, g_GKey[0].col, 0, 1.0f, 1.0f, 1);
	}
}

void SetGKey(D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	g_GKey[0].pos = pos;
	g_GKey[0].size = size;
	g_GKey[0].UseFlag = true;
}


GKey* GetGKey()
{
	return g_GKey;
}