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
#include "MapChip.h"

#define SWITCHWALL_NUMPATERN (1)

static SWITCHWALL g_SwitchWall[SWITCHWALL_MAX][SWITCHWALL_LIMIT];

static ID3D11ShaderResourceView* g_SwitchWallTexture;	//画像一枚で一つの変数が必要
static char* g_SwitchWallTextureName = (char*)"data\\texture\\鉄格子.png";	//テクスチャファイルパス
static int g_SwitchWallTextureNo = 0;

HRESULT InitSwitchWall() {
	for (int i = 0; i < SWITCHWALL_MAX; i++) {
		for (int j = 0; j < SWITCHWALL_LIMIT; j++) {
			g_SwitchWall[i][j].pos = D3DXVECTOR2(0.0f, 0.0f);
			g_SwitchWall[i][j].size = D3DXVECTOR2(0.0f, 0.0f);
			g_SwitchWall[i][j].sp = D3DXVECTOR2(0.0f, 0.0f);
			g_SwitchWall[i][j].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_SwitchWall[i][j].rot = 0;
			g_SwitchWall[i][j].PaternNo = 0.0f;
			g_SwitchWall[i][j].uv_w = 1.0f / 1.0f;
			g_SwitchWall[i][j].uv_h = 1.0f / 3.0f;
			g_SwitchWall[i][j].PieceIndex = -1;
			g_SwitchWall[i][j].SwitchIndex = -1;
			g_SwitchWall[i][j].UseFlag = false;
			g_SwitchWall[i][j].PressFlag = false;
		}
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
void DrawSwitchWall() {
	//SetWorldViewProjection2D();
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_SwitchWallTextureNo));
	for (int i = 0; i < SWITCHWALL_MAX; i++) {
		for (int j = 0; j < SWITCHWALL_LIMIT; j++) {
			if (g_SwitchWall[i][j].UseFlag) {
				if (!g_SwitchWall[i][j].PressFlag) {
					g_SwitchWall[i][j].PaternNo = j;

					SpriteDrawColorRotation(
						g_SwitchWall[i][j].pos.x,
						g_SwitchWall[i][j].pos.y,
						-0.1f,
						g_SwitchWall[i][j].size.x,
						-g_SwitchWall[i][j].size.y,
						g_SwitchWall[i][j].rot,
						g_SwitchWall[i][j].color,
						g_SwitchWall[i][j].PaternNo,
						g_SwitchWall[i][j].uv_w,
						g_SwitchWall[i][j].uv_h,
						SWITCHWALL_NUMPATERN
					);
				}
			}
		}
	}
}

void SetSwitchWall(D3DXVECTOR2 pos, D3DXVECTOR2 size, int PieceNo, int direction, int WallMax) {
	for (int i = 0; i < SWITCHWALL_MAX; i++) {
		if (!g_SwitchWall[i]->UseFlag) {
			for (int j = 0; j < SWITCHWALL_LIMIT; j++) {
				switch (direction) {
				case 0:
					g_SwitchWall[i][j].pos = D3DXVECTOR2(pos.x, pos.y + j * size.y);//↑
					g_SwitchWall[i][j].rot = (direction + 2) * 90;
					break;
				case 1:
					g_SwitchWall[i][j].pos = D3DXVECTOR2(pos.x + j * size.x, pos.y);//→
					g_SwitchWall[i][j].rot = direction * 90;
					break;
				case 2:
					g_SwitchWall[i][j].pos = D3DXVECTOR2(pos.x, pos.y - j * size.y);//↓
					g_SwitchWall[i][j].rot = (direction - 2) * 90;
					break;
				case 3:
					g_SwitchWall[i][j].pos = D3DXVECTOR2(pos.x - j * size.x, pos.y);//←
					g_SwitchWall[i][j].rot = direction * 90;
					break;
				}
				g_SwitchWall[i][j].size = size;
				g_SwitchWall[i][j].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				g_SwitchWall[i][j].PieceIndex = PieceNo;
				g_SwitchWall[i][j].SwitchIndex = i;
				g_SwitchWall[i][j].UseFlag = true;
				g_SwitchWall[i][j].PressFlag = false;
			}
			break;
		}
	}
}

SWITCHWALL* GetSwitchWall() {
	return &g_SwitchWall[0][0];
}
void DeleteSwitchWall(int PieceNo) {
	for (int i = 0; i < SWITCHWALL_MAX; i++) {
		for (int j = 0; j < SWITCHWALL_LIMIT; j++) {
			if (g_SwitchWall[i][j].UseFlag) {
				if (g_SwitchWall[i][j].PieceIndex == PieceNo) {
					g_SwitchWall[i][j].UseFlag = false;
					g_SwitchWall[i][j].PressFlag = false;
				}
			}
		}
	}
}

