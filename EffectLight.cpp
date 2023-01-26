/*================================================================================

	ライト処理[EffectLight.cpp]

												Author: 稲葉 陸斗
												 Date : 2023/01/23
----------------------------------------------------------------------------------
Update:

================================================================================*/
#include "EffectLight.h"
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "lamp_switch.h"

// デバッグ用
#include "mouse.h"

//**************************************************
// マクロ定義
//**************************************************
#define LIGHT_MAX	LAMP_SWITCH_MAX
#define LIGHT_NUM_X	1
#define LIGHT_NUM_Y	1
#define LIGHT_PATTERN_MAX	(LIGHT_NUM_X * LIGHT_NUM_Y)
#define LIGHT_UV_W	(1.0f / LIGHT_NUM_X)
#define LIGHT_UV_Y	(1.0f / LIGHT_NUM_Y)
#define LIGHT_SIZE_X	30.0f
#define LIGHT_SIZE_Y	45.0f

//**************************************************
// グローバル変数
//**************************************************
static LIGHT g_EffectLight[LIGHT_MAX];
static char* g_EffectTextureName1 = (char*)"data\\texture\\街灯の光.png";
//static char* g_EffectTextureName2 = (char*)"data\\texture\\explosion.png";

//==================================================
// 初期化
//==================================================
void InitEffectLight()
{
	for (int i = 0; i < LIGHT_MAX; i++) {
		g_EffectLight[i].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_EffectLight[i].size = D3DXVECTOR2(LIGHT_SIZE_X, LIGHT_SIZE_Y);
		g_EffectLight[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_EffectLight[i].rot = 0.0f;
		g_EffectLight[i].TexNo = LoadTexture(g_EffectTextureName1);
		g_EffectLight[i].PatternNo = 0.0f;

		g_EffectLight[i].bUse = false;
		g_EffectLight[i].stop = true;
	}
}

//==================================================
// 終了処理
//==================================================
void UninitEffectLight()
{
}

//==================================================
// 更新処理
//==================================================
void UpdateEffectLight()
{
	// 全チェック
	for (int i = 0; i < LIGHT_MAX; i++) {
		// 使用中
		if (g_EffectLight[i].bUse) 
		{
			if (g_EffectLight[i].stop == false)
			{
				g_EffectLight[i].bUse = true;
			}
			else
			{
				g_EffectLight[i].bUse = false;
			}
			/*if (g_EffectLight[i].stop == false)
			{
				g_EffectLight[i].PatternNo += 0.5f;
				if (g_EffectLight[i].PatternNo >= LIGHT_PATTERN_MAX / 2)
				{
					g_EffectLight[i].PatternNo = LIGHT_PATTERN_MAX / 2;
				}
			}
			else
			{
				g_EffectLight[i].PatternNo -= 0.5f;
				if (g_EffectLight[i].PatternNo <= 0)
				{
					g_EffectLight[i].bUse = false;
				}
			}*/
		}
	}
}

//==================================================
// 描画処理
//==================================================
void DrawEffectLight()
{
	SetBlendState(BLEND_MODE_ADD);

	// 全チェック
	for (int i = 0; i < LIGHT_MAX; i++) {
		// 使用中
		if (g_EffectLight[i].bUse) {
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_EffectLight[i].TexNo));

			SpriteDrawColorRotation(
				g_EffectLight[i].pos.x, g_EffectLight[i].pos.y, -0.1f,
				g_EffectLight[i].size.x, g_EffectLight[i].size.y, 180.0f + g_EffectLight[i].rot, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				g_EffectLight[i].PatternNo, LIGHT_UV_W, LIGHT_UV_Y, LIGHT_NUM_X
			);
		}
	}

	SetBlendState(BLEND_MODE_ALPHABLEND);
}

//==================================================
// セット関数
//==================================================
void SetEffectLight(D3DXVECTOR2 pos, float rot, int index)
{
	if (!g_EffectLight[index].bUse) 
	{
		g_EffectLight[index].pos = pos;
		g_EffectLight[index].rot = rot;
		g_EffectLight[index].bUse = true;
		g_EffectLight[index].stop = false;
	}
}


//==================================================
// ライトオフ
//==================================================
void StopEffectLight(int index)
{
	g_EffectLight[index].stop = true;
}