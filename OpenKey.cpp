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
static OPENKEY g_OpenKey[STAGE_OPEN_KEY_MAX][OPEN_KEY_MAX];
static ID3D11ShaderResourceView	*g_OpenKeytexture;	//画像一枚で一つの変数が必要

static char* g_OpenKeyTextureName = (char*)"data\\texture\\鍵付きドア.png";
static int g_OpenKeyTextureNo = 0;


HRESULT InitOpenKey()
{
	for (int j = 0; j < STAGE_OPEN_KEY_MAX; j++) {
		for (int i = 0; i < OPEN_KEY_MAX; i++) {
			g_OpenKey[j][i].Size = D3DXVECTOR2(0.0f, 0.0f);
			g_OpenKey[j][i].Position = D3DXVECTOR2(0.0f, 0.0f);
			g_OpenKey[j][i].rot = 0.0f;
			g_OpenKey[j][i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_OpenKey[j][i].index = -1;
			g_OpenKey[j][i].PaternNo = 0.0f;
			g_OpenKey[j][i].KeyOpen = false;
			g_OpenKey[j][i].UseFlag = false;
		}
	}
	g_OpenKeyTextureNo = LoadTexture(g_OpenKeyTextureName);
	return S_OK;
}

void UninitOpenKey(){
	if (g_OpenKeytexture != NULL) {
		g_OpenKeytexture->Release();
		g_OpenKeytexture = NULL;
	}
}

void UpdateOpenKey()
{
}

void DrawOpenKey()
{
	//SetWorldViewProjection2D();
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_OpenKeyTextureNo));
	for (int j = 0; j < STAGE_OPEN_KEY_MAX; j++) {
		for (int i = 0; i < OPEN_KEY_MAX; i++) {
			if (g_OpenKey[j][i].UseFlag) {
				g_OpenKey[j][i].PaternNo = i;
				SpriteDrawColorRotation(
					g_OpenKey[j][i].Position.x,
					g_OpenKey[j][i].Position.y,
					-0.1f,
					g_OpenKey[j][i].Size.x,
					-g_OpenKey[j][i].Size.y,
					g_OpenKey[j][i].rot,
					g_OpenKey[j][i].col,
					g_OpenKey[j][i].PaternNo,
					1.0f / 1.0f,
					1.0f / 3.0f,
					1
				);
			}
		}
	}
}
void SetOpenKey(D3DXVECTOR2 pos, D3DXVECTOR2 size, int direction, int index){
	for (int j = 0; j < STAGE_OPEN_KEY_MAX; j++) {
		for (int i = 0; i < OPEN_KEY_MAX; i++) {
			if (!g_OpenKey[j][i].KeyOpen) {
				if (!g_OpenKey[j][i].UseFlag) {
					switch (direction)
					{
					case 0:
						g_OpenKey[j][i].Position = D3DXVECTOR2(pos.x, pos.y + i * size.y);
						g_OpenKey[j][i].rot = (direction + 2) * 90;
						break;
					case 1:
						g_OpenKey[j][i].Position = D3DXVECTOR2(pos.x + i * size.x, pos.y);
						g_OpenKey[j][i].rot = direction * 90;
						break;
					case 2:
						g_OpenKey[j][i].Position = D3DXVECTOR2(pos.x, pos.y - i * size.y);
						g_OpenKey[j][i].rot = (direction - 2) * 90;
						break;
					case 3:
						g_OpenKey[j][i].Position = D3DXVECTOR2(pos.x - i * size.x, pos.y);
						g_OpenKey[j][i].rot = direction * 90;
						break;
					default:
						break;
					}
					g_OpenKey[j][i].Size = size;
					g_OpenKey[j][i].index = index;
					g_OpenKey[j][i].UseFlag = true;
					if (g_OpenKey[0][2].UseFlag) {
						continue;
					}
					else if (g_OpenKey[1][2].UseFlag) {
						continue;
					}
					else {
						break;
					}
				}
			}
		}
	}
}

void DeleteOpenKey(int PieceNo) {
	for (int j = 0; j < STAGE_OPEN_KEY_MAX; j++) {
		for (int i = 0; i < OPEN_KEY_MAX; i++) {
			if (g_OpenKey[j][i].index == PieceNo) {
				if (g_OpenKey[j][i].UseFlag) {
					g_OpenKey[j][i].UseFlag = false;
				}
			}
		}
	}
}

OPENKEY* GetOpenKey()
{
	return &g_OpenKey[0][0];
}
