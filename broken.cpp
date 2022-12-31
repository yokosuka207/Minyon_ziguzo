//=============================================================================
//
//壊れるブロック処理
//
//制作者/稲葉陸斗　制作日/2022/06/27
//=============================================================================
#pragma once

#include "broken.h"
#include "main.h"
#include "polygon.h"
#include "sprite.h"
#include "texture.h"
#include "player.h"
#include "time.h"
#include "scene.h"
#include"puzzle.h"

//=============================================================================
//マクロ定義
//=============================================================================

//=============================================================================
//プロトタイプ宣言
//=============================================================================

//=============================================================================
//グローバル変数
//=============================================================================
static BROKEN g_Broken[BROKEN_MAX];
static ID3D11ShaderResourceView	*g_textureBroken;	//画像一枚で一つの変数が必要

static char* g_TextureNameBroken = (char*)"data\\texture\\green.png";

BROKEN InitData[]=
{
	{true,D3DXVECTOR2(BROKEN_SIZE_W,BROKEN_SIZE_H),D3DXVECTOR2(400,100),D3DXVECTOR2(0,2),0,0,D3DXCOLOR(1,0,0,1),1,8,16,8,60 * 0},
};


//=============================================================================
//初期化処理
//=============================================================================
HRESULT InitBroken()
{
	srand(time(NULL));

	for (int i = 0; i < BROKEN_MAX; i++)
	{
		g_Broken[i].Postion = D3DXVECTOR2(SCREEN_WIDTH / 2 - 50.0f, 600.0f);
		g_Broken[i].Size = D3DXVECTOR2(BROKEN_SIZE_W, BROKEN_SIZE_H);
		g_Broken[i].index = -1;
		g_Broken[i].texno = LoadTexture(g_TextureNameBroken);
		g_Broken[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);;
		g_Broken[i].UseFlag = false;
	}
	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void UninitBroken()
{
	for (int i = 0; i < BROKEN_MAX; i++)
	{

	}
}

//=============================================================================
//更新処理
//=============================================================================
void UpdateBroken()
{
}

//=============================================================================
//描画処理
//=============================================================================
void DrawBroken()
{
	for (int i = 0; i < BROKEN_MAX; i++)
	{
		if (g_Broken[i].UseFlag)
		{
			//SetWorldViewProjection2D();

				//テクスチャの設定
				GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_Broken[i].texno));
				//スプライトを表示
				D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				SpriteDrawColorRotation(g_Broken[i].Postion.x, g_Broken[i].Postion.y,-0.1f, g_Broken[i].Size.x, g_Broken[i].Size.y, 
					g_Broken[i].rot, g_Broken[i].col, 0, 1.0f, 1.0f, 1);
				
		}
	}
}

void SetBroken(D3DXVECTOR2 Pos, D3DXVECTOR2 s,int index){
	for (int i = 0; i < BROKEN_MAX; i++){
		if (!g_Broken[i].UseFlag){
			g_Broken[i].Postion = Pos;
			g_Broken[i].Size = s;
			g_Broken[i].index = index;
			g_Broken[i].UseFlag = true;
			break;
		}
	}
}
void DeleteBroken(int PieceNo) {
	for (int i = 0; i < BROKEN_MAX; i++) {
		if (g_Broken[i].index == PieceNo) {
			if (g_Broken[i].UseFlag) {
				g_Broken[i].UseFlag = false;
			}
		}
	}
}

//=============================================================================
//ゲット関数
//=============================================================================
BROKEN* GetBroken()
{
	return g_Broken;
}