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
#include "player.h"

#define SWITCH_UV_W (1.0f / 1.0f)
#define SWITCH_UV_H (1.0f / 1.0f)
#define SWITCH_NUMPATERN (1)

SWITCH g_Switch[SWITCH_MAX];

static ID3D11ShaderResourceView* g_SwitchTexture;	//画像一枚で一つの変数が必要
static char* g_SwitchTextureName = (char*)"data\\texture\\yello.jpg";	//テクスチャファイルパス
static int g_SwitchTextureNo = 0;

HRESULT InitSwitch() {
	for (int i = 0; i < SWITCH_MAX; i++) {
		g_Switch[i].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_Switch[i].size = D3DXVECTOR2(0.0f, 0.0f);
		g_Switch[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Switch[i].PieceIndex = -1;
		g_Switch[i].SwitchIndex = -1;
		g_Switch[i].PaternNo = 0;
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

}
void DrawSwitch() {
	//SetWorldViewProjection2D();
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_SwitchTextureNo));

	for (int i = 0; i < SWITCH_MAX; i++) {
		if (g_Switch[i].UseFlag) {
			SpriteDrawColorRotation(
				g_Switch[i].pos.x,
				g_Switch[i].pos.y,
				-0.1f,
				g_Switch[i].size.x,
				g_Switch[i].size.y,
				0.0f,
				g_Switch[i].color,
				g_Switch[i].PaternNo,
				SWITCH_UV_W,
				SWITCH_UV_H,
				SWITCH_NUMPATERN
			);
		}
	}
}
void SetSwitch(D3DXVECTOR2 pos, D3DXVECTOR2 size, int PieceNo) {
	for (int i = 0; i < SWITCH_MAX; i++) {
		if (!g_Switch[i].UseFlag) {
			g_Switch[i].pos = pos;
			g_Switch[i].size = size;
			g_Switch[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_Switch[i].PieceIndex = PieceNo;
			g_Switch[i].SwitchIndex = i;
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

