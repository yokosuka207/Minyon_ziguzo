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
		g_OpenKey[i].Size = D3DXVECTOR2(0.0f, 0.0f);
		g_OpenKey[i].Position = D3DXVECTOR2(0.0f, 0.0f);
		g_OpenKey[i].rot = 0.0f;
		g_OpenKey[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_OpenKey[i].index = -1;
		g_OpenKey[i].PaternNo = 0.0f;
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
			g_OpenKey[i].PaternNo = i;
			if (g_OpenKey[i].PaternNo > 2.0f) {
				g_OpenKey[i].PaternNo = 0.0f;
			}
			//SetWorldViewProjection2D();

			//テクスチャの設定
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_OpenKey[i].texno));
			//スプライトを表示
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			SpriteDrawColorRotation(g_OpenKey[i].Position.x, g_OpenKey[i].Position.y,-0.1f, g_OpenKey[i].Size.x, g_OpenKey[i].Size.y,
				g_OpenKey[i].rot, g_OpenKey[i].col, g_OpenKey[i].PaternNo, 1.0f / 1.0f, 1.0f / 2.0f, 1);

		}
	}
	
}


void SetOpenKey(D3DXVECTOR2 size, D3DXVECTOR2 pos, int direction, int index)
{
	for (int i = 0; i < OPEN_KEY_MAX; i++) {
		if (!g_OpenKey[i].UseFlag) //!はNOT
		{
			switch (direction)
			{
			case 0:
				g_OpenKey[i].Position = D3DXVECTOR2(pos.x, pos.y + i * size.y);
				g_OpenKey[i].rot = (direction + 2) * 90;
				break;
			case 1:
				g_OpenKey[i].Position = D3DXVECTOR2(pos.x + i * size.x, pos.y);
				g_OpenKey[i].rot = direction * 90;
				break;
			case 2:
				g_OpenKey[i].Position = D3DXVECTOR2(pos.x, pos.y - i * size.y);
				g_OpenKey[i].rot = (direction - 2) * 90;
				break;
			case 3:
				g_OpenKey[i].Position = D3DXVECTOR2(pos.x - i * size.x, pos.y);
				g_OpenKey[i].rot = direction * 90;
				break;
			default:
				break;
			}
			g_OpenKey[i].Size = size;
			g_OpenKey[i].index = index;
			g_OpenKey[i].UseFlag = true;

			break;
		}
	}
	
}

void DeleteOpenKey(int PieceNo) {
	for (int i = 0; i < OPEN_KEY_MAX; i++) {
		if (g_OpenKey[i].index == PieceNo) {
			if (g_OpenKey[i].UseFlag) {
				g_OpenKey[i].UseFlag = false;
			}
		}
	}
}

OPENKEY* GetOpenKey()
{
	return g_OpenKey;
}
