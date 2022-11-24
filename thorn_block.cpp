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
#include "input.h"
#include "player.h"
#include "time.h"
#include "scene.h"
#include "puzzle.h"
#include "broken.h"
#include "collision.h"
#include "player.h"
#include "game.h"

THORNBLOCK g_ThornBlock[THORN_BLOCK_MAX];
static ID3D11ShaderResourceView	*g_textureThornBlock;	//画像一枚で一つの変数が必要
static char *g_textureName_ThornBlock = (char*)"data\\texture\\thorn_block.png";	//テクスチャファイルパス

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

static char* g_TextureNameThornBlock = (char*)"data\\texture\\thorn_block.png";

THORNBLOCK InitData[] =
{
	{true,D3DXVECTOR2(THORN_BLOCK_W,THORN_BLOCK_H),D3DXVECTOR2(400,100),D3DXVECTOR2(0,2),0,0,D3DXCOLOR(1,0,0,1),1,8,16,8,60 * 0},
};


//=============================================================================
//初期化処理
//=============================================================================
HRESULT InitThornBlock()
{
	srand(time(NULL));

	for (int i = 0; i < THORN_BLOCK_MAX; i++)
	{
<<<<<<< HEAD
		g_ThornBlock[i].texno = LoadTexture(g_textureName_ThornBlock);

		g_ThornBlock[i].Position = D3DXVECTOR2(0.0f, 0.0f);
		g_ThornBlock[i].Size = D3DXVECTOR2(THORN_BLOCK_W, THORN_BLOCK_H);
		g_ThornBlock[i].Rotation = 0.0f;
		g_ThornBlock[i].Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_ThornBlock[i].PieceNo = -1;
		g_ThornBlock[i].UseFlag = false;

	}

=======
		g_ThornBlock[i].Postion = D3DXVECTOR2(0.0f, 0.0f);
		g_ThornBlock[i].Size = D3DXVECTOR2(THORN_BLOCK_W, THORN_BLOCK_H);
		g_ThornBlock[i].texno = LoadTexture(g_TextureNameThornBlock);
		g_ThornBlock[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);;
		g_ThornBlock[i].UseFlag = false;
	}
>>>>>>> 90b99b71e27210bd6a8deaafb35e92c6ebed0d71
	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void UninitThornBlock()
{
	for (int i = 0; i < THORN_BLOCK_MAX; i++)
	{
<<<<<<< HEAD
		g_textureThornBlock->Release();
		g_textureThornBlock = NULL;
=======

>>>>>>> 90b99b71e27210bd6a8deaafb35e92c6ebed0d71
	}
}

//=============================================================================
//更新処理
//=============================================================================
void UpdateThornBlock()
{
	PLAYER* pPlayer = GetPlayer();
	for (int i = 0; i < THORN_BLOCK_MAX; i++) {
		if (CollisionBB(pPlayer->Position, g_ThornBlock[i].Position, pPlayer->size, g_ThornBlock[i].Size)) {
			ResetGame();
		}
	}
}

//=============================================================================
//描画処理
//=============================================================================
void DrawThornBlock()
{
<<<<<<< HEAD
	for (int i = 0; i < THORN_BLOCK_MAX; i++){
		if (g_ThornBlock[i].UseFlag){
			SetWorldViewProjection2D();

			//四角形の描画
			//D3DXCOLOR	col = D3DXCOLOR(1.0f, 0.8f, 0.8f, 0.5f);
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ThornBlock[i].texno));

			SpriteDrawColorRotation(g_ThornBlock[i].Position.x, g_ThornBlock[i].Position.y,
				g_ThornBlock[i].Size.x, g_ThornBlock[i].Size.y, g_ThornBlock[i].Rotation, g_ThornBlock[i].Col,
				0, 1.0f, 1.0f, 1);
=======
	for (int i = 0; i < THORN_BLOCK_MAX; i++)
	{
		if (g_ThornBlock[i].UseFlag)
		{
			SetWorldViewProjection2D();

			//テクスチャの設定
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_ThornBlock[i].texno));
			//スプライトを表示
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			SpriteDrawColorRotation(g_ThornBlock[i].Postion.x, g_ThornBlock[i].Postion.y, g_ThornBlock[i].Size.x, g_ThornBlock[i].Size.y,
				g_ThornBlock[i].rot, g_ThornBlock[i].col, 0, 1.0f, 1.0f, 1);

>>>>>>> 90b99b71e27210bd6a8deaafb35e92c6ebed0d71
		}
	}
}

<<<<<<< HEAD
void SetThornBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, int PieceNo) {
	for (int i = 0; i < THORN_BLOCK_MAX; i++) {
		if (!g_ThornBlock[i].UseFlag) {
			g_ThornBlock[i].Position = pos;
			g_ThornBlock[i].Size = size;
			g_ThornBlock[i].PieceNo = PieceNo;
			g_ThornBlock[i].UseFlag = true;
			break;
		}
	}
}


void SetThornBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, THORN_GRAND_TYPE type, THORN_BLOCK_TYPE btype, int pIndex)
=======
int SetThornBlock(D3DXVECTOR2 Pos, D3DXVECTOR2 s)
>>>>>>> 90b99b71e27210bd6a8deaafb35e92c6ebed0d71
{
	//PUZZLE* pPuzzle = GetPuzzle();

	for (int i = 0; i < THORN_BLOCK_MAX; i++)
	{
		if (!g_ThornBlock[i].UseFlag)
		{
<<<<<<< HEAD
			if (btype != THORN_TYPE_NUM)
			{
				switch (btype)
				{
				case THORN_TYPE_GRAND:
					(pPuzzle + pIndex)->BrokenIndex = SetBroken(pos, D3DXVECTOR2(BROKEN_SIZE_W, BROKEN_SIZE_H));
					switch (type)
					{
					case THORN_GRAND_DOWN:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x, pos.y + PUZZLE_HEIGHT / 2 - THORN_BLOCK_H / 2);
						g_ThornBlock[i].Rotation = 0.0f;
						g_ThornBlock[i].Size = size;
						(pPuzzle + pIndex)->blockIndex[0] = i;
						break;
					case THORN_GRAND_LEFT:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x - PUZZLE_WIDHT / 2 + THORN_BLOCK_W / 2, pos.y);
						g_ThornBlock[i].Rotation = 90.0f;
						g_ThornBlock[i].Size = size;
						(pPuzzle + pIndex)->blockIndex[0] = i;

						break;
					case THORN_GRAND_UP:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x, pos.y - PUZZLE_HEIGHT / 2 + THORN_BLOCK_H / 2);
						g_ThornBlock[i].Rotation = 180.0f;
						g_ThornBlock[i].Size = size;
						(pPuzzle + pIndex)->blockIndex[0] = i;

						break;
					case THORN_GRAND_RIGHT:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x + PUZZLE_WIDHT / 2 - THORN_BLOCK_W / 2, pos.y);
						g_ThornBlock[i].Rotation = 270.0f;
						g_ThornBlock[i].Size = size;
						(pPuzzle + pIndex)->blockIndex[0] = i;

						break;

					default:
						break;
					}

					break;

				case THORN_TYPE_HARFGRAND:
					switch (type)
					{
					case THORN_GRAND_DOWN:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x, pos.y + PUZZLE_HEIGHT / 2 - THORN_BLOCK_H / 2);
						g_ThornBlock[i].Rotation = 0.0f;
						g_ThornBlock[i].Size = size / 2;
						(pPuzzle + pIndex)->blockIndex[0] = i;
						(pPuzzle + pIndex)->RotNum = 0;
						break;
					case THORN_GRAND_LEFT:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x - PUZZLE_WIDHT / 2 + THORN_BLOCK_W / 2, pos.y);
						g_ThornBlock[i].Rotation = 0.0f;
						g_ThornBlock[i].Size = size / 2;
						(pPuzzle + pIndex)->blockIndex[0] = i;
						(pPuzzle + pIndex)->RotNum = 1;

						break;
					case THORN_GRAND_UP:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x, pos.y - PUZZLE_HEIGHT / 2 + THORN_BLOCK_H / 2);
						g_ThornBlock[i].Rotation = 0.0f;
						g_ThornBlock[i].Size = size / 2;
						(pPuzzle + pIndex)->blockIndex[0] = i;
						(pPuzzle + pIndex)->RotNum = 2;

						break;
					case THORN_GRAND_RIGHT:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x + PUZZLE_WIDHT / 2 - THORN_BLOCK_W / 2, pos.y);
						g_ThornBlock[i].Rotation = 0.0f;
						g_ThornBlock[i].Size = size / 2;
						(pPuzzle + pIndex)->blockIndex[0] = i;
						(pPuzzle + pIndex)->RotNum = 3;

						break;

					}

					break;
				case THORN_TYPE_CENTER:
					g_ThornBlock[i].Position = D3DXVECTOR2(pos.x, pos.y);
					g_ThornBlock[i].Rotation = 0.0f;
					g_ThornBlock[i].Size = size / 2;
					(pPuzzle + pIndex)->blockIndex[0] = i;

					break;
				case THORN_TYPE_T:
					switch (type)
					{
					case THORN_GRAND_DOWN:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x, pos.y + PUZZLE_HEIGHT / 2 - THORN_BLOCK_H / 2);
						g_ThornBlock[i].Rotation = 0.0f;
						g_ThornBlock[i].Size = size;
						(pPuzzle + pIndex)->blockIndex[0] = i;

						g_ThornBlock[i + 1].Position = D3DXVECTOR2(pos.x, pos.y);
						g_ThornBlock[i + 1].Rotation = 90.0f;
						g_ThornBlock[i + 1].Size = size;
						g_ThornBlock[i + 1].UseFlag = true;
						(pPuzzle + pIndex)->blockIndex[1] = i + 1;

						g_ThornBlock[i + 2].Position = D3DXVECTOR2(pos.x + PUZZLE_WIDHT / 2 - THORN_BLOCK_W / 2, pos.y);
						g_ThornBlock[i + 2].Rotation = 90.0f;
						g_ThornBlock[i + 2].Size = size;
						g_ThornBlock[i + 2].UseFlag = true;
						(pPuzzle + pIndex)->blockIndex[1] = i + 2;

						(pPuzzle + pIndex)->RotNum = 0;

						break;
					case THORN_GRAND_LEFT:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x - PUZZLE_WIDHT / 2 + THORN_BLOCK_W / 2, pos.y);
						g_ThornBlock[i].Rotation = 90.0f;
						g_ThornBlock[i].Size = size;

						g_ThornBlock[i + 1].Position = D3DXVECTOR2(pos.x, pos.y);
						g_ThornBlock[i + 1].Rotation = 0.0f;
						g_ThornBlock[i + 1].Size = size;
						g_ThornBlock[i + 1].UseFlag = true;
						(pPuzzle + pIndex)->blockIndex[1] = i + 1;


						g_ThornBlock[i + 2].Position = D3DXVECTOR2(pos.x, pos.y + PUZZLE_HEIGHT / 2 - THORN_BLOCK_H / 2);
						g_ThornBlock[i + 2].Rotation = 0.0f;
						g_ThornBlock[i + 2].Size = size;
						g_ThornBlock[i + 2].UseFlag = true;
						(pPuzzle + pIndex)->blockIndex[1] = i + 2;
						(pPuzzle + pIndex)->RotNum = 1;

						break;
					case THORN_GRAND_UP:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x, pos.y - PUZZLE_HEIGHT / 2 + THORN_BLOCK_H / 2);
						g_ThornBlock[i].Rotation = 0.0f;
						g_ThornBlock[i].Size = size;

						g_ThornBlock[i + 1].Position = D3DXVECTOR2(pos.x, pos.y);
						g_ThornBlock[i + 1].Rotation = 90.0f;
						g_ThornBlock[i + 1].Size = size;
						g_ThornBlock[i + 1].UseFlag = true;
						(pPuzzle + pIndex)->blockIndex[1] = i + 1;

						g_ThornBlock[i + 2].Position = D3DXVECTOR2(pos.x - PUZZLE_WIDHT / 2 + THORN_BLOCK_W / 2, pos.y);
						g_ThornBlock[i + 2].Rotation = 90.0f;
						g_ThornBlock[i + 2].Size = size;
						g_ThornBlock[i + 2].UseFlag = true;
						(pPuzzle + pIndex)->blockIndex[1] = i + 2;
						(pPuzzle + pIndex)->RotNum = 2;

						break;
					case THORN_GRAND_RIGHT:
						g_ThornBlock[i].Position = D3DXVECTOR2(pos.x + PUZZLE_WIDHT / 2 - THORN_BLOCK_W / 2, pos.y);
						g_ThornBlock[i].Rotation = 90.0f;
						g_ThornBlock[i].Size = size;


						g_ThornBlock[i + 1].Position = D3DXVECTOR2(pos.x, pos.y);
						g_ThornBlock[i + 1].Rotation = 0.0f;
						g_ThornBlock[i + 1].Size = size;
						g_ThornBlock[i + 1].UseFlag = true;
						(pPuzzle + pIndex)->blockIndex[1] = i + 1;

						g_ThornBlock[i + 2].Position = D3DXVECTOR2(pos.x, pos.y - PUZZLE_HEIGHT / 2 + THORN_BLOCK_H / 2);
						g_ThornBlock[i + 2].Rotation = 00.0f;
						g_ThornBlock[i + 2].Size = size;
						g_ThornBlock[i + 2].UseFlag = true;
						(pPuzzle + pIndex)->blockIndex[1] = i + 2;
						(pPuzzle + pIndex)->RotNum = 3;

						break;

					}

					break;
				case THORN_TYPE_SQUARE:

					g_ThornBlock[i].Position = D3DXVECTOR2(pos.x - PUZZLE_WIDHT / 2 + SQUAER_W / 2, pos.y - PUZZLE_HEIGHT / 2 + SQUAER_H / 2);
					g_ThornBlock[i].Rotation = 0.0f;
					g_ThornBlock[i].Size = D3DXVECTOR2(SQUAER_W, SQUAER_H);
					(pPuzzle + pIndex)->blockIndex[0] = i;

					g_ThornBlock[i + 1].Position = D3DXVECTOR2(pos.x - PUZZLE_WIDHT / 2 + SQUAER_W / 2, pos.y + PUZZLE_HEIGHT / 2 - SQUAER_H / 2);
					g_ThornBlock[i + 1].Rotation = 0.0f;
					g_ThornBlock[i + 1].Size = D3DXVECTOR2(SQUAER_W, SQUAER_H);
					g_ThornBlock[i + 1].UseFlag = true;
					(pPuzzle + pIndex)->blockIndex[1] = i + 1;

					g_ThornBlock[i + 2].Position = D3DXVECTOR2(pos.x + PUZZLE_WIDHT / 2 - SQUAER_W / 2, pos.y + PUZZLE_HEIGHT / 2 - SQUAER_H / 2);
					g_ThornBlock[i + 2].Rotation = 0.0f;
					g_ThornBlock[i + 2].Size = D3DXVECTOR2(SQUAER_W, SQUAER_H);
					g_ThornBlock[i + 2].UseFlag = true;

					(pPuzzle + pIndex)->blockIndex[2] = i + 2;

					g_ThornBlock[i + 3].Position = D3DXVECTOR2(pos.x + PUZZLE_WIDHT / 2 - SQUAER_W / 2, pos.y - PUZZLE_HEIGHT / 2 + SQUAER_H / 2);
					g_ThornBlock[i + 3].Rotation = 0.0f;
					g_ThornBlock[i + 3].Size = D3DXVECTOR2(SQUAER_W, SQUAER_H);
					g_ThornBlock[i + 3].UseFlag = true;

					(pPuzzle + pIndex)->blockIndex[3] = i + 3;

					break;

				}
			}

			g_ThornBlock[i].UseFlag = true;
			break;
=======

			g_ThornBlock[i].Postion = Pos;
			g_ThornBlock[i].Size = s;
			g_ThornBlock[i].UseFlag = true;
			return i;
>>>>>>> 90b99b71e27210bd6a8deaafb35e92c6ebed0d71

		}


	}

}

//=============================================================================
//ゲット関数
//=============================================================================
THORNBLOCK* GetThornBlock()
{
<<<<<<< HEAD
	return &g_ThornBlock[0];
}
=======
	return g_ThornBlock;
}
>>>>>>> 90b99b71e27210bd6a8deaafb35e92c6ebed0d71
