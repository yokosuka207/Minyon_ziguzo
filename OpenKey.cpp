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
static OPENKEY g_OpenKey[OPEN_KEY_MAX];
static ID3D11ShaderResourceView	*g_textureOpenKey;	//画像一枚で一つの変数が必要

static char* g_TextureNameOpenKey = (char*)"data\\texture\\EF_46dCUEAA5c4Y.jpg";

//=============================================================================



HRESULT InitOpenKey()
{
	for (int i = 0; i < OPEN_KEY_MAX; i++)
	{
		g_OpenKey[i].Size = D3DXVECTOR2(OPEN_KEY_W, OPEN_KEY_H);
		g_OpenKey[i].Position = D3DXVECTOR2(300, 400);
		g_OpenKey[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_OpenKey[i].texno = LoadTexture(g_TextureNameOpenKey);
		g_OpenKey[i].UseFlag = false;
		return S_OK;
	}
	
}

void UninitOpenKey()
{
}

void UpdateOpenKey()
{
}

void DrawOpenKey()
{
	for (int i = 0; i < OPEN_KEY_MAX; i++) {
		if (g_OpenKey[i].UseFlag)
		{
			SetWorldViewProjection2D();

			//テクスチャの設定
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_OpenKey[i].texno));
			//スプライトを表示
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			SpriteDrawColorRotation(g_OpenKey[i].Position.x, g_OpenKey[i].Position.y, g_OpenKey[i].Size.x, g_OpenKey[i].Size.y,
				g_OpenKey[i].rot, g_OpenKey[i].col, 0, 1.0f, 1.0f, 1);

		}
	}
	
}


void SetOpenKey(D3DXVECTOR2 size, D3DXVECTOR2 pos)
{
	for (int i = 0; i < OPEN_KEY_MAX; i++) {
		if (!g_OpenKey[i].UseFlag) //!はNOT
		{

			g_OpenKey[i].Position = pos;
			g_OpenKey[i].Size = size;
			g_OpenKey[i].UseFlag = true;


		}
	}
	
}

void DeleteOpenKey(int PieceNo) {
	for (int i = 0; i < OPEN_KEY_MAX; i++) {
		if (g_OpenKey[i].UseFlag) {
			g_OpenKey[i].UseFlag = false;
		}
	}
}

OPENKEY* GetOpenKey()
{
	return g_OpenKey;
}
