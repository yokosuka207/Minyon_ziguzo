
#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "sprite.h"
#include "MoveBlock.h"
#include "player.h"
#include "collision.h"
#include "block.h"
#include "puzzle.h"
#include "MapChip.h"

static MOVEBLOCK gMoveBlock[MOVE_BLOCK_MAX];

static PLAYER* p_Player;
static BLOCK* cipblock;

static ID3D11ShaderResourceView* g_textureBlock;	//画像一枚で一つの変数が必要
static char* g_textureName_Block = (char*)"data\\texture\\MoveBlock.jpg";	//テクスチャファイルパス
static int	  g_TextureNo = 0;	//プレイヤー用テクスチャの識別子

HRESULT InitMoveBlock()
{
	for (int i = 0; i < MOVE_BLOCK_MAX; i++) 
	{
		g_TextureNo = LoadTexture(g_textureName_Block);

		gMoveBlock[i].pos = D3DXVECTOR2(330.0f + 120, 245.0f - 120);
		gMoveBlock[i].size = D3DXVECTOR2(MOVE_BLOCK_SIZE, MOVE_BLOCK_SIZE);

		gMoveBlock[i].PieceIndex = -1;

		gMoveBlock[i].bUse = true;
	}

	return S_OK;
}

void UninitMoveBlock()
{
	if (g_textureBlock)
	{
		g_textureBlock->Release();
		g_textureBlock = NULL;
	}
}

void UpdateMoveBlock()
{
	p_Player = GetPlayer();

	for (int i = 0; i < MOVE_BLOCK_MAX; i++)
	{
		if (gMoveBlock[i].bUse)
		{
			gMoveBlock[i].oldpos = gMoveBlock[i].pos;

			//プレイヤーが持ってるときの判定
			if (gMoveBlock[i].GetMoveBlock)
			{
				gMoveBlock[i].sp = p_Player->sp;
				gMoveBlock[i].pos.x += gMoveBlock[i].sp.x;
			}

			gMoveBlock[i].pos.y++;

			//ブロックとの当たり判定

			cipblock = GetChipBlock();

			for (int j = 0; j < BLOCK_CHIP_MAX; j++)
			{
				if ((cipblock + j)->UseFlag)
				{
					//if (gMoveBlock[i].pos.x    + gMoveBlock[i].size.x / 2 > (p_Block + j)->Position.x   - (p_Block + j)->Size.x / 2 &&
					//	gMoveBlock[i].pos.x    - gMoveBlock[i].size.x / 2 < (p_Block + j)->Position.x   + (p_Block + j)->Size.x / 2 &&
					//	gMoveBlock[i].pos.y    + gMoveBlock[i].size.y / 2 > (p_Block + j)->Position.y   - (p_Block + j)->Size.y / 2 &&
					//	gMoveBlock[i].oldpos.y + gMoveBlock[i].size.y / 2 <= (p_Block + j)->Position.y  - (p_Block + j)->Size.y / 2)
					//{
					//	gMoveBlock[i].pos.y = gMoveBlock[i].oldpos.y;
					//}
					//if (gMoveBlock[i].pos.x    + gMoveBlock[i].size.x / 2 > (p_Block + j)->Position.x  - (p_Block + j)->Size.x / 2 &&
					//	gMoveBlock[i].oldpos.x + gMoveBlock[i].size.x / 2 <= (p_Block + j)->Position.x - (p_Block + j)->Size.x / 2 &&
					//	gMoveBlock[i].pos.y    + gMoveBlock[i].size.y / 2 > (p_Block + j)->Position.y  - (p_Block + j)->Size.y / 2 &&
					//	gMoveBlock[i].pos.y    - gMoveBlock[i].size.y / 2 < (p_Block + j)->Position.y  + (p_Block + j)->Size.y / 2)
					//{
					//	gMoveBlock[i].pos.x = gMoveBlock[i].oldpos.x;
					//}
					//if (gMoveBlock[i].pos.x    - gMoveBlock[i].size.x / 2 < (p_Block + j)->Position.x  + (p_Block + j)->Size.x / 2 &&
					//	gMoveBlock[i].oldpos.x - gMoveBlock[i].size.x / 2 >= (p_Block + j)->Position.x + (p_Block + j)->Size.x / 2 &&
					//	gMoveBlock[i].pos.y    + gMoveBlock[i].size.y / 2 > (p_Block + j)->Position.y  - (p_Block + j)->Size.y / 2 &&
					//	gMoveBlock[i].pos.y    - gMoveBlock[i].size.y / 2 < (p_Block + j)->Position.y  + (p_Block + j)->Size.y / 2)
					//{
					//	gMoveBlock[i].pos.x = gMoveBlock[i].oldpos.x;
					//}
					////プレイヤー下・トゲブロック上,
					//if (gMoveBlock[i].pos.x    + gMoveBlock[i].size.x / 2 > (p_Block + j)->Position.x   - (p_Block + j)->Size.x / 2 &&
					//	gMoveBlock[i].pos.x    - gMoveBlock[i].size.x / 2 < (p_Block + j)->Position.x   + (p_Block + j)->Size.x / 2 &&
					//	gMoveBlock[i].pos.y    - gMoveBlock[i].size.y / 2 < (p_Block + j)->Position.y   + (p_Block + j)->Size.y / 2 &&
					//	gMoveBlock[i].oldpos.y - gMoveBlock[i].size.y / 2 >= (p_Block + j)->Position.y  + (p_Block + j)->Size.y / 2)
					//{
					//	gMoveBlock[i].pos.y = gMoveBlock[i].oldpos.y;
					//}

					//プレイヤー左・ブロック右
					if (gMoveBlock[i].pos.x	   + gMoveBlock[i].size.x / 2 > (cipblock + j)->Position.x  - (cipblock + j)->Size.x / 2 &&
						gMoveBlock[i].oldpos.x + gMoveBlock[i].size.x / 2 <= (cipblock + j)->Position.x - (cipblock + j)->Size.x / 2 &&
						gMoveBlock[i].pos.y	   + gMoveBlock[i].size.y / 2 > (cipblock + j)->Position.y  - (cipblock + j)->Size.y / 2 &&
						gMoveBlock[i].pos.y	   - gMoveBlock[i].size.y / 2 < (cipblock + j)->Position.y  + (cipblock + j)->Size.y / 2)
					{
						gMoveBlock[i].pos.x = (cipblock + j)->Position.x - (cipblock + j)->Size.x / 2 - gMoveBlock[i].size.x / 2;
					}
					//プレイヤー右・ブロック左
					if (gMoveBlock[i].pos.x	   - gMoveBlock[i].size.x / 2 < (cipblock + j)->Position.x + (cipblock + j)->Size.x / 2 &&
						gMoveBlock[i].oldpos.x - gMoveBlock[i].size.x / 2 >= (cipblock + j)->Position.x + (cipblock + j)->Size.x / 2 &&
						gMoveBlock[i].pos.y    + gMoveBlock[i].size.y / 3 > (cipblock + j)->Position.y - (cipblock + j)->Size.y / 3 &&
						gMoveBlock[i].pos.y    - gMoveBlock[i].size.y / 3 < (cipblock + j)->Position.y + (cipblock + j)->Size.y / 3)
					{
						gMoveBlock[i].pos.x = (cipblock + j)->Position.x + (cipblock + j)->Size.x / 2 + gMoveBlock[i].size.x / 2;
					}
					//プレイヤー上・ブロック下,着地する
					if (gMoveBlock[i].pos.x + gMoveBlock[i].size.x / 2 > (cipblock + j)->Position.x - (cipblock + j)->Size.x / 2 &&
						gMoveBlock[i].pos.x - gMoveBlock[i].size.x / 2 < (cipblock + j)->Position.x + (cipblock + j)->Size.x / 2 &&
						gMoveBlock[i].pos.y + gMoveBlock[i].size.y / 2 > (cipblock + j)->Position.y - (cipblock + j)->Size.y / 2 &&
						gMoveBlock[i].oldpos.y + gMoveBlock[i].size.y / 2 <= (cipblock + j)->Position.y - (cipblock + j)->Size.y / 2)
					{
						gMoveBlock[i].pos.y = (cipblock + j)->Position.y - (cipblock + j)->Size.y / 2 - gMoveBlock[i].size.y / 2;
					}
					//プレイヤー下・ブロック上,落下する
					if (gMoveBlock[i].pos.x + gMoveBlock[i].size.x / 2 > (cipblock + j)->Position.x - (cipblock + j)->Size.x / 2 &&
						gMoveBlock[i].pos.x - gMoveBlock[i].size.x / 2 < (cipblock + j)->Position.x + (cipblock + j)->Size.x / 2 &&
						gMoveBlock[i].pos.y - gMoveBlock[i].size.y / 2 < (cipblock + j)->Position.y + (cipblock + j)->Size.y / 2 &&
						gMoveBlock[i].oldpos.y - gMoveBlock[i].size.y / 2 >= (cipblock + j)->Position.y + (cipblock + j)->Size.y / 2)
					{
						gMoveBlock[i].pos.y = (cipblock + j)->Position.y + (cipblock + j)->Size.y / 2 + gMoveBlock[i].size.y / 2;
					}

				}
			}

		}

	}
	
}

void DrawMoveBlock()
{
	for (int i = 0; i < MOVE_BLOCK_MAX; i++) {
		if (gMoveBlock[i].bUse)
		{
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TextureNo));

			SpriteDrawColorRotation(gMoveBlock[i].pos.x, gMoveBlock[i].pos.y,
				gMoveBlock[i].size.x, gMoveBlock[i].size.y, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
				0, 1.0f, 1.0f, 1);
		}
	}
}

MOVEBLOCK* GetMoveBlock()
{
	return &gMoveBlock[0];
}

void SetMoveBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, int PieceNo) {
	for (int i = 0; i < MOVE_BLOCK_MAX; i++) {
		if (!gMoveBlock[i].bUse) {
			gMoveBlock[i].pos = pos;
			gMoveBlock[i].size = size;
			gMoveBlock[i].PieceIndex = PieceNo;
			gMoveBlock[i].bUse = true;
			break;
		}
	}
}

void DeleteMoveBlock(int PieceNo) {
	//配列にしないとマップ上に存在するジャンプ台全部消えることになる
	//今消したいのは PieceNo番目 のピースに存在するジャンプ台のみ
	for (int i = 0; i < MOVE_BLOCK_MAX; i++) {
		if (gMoveBlock[i].bUse) {
			if (gMoveBlock[i].PieceIndex == PieceNo)
			{
				gMoveBlock[i].bUse = false;

			}
		}
	}
}