//=============================================================================
//
//	ステージスイッチ処理[switch.cpp]
//															Author:	Fusegi
//															Date:	Fusegi
//-----------------------------------------------------------------------------
//															Update:	22/12/06
//=============================================================================

#include "SwitchWall.h"
#include "texture.h"
#include "sprite.h"
#include "renderer.h"

#define SWITCHWALL_UV_W (1.0f / 1.0f)
#define SWITCHWALL_UV_H (1.0f / 1.0f)
#define SWITCHWALL_NUMPATERN (1)

static SWITCHWALL g_SwitchWall[SWITCHWALL_MAX];

static ID3D11ShaderResourceView* g_SwitchWallTexture;	//画像一枚で一つの変数が必要
static char* g_SwitchWallTextureName = (char*)"data\\texture\\black&white.jpg";	//テクスチャファイルパス
static int g_SwitchWallTextureNo = 0;
HRESULT InitSwitchWall() {
	for (int i = 0; i < SWITCHWALL_MAX; i++) {
		g_SwitchWall[i].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_SwitchWall[i].size = D3DXVECTOR2(0.0f, 0.0f);
		g_SwitchWall[i].sp = D3DXVECTOR2(0.0f, 0.0f);
		g_SwitchWall[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_SwitchWall[i].PaternNo = 0;
		g_SwitchWall[i].PieceIndex = -1;
		g_SwitchWall[i].SwitchIndex = -1;
		g_SwitchWall[i].UseFlag = false;
	}
	g_SwitchWallTextureNo = LoadTexture(g_SwitchWallTextureName);
	return S_OK;
}
void UninitSwitchWall(){
	if (g_SwitchWallTexture != NULL) {
		g_SwitchWallTexture->Release();
		g_SwitchWallTexture = NULL;
	}
}
void UpdateSwitchWall() {

}
void DrawSwitchwall() {
	for (int i = 0; i < SWITCHWALL_MAX; i++) {
		if (g_SwitchWall[i].UseFlag) {
			if (g_SwitchWall[i].UseFlag) {
				SetWorldViewProjection2D();
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_SwitchWallTextureNo));
				SpriteDrawColorRotation(
					g_SwitchWall[i].pos.x,
					g_SwitchWall[i].pos.y,
					g_SwitchWall[i].size.x,
					g_SwitchWall[i].size.y,
					0.0f,
					g_SwitchWall[i].color,
					g_SwitchWall[i].PaternNo,
					SWITCHWALL_UV_W,
					SWITCHWALL_UV_H,
					SWITCHWALL_NUMPATERN
				);
			}
		}
	}
}
void SetSwitchWall(D3DXVECTOR2 pos, D3DXVECTOR2 size, int PieceNo) {
	for (int i = 0; i < SWITCHWALL_MAX; i++) {
		if (!g_SwitchWall[i].UseFlag) {
			g_SwitchWall[i].pos = pos;
			g_SwitchWall[i].size = size;
			g_SwitchWall[i].PieceIndex = PieceNo;
			g_SwitchWall[i].SwitchIndex = i;
			g_SwitchWall[i].UseFlag = false;
			break;
		}
	}
}
SWITCHWALL* GetSwitchWall() {
	return g_SwitchWall;
}
void DeleteSwitchWall(int PieceNo) {
	for (int i = 0; i < SWITCHWALL_MAX; i++) {
		if (g_SwitchWall[i].UseFlag) {
			if (g_SwitchWall[i].PieceIndex == PieceNo) {
				g_SwitchWall[i].UseFlag = false;
			}
		}
	}
}

