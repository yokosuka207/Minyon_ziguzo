//=============================================================================
//
//鍵で開く何か
//
//制作者/菊地 空　
//=============================================================================
#include "OpenKey.h"
#include "Key.h"
#include "main.h"
#include "polygon.h"
#include "sprite.h"
#include "texture.h"
#include "input.h"
#include "player.h"
#include "time.h"
#include "scene.h"
#include"puzzle.h"


//=============================================================================
//グローバル変数
//=============================================================================
static OPENKEY g_OpenKey;
static ID3D11ShaderResourceView	*g_textureOpenKey;	//画像一枚で一つの変数が必要

static char* g_TextureNameOpenKey = (char*)"data\\texture\\EF_46dCUEAA5c4Y.jpg";

//=============================================================================



HRESULT InitOpenKey()
{
	g_OpenKey.Size = D3DXVECTOR2(OPEN_KEY_W, OPEN_KEY_H);
	g_OpenKey.Position = D3DXVECTOR2(300, 400);
	g_OpenKey.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_OpenKey.texno = LoadTexture(g_TextureNameOpenKey);
	g_OpenKey.UseFlag = true;
	return S_OK;
}

void UninitOpenKey()
{
}

void UpdateOpenKey()
{
}

void DrawOpenKey()
{
	if (g_OpenKey.UseFlag)
	{
		SetWorldViewProjection2D();

		//テクスチャの設定
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_OpenKey.texno));
		//スプライトを表示
		D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		SpriteDrawColorRotation(g_OpenKey.Position.x, g_OpenKey.Position.y, g_OpenKey.Size.x, g_OpenKey.Size.y,
			g_OpenKey.rot, g_OpenKey.col, 0, 1.0f, 1.0f, 1);

	}
}

OPENKEY * OpenKey()
{
	return &g_OpenKey;
}

void SetOpenKey(D3DXVECTOR2 size, D3DXVECTOR2 pos)
{
	if (!g_OpenKey.UseFlag)
	{

		g_OpenKey.Position = pos;
		g_OpenKey.Size = size;
		g_OpenKey.UseFlag = false;


	}
}
