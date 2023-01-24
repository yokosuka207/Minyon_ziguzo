
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
#include "sound.h"

static MOVEBLOCK gMoveBlock[MOVE_BLOCK_MAX];

static PLAYER* p_Player;
static BLOCK* cipblock;

static ID3D11ShaderResourceView* g_textureBlock;	//画像一枚で一つの変数が必要
static char* g_textureName_Block = (char*)"data\\texture\\Moveblock.png";	//テクスチャファイルパス
static int	  g_TextureNo = 0;	//プレイヤー用テクスチャの識別子

//サウンド
static int g_MoveBlockMoveSoundNo = 0;
static char g_MoveBlockMoveSoundName[] = "data\\SoundData\\SE\\引きずる音(要編集).wav";
static int g_MoveBolckLandingSoundNo = 0;
static char g_g_MoveBolckLandingSoundName[] = "data\\SoundData\\SE\\物の落下音(無料効果音で遊ぼう！).wav";



HRESULT InitMoveBlock()
{
	for (int i = 0; i < MOVE_BLOCK_MAX; i++) 
	{
		g_TextureNo = LoadTexture(g_textureName_Block);

		gMoveBlock[i].pos = D3DXVECTOR2(330.0f + 120, 245.0f - 120);
		gMoveBlock[i].size = D3DXVECTOR2(MOVE_BLOCK_SIZE, MOVE_BLOCK_SIZE);

		gMoveBlock[i].PieceIndex = -1;

		gMoveBlock[i].bUse = false;

		gMoveBlock[i].MoveBlockNotMove = false;
		gMoveBlock[i].MoveFlag = false;

		g_MoveBlockMoveSoundNo = LoadSound(g_MoveBlockMoveSoundName);
		g_MoveBolckLandingSoundNo = LoadSound(g_g_MoveBolckLandingSoundName);
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
	StopSound(g_MoveBlockMoveSoundNo);
	StopSound(g_MoveBolckLandingSoundNo);
}

void UpdateMoveBlock()
{
	p_Player = GetPlayer();

	for (int i = 0; i < MOVE_BLOCK_MAX; i++)
	{
		if (gMoveBlock[i].bUse)
		{
			gMoveBlock[i].oldoldpos = gMoveBlock[i].oldpos;
			gMoveBlock[i].oldpos = gMoveBlock[i].pos;


			////動くブロック右・プレイヤー左
			//if (p_Player->Position.x + p_Player->size.x / 2 > gMoveBlock[i].pos.x - gMoveBlock[i].size.x / 2 &&
			//	p_Player->oldpos.x + p_Player->size.x / 2 <= gMoveBlock[i].pos.x - gMoveBlock[i].size.x / 2 &&
			//	p_Player->Position.y + p_Player->size.y / 2 > gMoveBlock[i].pos.y - gMoveBlock[i].size.y / 2 &&
			//	p_Player->Position.y - p_Player->size.y / 2 < gMoveBlock[i].pos.y + gMoveBlock[i].size.y / 2)
			//{
			//	p_Player->Position.x = gMoveBlock[i].pos.x - gMoveBlock[i].size.x / 2 - p_Player->size.x / 2;
			//}
			////プレイヤー右・動くブロック左
			//if (p_Player->Position.x - p_Player->size.x / 2 < gMoveBlock[i].pos.x + gMoveBlock[i].size.x / 2 &&
			//	p_Player->oldpos.x - p_Player->size.x / 2 >= gMoveBlock[i].pos.x + gMoveBlock[i].size.x / 2 &&
			//	p_Player->Position.y + p_Player->size.y / 2 > gMoveBlock[i].pos.y - gMoveBlock[i].size.y / 2 &&
			//	p_Player->Position.y - p_Player->size.y / 2 < gMoveBlock[i].pos.y + gMoveBlock[i].size.y / 2)
			//{
			//	p_Player->Position.x = gMoveBlock[i].pos.x + gMoveBlock[i].size.x / 2 + p_Player->size.x / 2;
			//}


			//プレイヤーが持ってるときの判定
			if (gMoveBlock[i].GetMoveBlock)
			{
				gMoveBlock[i].sp = p_Player->sp;
				gMoveBlock[i].pos.x += gMoveBlock[i].sp.x;

				//引きずる音
				if (gMoveBlock[i].oldpos.x != gMoveBlock[i].pos.x && gMoveBlock[i].MoveBlockNotMove == true)//動かした瞬間
				{
					//SetVolume(g_MoveBlockMoveSoundNo, 0.5f);
					PlaySound(g_MoveBlockMoveSoundNo, -1);
					gMoveBlock[i].MoveBlockNotMove = false;
				}
			}
			if (gMoveBlock[i].oldpos.x == gMoveBlock[i].pos.x && gMoveBlock[i].MoveBlockNotMove == false)//動かしてない時
			{
				gMoveBlock[i].MoveBlockNotMove = true;
				StopSound(g_MoveBlockMoveSoundNo);
			}

				
				gMoveBlock[i].pos.y--;

			

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

					//動くブロック左・ブロック右
					if (gMoveBlock[i].pos.x	   + gMoveBlock[i].size.x / 2 > (cipblock + j)->Position.x  - (cipblock + j)->Size.x / 3 &&
						gMoveBlock[i].oldpos.x + gMoveBlock[i].size.x / 2 <= (cipblock + j)->Position.x - (cipblock + j)->Size.x / 3 &&
						gMoveBlock[i].pos.y	   + gMoveBlock[i].size.y / 2 > (cipblock + j)->Position.y  - (cipblock + j)->Size.y / 3 &&
						gMoveBlock[i].pos.y	   - gMoveBlock[i].size.y / 2 < (cipblock + j)->Position.y  + (cipblock + j)->Size.y / 3)
					{
						gMoveBlock[i].pos.x = (cipblock + j)->Position.x - (cipblock + j)->Size.x / 2 - gMoveBlock[i].size.x / 2;

					}
					//動くブロック右・ブロック左
					if (gMoveBlock[i].pos.x	   - gMoveBlock[i].size.x / 2 < (cipblock + j)->Position.x + (cipblock + j)->Size.x / 3 &&
						gMoveBlock[i].oldpos.x - gMoveBlock[i].size.x / 2 >= (cipblock + j)->Position.x + (cipblock + j)->Size.x / 3 &&
						gMoveBlock[i].pos.y    + gMoveBlock[i].size.y / 3 > (cipblock + j)->Position.y - (cipblock + j)->Size.y / 3 &&
						gMoveBlock[i].pos.y    - gMoveBlock[i].size.y / 3 < (cipblock + j)->Position.y + (cipblock + j)->Size.y / 3)
					{
						gMoveBlock[i].pos.x = (cipblock + j)->Position.x + (cipblock + j)->Size.x / 2 + gMoveBlock[i].size.x / 2;
					}
					//動くブロック上・ブロック下,着地する
					if (gMoveBlock[i].pos.x + gMoveBlock[i].size.x / 2 > (cipblock + j)->Position.x - (cipblock + j)->Size.x / 2 &&
						gMoveBlock[i].pos.x - gMoveBlock[i].size.x / 2 < (cipblock + j)->Position.x + (cipblock + j)->Size.x / 2 &&
						gMoveBlock[i].pos.y + gMoveBlock[i].size.y / 2 > (cipblock + j)->Position.y - (cipblock + j)->Size.y / 2 &&
						gMoveBlock[i].oldpos.y + gMoveBlock[i].size.y / 2 <= (cipblock + j)->Position.y - (cipblock + j)->Size.y / 2)
					{
						gMoveBlock[i].pos.y = (cipblock + j)->Position.y - (cipblock + j)->Size.y / 2 - gMoveBlock[i].size.y / 2;
						
						//着地した瞬間だけ音が鳴る
						if (gMoveBlock[i].oldoldpos.y != gMoveBlock[i].pos.y)
						{
							//SetVolume(g_MoveBolckLandingSoundNo, 0.5f);
							//PlaySound(g_MoveBolckLandingSoundNo, 0);
						}
					}
					//動くブロック下・ブロック上,落下する
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

			SpriteDrawColorRotation(gMoveBlock[i].pos.x, gMoveBlock[i].pos.y,-0.1f,
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
			gMoveBlock[i].pos.y += 1.0f ;
			gMoveBlock[i].size = D3DXVECTOR2(size.x - 3.0f, size.y - 3.0f);
			gMoveBlock[i].PieceIndex = PieceNo;
			gMoveBlock[i].bUse = true;
			break;
		}
	}
}

void DeleteMoveBlock(int PieceNo) {
	for (int i = 0; i < MOVE_BLOCK_MAX; i++) {
		if (gMoveBlock[i].bUse) {
			if (gMoveBlock[i].PieceIndex == PieceNo)
			{
				gMoveBlock[i].bUse = false;

			}
		}
	}
}