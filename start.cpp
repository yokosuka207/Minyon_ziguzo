
#include "start.h"
#include "renderer.h"
#include "texture.h"
#include "sprite.h"

#define START_UV_W (1.0f / 1.0f)
#define START_UV_H (1.0f / 2.0f)
#define START_NUMPATERN (1)

static START g_Start[START_MAX];

static ID3D11ShaderResourceView* g_StartTexture;	//画像一枚で一つの変数が必要
static char* g_StartTextureName = (char*)"data\\texture\\ドア.png";	//テクスチャファイルパス
static int g_StartTextureNo = 0;

HRESULT InitStart() {
	for (int i = 0; i < START_MAX; i++) {
		g_Start[i].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_Start[i].size = D3DXVECTOR2(0.0f, 0.0f);
		g_Start[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Start[i].PieceIndex = -1;
		g_Start[i].PaternNo = 0;
		g_Start[i].GoalFlag = false;
		g_Start[i].UseFlag = false;
	}
	g_StartTextureNo = LoadTexture(g_StartTextureName);
	return S_OK;
}
void UninitStart() {
	if (g_StartTexture != NULL) {
		g_StartTexture->Release();
		g_StartTexture = NULL;
	}
}
void UpdateStart() {

}
void DrawStart() {
	//SetWorldViewProjection2D();
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_StartTextureNo));
	for (int i = 0; i < START_MAX; i++) {
		g_Start[i].PaternNo += i;
		if (g_Start[i].UseFlag) {
			SpriteDrawColorRotation(
				g_Start[i].pos.x,
				g_Start[i].pos.y,
				-0.1f,
				g_Start[i].size.x,
				-g_Start[i].size.y,
				0.0f,
				g_Start[i].color,
				g_Start[i].PaternNo,
				START_UV_W,
				START_UV_H,
				START_NUMPATERN
			);
		}
	}
}
void SetStart(D3DXVECTOR2 pos, D3DXVECTOR2 size, int PieceNo) {
	for (int i = 0; i < START_MAX; i++) {
		if (!g_Start[i].UseFlag) {
			g_Start[i].pos = D3DXVECTOR2(pos.x, pos.y - i * size.y);
			g_Start[i].size = size;
			g_Start[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_Start[i].PieceIndex = PieceNo;
			g_Start[i].UseFlag = true;
			g_Start[i].GoalFlag = false;
		}
	}
}
START* GetStart() {
	return g_Start;
}
void DeleteStart(int PieceNo) {
	for (int i = 0; i < START_MAX; i++) {
		if (g_Start[i].UseFlag) {
			if (g_Start[i].PieceIndex == PieceNo) {
				g_Start[i].UseFlag = false;
			}
		}
	}
}
