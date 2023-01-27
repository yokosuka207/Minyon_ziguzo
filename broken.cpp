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
static BROKEN_ANIME g_BrokenAnime[BROKEN_ANIME_MAX];

static ID3D11ShaderResourceView	*g_textureBroken;	//画像一枚で一つの変数が必要
static ID3D11ShaderResourceView	*g_textureBrokenAnime;	//画像一枚で一つの変数が必要

static char* g_TextureNameBroken = (char*)"data\\texture\\jump_break.png";
static char* g_TextureNameBrokenAnime = (char*)"data\\texture\\explosion.png";

static int g_TextureNoBrokenAnime = 0;
//BROKEN InitData[]=
//{
//	{true,D3DXVECTOR2(BROKEN_SIZE_W,BROKEN_SIZE_H),D3DXVECTOR2(400,100),D3DXVECTOR2(0,2),0,0,D3DXCOLOR(1,0,0,1),1,8,16,8,60 * 0},
//};
static int BrokenIndex;
static int BrokenNoIndex[BROKEN_MAX];

//=============================================================================
//初期化処理
//=============================================================================
HRESULT InitBroken()
{
	BrokenIndex = 0;
	srand(time(NULL));

	for (int i = 0; i < BROKEN_MAX; i++)
	{
		BrokenNoIndex[i] = -1;
		g_Broken[i].Postion = D3DXVECTOR2(SCREEN_WIDTH / 2 - 50.0f, 600.0f);
		g_Broken[i].Size = D3DXVECTOR2(BROKEN_SIZE_W, BROKEN_SIZE_H);
		g_Broken[i].index = -1;
		g_Broken[i].Number = -1;
		g_Broken[i].texno = LoadTexture(g_TextureNameBroken);
		g_Broken[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Broken[i].UseFlag = false;
		g_Broken[i].breakFlag = false;
	}
	for (int i = 0; i < BROKEN_ANIME_MAX; i++) {
		g_BrokenAnime[i].Postion = D3DXVECTOR2(0.0f, 0.0f);
		g_BrokenAnime[i].Size = D3DXVECTOR2(0.0f, 0.0f);
		g_BrokenAnime[i].index = -1;
		g_BrokenAnime[i].PaternNo = 0.0f;
		g_BrokenAnime[i].uv_w = 1.0f / 4.0f;
		g_BrokenAnime[i].uv_h = 1.0f / 4.0f;
		g_BrokenAnime[i].NumPatern = 4;
		g_BrokenAnime[i].UseFlag = false;
	}
	g_TextureNoBrokenAnime = LoadTexture(g_TextureNameBrokenAnime);
	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void UninitBroken()
{
	if (g_textureBrokenAnime != NULL) {
		g_textureBrokenAnime->Release();
		g_textureBrokenAnime = NULL;
	}
}

//=============================================================================
//更新処理
//=============================================================================
void UpdateBroken()
{
	//for (int i = 0; i < BROKEN_MAX; i++) {
	//	if (g_Broken[i].breakFlag) {
	//		SetBrokenAnime(g_Broken[i].Postion, g_Broken[i].Size, g_Broken[i].index);
	//		//g_Broken[i].breakFlag = false;
	//	}
	//}

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
				SpriteDrawColorRotation(
					g_Broken[i].Postion.x,
					g_Broken[i].Postion.y,
					-0.1f,
					g_Broken[i].Size.x,
					g_Broken[i].Size.y, 
					g_Broken[i].rot,
					g_Broken[i].col,
					0,
					1.0f,
					1.0f,
					1
				);
				
		}
	}
	for (int i = 0; i < BROKEN_ANIME_MAX; i++) {
		if (g_BrokenAnime[i].UseFlag) {
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TextureNoBrokenAnime));
			SpriteDrawColorRotation(
				g_BrokenAnime[i].Postion.x,
				g_BrokenAnime[i].Postion.y,
				-0.1f,
				g_BrokenAnime[i].Size.x,
				-g_BrokenAnime[i].Size.y,
				0.0f,
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				g_BrokenAnime[i].PaternNo,
				g_BrokenAnime[i].uv_w,
				g_BrokenAnime[i].uv_h,
				g_BrokenAnime[i].NumPatern
			);
			g_BrokenAnime[i].PaternNo += 0.5f;
			if (g_BrokenAnime[i].PaternNo > 16.0f) {
				g_BrokenAnime[i].PaternNo = 0.0f;
			}
			if (g_BrokenAnime[i].PaternNo == 16.0f) {
				g_BrokenAnime[i].UseFlag = false;
			}
		}
	}

}

void SetBroken(D3DXVECTOR2 Pos, D3DXVECTOR2 s,int index, int number){

	bool MatchFlag = false;

	for (int i = 0; i < BROKEN_MAX; i++)
	{
		if (!g_Broken[i].UseFlag) 
		{
			if (g_Broken[i].index == index)
			{
				if (g_Broken[i].Number == number-1)
				{
					MatchFlag = true;
					if (!g_Broken[i].breakFlag)
					{
						g_Broken[i].Postion = Pos;
						g_Broken[i].Size = s;
						g_Broken[i].index = index;
						g_Broken[i].Number = number;
						g_Broken[i].UseFlag = true;
						break;

					}
					else {

						break;

					}
				}
			}

		}


	}

	if (!MatchFlag)
	{
		for (int i = BrokenIndex; i < BROKEN_MAX; i++) {
			if (!g_Broken[i].UseFlag) {
				g_Broken[i].Postion = Pos;
				g_Broken[i].Size = s;
				g_Broken[i].index = index;
				g_Broken[i].Number = number;
				g_Broken[i].UseFlag = true;
				BrokenIndex++;
				if (BrokenIndex == BROKEN_MAX)
				{
					BrokenIndex = 0;
				}
				break;
			}
		}
	}
}

void SetBrokenAnime(D3DXVECTOR2 pos, D3DXVECTOR2 size, int index) {
	for (int i = 0; i < BROKEN_ANIME_MAX; i++) {
		if (!g_BrokenAnime[i].UseFlag) {
			g_BrokenAnime[i].Postion = pos;
			g_BrokenAnime[i].Size = size;
			g_BrokenAnime[i].index = index;
			g_BrokenAnime[i].UseFlag = true;
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