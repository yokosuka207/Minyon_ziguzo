//=============================================================================
//
//	街灯処理[lamp.cpp]
//															Author: 稲葉 陸斗
//															 Date : 2023/01/23
//-----------------------------------------------------------------------------
//															Update:	22/12/06
//=============================================================================

#include "lamp.h"
#include "texture.h"
#include "sprite.h"
#include "renderer.h"
#include "MapChip.h"

#define LAMP_NUMPATERN (1)

static LAMP g_Lamp[LAMP_MAX];

static ID3D11ShaderResourceView* g_LampTexture;	//画像一枚で一つの変数が必要
static char* g_LampTextureName = (char*)"data\\texture\\鉄格子.png";	//テクスチャファイルパス
static int g_LampTextureNo = 0;

HRESULT InitLamp() {
	for (int i = 0; i < LAMP_MAX; i++) {
		g_Lamp[i].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_Lamp[i].size = D3DXVECTOR2(0.0f, 0.0f);
		g_Lamp[i].sp = D3DXVECTOR2(0.0f, 0.0f);
		g_Lamp[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Lamp[i].rot = 0;
		g_Lamp[i].PaternNo = 0.0f;
		g_Lamp[i].uv_w = 1.0f / 1.0f;
		g_Lamp[i].uv_h = 1.0f / 3.0f;
		g_Lamp[i].PieceIndex = -1;
		g_Lamp[i].SwitchIndex = -1;
		g_Lamp[i].LampMax = 0;
		g_Lamp[i].UseFlag = false;
	}
	g_LampTextureNo = LoadTexture(g_LampTextureName);
	return S_OK;
}
void UninitLamp() {
	if (g_LampTexture != NULL) {
		g_LampTexture->Release();
		g_LampTexture = NULL;
	}
}
void UpdateLamp() {
	for (int i = 0; i < LAMP_MAX; i++) {
		if (g_Lamp[i].UseFlag) {

		}
	}
}
void DrawLamp() {
	//SetWorldViewProjection2D();
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_LampTextureNo));
	for (int i = 0; i < LAMP_MAX; i++) {
		for (int j = 0; j < g_Lamp[i].LampMax; j++) {
			if (g_Lamp[i + j].UseFlag) {
				g_Lamp[i + j].PaternNo = j;

				SpriteDrawColorRotation(
					g_Lamp[i + j].pos.x,
					g_Lamp[i + j].pos.y,
					-0.1f,
					g_Lamp[i + j].size.x,
					-g_Lamp[i + j].size.y,
					g_Lamp[i + j].rot,
					g_Lamp[i + j].color,
					g_Lamp[i + j].PaternNo,
					g_Lamp[i + j].uv_w,
					g_Lamp[i + j].uv_h,
					LAMP_NUMPATERN
				);
			}
		}
	}
}

void SetLamp(D3DXVECTOR2 pos, D3DXVECTOR2 size, int PieceNo, int direction, int LampMax) {
	for (int i = 0; i < LAMP_MAX; i++) {
		if (!g_Lamp[i].UseFlag) {
			g_Lamp[i].LampMax = 0;
			//方向変換できればドアもできる(0,2しか来ない)、あとはインデックスだけ
			for (int j = 0; j < LampMax; j++) {
				switch(direction) {
				case 0:
					g_Lamp[i + j].pos = D3DXVECTOR2(pos.x, pos.y + j * size.y);//↑
					g_Lamp[i + j].rot = (direction + 2) * 90;
					break;
				case 1:
					g_Lamp[i + j].pos = D3DXVECTOR2(pos.x + j * size.x, pos.y);//→
					g_Lamp[i + j].rot = direction * 90;
					break;
				case 2:
					g_Lamp[i + j].pos = D3DXVECTOR2(pos.x, pos.y - j * size.y);//↓
					g_Lamp[i + j].rot = (direction - 2) * 90;
					break;
				case 3:
					g_Lamp[i + j].pos = D3DXVECTOR2(pos.x - j * size.x, pos.y);//←
					g_Lamp[i + j].rot = direction * 90;
					break;
				}
				g_Lamp[i + j].size = size;
				g_Lamp[i + j].color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				g_Lamp[i + j].PieceIndex = PieceNo;
				g_Lamp[i + j].SwitchIndex = i;
				g_Lamp[i + j].UseFlag = true;

				g_Lamp[i].LampMax++;
			}
			break;
		}
	}
}

LAMP* GetLamp() {
	return g_Lamp;
}
void DeleteLamp(int PieceNo) {
	for (int i = 0; i < LAMP_MAX; i++) {
		if (g_Lamp[i].UseFlag) {
			if (g_Lamp[i].PieceIndex == PieceNo) {
				g_Lamp[i].UseFlag = false;
			}
		}
	}
}