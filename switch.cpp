//=============================================================================
//
//	ステージスイッチ処理[switch.cpp]
//															Author:	Fusegi
//															Date:	Fusegi
//-----------------------------------------------------------------------------
//															Update:	22/12/06
//=============================================================================

#include "switch.h"
#include "SwitchWall.h"
#include "renderer.h"
#include "texture.h"
#include "sprite.h"

SWITCH g_Switch[SWITCH_MAX];

static ID3D11ShaderResourceView* g_SwitchTexture;	//画像一枚で一つの変数が必要
static char* g_SwitchTextureName = (char*)"data\\texture\\black&white.jpg";	//テクスチャファイルパス
static int g_SwitchTextureNo = 0;

HRESULT InitSwitch() {
	for (int i = 0; i < SWITCH_MAX; i++) {
		g_Switch[i].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_Switch[i].size = D3DXVECTOR2(0.0f, 0.0f);
		g_Switch[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Switch[i].PieceIndex = -1;
		g_Switch[i].SwitchIndex = -1;
		g_Switch[i].PressFlag = false;
		g_Switch[i].UseFlag = false;
	}
	g_SwitchTextureNo = LoadTexture(g_SwitchTextureName);
	return S_OK;
}
void UninitSwitch() {
	if (g_SwitchTexture != NULL) {
		g_SwitchTexture->Release();
		g_SwitchTexture = NULL;
	}
}
void UpdateSwitch() {
	for (int i = 0; i < SWITCH_MAX; i++) {
		if (g_Switch[i].UseFlag) {

		}
	}
}
void DrawSwitch() {
	for (int i = 0; i < SWITCH_MAX; i++) {
		if (g_Switch[i].UseFlag) {
			SetWorldViewProjection2D();
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_SwitchTextureNo));
			SpriteDrawColorRotation(
				g_Switch[i].pos.x,
				g_Switch[i].pos.y,
				g_Switch[i].size.x,
				g_Switch[i].size.y,
				0.0f,
				g_Switch[i].color,
				0.0f,
				1.0f / 1.0f,
				1.0f / 1.0f,
				1
			);
		}
	}
}
void SetSwitch(D3DXVECTOR2 pos, D3DXVECTOR2 size, int PieceNo, int SwitchIndex) {
	for (int i = 0; i < SWITCH_MAX; i++) {
		if (!g_Switch[i].UseFlag) {
			g_Switch[i].pos = pos;
			g_Switch[i].size = size;
			g_Switch[i].PieceIndex = PieceNo;
			g_Switch[i].SwitchIndex = SwitchIndex;
			g_Switch[i].UseFlag = true;
			break;
		}
	}
}
SWITCH* GetSwitch() {
	return g_Switch;
}
void DeleteSwitch(int PieceNo) {
	for (int i = 0; i < SWITCH_MAX; i++) {
		if (g_Switch[i].UseFlag) {
			if (g_Switch[i].PieceIndex == PieceNo) {
				g_Switch[i].UseFlag = false;
			}
		}
	}
}

