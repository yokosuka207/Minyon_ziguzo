//=============================================================================
//
//	ステージ街灯スイッチ処理[lamp_switch.cpp]
//															Author: 稲葉 陸斗
//															 Date : 2023/01/23
//-----------------------------------------------------------------------------
//															Update:	22/12/06
//=============================================================================

#include "lamp_switch.h"
#include "lamp.h"
#include "renderer.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "sound.h"

#define LAMP_SWITCH_UV_W (1.0f / 2.0f)
#define LAMP_SWITCH_UV_H (1.0f / 1.0f)
#define LAMP_SWITCH_NUMPATERN (2)

LAMP_SWITCH g_LampSwitch[LAMP_SWITCH_MAX];

static ID3D11ShaderResourceView* g_LampSwitchTexture;	//画像一枚で一つの変数が必要
static char* g_LampSwitchTextureName = (char*)"data\\texture\\街頭スイッチ.png";	//テクスチャファイルパス
static int g_LampSwitchTextureNo = 0;


HRESULT InitLampSwitch() {
	for (int i = 0; i < LAMP_SWITCH_MAX; i++) {
		g_LampSwitch[i].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_LampSwitch[i].size = D3DXVECTOR2(0.0f, 0.0f);
		g_LampSwitch[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_LampSwitch[i].rot = 0;
		g_LampSwitch[i].PieceIndex = -1;
		g_LampSwitch[i].LampSwitchIndex = -1;
		g_LampSwitch[i].PaternNo = 0;
		g_LampSwitch[i].PressFlag = false;
		g_LampSwitch[i].UseFlag = false;
		g_LampSwitch[i].NotPressed = true;
	}
	g_LampSwitchTextureNo = LoadTexture(g_LampSwitchTextureName);
	return S_OK;
}
void UninitLampSwitch() {
	if (g_LampSwitchTexture != NULL) {
		g_LampSwitchTexture->Release();
		g_LampSwitchTexture = NULL;

	}
}
void UpdateLampSwitch() {
	for (int i = 0; i < LAMP_SWITCH_MAX; i++) {
		if (g_LampSwitch[i].UseFlag) {
			if (g_LampSwitch[i].PaternNo > 1) {
				g_LampSwitch[i].PaternNo -= 1;
			}
		}
	}
}
void DrawLampSwitch() {
	//SetWorldViewProjection2D();
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_LampSwitchTextureNo));

	for (int i = 0; i < LAMP_SWITCH_MAX; i++) {
		if (g_LampSwitch[i].UseFlag) {
			SpriteDrawColorRotation(
				g_LampSwitch[i].pos.x,
				g_LampSwitch[i].pos.y,
				-0.1f,
				g_LampSwitch[i].size.x,
				-g_LampSwitch[i].size.y,
				g_LampSwitch[i].rot,
				g_LampSwitch[i].color,
				g_LampSwitch[i].PaternNo,
				LAMP_SWITCH_UV_W,
				LAMP_SWITCH_UV_H,
				LAMP_SWITCH_NUMPATERN
			);
		}
	}
}
void SetLampSwitch(D3DXVECTOR2 pos, D3DXVECTOR2 size, int direction, int PieceNo) {
	for (int i = 0; i < LAMP_SWITCH_MAX; i++) {
		if (!g_LampSwitch[i].UseFlag) {
			switch (direction)
			{
			case 0:g_LampSwitch[i].rot = (direction + 2) * 90;
				break;
			case 1:g_LampSwitch[i].rot = direction * 90;
				break;
			case 2:g_LampSwitch[i].rot = (direction - 2) * 90;
				break;
			case 3:g_LampSwitch[i].rot = direction * 90;
				break;
			default:
				break;
			}
			g_LampSwitch[i].pos = pos;
			g_LampSwitch[i].size = size;
			g_LampSwitch[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_LampSwitch[i].PieceIndex = PieceNo;
			g_LampSwitch[i].LampSwitchIndex = i;
			g_LampSwitch[i].UseFlag = true;
			break;
		}
	}
}
LAMP_SWITCH* GetLampSwitch() {
	return g_LampSwitch;
}
void DeleteLampSwitch(int PieceNo) {
	for (int i = 0; i < LAMP_SWITCH_MAX; i++) {
		if (g_LampSwitch[i].UseFlag) {
			if (g_LampSwitch[i].PieceIndex == PieceNo) {
				g_LampSwitch[i].UseFlag = false;
			}
		}
	}
}