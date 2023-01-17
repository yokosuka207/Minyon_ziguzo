/*================================================================================

	ヒバナエフェクト処理[EffectSpark.cpp]

												Author: 齊藤 零登
												 Date : 2023/01/10
----------------------------------------------------------------------------------
Update:

================================================================================*/
#include "EffectSpark.h"
#include "main.h"
#include "texture.h"
#include "sprite.h"

// デバッグ用
#include "mouse.h"

//**************************************************
// マクロ定義
//**************************************************
#define EFFECT_MAX	6
#define EFFECT_NUM_X	4
#define EFFECT_NUM_Y	4
#define EFFECT_PATTERN_MAX	(EFFECT_NUM_X * EFFECT_NUM_Y)
#define EFFECT_UV_W	(1.0f / EFFECT_NUM_X)
#define EFFECT_UV_Y	(1.0f / EFFECT_NUM_Y)
#define EFFECT_SIZE_X	100.0f
#define EFFECT_SIZE_Y	100.0f

//**************************************************
// グローバル変数
//**************************************************
static EFFECT_SPARK g_EffectSpark[EFFECT_MAX];
static char* g_TextureName = (char*)"data\\texture\\test_SparkEffect.png";

//==================================================
// 初期化
//==================================================
void InitEffectSpark()
{
	for (int i = 0; i < EFFECT_MAX; i++) {
		g_EffectSpark[i].pos = D3DXVECTOR2(0.0f, 0.0f);
		g_EffectSpark[i].size = D3DXVECTOR2(EFFECT_SIZE_X, EFFECT_SIZE_Y);
		g_EffectSpark[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_EffectSpark[i].rot = 0.0f;
		g_EffectSpark[i].TexNo = LoadTexture(g_TextureName);
		g_EffectSpark[i].PatternNo = 0.0f;

		g_EffectSpark[i].bUse = false;
	}
}

//==================================================
// 終了処理
//==================================================
void UninitEffectSpark()
{
}

//==================================================
// 更新処理
//==================================================
void UpdateEffectSpark()
{
	// 全チェック
	for (int i = 0; i < EFFECT_MAX; i++) {
		// 使用中
		if (g_EffectSpark[i].bUse) {
			g_EffectSpark[i].PatternNo += 0.5f;
			if (g_EffectSpark[i].PatternNo >= EFFECT_PATTERN_MAX) {
				g_EffectSpark[i].PatternNo = 0;
				g_EffectSpark[i].bUse = false;
			}
		}
	}
}

//==================================================
// 描画処理
//==================================================
void DrawEffectSpark()
{
	SetBlendState(BLEND_MODE_ADD);

	// 全チェック
	for (int i = 0; i < EFFECT_MAX; i++) {
		// 使用中
		if (g_EffectSpark[i].bUse) {
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_EffectSpark[i].TexNo));

			SpriteDrawColorRotation(
				g_EffectSpark[i].pos.x, g_EffectSpark[i].pos.y, -0.1f,
				g_EffectSpark[i].size.x, g_EffectSpark[i].size.y, 180.0f + g_EffectSpark[i].rot, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				g_EffectSpark[i].PatternNo, EFFECT_UV_W, EFFECT_UV_Y, EFFECT_NUM_X
			);
		}
	}

	SetBlendState(BLEND_MODE_ALPHABLEND);
}

//==================================================
// セット関数
//==================================================
void SetEffectSpark(D3DXVECTOR2 pos, float rot)
{
	for (int i = 0; i < EFFECT_MAX; i++) {
		if (!g_EffectSpark[i].bUse) {
			g_EffectSpark[i].pos = pos;
			g_EffectSpark[i].rot = rot;
			g_EffectSpark[i].bUse = true;
			break;
		}
	}
}
