//=============================================================================
//
//ワープ処理
//
//制作者/稲葉陸斗　制作日/2022/06/27
//=============================================================================
#pragma once

#include "warp.h"
#include "main.h"
#include "polygon.h"
#include "sprite.h"
#include "texture.h"
#include "player.h"
#include "time.h"
#include "scene.h"

//=============================================================================
//マクロ定義
//=============================================================================

//=============================================================================
//プロトタイプ宣言
//=============================================================================

//=============================================================================
//グローバル変数
//=============================================================================
static WARP g_Warp[WARP_MAX];
static ID3D11ShaderResourceView	*g_textureWarp;	//画像一枚で一つの変数が必要

static char* g_TextureNameWarp= (char*)"data\\texture\\ワープ.png";

WARP InitData[]=
{
	{true,D3DXVECTOR2(WARP_SIZE_W,WARP_SIZE_H),D3DXVECTOR2(800,100),D3DXVECTOR2(0,2),0,0,D3DXCOLOR(0,1,0,1),1,8,16,8,60 * 0},
	{true,D3DXVECTOR2(WARP_SIZE_W,WARP_SIZE_H),D3DXVECTOR2(800,400),D3DXVECTOR2(0,2),0,0,D3DXCOLOR(0,1,0,1),1,8,16,8,60 * 0},
};


//=============================================================================
//初期化処理
//=============================================================================
HRESULT InitWarp()
{
	srand(time(NULL));

	for (int i = 0; i < WARP_MAX; i++)
	{
		//g_Warp[i] = InitData[i];
		g_Warp[i].Position = D3DXVECTOR2(0.0f,0.0f);
		g_Warp[i].Size = D3DXVECTOR2(0.0f, 0.0f);
		g_Warp[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Warp[i].texno = LoadTexture(g_TextureNameWarp);
		
		//アニメーション系
		g_Warp[i].uv_w = WARP_UV_W; //ワープ横
		g_Warp[i].uv_h = WARP_UV_H; //ワープ縦
		g_Warp[i].PaternNo = 0; //パターン番号
		g_Warp[i].NumPatern = 4; //ヨコの枚数
		
		//使用フラグ
		g_Warp[i].UseFlag = false;
		g_Warp[i].InventoryFlag = false;
	}
	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void UninitWarp()
{
	for (int i = 0; i < WARP_MAX; i++)
	{

	}
}

//=============================================================================
//更新処理
//=============================================================================
void UpdateWarp()
{
	for (int i = 0; i < WARP_MAX; i++)
	{
		if (g_Warp[i].UseFlag == true)
		{
			g_Warp[i].PaternNo += 0.25f;

			if (g_Warp[i].PaternNo >= 16) { g_Warp[i].PaternNo -= 16; }
			if (g_Warp[i].PaternNo < 0) { g_Warp[i].PaternNo += 16; }
		}
	}
	
}

//=============================================================================
//描画処理
//=============================================================================
void DrawWarp()
{
	for (int i = 0; i < WARP_MAX; i++)
	{
		if (g_Warp[i].UseFlag)
		{
			//SetWorldViewProjection2D();

				//テクスチャの設定
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Warp[i].texno));
				//スプライトを表示
				//D3DXCOLOR col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
				/*SpriteDrawColorRotation(g_Warp[i].Position.x, g_Warp[i].Position.y,-0.1f, g_Warp[i].Size.x, g_Warp[i].Size.y,
					g_Warp[i].rot, g_Warp[i].col, 0, 1.0f, 1.0f, 1);
			*/

				SpriteDrawColorRotation(g_Warp[i].Position.x, g_Warp[i].Position.y, -0.1f, g_Warp[i].Size.x, g_Warp[i].Size.y,
					g_Warp[i].rot, g_Warp[i].col, g_Warp[i].PaternNo, g_Warp[i].uv_w, g_Warp[i].uv_h, g_Warp[i].NumPatern);

		}
	}
}
//---------------------------------------------------
//ピースのセットワープ
//引数：ポジション、サイズ、ピースの番号
//--------------------------------------------------
void cipSetWarp(D3DXVECTOR2 pos, D3DXVECTOR2 size,int index,bool in)
{
	for (int i = 0; i < WARP_MAX; i++)
	{
		if (!g_Warp[i].UseFlag)
		{

			g_Warp[i].Position = pos;
			g_Warp[i].Size = size;
			g_Warp[i].PieceIndex = index;
			g_Warp[i].UseFlag = true;
			g_Warp[i].InventoryFlag = in;
			break;

		}


	}

}


int SetWarp(D3DXVECTOR2 pos, D3DXVECTOR2 size)
{
	for (int i = 0; i < WARP_MAX; i++)
	{
		if (!g_Warp[i].UseFlag)
		{

			g_Warp[i].Position = pos;
			g_Warp[i].Size = size;
			g_Warp[i].UseFlag = true;
			return i;

		}


	}

}

void DeleteWarp(int PieceNo)
{
	for (int i = 0; i < WARP_MAX; i++) {
		if (g_Warp[i].UseFlag) {
			if (g_Warp[i].PieceIndex == PieceNo) {
				g_Warp[i].UseFlag = false;
			}
		}
	}

}

//=============================================================================
//ゲット関数
//=============================================================================
WARP* GetWarp()
{
	return g_Warp;
}