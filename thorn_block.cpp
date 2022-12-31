/*==============================================================================

   トゲブロック [thorn_block.cpp]
														 Author		:座間研佑
														 Date		:2022/11/09
														 最終更新	:2022/11/224
==============================================================================*/

#include "thorn_block.h"
#include "main.h"
#include "polygon.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "time.h"
#include "scene.h"
#include "puzzle.h"

//=============================================================================
//マクロ定義
//=============================================================================

//=============================================================================
//プロトタイプ宣言
//=============================================================================

//=============================================================================
//グローバル変数
//=============================================================================
static THORNBLOCK g_ThornBlock[THORN_BLOCK_MAX];
static ID3D11ShaderResourceView* g_textureThornBlock;	//画像一枚で一つの変数が必要

static char* g_TextureNameThornBlock = (char*)"data\\texture\\Spikes.png";

//THORNBLOCK InitData[] =
//{
//	{true,D3DXVECTOR2(THORN_BLOCK_W,THORN_BLOCK_H),D3DXVECTOR2(400,100),D3DXVECTOR2(0,2),0,0,D3DXCOLOR(1,0,0,1),1,8,16,8,60 * 0},
//};


//=============================================================================
//初期化処理
//=============================================================================
HRESULT InitThornBlock()
{
	srand(time(NULL));

	for (int i = 0; i < THORN_BLOCK_MAX; i++)
	{
		g_ThornBlock[i].Postion = D3DXVECTOR2(0.0f, 0.0f);
		g_ThornBlock[i].Size = D3DXVECTOR2(THORN_BLOCK_W, THORN_BLOCK_H);
		g_ThornBlock[i].texno = LoadTexture(g_TextureNameThornBlock);
		g_ThornBlock[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);;
		g_ThornBlock[i].PieceIndex = -1;
		g_ThornBlock[i].UseFlag = false;
	}
	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void UninitThornBlock()
{
	for (int i = 0; i < THORN_BLOCK_MAX; i++)
	{

	}
}

//=============================================================================
//更新処理
//=============================================================================
void UpdateThornBlock()
{
	for (int i = 0; i < THORN_BLOCK_MAX; i++) {
		
	}
}

//=============================================================================
//描画処理
//=============================================================================
void DrawThornBlock()
{
	for (int i = 0; i < THORN_BLOCK_MAX; i++)
	{
		if (g_ThornBlock[i].UseFlag)
		{
			//SetWorldViewProjection2D();

			//テクスチャの設定
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ThornBlock[i].texno));
			//スプライトを表示
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			SpriteDrawColorRotation(g_ThornBlock[i].Postion.x, g_ThornBlock[i].Postion.y, 0.0f,g_ThornBlock[i].Size.x, g_ThornBlock[i].Size.y,
				g_ThornBlock[i].rot, g_ThornBlock[i].col, 0, 1.0f, 1.0f, 1);

		}
	}
}
void SetThornBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, int PieceNo) {
	for (int i = 0; i < THORN_BLOCK_MAX; i++) {
		if (!g_ThornBlock[i].UseFlag) {
			g_ThornBlock[i].Postion = pos;
			g_ThornBlock[i].Size = size;
			g_ThornBlock[i].PieceIndex = PieceNo;
			g_ThornBlock[i].UseFlag = true;
			break;
		}
	}
 }
void DeleteThornBlock(int PieceNo) {
	for (int i = 0; i < THORN_BLOCK_MAX; i++) {
		if (g_ThornBlock[i].UseFlag) {
			if (g_ThornBlock[i].PieceIndex == PieceNo)
			{
				g_ThornBlock[i].UseFlag = false;

			}
		}
	}
}

 //なんか二つあったのでコメントアウトしておきます
 // 
//int SetThornBlock(D3DXVECTOR2 Pos, D3DXVECTOR2 s)
//{
//	//PUZZLE* pPuzzle = GetPuzzle();
//
//	for (int i = 0; i < THORN_BLOCK_MAX; i++)
//	{
//		if (!g_ThornBlock[i].UseFlag)
//		{
//
//			g_ThornBlock[i].Postion = Pos;
//			g_ThornBlock[i].Size = s;
//			g_ThornBlock[i].UseFlag = true;
//			return i;
//
//		}
//
//
//	}

//}

//=============================================================================
//ゲット関数
//=============================================================================
THORNBLOCK* GetThornBlock()
{
	return g_ThornBlock;
}