
//=============================================================================
//
//バレット処理
//
//制作者/SORA　
//=============================================================================
#pragma once

#include "bullet.h"
#include "player.h"
#include "main.h"
#include "polygon.h"
#include "sprite.h"
#include "texture.h"
#include "input.h"


//=============================================================================
//マクロ定義
//=============================================================================

//=============================================================================
//プロトタイプ宣言
//=============================================================================

//=============================================================================
//グローバル変数
//=============================================================================
static BULLET g_Bullet[BULLET_MAX];
static char* g_TextureName = (char*)"data\\texture\\弾.png";



//=============================================================================
//初期化処理
//=============================================================================
HRESULT InitBullet()
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		//バレットの初期化
		g_Bullet[i].pos = D3DXVECTOR2(0, 0);
		g_Bullet[i].sp = D3DXVECTOR2(-BULLET_SPEED, 0.0f);
		//g_Bullet[i].sp = D3DXVECTOR2(BULLET_SPEED, 0);
		g_Bullet[i].w = BULLET_SIZE_W;
		g_Bullet[i].h = BULLET_SIZE_H;
		g_Bullet[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Bullet[i].rot = 0.0f;
		g_Bullet[i].use = false;
		g_Bullet[i].texno = LoadTexture(g_TextureName);

		g_Bullet[i].PaternNo = 0;//パターン番号
		g_Bullet[i].uv_w = 1;//横サイズ
		g_Bullet[i].uv_h = 1;//縦サイズ
		g_Bullet[i].NumPatern = 1;//横枚数
		g_Bullet[i].hit = false;
		g_Bullet[i].Damage = 1;
	}

	
	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void UninitBullet()
{
	for (int i = 0; i < BULLET_MAX; i++)
	{

	}
}

//=============================================================================
//更新処理
//=============================================================================
void UpdateBullet()
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullet[i].use == true)
		{
			g_Bullet[i].pos.x += g_Bullet[i].sp.x;
		}

		if (g_Bullet[i].pos.y < SCREEN_LIMIT_UP - (g_Bullet[i].h / 2.0f))
		{
			g_Bullet[i].use = false;
		}
	}
}

//=============================================================================
//描画処理
//=============================================================================
void DrawBullet()
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullet[i].use == true)
		{
			//テクスチャの設定
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Bullet[i].texno));
			//スプライトを表示
			D3DXCOLOR col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
			//ここの引数間違ってるかも
			SpriteDrawColorRotation(g_Bullet[i].pos.x, g_Bullet[i].pos.y, 0.0f, g_Bullet[i].w, g_Bullet[i].h, g_Bullet[i].rot, g_Bullet[i].col, g_Bullet[i].PaternNo, g_Bullet[i].uv_w, g_Bullet[i].uv_h, g_Bullet[i].NumPatern);
		}
	}
}

//=============================================================================
//セット関数
//=============================================================================
void SetBullet(D3DXVECTOR2 pos, D3DXVECTOR2 size, int index)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullet[i].use == false)
		{
			g_Bullet[i].pos = pos;
			g_Bullet[i].h = BULLET_SIZE_H;
			g_Bullet[i].w = BULLET_SIZE_W;
			g_Bullet[i].use = true;
			
			return;
		}
	}
}

//=============================================================================
//ゲット関数
//=============================================================================
BULLET* GetBullet()
{
	return g_Bullet;
}