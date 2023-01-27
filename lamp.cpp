//=============================================================================
//
//	�X������[lamp.cpp]
//															Author: ��t ���l
//															 Date : 2023/01/23
//-----------------------------------------------------------------------------
//															Update:	22/12/06
//=============================================================================

#include "lamp.h"
#include "texture.h"
#include "sprite.h"
#include "renderer.h"
#include "MapChip.h"

#define LAMP_NUMPATERN (2)

static LAMP g_Lamp[LAMP_MAX];

static ID3D11ShaderResourceView* g_LampTexture;	//�摜�ꖇ�ň�̕ϐ����K�v
static char* g_LampTextureName = (char*)"data\\texture\\�X��.png";	//�e�N�X�`���t�@�C���p�X
static int g_LampTextureNo = 0;

HRESULT InitLamp() {
	for (int i = 0; i < LAMP_MAX; i++) {
		g_Lamp[i].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_Lamp[i].size = D3DXVECTOR2(0.0f, 0.0f);
		g_Lamp[i].sp = D3DXVECTOR2(0.0f, 0.0f);
		g_Lamp[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Lamp[i].rot = 0;
		g_Lamp[i].PaternNo = 0.0f;
		g_Lamp[i].uv_w = 1.0f / 2.0f;
		g_Lamp[i].uv_h = 1.0f / 1.0f;
		g_Lamp[i].PieceIndex = -1;
		g_Lamp[i].SwitchIndex = -1;
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
			if (g_Lamp[i].UseFlag) {
				SpriteDrawColorRotation(
					g_Lamp[i].pos.x,
					g_Lamp[i].pos.y,
					-0.1f,
					g_Lamp[i].size.x,
					-g_Lamp[i].size.y,
					g_Lamp[i].rot,
					g_Lamp[i].color,
					g_Lamp[i].PaternNo,
					g_Lamp[i].uv_w,
					g_Lamp[i].uv_h,
					LAMP_NUMPATERN
				);
			}
	}
}

void SetLamp(D3DXVECTOR2 pos, D3DXVECTOR2 size, int PieceNo, int direction, int LampMax) {
	for (int i = 0; i < LAMP_MAX; i++) {
		if (!g_Lamp[i].UseFlag) {
			switch (direction)
			{
			case 0:g_Lamp[i].rot = (direction + 2) * 90;
				break;
			case 1:g_Lamp[i].rot = direction * 90;
				break;
			case 2:g_Lamp[i].rot = (direction - 2) * 90;
				break;
			case 3:g_Lamp[i].rot = direction * 90;
				break;
			default:
				break;
			}
			g_Lamp[i].pos = pos;
			g_Lamp[i].size = D3DXVECTOR2(size.x + 20, size.y + 28);
			g_Lamp[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_Lamp[i].PieceIndex = PieceNo;
			g_Lamp[i].SwitchIndex = i;
			g_Lamp[i].UseFlag = true;
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