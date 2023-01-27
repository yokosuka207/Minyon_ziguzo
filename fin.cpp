
#include "fin.h"
#include "sprite.h"
#include "texture.h"
#include "sound.h"

#include "xkeyboard.h"
#include "fade.h"
#include "scene.h"

static ID3D11ShaderResourceView* g_FinTexture;	//画像一枚で一つの変数が必要
static ID3D11ShaderResourceView* g_FinBGTexture;	//画像一枚で一つの変数が必要
static char* g_FinTextureName = (char*)"data\\texture\\number.png";
static char* g_FinBGTextureName = (char*)"data\\texture\\number.png";
static int g_FinTextureNo = 0;
static int g_FinBGTextureNo = 0;

static int g_FinSoundNo = 0;

static FIN g_Fin;
static FIN g_FinBG;

void InitFin() {
	g_Fin.pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	g_Fin.size = D3DXVECTOR2(100.0f, 100.0f);
	g_Fin.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Fin.PaternNo = 0;
	g_Fin.uv_w = 1.0f / 1.0f;
	g_Fin.uv_h = 1.0f / 1.0f;
	g_Fin.NumPatern = 1;

	g_FinBG.pos = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	g_FinBG.size = D3DXVECTOR2(100.0f, 100.0f);
	g_FinBG.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_FinBG.PaternNo = 0;
	g_FinBG.uv_w = 1.0f / 1.0f;
	g_FinBG.uv_h = 1.0f / 1.0f;
	g_FinBG.NumPatern = 1;

	g_FinTextureNo = LoadTexture(g_FinTextureName);
	g_FinBGTextureNo = LoadTexture(g_FinBGTextureName);
	char filename[] = "data\\SoundData\\SE\\タイプライター.wav";
	g_FinSoundNo = LoadSound(filename);
	PlaySound(g_FinSoundNo, -1);
}
void UninitFin() {
	StopSound(g_FinSoundNo);
	if (g_FinTexture != NULL) {
		g_FinTexture->Release();
		g_FinTexture = NULL;
	}
	if (g_FinBGTexture != NULL) {
		g_FinBGTexture->Release();
		g_FinBGTexture = NULL;
	}
}
void UpdateFin() {
	//StartFade(FADE::FADE_ALPHA_OUT);
}
void DrawFin() {
	SetWorldViewProjection2D();
	//背景
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_FinBGTextureNo));

		SpriteDrawColorRotation
		(
			g_FinBG.pos.x,
			g_FinBG.pos.y,
			0.0f,
			g_FinBG.size.x,
			g_FinBG.size.y,
			0.0f,
			g_FinBG.color,
			g_FinBG.PaternNo,
			g_FinBG.uv_w,
			g_FinBG.uv_h,
			g_FinBG.NumPatern
		);
	}
	//fin
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_FinTextureNo));

		SpriteDrawColorRotation
		(
			g_Fin.pos.x,
			g_Fin.pos.y,
			0.0f,
			g_Fin.size.x,
			g_Fin.size.y,
			0.0f,
			g_Fin.color,
			g_Fin.PaternNo,
			g_Fin.uv_w,
			g_Fin.uv_h,
			g_Fin.NumPatern
		);
	}
}

